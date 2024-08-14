/*
 * umlab.c
 *
 * Functions to generate UM unit tests. Once complete, this module
 * should be augmented and then linked against umlabwrite.c to produce
 * a unit test writing program.
 *  
 * A unit test is a stream of UM instructions, represented as a Hanson
 * Seq_T of 32-bit words adhering to the UM's instruction format.  
 * 
 * Any additional functions and unit tests written for the lab go
 * here. 
 *  
 */


#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <seq.h>
#include <bitpack.h>


typedef uint32_t Um_instruction;
typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, MAP, UNMAP, OUT, IN, LOADP, LV
} Um_opcode;


/* Functions that return the two instruction types */

Um_instruction three_register(Um_opcode op, int ra, int rb, int rc);
Um_instruction loadval(unsigned ra, unsigned val);


/* function definitions */

/* builds a 3-register UM instruction (32 bits) */
Um_instruction three_register(Um_opcode op, int ra, int rb, int rc) 
{
        Um_instruction word = (uint32_t)0; /* 32 bits of 0's */

        // check that opcode is one of the 14 instructions
        // check that each int ra, rb, and rc can fit into 3 bits

        /* insert opcode in high 4 bits */
        word = Bitpack_newu(word, 4, 28, op); 
        word = Bitpack_newu(word, 3, 6, ra);  /* insert register a */
        word = Bitpack_newu(word, 3, 3, rb);  /* insert register b */
        word = Bitpack_newu(word, 3, 0, rc);  /* insert register c */

        return word;
        
}

/* builds a load value UM instruction (32 bits) */
Um_instruction loadval(unsigned ra, unsigned val)
{
        Um_instruction word = (uint32_t)0;

        // check that int ra can fit into 3 bits
        // check that val can fit into 25 bits
        
        /* insert opcode to LOAD into the high 4 bits*/
        /* insert the destination register next 3 bits */
        /* insert the value into the remaining bits */
        word = Bitpack_newu(word, 4, 28, LV);
        word = Bitpack_newu(word, 3, 25, ra);
        word = Bitpack_newu(word, 25, 0, val);

        return word;

}

/* Wrapper functions for each of the instructions */

static inline Um_instruction halt(void) 
{
        return three_register(HALT, 0, 0, 0);
}

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;

static inline Um_instruction add(Um_register a, Um_register b, Um_register c)
{
        return three_register(ADD, a, b, c);
}

static inline Um_instruction mul(Um_register a, Um_register b, Um_register c)
{
        return three_register(MUL, a, b, c);
}

static inline Um_instruction cmov(Um_register a, Um_register b, Um_register c)
{
        return three_register(CMOV, a, b, c);
}

static inline Um_instruction sload(Um_register a, Um_register b, Um_register c)
{
        return three_register(SLOAD, a, b, c);
}

static inline Um_instruction sstore(Um_register a, Um_register b, Um_register c)
{
        return three_register(SSTORE, a, b, c);
}

static inline Um_instruction div(Um_register a, Um_register b, Um_register c)
{
        return three_register(DIV, a, b, c);
}

static inline Um_instruction nand(Um_register a, Um_register b, Um_register c) 
{
        return three_register(NAND, a, b, c);
}

static inline Um_instruction map(Um_register b, Um_register c)
{
        return three_register(MAP, 0, b, c);
}

static inline Um_instruction unmap(Um_register c)
{
        return three_register(UNMAP, 0, 0, c);
}

static inline Um_instruction loadp(Um_register b, Um_register c)
{
        return three_register(LOADP, 0, b, c);
}

Um_instruction output(Um_register c);

/* funciton to produce an output instruction*/
Um_instruction output(Um_register c)
{
        Um_instruction word = three_register(OUT, 0, 0, c);
        
        return word;
}

Um_instruction input(Um_register c);

Um_instruction input(Um_register c)
{
        Um_instruction word = three_register(IN, 0, 0, c);
        
        return word;
}

/* Functions for working with streams */

static inline void append(Seq_T stream, Um_instruction inst)
{
        assert(sizeof(inst) <= sizeof(uintptr_t));
        Seq_addhi(stream, (void *)(uintptr_t)inst);
}

const uint32_t Um_word_width = 32;

void Um_write_sequence(FILE *output, Seq_T stream)
{
        assert(output != NULL && stream != NULL);
        int stream_length = Seq_length(stream);
        for (int i = 0; i < stream_length; i++) {
                Um_instruction inst = (uintptr_t)Seq_remlo(stream);
                for (int lsb = Um_word_width - 8; lsb >= 0; lsb -= 8) {
                        fputc(Bitpack_getu(inst, 8, lsb), output);
                }
        }
      
}


/* Unit tests for the UM */

void build_halt_test(Seq_T stream)
{
        append(stream, halt());
}

/* test that puts halt instruction + a bunch of others
* (if anything outputs = BAD!!) */
void build_verbose_halt_test(Seq_T stream)
{
        append(stream, halt());
        append(stream, loadval(r1, 'B'));
        append(stream, output(r1));
        append(stream, loadval(r1, 'a'));
        append(stream, output(r1));
        append(stream, loadval(r1, 'd'));
        append(stream, output(r1));
        append(stream, loadval(r1, '!'));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
}

/* test that adds ascii 60 + 4 and prints it (@ symbol)*/
void build_add_test(Seq_T stream)
{     
        append(stream, loadval(r2, 60));
        append(stream, loadval(r3, 4)); 
        append(stream, add(r1, r2, r3));
        append(stream, output(r1)); 
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1)); 
        append(stream, halt()); 
        
}

