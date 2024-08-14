/* detransform.c
*
* by Ayah Harper and Nana Adjekum, 10/21/23
*
* This file contains the implementation of the growToTransform function 
* defined in the detransform.h interface. 
*/

#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <assert.h>
#include <mem.h>
#include <uarray2b.h>
#include <uarray2.h>
#include <a2methods.h>
#include <a2blocked.h>
#include <math.h>
#include "transform.h"
#include "compress40.h"
#include "convertandwrite.h"
#include "arith40.h"
#include "structs.h"

/*********************** APPLY & HELPER FUNCTIONS **************************/
void init_FourPixelFloats(int col, int row, UArray2_T FourPixelFloats, 
                        void *elem, void *cl);
void restore4pixels(int col, int row, UArray2_T CodeWords, void *elem, 
                    void *cl);
void rebuildCV(int col, int row, UArray2_T FourPixelGroups, 
              void *elem, void *cl);

/****** requantizeBCD (helper) ****
*
*       quantises the float vals for b,c,d
*       i.e. sets the floor and ceiling for what
*       the vals can be
* parameters: the float val b,c,d
* returns: the float quantised value
* expects: N/A
* notes: N/A
* */
static float requantizeBCD(float val)
{
        if (val < -0.3) {
                return -0.3;
        } 
        if (val > 0.3) {
                return 0.3;
        }
        
        return val;
}

/************************* FUNCTION DEFINITIONS ****************************/

/********** growToTransform ********
 *
 * converts a shrunken array of signed/unsigned Pb/Pr/abcd CodeWords back to
 * a 2D array of floating point y/pb/pr pixels
 *
 * Parameters:
 *      UArray2_T CodeWords:    2D array of CodeWord structs
 *
 * Return: 2D array of y/pb/pr float pixels
 *
 * Expects:
 *      each pixel in CodeWords stroes a CodeWords struct
 *      CodeWords is not NULL
 *      dimensions of CodeWords array are 1/4 dimensions of original array
 * Notes:
 *      may CRE if CodeWords is NULL.
 ************************/
UArray2b_T growToTransform(UArray2_T CodeWords)
{
        assert(CodeWords);
        int width = UArray2_width(CodeWords);
        int height = UArray2_height(CodeWords);

        /* rebuild and initialize an array for the four pixel groups */
        UArray2_T FourPixelGroups = UArray2_new(width, height, 
                                    sizeof(FourPixelFloat));
        assert(FourPixelGroups);
        UArray2_map_row_major(FourPixelGroups, init_FourPixelFloats, &width);
        
        /* map through the codewords and restore the four pixel groups */
        UArray2_map_row_major(CodeWords, restore4pixels, &FourPixelGroups);

        UArray2b_T CVmodel = UArray2b_new((width * 2), (height * 2), 
                             sizeof(CV_float), 2);
        assert(CVmodel);

        /* restore the original y/pb/pr values of each pixel */
        UArray2_map_row_major(FourPixelGroups, rebuildCV, &CVmodel);

        UArray2_free(&FourPixelGroups);

        return CVmodel;

}

/********** init_FourPixelFloats (APPLY) ********
 *
 * initializes an array of FourPixelFloat structs 
 *
 * Parameters:
 *      int col:                        col # of current element
 *      int row:                        row # of current element 
 *      UArray2_T FourPixelFloats:      array of FourPixelFloat structs
 *      void *elem:                     pointer to current element, unused
 *      void *cl:                       closure, unused
 *
 * Return: none, effectively initializes an array of FourPixelFloat structs
 *
 * Expects:
 *      FourPixelFloats is not NULL
 * Notes:
 *      initializes Pb/Pr/a/b/c/d/y_index to 0.0.
 ************************/
void init_FourPixelFloats(int col, int row, UArray2_T FourPixelFloats, 
                          void *elem, void *cl)
{
        (void)col;
        (void)row;
        (void)cl;
        (void)FourPixelFloats;

        FourPixelFloat initial = {0.0, 0.0, {0.0, 0.0, 0.0, 0.0}, 0};

       *(FourPixelFloat *)elem = initial;

}

