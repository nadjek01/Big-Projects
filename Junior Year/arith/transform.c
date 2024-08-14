/* transform.c
*
* by Ayah Harper and Nana Adjekum, 10/21/23
*
* This file contains the implementation of the shrinkToTransform function 
* defined in the transform.h interface.
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
#include "transform.h"
#include "compress40.h"
#include "convertandwrite.h"
#include "detransform.h"
#include "arith40.h"
#include "structs.h"
#include <math.h>

/************************* APPLY & HELPER FUNCTIONS *****************/
void initialize(int col, int row, UArray2_T FourPixelGroups, 
                void *elem, void *cl);
void group4pixels(int col, int row, UArray2b_T CVfloats, 
                void *elem, void *cl);
void buildCodeWords(int col, int row, UArray2_T smallplain, 
                void *elem, void *cl);

/****** quantizeBCD (helper) ****
*
*       quantises the float vals for b, c, d
*       i.e. sets the floor and ceiling for what
*       the vals can be
* parameters: the float val (b,c,d)
* returns: the float quantised value
* expects: N/A
* notes: N/A
* */
static float quantizeBCD(float val)
{
        if (val < -0.3) {
                return -0.3;
        } 
        if (val > 0.3) {
                return 0.3;
        }
        
        return val;
}

/********** shrinkToTransform ********
 *
 * converts a 2D array of floating point y/pb/pr pixels to a shrunken
 * array of signed/unsigned Pb/Pr/abcd CodeWords.
 *
 * Parameters:
 *      UArray2b_T CVfloats:     2D of CV_float structs
 *
 * Return: compressed 2D array of CodeWord structs
 *
 * Expects:
 *      each pixel in CVfloats is a CV_float struct
 *      width and height to be at least 0
 * Notes:
 *      may CRE if CVfloats is NULL.
 ************************/
UArray2_T shrinkToTransform(UArray2b_T CVfloats)
{
        assert(CVfloats);
        int width = UArray2b_width(CVfloats)/2;
        int height = UArray2b_height(CVfloats)/2;

        /* build and initialize an array for the four-pixel groups */
        UArray2_T FourPixelGroups = UArray2_new(width, height, 
        sizeof(FourPixelFloat));
        assert(FourPixelGroups);
        UArray2_map_row_major(FourPixelGroups, initialize, &width);
        
        /* map through CV floats array, grouping four pixels at a time */
        UArray2b_map(CVfloats, group4pixels, &FourPixelGroups);

        // /* build an array for the codewords */
        UArray2_T CodeWords = UArray2_new(width, height, sizeof(CodeWord));
        assert(CodeWords);

        // /* map through the grouped pixels, converting each to a CodeWord */
        UArray2_map_row_major(FourPixelGroups, buildCodeWords, &CodeWords);

        UArray2_free(&FourPixelGroups);

        return CodeWords;
}

/********** initialize ********
 *
 * reads a PPM image file into a Pnm_ppm object (using blocked methods) and    
 * returns it
 *
 * Parameters:
 *      FILE *file:     input file containing ppm image
 *
 * Return: pixmap object if created successfully
 *
 * Expects
 *      file contains a valid ppm image
 * Notes:
 *      may CRE if Pnm_ppmread fails, or if pixmap is NULL.
 ************************/
void initialize(int col, int row, UArray2_T FourPixelGroups, 
void *elem, void *cl)
{
        (void)col;
        (void)row;
        (void)cl;
        (void)FourPixelGroups;

        FourPixelFloat initial = {0.0, 0.0, {0.0, 0.0, 0.0, 0.0}, 0};

       *(FourPixelFloat *)elem = initial;

}

/********** group4pixels ********
 *
 * reads a PPM image file into a Pnm_ppm object (using blocked methods) and    
 * returns it
 *
 * Parameters:
 *      FILE *file:     input file containing ppm image
 *
 * Return: pixmap object if created successfully
 *
 * Expects
 *      file contains a valid ppm image
 * Notes:
 *      may CRE if Pnm_ppmread fails, or if pixmap is NULL.
 ************************/
void group4pixels(int col, int row, UArray2b_T CVfloats, void *elem, void *cl)
{
        /* compute which "block" of the grouped array this pixel should go in*/
        int new_col = col/UArray2b_blocksize(CVfloats);
        int new_row = row/UArray2b_blocksize(CVfloats);

        /* get the destination group */
        UArray2_T *FourPixelGroups = cl;
        FourPixelFloat *destination = 
        (FourPixelFloat *)UArray2_at(*FourPixelGroups, new_col, new_row);

        /* add the current pixel's data to this four pixel block */
        CV_float current = *(CV_float *)elem;
        destination->Pb += current.pb;
        destination->Pr += current.pr;
        destination->yVals[destination->y_index] = current.y;
        destination->y_index += 1;

        if (destination->y_index == 4) {
                destination->Pb = destination->Pb / 4.0;
                destination->Pr = destination->Pr / 4.0;
        }

}

/********** buildCodeWords (APPLY) ********
 *
 * maps through array of four-pixel groups ()
 *
 * Parameters:
 *      FILE *file:     input file containing ppm image
 *
 * Return: pixmap object if created successfully
 *
 * Expects
 *      file contains a valid ppm image
 * Notes:
 *      may CRE if Pnm_ppmread fails, or if pixmap is NULL.
 ************************/
void buildCodeWords(int col, int row, UArray2_T FourPixelGroups, 
void *elem, void *cl)
{
        (void)FourPixelGroups;

        /* grab a pixel from the array of CodeWord structs*/
        UArray2_T *CodeWords = cl;
        CodeWord *destination = (CodeWord *)UArray2_at(*CodeWords, col, row);

        FourPixelFloat current = *(FourPixelFloat *)elem;

        /* grab each y value and use DCT to compute a, b, c, d */
        float y1 = current.yVals[0];
        float y2 = current.yVals[1];
        float y3 = current.yVals[2];
        float y4 = current.yVals[3];

        float a = (y4 + y3 + y2 + y1)/4.0;
        float b = (y4 + y3 - y2 - y1)/4.0;
        float c = (y4 - y3 + y2 - y1)/4.0;
        float d = (y4 - y3 - y2 + y1)/4.0;

        /* quantize a, b, c, and d */
        if (a > 1.0) { a = 1.0; }
        if (a < 0.0 ) { a = 0.0; }
        b = quantizeBCD(b);
        c = quantizeBCD(c);
        d = quantizeBCD(d);

        /* convert avg Pb and Pr to signed, 4-bit quantized numbers */
        destination->Pb = Arith40_index_of_chroma(current.Pb);
        destination->Pr = Arith40_index_of_chroma(current.Pr);

        /* convert a -> unsigned 9-bit, and b, c, d -> signed 5 bit*/
        destination->a = (unsigned)round(a * 511);
        destination->b = (signed)round(b * 50);
        destination->c = (signed)round(c * 50);
        destination->d = (signed)round(d * 50);

}