/* test that LITERALLY PRINTS SIX */
void build_print_digit(Seq_T stream)
{
        append(stream, loadval(r1, '6'));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
        append(stream, halt());
}

/* CMOV that actually CMOV's (meets 0 condition) */
void build_cmov_test(Seq_T stream)
{
        append(stream, loadval(r1, '0')); // put a 0 in register 1
        append(stream, loadval(r2, 'X')); // put an X in register 5
        append(stream, cmov(r3, r2, r1)); // if r1 != 0, r2 --> r3
        append(stream, output(r3)); // LITERALLY OUTPUTS X
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1)); 
        append(stream, halt());

}

/* DIV TEST ON CHARACTERS*/
void build_char_div_test(Seq_T stream)
{     
        append(stream, loadval(r2, 'z'));
        append(stream, loadval(r3, 1)); 
        append(stream, div(r1, r2, r3));
        append(stream, output(r1)); // should output 4
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1)); 
        append(stream, halt());    
}

/* DIV TEST ON OUT OF BOUNDS VALS */
void build_OOB_div_test(Seq_T stream)
{     
        append(stream, loadval(r2, 1000));
        append(stream, loadval(r3, 2)); 
        append(stream, div(r1, r2, r3));
        append(stream, output(r1)); 
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1)); 
        append(stream, halt()); 
        
}

/* MULT TEST ON CHARACTERS*/
void build_char_mult_test(Seq_T stream)
{     
        append(stream, loadval(r2, 'a'));
        append(stream, loadval(r3, 2)); 
        append(stream, mul(r1, r2, r3));
        append(stream, output(r1)); // should output 4
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1)); 
        append(stream, halt());    
}

/* MULT TEST ON OUT OF BOUNDS VALS */
void build_OOB_mult_test(Seq_T stream)
{     
        append(stream, loadval(r2, 'b'));
        append(stream, loadval(r3, 's')); 
        append(stream, mul(r1, r2, r3));
        append(stream, output(r1)); 
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1)); 
        append(stream, halt()); 
        
}

/* NAND test on nonzero numbers (should be true)*/
void build_NAND_nonzero(Seq_T stream)
{     
        append(stream, loadval(r2, 6));
        append(stream, loadval(r3, 10)); 
        append(stream, nand(r1, r2, r3));
        //append(stream, output(r1));
        // append(stream, loadval(r1, '\n'));
        // append(stream, output(r1)); 
        append(stream, halt()); 
        
}

/* NAND test on two zero's (should be false)*/
void build_NAND_zero(Seq_T stream)
{     
        append(stream, loadval(r2, 0));
        append(stream, loadval(r3, 0)); 
        append(stream, nand(r1, r2, r3));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1)); 
        append(stream, halt()); 
        
}

/* maps a segment, stores a value in that segment, then
* loads that value from the segment into register */
void build_map_store_load(Seq_T stream)
{
        append(stream, loadval(r2, 10));
        append(stream, map(r1, r2)); // m[r1], 10 word segment
        append(stream, loadval(r3, 'B')); // letter to store
        append(stream, loadval(r4, 5)); // offset
        append(stream, sstore(r1, r4, r3)); // store B in m[r1][r4]
        append(stream, sload(r5, r1, r4));
        append(stream, output(r5));
        append(stream, sload(r5, r1, r4));
        append(stream, output(r5));
        append(stream, loadval(r5, '\n'));
        append(stream, output(r5)); 
        append(stream, halt());
}

// /* maps a segment then unmaps that segment */
void build_map_unmap(Seq_T stream)
{
        append(stream, loadval(r1, 10));
        for (int i = 0; i < 100; i++) {
                append(stream, map(r2, r1));
                append(stream, unmap(r2));
        }
        append(stream, halt());
}

/* prompts for input, then outputs the provided input */
void build_input(Seq_T stream)
{
        append(stream, input(r1));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
        append(stream, halt());
}

/* prompts for input, then outputs the provided input */
void build_map_simple(Seq_T stream)
{
        append(stream, loadval(r1, 10));
        append(stream, map(r2, r1));
        append(stream, output(r2));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
        append(stream, halt());
}

/* maps a segment, then loads this segment as
*  the program */
void build_load_prog(Seq_T stream)
{
        append(stream, loadval(r1, 10));
        append(stream, map(r2, r1));
        append(stream, loadval(r3, 5));
        append(stream, loadp(r2, r3));
        append(stream, halt());
}

/* load multiple programs */
void build_load_multiple(Seq_T stream)
{
        append(stream, loadval(r1, 'X'));
        append(stream, output(r1)); //instruction 
        append(stream, loadval(r2, 0)); // segment
        append(stream, loadval(r3, 2)); // offset
        append(stream, loadp(r2, r3)); // should go back 
        append(stream, halt());
}

/* load program and segmented load */
void build_load_PS(Seq_T stream)
{
        append(stream, loadval(r1, 'X')); 
        append(stream, loadval(r2, 0)); // segment
        append(stream, loadval(r3, 5)); // offset
        append(stream, loadp(r2, r3));
        append(stream, output(r1)); // 4
        append(stream, loadval(r1, 'Z')); // 5
        append(stream, output(r1)); // 6
        append(stream, sload(r4, r2, r3));
        append(stream, halt());
}