/********** restore4pixels (APPLY) ********
 *
 * maps through an array of CodeWord structs and restores the four float 
 * values in a FourPixelFloat struct (Pb, Pr, a, b, c, d) for each pixel 
 *
 * Parameters:
 *      int col:                        col # of current element
 *      int row:                        row # of current element 
 *      UArray2_T CodeWords:            array of CodeWord structs
 *      void *elem:                     pointer to current element
 *      void *cl:                       closure

 * Return: none, returns a populated array of FourPixelFloat structs via the
 * closure
 *
 * Expects:
 *      CodeWords is not NULL
 *      cl points to a 2D blocked array of FourPixelFloat structs
 *      closure array and mapped array have equal dimensions
 *      every element in CodeWords contains a CodeWord struct
 *      
 * Notes:
 *      quantizes b, c, and d so they are within the range -0.3 < x < 0.3
 *      forces any reproduced y-values that are within 0.01 of 0.0 down to 0.0
 ************************/
void restore4pixels(int col, int row, UArray2_T CodeWords, 
                    void *elem, void *cl) 
{
        (void)CodeWords;

        /* grab a pixel from the array of four-pixel groups */
        UArray2_T *FourPixelGroups = cl;
        FourPixelFloat *destination = 
        (FourPixelFloat *)UArray2_at(*FourPixelGroups, col, row);

        /* convert a, b, c, & d to floating point from signed/unsigned reps */
        CodeWord current = *(CodeWord *)elem;
        float a = current.a / 511.0;
        float b = current.b / 50.0;
        float c = current.c / 50.0;
        float d = current.d / 50.0;

        /* quantize a, b, c, and d */
        if (a > 1.0) { a = 1.0; }
        if (a < 0.0 ) { a = 0.0; }
        b = requantizeBCD(b);
        c = requantizeBCD(c);
        d = requantizeBCD(d);

        /* get the floating pt reps of Pb and Pr */
        destination->Pb = Arith40_chroma_of_index(current.Pb);
        destination->Pr = Arith40_chroma_of_index(current.Pr);
       
        /* get the floating point reps of each y value and clamp/quantize */
        destination->yVals[0] = a - b - c + d;
        if (fabs(destination->yVals[0]) < 0.01) { destination->yVals[0] = 0.0;}
        destination->yVals[1] = a - b + c - d;
        if (fabs(destination->yVals[1]) < 0.01) {destination->yVals[1] = 0.0;}
        destination->yVals[2] = a + b - c - d;
        if (fabs(destination->yVals[2]) < 0.01) {destination->yVals[2] = 0.0;}
        destination->yVals[3] = a + b + c + d;
        if (fabs(destination->yVals[3]) < 0.01) {destination->yVals[3] = 0.0;}

}

/********** rebuildCV (APPLY) ********
 *
 * apply function for restoring the expanded array of CV float structs from a 
 * compressed array of FourPixelFloat structs
 *
 * Parameters:
 *      FILE *file:     input file containing ppm image
 *
 * Return: none, returns a populated array of CV_float structs via closure
 *
 * Expects
 *      FourPixelGroups is nt NULL
 *      elem points to a FourPixelFloat struct
 *      cl points to an array of CV_float structs
 *      every col and row is within the bounds of the CVarray
 * Notes:
 *      
 ************************/
void rebuildCV(int col, int row, UArray2_T FourPixelGroups, 
               void *elem, void *cl)
{
        (void)FourPixelGroups;

        /* array of CV floats to copy elements into */
        UArray2b_T *CVarray = cl;

        /* grab the current four-pixel group */
        FourPixelFloat current = *(FourPixelFloat *)elem;

        /* grab each of the four pixels in the CV float array */
        int blksize = UArray2b_blocksize(*CVarray);
        CV_float *pixel1 = (CV_float *)UArray2b_at(*CVarray, col * blksize, 
                                                row * blksize);
        CV_float *pixel2 = (CV_float *)UArray2b_at(*CVarray, 
                                        (col * blksize) + 1, row * blksize);
        CV_float *pixel3 = (CV_float *)UArray2b_at(*CVarray, col * blksize,
                                                (row * blksize) + 1);
        CV_float *pixel4 = (CV_float *)UArray2b_at(*CVarray, 
                                 (col * blksize) + 1, (row * blksize) + 1);

        pixel1->y = current.yVals[0];
        pixel2->y = current.yVals[2];
        pixel3->y = current.yVals[1];
        pixel4->y = current.yVals[3];

        float pb = current.Pb;
        pixel1->pb = pb;
        pixel2->pb = pb;
        pixel3->pb = pb;
        pixel4->pb = pb;

        float pr = current.Pr;
        pixel1->pr = pr;
        pixel2->pr = pr;
        pixel3->pr = pr;
        pixel4->pr = pr;
       
}