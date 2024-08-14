/* writecodewords.c
*
* by Ayah Harper and Nana Adjekum, 10/19/23
*
* This file contains the implementation of the writeCodeWords function, defined 
* in the writecodewords.h interface. This function accepts an array of CodeWord 
* structs, bit-packs each CodeWord into a 64-bit int, and writes the bits to 
* standard output as a PBM image file.
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <mem.h>
#include <uarray2.h>
#include "writecodewords.h"
#include "bitpack.h"
#include "structs.h"

/************************** APPLY FUNCTIONS **************************/
void packcodewords(int col, int row, UArray2_T CWarray, 
void *elem, void *cl);
void writeCompressed(int col, int row, UArray2_T packedWords, 
void *elem, void *cl);

/********** writeCodeWords ********
 *
 * converts a 2D array of unsigned and signed pb, pr, a, b, c, d 
 * pixels to a 32-bit word (via bitpacking)
 *
 * Parameters:
 *      UArray2_T CodeWordStructs:    2D array of CodeWord structs
 *
 * Return: N/A
 *
 * Expects: N/A
 * Notes:
 *      may CRE if CodeWordStructs is NULL.
 ************************/
void writeCodeWords(UArray2_T CodeWordStructs)
{
        assert(CodeWordStructs);
        int width = UArray2_width(CodeWordStructs);
        int height = UArray2_height(CodeWordStructs);

        /* build an array for the packed codewords (uint64_t's) */
        UArray2_T PackedWords = UArray2_new(width, height, sizeof(uint64_t));
        assert(PackedWords);

        /* map through CodeWords, pack each word into a uint64_t, and store in 
        * the PackedWords array */
        UArray2_map_row_major(CodeWordStructs, packcodewords, &PackedWords);

        /* write a properly formatted header */
        printf("COMP40 Compressed image format 2\n%u %u", width, height);
        printf("\n");

        /*map through the packed codewords and print each one to stdout*/
        UArray2_map_row_major(PackedWords, writeCompressed, &width);

        UArray2_free(&PackedWords);
}

/********** packcodewords ********
 * packs each value in the Codeword array into a 32-bit wode via
 * bitpack implementation
 *      these vals are stored in another 2-d array as uint64_t
 *
 * Parameters:
 *      CodeWord Array: array of unsigned/signed pb,pr,a,b,c,d vals    
 *
 * Return: array of uint64_t words representing the packed vals
 *
 * Expects
 *      the array to be init with the unsigned/signed a,b,c,d,pb,pr vals
 * Notes:
 *      N/A
 ************************/
void packcodewords(int col, int row, UArray2_T CWarray, void *elem, void *cl)
{
        (void)CWarray;

        /* get the destination position for the packed word we will build */
        UArray2_T *PackedWords = cl;
        uint64_t *destination = (uint64_t *)UArray2_at(*PackedWords, col, row);

        /* get the CodeWord struct at the current position in the array */
        CodeWord current = *(CodeWord *)elem;
        
        /* pull out each signed/unsigned value and store in 64-bit variables*/
        uint64_t pb = current.Pb;
        uint64_t pr = current.Pr;
        uint64_t a = current.a;
        int64_t b = current.b;
        int64_t c = current.c;
        int64_t d = current.d;
        
        uint64_t finalword = (uint64_t)0; /* initialize 64-bit word */

        /* individually pack each value into the word in big-endian order*/
        finalword = Bitpack_newu(finalword, 9, 23, a);
        finalword = Bitpack_news(finalword, 5, 18, b); 
        finalword = Bitpack_news(finalword, 5, 13, c); 
        finalword = Bitpack_news(finalword, 5, 8, d); 
        finalword = Bitpack_newu(finalword, 4, 4, pb); 
        finalword = Bitpack_newu(finalword, 4, 0, pr);

        /* ensure everything was packed correctly */
        assert(Bitpack_getu(finalword, 9, 23) == a);
        assert(Bitpack_gets(finalword, 5, 18) == b);
        assert(Bitpack_gets(finalword, 5, 13) == c);
        assert(Bitpack_gets(finalword, 5, 8) == d);
        assert(Bitpack_getu(finalword, 4, 4) == pb);
        assert(Bitpack_getu(finalword, 4, 0) == pr);

        /* place the final, packed codeword at its destination 
        position in the PackedWords array! */
        *destination = finalword;

}

/********** writeCompressed ********
 * writes the compressed unit64 words to stdout via putchar
 *
 * Parameters:
 *      PackedWords Array: array of compressed unit64 words   
 *
 * Return: N/A
 *
 * Expects
 *      the array to be init with the uint64_t words
 * Notes:
 *      N/A
 ************************/
void writeCompressed(int col, int row, UArray2_T PackedWords, 
void *elem, void *cl)
{
        (void)cl;
        (void)col;
        (void)row;
        (void)PackedWords;

        /* grab the current codeword (bitpacked into 64-bit int) */
        uint64_t word = *(uint64_t *)elem;

        /* write the codewords, one byte at a time, in big-endian order */
        uint64_t byte = (uint64_t)0;
        for (int i = 24; i >= 0; i-= 8) {
                byte = Bitpack_getu(word, 8, i);
                putchar(byte);
        }

}