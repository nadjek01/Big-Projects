#ifndef UM_OPCODE_INCLUDED
#define UM_OPCODE_INCLUDED

typedef enum Um_Opcode
{
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_Opcode;

#endif
