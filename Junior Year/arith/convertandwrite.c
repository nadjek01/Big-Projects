/* convertandwrite.c
*
* by Ayah Harper and Nana Adjekum, 10/19/23
*
* This file contains the implementation of the convertandwrite.h interface. 
* This file handles converting the image back to RGB color space,
* rebuilding the pixmap and writing it to standard output. 
*/

#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <assert.h>
#include <mem.h>
#include <uarray2b.h>
#include <a2methods.h>
#include <a2blocked.h>
#include "compress40.h"
#include "convertandwrite.h"
#include "structs.h"

/************************** HELPER/APPLY FUNCTIONS *************************/
void float_to_unsigned(int col, int row, A2Methods_UArray2 array2D, 
                        void *elem, void *cl);
void cvConvertRGB(int col, int row, UArray2b_T CVarray, void *elem, void *cl);
void writePPM(Pnm_ppm pixmap);

static float requantizeChroma(float val) 
{
        if (val < -0.5) {
                return -0.5;
        }
        if (val > 0.5) {
                return 0.5;
        }

        return val;
}

/************************* FUNCTION DEFINITIONS **************************/

/********** convertandWrite ********
 *
 * converts a 2D array in floating point, CV colorspace to a pixmap and writes
 * the PPM image to stdout
 *
 * Parameters:
 *      UArray2b_T CVfloats:     2D blocked array with CV_float structs at each 
 *                               element
 *
 * Return: none, writes the pixmap to stdout
 *
 * Expects:
 *      CVfloats is not NULL
 *      each element of CVfloats contains a CV_float struct
 *      width and height of CVfloats are greater than 0
 * Notes:
 *      will CRE if CVfloats is NULL.
 ************************/
void convertandWrite(UArray2b_T CVfloats) 
{
        assert(CVfloats);
        int width = UArray2b_width(CVfloats);
        int height = UArray2b_height(CVfloats);

        /*build an array for the RGB float pixels 
        (with CVfloats's dimensions)*/
        UArray2b_T rgbModel = UArray2b_new(width, height, 
                                           sizeof(RGB_float), 2);
        assert(rgbModel);

        /*convert each CV_float struct in CVfloats to RGB_float in rgbModel*/
        UArray2b_map(CVfloats, cvConvertRGB, &rgbModel);
        
        /*manually construct a pixmap*/
        Pnm_ppm pixmap = malloc(width * height * sizeof(*pixmap));
        assert(pixmap);
        pixmap->width = (unsigned)width;
        pixmap->height = (unsigned)height;
        pixmap->denominator = 255;
        pixmap->methods = uarray2_methods_blocked;
        pixmap->pixels = pixmap->methods->new(width, height, 
        sizeof(struct Pnm_rgb));
        assert(pixmap->pixels);

        /*convert float RGB pixels to unsigned RGB pixels and store in pixmap*/
        pixmap->methods->map_default(pixmap->pixels, 
        (A2Methods_applyfun *)float_to_unsigned, &rgbModel);
        assert(pixmap->pixels);

        writePPM(pixmap);

        Pnm_ppmfree(&pixmap);
        UArray2b_free(&rgbModel);
}

/********** writePPM ********
 *
 * writes the argument pixmap to an output file stream and frees it
 *
 * Parameters:
 *      Pnm_ppm pixmap:     a pixmap 
 *
 * Return: none
 *
 * Expects:
 *      pixmap is not NULL
 * Notes:
 *      Pnm_ppmwrite raises CRE if pixmap is empty.
 ************************/
void writePPM(Pnm_ppm pixmap)
{
        Pnm_ppmwrite(stdout, pixmap);
}
        

/********** float_to_unsigned (APPLY) ********
 *
 * apply function which converts floating pt r/g/b pixels to unsigned r/g/b
 * pixels in a new array
 *
 * Parameters:
 *      int col:                        column # of current element
 *      int row:                        row # of current element
 *      A2Methods_UArray2 array2D:      2D array being mapped through
 *      void *elem:                     ptr to current element
 *      void *cl:                       closure (passed in by caller)
 *
 * Return: none, but returns the closure by reference
 *
 * Expects:
 *      array2D is not NULL
 *      elem points to a Pnm_rgb struct
 *      cl points to a 2D blocked array pf RGB_float structs
 *      every col and row is within the bounds of the cl array
 * Notes:
 *      may CRE if array2D is NULL
 *      may CRE if col or row is out of bounds of the array pointed to by cl
 ************************/
void float_to_unsigned(int col, int row, A2Methods_UArray2 array2D, 
                        void *elem, void *cl)
{      
        (void)array2D;

        /* array of RGB floats (to be converted to RGB unsigned) */
        UArray2b_T *RGBfloats = cl; 
        RGB_float original = *(RGB_float *)UArray2b_at(*RGBfloats, col, row);

        /* scale each float val by the denominator and convert to unsigned */
        unsigned red = original.red * 255;
        unsigned green = original.green * 255;
        unsigned blue = original.blue * 255;

        /* force unruly RGB values into range */
        if (red > 255) { red = 255; }
        if (green > 255) { green = 255; }
        if (blue > 255 ) { blue = 255; }

        /* copy over to pixmap */
        Pnm_rgb current = elem;
        current->red = red;
        current->green = green;
        current->blue = blue;

}

/********** cvConvertRGB (APPLY) ********
 *
 * apply function to convert floating point y/pb/pr pixels to floating point 
 * r/g/b pixels
 *
 * Parameters:
 *      int col:                        column # of current element
 *      int row:                        row # of current element
 *      UArray2b_T CVarray:             2D blocked array being mapped through
 *      void *elem:                     ptr to current element
 *      void *cl:                       closure (passed in by caller)
 *
 * Return: none, but returns the closure by reference
 *
 * Expects
 *      CVarray is not NULL, cl is not NULL
 *      elem points to a CV_float struct
 *      cl points to a 2D blocked array pf RGB_float structs
 *      every col and row is within the bounds of the cl array 
 Notes:
 *      may CRE if CVarray is empty/NULL
 *      may CRE if col or row is out of bounds of the array pointed to by cl
 ************************/
void cvConvertRGB(int col, int row, UArray2b_T CVarray, void *elem, void *cl)
{    
        (void)CVarray;

        /* get the destination pixel in the array of RGB floats */
        UArray2b_T *RGBarray = cl; 
        RGB_float *destination = (RGB_float *)UArray2b_at((*RGBarray), 
                                  col, row);

        /* get the current pixel to convert & copy over*/
        CV_float current = *(CV_float *)elem;

        float y = current.y;
        float pb = current.pb;
        float pr = current.pr;

        pb = requantizeChroma(pb);
        pr = requantizeChroma(pr);
        
        /* convert pizel value */
        float r = 1.0 * y + 0.0 * pb + 1.402 * pr;
        float g = 1.0 * y - 0.344136 * pb - 0.714136 * pr;
        float b = 1.0 * y + 1.772 * pb + 0.0 * pr;
        
        /* force any negative pixel values into range */
        if (r < 0) { r = 0; }
        if (g < 0) { g = 0; }
        if (b < 0) { b = 0; }

        /* copy pixel values to the destination pixel*/
        destination->red = r;
        destination->green = g;
        destination->blue = b;   

}
