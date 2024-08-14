/* readandconvert.c
*
* by Ayah Harper and Nana Adjekum, 10/19/23
*
* This file contains the implementation of the readandconvert.h interface. 
* Together, the functions in this file convert an input pixmap from unsigned,
* r/g/b representation to floating point, y/pb/pr representation.
*/

#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <a2methods.h>
#include <a2blocked.h>
#include <uarray2b.h>
#include "readandconvert.h"
#include "assert.h"
#include "compress40.h"
#include "structs.h"

/************************* APPLY & HELPER FUNCTIONS ************************/
void unsigned_to_float(int col, int row, UArray2b_T array2D, 
                        void *elem, void *cl);
void rgbConvertCV(int col, int row, UArray2b_T RGBarray,
                        void *elem, void *cl);
Pnm_ppm readPPM(FILE *file);

/****** quantizeChroma (helper) ****
*
*       quantises the float vals for pb, pr
*       i.e. sets the floor and ceiling for what
*       the vals can be
* parameters: the float val pb, pr
* returns: the float quantised value
* expects: N/A
* notes: N/A
* */
static float quantizeChroma(float val)
{
        if (val < -0.5) {
                return -0.5;
        }
        if (val > 0.5) {
                return 0.5;
        }

        return val;    
}

/******************** FUNCTION DEFINITIONS ****************/

/********** readandConvert ********
 *
 * converts the pixmap->pixels array from unsigned R/G/B representation to
 * floating point R/G/B representation
 *
 * Parameters:
 *      Pnm_ppm pixmap:    pixmap to be converted
 *
 * Return: 2D blocked array which is the floating point representation of      
 *         the pixmap->pixels array
 *
 * Expects:
 *      argument pixmap contains a valid 2D array with Pnm_rgb structs at each 
 *      pixel
 *      argument pixmap is not NULL
 * Notes:
 *      the float version of pixmap->pixels has "trimmed" dimensions so width 
 *      and height are divisible by 2.
 ************************/
UArray2b_T readandConvert(FILE *file)
{
        Pnm_ppm pixmap = readPPM(file);

        int width = pixmap->width;
        int height = pixmap->height;

        /* trim dimensions if necessary */
        if (pixmap->width % 2 != 0 && pixmap->width != 0) {
                width = pixmap->width - 1;
        }
        if (pixmap->height % 2 != 0 && pixmap->height != 0) {
                height = pixmap->height - 1;
        }

        /* 2D array for the floating point R/G/B pixels */
        UArray2b_T floatmodel = UArray2b_new(width, height, 
                                sizeof(RGB_float), 2);

        assert(floatmodel);
        
        /* unsigned int r/g/b -> floating point r/g/b */
        UArray2b_map(floatmodel, unsigned_to_float, &pixmap);

        /* 2D array for floating point Y/PB/PR pixels */
        UArray2b_T CVmodel = UArray2b_new(width, height, sizeof(CV_float), 2);

        assert(CVmodel);

        /* floating point r/g/b -> floating point y/pb/pr */
        UArray2b_map(floatmodel, rgbConvertCV, &CVmodel);

        UArray2b_free(&floatmodel);
        Pnm_ppmfree(&pixmap);
        
        return CVmodel;

}

/********** readPPM ********
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
Pnm_ppm readPPM(FILE *file)
{
        Pnm_ppm pixmap = Pnm_ppmread(file, uarray2_methods_blocked);
        assert(pixmap);
        return pixmap;
}

/********** unsigned_to_float (APPLY) ********
 *
 * apply function which converts unsigned r/g/b pixels to floating pt r/g/b
 * pixels in a new array
 *
 * Parameters:
 *      int col:                        column # of current element
 *      int row:                        row # of current element
 *      UArray2b_T RGBfloats:           2D array being mapped through
 *      void *elem:                     ptr to current element
 *      void *cl:                       closure (passed in by caller)
 *
 * Return: none, but returns the closure by reference
 *
 * Expects:
 *      RGBfloats is not NULL
 *      elem points to an RGB_float struct
 *      cl points to a pixmap containing Pnm_rgb structs
 *      every col and row is within the bounds of the cl array
 * Notes:
 *      may CRE if array2D is NULL
 *      may CRE if col or row is out of bounds of the array pointed to by cl
 ************************/
void unsigned_to_float(int col, int row, UArray2b_T RGBfloats, 
                        void *elem, void *cl)
{      
        (void)RGBfloats;
        assert(cl);

        /* copy a pixel from the provided pixmap */
        Pnm_ppm *pixmap = cl; 
        Pnm_rgb original = (Pnm_rgb)(*pixmap)->methods->at((*pixmap)->pixels,
                        col, row);

        /* scale each pixel by the denominator */
        float denom = (*pixmap)->denominator;
        float red = original->red / denom;
        float green = original->green / denom;
        float blue = original->blue / denom;

        /* copy the pixel to the RGBfloats array */
        RGB_float current = {red, green, blue};
        *(RGB_float *)elem = current;

}

/********** rgbConvertCV (APPLY) ********
 *
 * apply function which converts pixels from RGB floating pt represenation to
 * y/pb/pr floating pt representation
 *
 * Parameters:
 *      int col:                        column # of current element
 *      int row:                        row # of current element
 *      UArray2b_T RGBarray:            2D array being mapped through
 *      void *elem:                     ptr to current element
 *      void *cl:                       closure (passed in by caller)
 *
 * Return: none
 *
 * Expects:
 *      RGBarray is not NULL;
 *      cl points to a 2D blocked array of CV_float structs
 *      elem points to an RGB_float struct
 *      
 * Notes:
 *      may CRE if Pnm_ppmread fails, or if pixmap is NULL.
 ************************/
void rgbConvertCV(int col, int row, UArray2b_T RGBarray, void *elem, void *cl)
{
        
        (void)RGBarray;

        /* copy a pixel from the array of CV floats */
        UArray2b_T *CVarray = cl;
        CV_float *current = (CV_float *)UArray2b_at((*CVarray), col, row);

        /* grab RGB float values from RGB float pixel */
        RGB_float original = *(RGB_float *)elem;
        float r = original.red;
        float g = original.green;
        float b = original.blue;

        if (r < 0) { r = 0; }
        if (g < 0) { g = 0; }
        if (b < 0) { b = 0; }
        
        /* compute the new pixel's y/pb/pr values */
        float y = 0.299 * r + 0.587 * g + 0.114 * b;
        float pb = -0.168736 * r - 0.331264 * g + 0.5 * b;
        float pr = 0.5 * r - 0.418688 * g - 0.081312 * b;

        /* quantizing pb and pr */
        pb = quantizeChroma(pb);
        pr = quantizeChroma(pr);

        /* copy the pixel over to the CV float array */
        current->y = y;
        current->pb = pb;
        current->pr = pr;   

}

