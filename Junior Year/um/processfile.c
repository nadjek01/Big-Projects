/* processfile.c
*
* by Ayah Harper and Nana Adjekum
* 
* purpose: implementation of the file processing module, which takes 
* a binary um file and builds a sequence of memory segments, with 
* the 0-segment containing all the program instructions.
*/

#include <stdio.h>
#include <stdlib.h>
#include "seq.h"
#include <string.h>
#include <bitpack.h>
#include "processfile.h"

/********** processFile ********
 * read the contents of a binary um file into a
 * Hanson sequence of pointers to 32-bit instructions
 *
 * Parameters:
 *      FILE *fp: pointer to (opened) um file 
 *
 * Returns:
 *      The sequence of "segments," or pointers to
 *      sequences of 32-bit instructions
 *
 * Expects
 *      fp is opened and contains a sequence of 32-bit instructions
 * Notes:
 *      PLACE FOR TIME IMPROVEMENT THE WHILE AND FOR LOOP
 *
 ************************/
Seq_T processFile(FILE *fp)
{
    Seq_T instructions = Seq_new(0);        /* all program instructions */ 
    Seq_T segmentIDs = Seq_new(0);          /* all segments */  
    
    int byte = getc(fp); /* get the first byte */ 
    while (byte != EOF)
    {
        /* malloc an instance of a 32-bit word */
        uint32_t *umword = (uint32_t *)malloc(sizeof(uint32_t));

        /* starting lsb and byte-size width */
        unsigned lsb = 24;            
        unsigned width = 8;           

        uint64_t temp = 0;

        /* grab 4 bytes at a time and pack into a 64-bit word */
        for (int i = 0; i < 4; i++) {
                //printf("width: %u\n", width);
                temp = Bitpack_newu(temp, width, lsb, byte);
                lsb -= 8;
                byte = getc(fp);
        }

        *umword = temp;
        
        /* append the word onto a sequence of instructions */
        Seq_addhi(instructions, (void *)(uint32_t *)(umword));

    }
        /* add the program instructions to the 0-segment */
        Seq_addlo(segmentIDs, (void *)instructions);
        
        return segmentIDs;
}


