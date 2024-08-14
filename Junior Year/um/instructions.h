/* instructions.h
*
* by Ayah Harper and Nana Adjekum
*
* purpose: interface for the functions that execute
* each of the 14 instructions
*/

#include "seq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>
#include <bitpack.h>
#include <assert.h>

/************ MEMPACK STRUCT ***********/
typedef struct memPack {
        Seq_T segmentIDs;        /* sequence of memory segments */ 
        Stack_T freedIDs;        /* stack of available segment ID #s */ 
        uint32_t registers[8];   /* 8, 32-bit registers */ 
        uint32_t pcount;         /* program counter */ 
} memPack;

/*************** INSTRUCTION SET FUNCTIONS *****************/
extern void exec_CMOV(memPack *program, uint32_t instruction);
extern void exec_LOADV(memPack *program, uint32_t instruction);
extern void exec_ADD(memPack *program, uint32_t instruction);
extern void exec_MULT(memPack *program, uint32_t instruction);
extern void exec_OUTPUT(memPack *program, uint32_t instruction);
extern void exec_DIV(memPack *program, uint32_t instruction);
extern void exec_NAND(memPack *program, uint32_t instruction);
extern void exec_INPUT(memPack *program, uint32_t instruction);
extern void exec_MAP(memPack *program, uint32_t instruction);
extern void exec_UNMAP(memPack *program, uint32_t instruction);
extern void exec_LOADP(memPack *program, uint32_t instruction);
extern void exec_SLOAD(memPack *program, uint32_t instruction);
extern void exec_SSTORE(memPack *program, uint32_t instruction);


