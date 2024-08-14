/* instructions.c
*
* by Ayah Harper and Nana Adjekum
*
* purpose: implementation of the functions that execute each of the 14
* instructions
*/

#include "seq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>
#include <bitpack.h>
#include <assert.h>
#include "instructions.h"

/********** exec_CMOV ********
 * Performs a conditional move based on the values
 * in the registers at the time of function call
 *
 * Parameters:
 *      memPack *program: 
 *              - a pointer to a struct containing our UM memory 
                  data structures
 *      uint32_t instruction:
 *              - the instruction with opcode + register info
 *
 * Returns:
 *      none, updates memPack by reference
 *
 * Expects:
 *      memPack to be initalised and the instructions to have a valid
 *      opcode, register value, value
 * Notes:
 *      the instructions can be placed in a struct
 *      with all the info: code, registers, vals
 *
 ************************/
void exec_CMOV(memPack *program, uint32_t instruction)
{
        uint32_t ra = Bitpack_getu(instruction, 3, 6);
        uint32_t rb = Bitpack_getu(instruction, 3, 3);
        uint32_t rc = Bitpack_getu(instruction, 3, 0);

        if (((program->registers))[rc] != 0) {
                ((program->registers))[ra] = ((program->registers))[rb];
        }

}

/********** exec_LOADV ********
 * Performs a conditional move based on the values
 * in the registers at the time of function call
 *
 * Parameters:
 *      memPack program: 
 *      -a pointer to a struct containing our UM memory data structures
 *      uint32_t instruction:
 *      -the instruction with all the important info (vals, registers)
 *
 * Returns:
 *      none, updates memPack by reference
 *
 * Expects
 *      memPack to be initalised and the instructions to have a valid
 *      opcode, register value, value
 * Notes:
 *      the instructions can b placed in a struct
 *      with all the info: code, registers, vals
 *
 ************************/
void exec_LOADV(memPack *program, uint32_t instruction)
{
        uint32_t ra = Bitpack_getu(instruction, 3, 25);
        uint32_t value = Bitpack_getu(instruction, 25, 0);
        
        (program->registers)[ra] = value;
}

/********** exec_ADD ********
 * Performs a conditional move based on the values
 * in the registers at the time of function call
 *
 * Parameters:
 *      memPack program: 
 *      -a pointer struct containing our UM memory data structures
 *      uint32_t instruction:
 *      -the instruction with all the important info (vals, registers)
 *
 * Returns:
 *      none, updates memPack by reference
 *
 * Expects
 *      memPack to be initalised and the instructions to have a valid
 *      opcode, register value, value
 * Notes:
 *      the instructions can b placed in a struct
 *      with all the info: code, registers, vals
 *
 ************************/
void exec_ADD(memPack *program, uint32_t instruction)
{
        uint32_t ra = Bitpack_getu(instruction, 3, 6);
        uint32_t rb = Bitpack_getu(instruction, 3, 3);
        uint32_t rc = Bitpack_getu(instruction, 3, 0);

        (program->registers)[ra] = (program->registers)[rb] + 
                                (program->registers)[rc];
        
}

/********** exec_MULT ********
 * Multiplies register values and stores their
 * product in a register
 *
 * Parameters:
 *      memPack program:
 *      -a pointer to a struct containing our UM memory data structures
 *      uint32_t instruction:
 *      -the instruction with all the important info (vals, registers)
 *
 * Returns:
 *      none, updates memPack by reference
 *
 * Expects
 *      memPack to be initalised and the instructions to have a valid
 *      opcode, register value, value
 * Notes:
 *      the instructions can b placed in a struct
 *      with all the info: code, registers, vals
 *
 ************************/
void exec_MULT(memPack *program, uint32_t instruction)
{
        uint32_t ra = Bitpack_getu(instruction, 3, 6);
        uint32_t rb = Bitpack_getu(instruction, 3, 3);
        uint32_t rc = Bitpack_getu(instruction, 3, 0);

        (program->registers)[ra] = (program->registers)[rb] * 
                                (program->registers)[rc];
        
}

