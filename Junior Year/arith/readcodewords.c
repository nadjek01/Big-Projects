/* readcodewords.c
*
* by Ayah Harper and Nana Adjekum, 10/19/23
*
* This file contains the implementation of the readCodeWords function defined 
* in the readcodewords.h interface. This function covers steps (6) and (7) of
* decompression on the arith spec.
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <mem.h>
#include <uarray2.h>
#include "readcodewords.h"
#include "bitpack.h"
#include "structs.h"

/************************** HELPER/APPLY FUNCTIONS ***********************/
void unpackwords(int col, int row, UArray2_T PackedWords, 
                                        void *elem, void *cl);
void readPBM(int col, int row, UArray2_T packedWords,
                                        void *elem, void *cl);

/*************************** FUNCTION DEFINITIONS **********************/

/********** readCodeWords ********
 * reads the input PBM image file into an array of CodeWord structs
 *
 * Parameters:
 *      FILE *PBMfile:  file containing valid pbm image   
 *
 * Return: 2D array of CodeWord structs
 *
 * Expects
 *      PBMfile to be properly formatted in COMP40 Compressed image format
 *      
 * Notes:
 *      N/A
 ************************/
UArray2_T readCodeWords(FILE *PBMfile) 
{
        /* process the header, pulling out the width and height of the image */
        unsigned height, width;
        int read = fscanf(PBMfile, "COMP40 Compressed image format 2\n%u %u",
                                &width, &height);
        assert(read == 2);
        int c = getc(PBMfile);
        assert(c == '\n');

        /* build an array for bitpacked codewords (uint64_t's) */ 
        UArray2_T PackedWords = UArray2_new(width, height, sizeof(uint64_t));
        assert(PackedWords);

        /* read through the file and store each bitpacked codeword 
        as an element in the array */
        UArray2_map_row_major(PackedWords, readPBM, PBMfile);

        /* build an array for CodeWord structs */
        UArray2_T CodeWordStructs = UArray2_new(width, height, 
                                        sizeof(CodeWord));
        assert(CodeWordStructs);

        /* unpack each bit-packed codeword and store in a CodeWord struct */
        UArray2_map_row_major(PackedWords, unpackwords, &CodeWordStructs);

        UArray2_free(&PackedWords);

        return CodeWordStructs;
}

/********** unpackwords (APPLY) ********
 *
 * apply function converts a 64-bit packed codeword into
 * a CodeWord struct
 *
 * Parameters:
 *      int col:                        column # of current element
 *      int row:                        row # of current element
 *      UArray2b_T PackedWods:          2D array being mapped through
 *      void *elem:                     ptr to current element
 *      void *cl:                       closure (passed in by caller)
 *
 * Return: none, but returns the closure by reference
 *
 * Expects:
 *      PackedWords is not NULL
 *      elem points to an uint64_t
 *      cl points to an array of CodeWord structs
 *      every col and row is within the bounds of the cl array
 * Notes:
 *      may CRE if PackedWords is empty/null
 *      may CRE if col or row is out of bounds of the array pointed to by cl
 ************************/
void unpackwords(int col, int row, UArray2_T PackedWords, void *elem, void *cl)
{
        (void)PackedWords;

        /* get the destination position for the 
        CodeWord Struct we will build */
        UArray2_T *CodeWordStructs = cl;
        CodeWord *destination = (CodeWord *)UArray2_at(*CodeWordStructs,
                                                        col, row);

        /* grab the current bitpacked CodeWord from the array */
        uint64_t word = *(uint64_t *)elem;

        /* pull out each packed field into local variables */
        uint64_t Pr = Bitpack_getu(word, 4, 0);
        uint64_t Pb = Bitpack_getu(word, 4, 4);
        int64_t d = Bitpack_gets(word, 5, 8);
        int64_t c = Bitpack_gets(word, 5, 13);
        int64_t b = Bitpack_gets(word, 5, 18);
        uint64_t a = Bitpack_getu(word, 9, 23);

        /* cast each uint64_t to its signed/unsigned rep and 
        store in a CodeWord struct */
        CodeWord word_struct = {(unsigned)Pb, (unsigned)Pr, (unsigned)a, 
                                (signed)b, (signed)c, (signed)d};

        /* place the CodeWord struct at its destination position
        in the CodeWordStructs array */
        *destination = word_struct;

}

/********** readPBM (APPLY) ********
 *
 * apply function that reads a byte from an input file 
 * and packs it into a 64-bit codeword
 *
 * Parameters:
 *      int col:                        column # of current element
 *      int row:                        row # of current element
 *      UArray2b_T PackedWords:         2D array being mapped through
 *      void *elem:                     ptr to current element
 *      void *cl:                       closure (passed in by caller)
 *
 * Return: none, but returns the closure by reference
 *
 * Expects:
 *      PackedWords is not NULL
 *      elem points to an uint64_t
 *      cl points to the file to read from
 *      every col and row is within the bounds of the cl array
 * Notes:
 *      may CRE if PackedWords is empty/null
 *      may CRE if col or row is out of bounds of the array pointed to by cl
 ************************/
void readPBM(int col, int row, UArray2_T PackedWords, void *elem, void *cl)
{
        (void)col;
        (void)row;
        (void)PackedWords;

        FILE *inputfp = cl;

        /* prepare a 64-bit int to pack the bytes into */
        uint64_t word = (uint64_t)0;

        uint64_t byte = (uint64_t)0;

        /* pack the codewords by grabbing one byte at a time */
        for (int i = 24; i >= 0; i -= 8) {
                byte = getc(inputfp);
                assert((int)byte != EOF);
                word = Bitpack_newu(word, 8, i, byte); 
        }

        /* place the packed codeword at the curr pos. in PackedWords array */
        *(uint64_t *)elem = word;

}
