/* compress40.c
*
* by Ayah Harper and Nana Adjekum, 10/18/23
*
* This file contains the implementation of the functions, compress40 and
* decompress40, defined in the compress40.h interface. Together, these 
* functions work as inverses to compress and decompress a P6, PPM image. 
*/

#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <a2methods.h>
#include <uarray2b.h>
#include "assert.h"
#include "compress40.h"
#include "readandconvert.h"
#include "convertandwrite.h"
#include "readcodewords.h"
#include "writecodewords.h"
#include <bitpack.h>
#include "transform.h"
#include "detransform.h"

/********** compress40 ********
 *
 * performs lossy image compression on the input PPM image file 
 *
 * Parameters:
 *      FILE *input:     input file containing ppm image
 *
 * Return: none, writes a compressed PBM image file to standard output
 *
 * Expects
 *      file contains a valid ppm image
 * Notes:
 *      may CRE if an assertion is failed within any of the called functions.
 ************************/
void compress40(FILE *input)
{
        /* rgb unsigned array (pixmap) -> y/pb/pr float array (CV) */
        UArray2b_T CVfloats1 = readandConvert(input);

        /* y/pb/pr float array (CV) -> Codewords array */
        UArray2_T CodeWords1 = shrinkToTransform(CVfloats1);

        /* CodeWords array -> bitpacked 64-bit integers -> stdout */
        writeCodeWords(CodeWords1);

        /* FREE! */
        UArray2_free(&CodeWords1);
        UArray2b_free(&CVfloats1);
}

/********** decompress40 ********
 *
 * decompresses a PBM image file into its restored image in PPM format 
 *
 * Parameters:
 *      FILE *input:     input file containing pbm image file
 *
 * Return: none, writes a ppm image to stdout
 *
 * Expects
 *      file contains a valid, properly formatted pbm image
 * Notes:
 *      may CRE if an assertion is failed within any of the called functions.
 ************************/
void decompress40(FILE *input)
{
        /* input file -> array of CodeWord structs */
        UArray2_T CodeWords2 = readCodeWords(input);

        /* array of CodeWord structs -> y/pb/pr float array (CV) */
        UArray2b_T CVfloats2 = growToTransform(CodeWords2);

        /* y/pb/pr float array (CV) -> rgb unsigned array (pixmap) */
        convertandWrite(CVfloats2);

        /* FREE! */
        UArray2_free(&CodeWords2);
        UArray2b_free(&CVfloats2);

}