/********** exec_OUTPUT ********
 * executes output instruction
 *
 * Parameters:
 *      memPack program: 
 *      -a pointer to a struct containing our UM memory data structures
 *      uint32_t instruction:
 *      -the instruction with all the important info (vals, registers)
 *
 * Returns:
 *      none, updates memPack by reference
 *
 * Expects
 *      memPack to be initalised and the instructions to have a valid
 *      opcode, register value, value
 * Notes:
 *      the instructions can b placed in a struct
 *      with all the info: code, registers, vals
 *
 ************************/
void exec_OUTPUT(memPack *program, uint32_t instruction)
{
        uint32_t rc = Bitpack_getu(instruction, 3, 0);
        uint32_t value = (program->registers)[rc];

        fprintf(stdout, "%c", value);
}

/********** exec_INPUT ********
 * executes input instruction
 *
 * Parameters:
 *      memPack program: 
 *      -a pointer struct containing our UM memory data structures
 *      uint32_t instruction:
 *      -the instruction with all the important info (vals, registers)
 *
 * Returns:
 *      none, updates memPack by reference
 *
 * Expects
 *      memPack to be initalised and the instructions to have a valid
 *      opcode, register value, value
 * Notes:
 *      the instructions can b placed in a struct
 *      with all the info: code, registers, vals
 *
 ************************/
void exec_INPUT(memPack *program, uint32_t instruction)
{
        uint32_t rc = Bitpack_getu(instruction, 3, 0);
        int value;
        scanf("%d", &value);

        /* check if input is signaled */
        if (value == EOF) {
                (program->registers)[rc] = ~0; 
                return;  
        }

        (program->registers)[rc] = (uint32_t)value;
}

/********** exec_DIV ********
 * executes division instruction
 *
 * Parameters:
 *      memPack *program: 
 *      -pointer to the struct containing our UM memory data structures
 *      uint32_t instruction:
 *      -the instruction with all the important info (vals, registers)
 *
 * Returns:
 *      none, updates memPack by reference
 *
 * Expects
 *      memPack to be initalised and the instructions to have a valid
 *      opcode, register value, value
 * Notes:
 *      the instructions can b placed in a struct
 *      with all the info: code, registers, vals
 *
 ************************/
void exec_DIV(memPack *program, uint32_t instruction)
{
        uint32_t ra = Bitpack_getu(instruction, 3, 6);
        uint32_t rb = Bitpack_getu(instruction, 3, 3);
        uint32_t rc = Bitpack_getu(instruction, 3, 0);

        (program->registers)[ra] = (program->registers)[rb] / 
                                (program->registers)[rc];
}

/********** exec_NAND ********
 * executes NAND instruction
 *
 * Parameters:
 *      memPack *program: 
 *      -pointer to the struct containing our UM memory data structures
 *      uint32_t instruction:
 *      -the instruction with all the important info (vals, registers)
 *
 * Returns:
 *      none, updates memPack by reference
 *
 * Expects
 *      memPack to be initalised and the instructions to have a valid
 *      opcode, register value, value
 * Notes:
 *      the instructions can b placed in a struct
 *      with all the info: code, registers, vals
 *
 ************************/
void exec_NAND(memPack *program, uint32_t instruction)
{
        uint32_t ra = Bitpack_getu(instruction, 3, 6);
        uint32_t rb = Bitpack_getu(instruction, 3, 3);
        uint32_t rc = Bitpack_getu(instruction, 3, 0);

        (program->registers)[ra] = ~((program->registers)[rb] & 
                                (program->registers)[rc]);
        
}

/********** exec_MAP ********
 * Maps a new memory segment
 *
 * Parameters:
 *      memPack *program: 
 *      -pointer to the struct containing our UM memory data structures
 *      uint32_t instruction:
 *      -the instruction with all the important info (vals, registers)
 *
 * Returns:
 *      none, updates memPack by reference
 *
 * Expects
 *      memPack to be initalised and the instructions to have a valid
 *      opcode, register value, value
 * Notes:
 *      the instructions can b placed in a struct
 *      with all the info: code, registers, vals
 *
 ************************/
