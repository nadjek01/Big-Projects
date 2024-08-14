/* execute.c
*
* by Ayah Harper and Nana Adjekum
*
* purpose: implentation of the execution cycle module 
* for the UM emulator
*/

#include "seq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>
#include <bitpack.h>
#include <assert.h>
#include "execute.h"
#include "instructions.h"


/************* OPCODES ****************/
typedef enum opcodes {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, MAP, UNMAP, OUT, IN, LOADP, LOADV
} opcodes;

/******** HELPER FUNCTION ***********/
void execution_cycle(memPack program);

/********** initialize ********
 * initialize the struct of program information
 *
 * Parameters:
 *      Seq_T segments:   a sequence of memory segments
 *
 * Returns:
 *      initialized memPack struct
 *
 * Expects
 *      the 0-segment of "segments" is mapped
 *      segments is not NULL
 * Notes:
 *     creates and initializes stack
 *     initializes registers
 *     points program counter to first instruction
 ************************/
static memPack *initialize(Seq_T segments)
{
        /* initialize an empty stack */
        Stack_T freedIDs = Stack_new();

        memPack *bundle = (memPack *)malloc(sizeof(memPack));

        bundle->segmentIDs = segments;
        (*bundle).freedIDs = freedIDs;
        for (int i = 0; i < 8; i++) {
                (*bundle).registers[i] = 0;
        }
        (*bundle).pcount = 0;

        return bundle;   
}


/********** freeSegments ********
 * frees the memory allocated by the segmented
 * memory space
 *
 * Parameters:
 *      Seq_T allSegments:  sequence of memory segments 
 *
 * Returns:
 *      None
 *
 * Expects:
 *      allSegments is not NULL
 * Notes:
 *      frees every uint32_t instruction in every segment
 *      frees the segment (sequence) itself
 *      frees the overall sequence of segments
 ************************/
static void freeSegments(Seq_T allSegments)
{
        /* iterate over all segments */
        for (int i = 0; i < Seq_length(allSegments); i++) {
                
                /* disregard any NULL segments */
                if (Seq_get(allSegments, i) == NULL) {
                        continue;
                }
                /* iterate over the segment, freeing each uint32_t instruct. */
                for (int j = 0; j < Seq_length(Seq_get(allSegments, i)); j++) {
                        free(Seq_get(Seq_get(allSegments, i), j));
                }
                /* free the segment itself */
                Seq_T segment = (Seq_T)Seq_get(allSegments, i);
                Seq_free(&segment);
        }
        /* free the sequence of memory segments */
        Seq_free(&allSegments);

}

/********** cleanUp ********
 * "clean up" all dynamically allocated memory (stack, sequences,
 * pointers, etc.)
 *
 * Parameters:
 *      memPack obj:    struct of program memory info to be cleared 
 *
 * Returns:
 *      none
 *
 * Expects
 *      segmentIDs sequence is not NULL
 *      freedID stack is not NULL
 * Notes:
 *      calls freeSegments helper func to handle freeing segmented memory
 *
 ************************/
static void cleanUp(memPack obj)
{
        freeSegments(obj.segmentIDs); /* free segmented memory */

        while (!Stack_empty(obj.freedIDs)) {
                uint32_t *value = Stack_pop(obj.freedIDs);
                free(value);
        }
        Stack_free(&obj.freedIDs);   /* free the stack of available ID's */
}

/********** execute_program ********
 * wrapper function for initializing the UM, executing instructions,
 * and cleaning up/freeing allocated memory.
 *
 * Parameters:
 *      Seq_T segmentIDs:       sequence of memory segments 
 *
 * Returns:
 *      none
 *
 * Expects:
 *      segmentIDs sequence is not NULL
 * Notes:
 *
 ************************/
void execute_program(Seq_T segmentIDs)
{
        memPack *program = initialize(segmentIDs);

        execution_cycle(*program);

        cleanUp(*program);
        free(program);
}


/********** execution_cycle ********
 * function to perform the execution of instructions
 *
 * Parameters:
 *      memPack program: struct of program information 
 *
 * Returns:
 *      memPack struct with program information in its
 *      post-execution state
 *
 * Expects:
 *      program counter points to the first instruction in the 0-segment
 *      only the 0-segment of memory is mapped at the start of execution
 * Notes:
 *      PLACE FOR TIME IMPROVEMENT THE WHILE AND FOR LOOP
 *
 ************************/
void execution_cycle(memPack program)
{
        uint32_t instruction;
        uint32_t code;
        bool exit = false;

        do {
                instruction = *(uint32_t *)Seq_get
                        (Seq_get(program.segmentIDs, 0), program.pcount);
                code = Bitpack_getu(instruction, 4, 28); /* retrieve opcode */

                if (code == CMOV) {
                        exec_CMOV(&program, instruction);
                } else if (code == SLOAD) { 
                        exec_SLOAD(&program, instruction);
                } else if (code == SSTORE) { 
                        exec_SSTORE(&program, instruction);
                } else if (code == ADD) {
                        exec_ADD(&program, instruction);
                } else if (code == MUL) {
                        exec_MULT(&program, instruction);
                } else if (code == DIV) {
                        exec_DIV(&program, instruction);
                } else if (code == NAND) {
                        exec_NAND(&program, instruction);
                } else if (code == MAP) {
                        exec_MAP(&program, instruction);
                } else if (code == UNMAP) {
                        exec_UNMAP(&program, instruction);
                } else if (code == OUT) { 
                        exec_OUTPUT(&program, instruction);
                } else if (code == IN) {
                        exec_INPUT(&program, instruction);
                } else if (code == LOADP) {
                        exec_LOADP(&program, instruction);
                        continue;
                } else if (code == LOADV) {
                        exec_LOADV(&program, instruction);
                } else if (code == HALT) {
                        exit = true;
                }

                program.pcount++;

        } while (!exit);
        
        return;    
}