void exec_MAP(memPack *program, uint32_t instruction)
{
        uint32_t rb = Bitpack_getu(instruction, 3, 3); /* segID destination */
        uint32_t rc = Bitpack_getu(instruction, 3, 0); /* seg size location */
        
        uint32_t size = (program->registers)[rc]; /* grab segment size */

        /* build the segment, calloc'ing [size] instructions */
        Seq_T new_segment = Seq_new(0);
        unsigned i = 0;
        while (i < size) {
                uint32_t *umword = (uint32_t *)calloc(1, sizeof(uint32_t));
                Seq_addhi(new_segment, (void *)(uint32_t *)umword);
                i++;
        }

        /* assign the new segment an ID # */
        uint32_t ID = 0;
        
        /* chcek the stack any ID #'s that are available for reuse. 
        * otherwise, append the segment onto the sequence of memory segments */
        if (!Stack_empty(program->freedIDs)) {
                uint32_t *IDptr = (uint32_t *)Stack_pop(program->freedIDs);
                ID = *IDptr; 
                free(IDptr);
                Seq_put(program->segmentIDs, ID, new_segment); /* ID = index */
        } else {
                ID = (uint32_t)Seq_length(program->segmentIDs);
                Seq_addhi(program->segmentIDs, new_segment);
        }

        (program->registers)[rb] = ID;

}


/********** exec_UNMAP ********
 * Unmaps a previously mapped segment
 *
 * Parameters:
 *      memPack *program: 
 *      -pointer to the struct containing our UM memory data structures
 *      uint32_t instruction:
 *      -the instruction with all the important info (vals, registers)
 *
 * Returns:
 *      none, updates memPack by reference
 *
 * Expects
 *      memPack to be initalised and the instructions to have a valid
 *      opcode, register value, value
 * Notes:
 *      the instructions can b placed in a struct
 *      with all the info: code, registers, vals
 *
 ************************/
void exec_UNMAP(memPack *program, uint32_t instruction)
{
        uint32_t rc = Bitpack_getu(instruction, 3, 0);
        uint32_t unmapID = (program->registers)[rc];

        uint32_t *IDptr = (uint32_t *)malloc(sizeof(uint32_t));

        *IDptr = unmapID;

        /* grab the segment to unmap */
        Seq_T unmapSeg = (Seq_T)Seq_get(program->segmentIDs, unmapID);

        /* iterate over the segment, freeing each uint32_t instruct. */
        for (int i = 0; i < Seq_length(unmapSeg); i++) {
                free(Seq_get(unmapSeg, i));
        }

        /* free the segment itself*/
        Seq_free(&unmapSeg);

        /* set the unmapped segment's pointer to NULL */
        Seq_put(program->segmentIDs, unmapID, NULL);

        /* push the unmapped segment's ID onto the stack of free ID's */
        Stack_push(program->freedIDs, (IDptr));
        
}

/********** exec_LOADP ********
 * Loads a new sequence of instructions into the 0 segment
 *
 * Parameters:
 *      memPack *program: 
 *      -pointer to the struct containing our UM memory data structures
 *      uint32_t instruction:
 *      -the instruction with all the important info (vals, registers)
 *
 * Returns:
 *      none, updates memPack by reference
 *
 * Expects
 *      memPack to be initalised and the instructions to have a valid
 *      opcode, register value, value
 * Notes:
 *      the instructions can b placed in a struct
 *      with all the info: code, registers, vals
 *
 ************************/
void exec_LOADP(memPack *program, uint32_t instruction)
{

        uint32_t rb = Bitpack_getu(instruction, 3, 3); /* segID */ 
        uint32_t rc = Bitpack_getu(instruction, 3, 0); /* pcount offset */

        uint32_t segID = (program->registers)[rb];
        uint32_t offset = (program->registers)[rc];

        if (segID != (uint32_t)0) {
                /* grab the new segment, duplicate it, and load into 0-index */
                Seq_T newSegment = (Seq_T)Seq_get(program->segmentIDs, segID);

                /* build an instance for the duplicate */
                Seq_T segmentDUPE = Seq_new(0);

                /* deep copy the entire segment */
                for (int i = 0; i < Seq_length(newSegment); i++) {
                        uint32_t word = *(uint32_t *)Seq_get(newSegment, i);
                        uint32_t *wordptr = 
                                (uint32_t *)malloc(sizeof(uint32_t));
                        *wordptr = word;
                        Seq_addhi(segmentDUPE, wordptr);
                }

                Seq_T zeroSegment = (Seq_T)Seq_put(program->segmentIDs, 
                                     0, segmentDUPE);

                /* free each uint32_t instruction */
                for (int i = 0; i < Seq_length(zeroSegment); i++) {
                        free(Seq_get(zeroSegment, i));
                }
                
                Seq_free(&zeroSegment);
        }

        /* note: if duplicating 0-segment -> update program counter + return */
        program->pcount = offset;
        
}

/********** exec_SSTORE ********
 * stores a value from a register into a segment
 *
 * Parameters:
 *      memPack *program: 
 *      -the pointer to struct containing our UM memory data structures
 *      uint32_t instruction:
 *      -the instruction with all the important info (vals, registers)
 *
 * Returns:
 *      none, updates memPack by reference
 *
 * Expects
 *      memPack to be initalised and the instructions to have a valid
 *      opcode, register value, value
 * Notes:
 *      the instructions can b placed in a struct
 *      with all the info: code, registers, vals
 *
 ************************/
void exec_SSTORE(memPack *program, uint32_t instruction)
{
        uint32_t ra = Bitpack_getu(instruction, 3, 6);
        uint32_t rb = Bitpack_getu(instruction, 3, 3);
        uint32_t rc = Bitpack_getu(instruction, 3, 0);

        uint32_t segID = (program->registers)[ra]; /* ID # storage segment */
        uint32_t index = (program->registers)[rb]; /* index within segment */
        uint32_t *value = (uint32_t *)malloc(sizeof(uint32_t));
        
        *value = (program->registers)[rc]; /* value to be stored */

        /* grab the segment */
        Seq_T segment = (Seq_T)Seq_get(program->segmentIDs, segID);

        /* get a pointer to the position in segment where we will be storing */
        uint32_t *word = (uint32_t *)Seq_get(segment, index);

        /* store the value at the position in the segment */
        *word = *value;    

        free(value);

}

/********** exec_SLOAD ********
 * loads a value from a segment into a register
 *
 * Parameters:
 *      memPack *program: 
 *      -pointer to the struct containing our UM memory data structures
 *      uint32_t instruction:
 *      -the instruction with all the important info (vals, registers)
 *
 * Returns:
 *      none, updates memPack by reference
 *
 * Expects
 *      memPack to be initalised and the instructions to have a valid
 *      opcode, register value, value
 * Notes:
 *      the instructions can b placed in a struct
 *      with all the info: code, registers, vals
 *
 ************************/
void exec_SLOAD(memPack *program, uint32_t instruction)
{
        uint32_t ra = Bitpack_getu(instruction, 3, 6);
        uint32_t rb = Bitpack_getu(instruction, 3, 3);
        uint32_t rc = Bitpack_getu(instruction, 3, 0);

        uint32_t segID = (program->registers)[rb];  /* segment to load from */
        uint32_t index = (program->registers)[rc]; /* index the segment*/

        Seq_T segment = Seq_get(program->segmentIDs, segID);

        /* grab the word to load */
        uint32_t word = *(uint32_t *)Seq_get(segment, index);

        /* load the word into register A */
        (program->registers)[ra] = word;

}