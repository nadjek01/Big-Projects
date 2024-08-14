/* bitpack.c
*
* by Ayah Harper and Nana Adjekum, 10/23/23
*
* This file defines the implementation of the bitpack.h interface, which 
* provides functions for width-testing, field-extraction and field-update on 
* 64-bit integers
*/

#include <stdbool.h>
#include <stdint.h>
#include <except.h>
#include <stdlib.h>
#include <stdio.h>
#include <bitpack.h>
#include <math.h>
#include <assert.h>
#include <except.h>

Except_T Bitpack_Overflow = { "Overflow packing bits" };

uint64_t leftshift(uint64_t value, unsigned shift_amt);
uint64_t rightshift(uint64_t value, unsigned shift_amt);
uint64_t complement(uint64_t value);

/********** Bitpack_fitssu ********
 *
 * width-test function to see if the unsigned integer n can be represented 
 * in "width" bits
 *
 * Parameters:
 *      uint64_t n:             unsigned 64-bit integer
 *      unsigned width:         number of bits to test
 *
 * Return: boolean
 *
 * Expects:
 *      n is an unsigned integer
 * Notes:
 *      none
 ************************/
bool Bitpack_fitsu(uint64_t n, unsigned width)
{
        if (width == 0) { return false; }

        /* determine the range of integers for "width" unsigned bits */
        uint64_t upper_bound = leftshift(1, width) - (uint64_t)1;

        /* test to see if n is within this range */
        return (n <= upper_bound);
}

/********** Bitpack_fitss ********
 *
 * width-test function to see if the signed integer n can be represented 
 * "width" signed bits
 *
 * Parameters:
 *      int64_t n:              signed 64-bit integer
 *      unsigned width:         number of bits to test
 *
 * Return: boolean
 *
 * Expects:
 *      n is a signed integer
 * Notes:
 *      none
 ************************/
bool Bitpack_fitss(int64_t n, unsigned width)
{
        if (width == 0) { return false; }
        
        /* determine the range of integers for "width" signed bits */
        int64_t lower_bound = (int64_t)-1 * leftshift(1, width - 1);
        int64_t upper_bound = leftshift(1, width - 1) - (uint64_t)1;

        /* test to see if n is within this range */
        return (n >= lower_bound && n <= upper_bound);
}

/********** Bitpack_getu ********
 *
 * field-extraction function to get the unsigned, "width"-bit value at position 
 * lsb in the provided word
 *
 * Parameters:
 *      uint64_t word:          64-bit integer to extract from
 *      unsigned width:         width (# of bits) of the field
 *      unsigned lsb:           lsb of the field within word
 *
 * Return: the extracted, 64-bit unsigned value
 *
 * Expects:
 *      width is less than or equal to 64 bits (out of bounds)
 *      width + lsb does not exceed 64 bits (out of bounds)
 * Notes:
 *      a 0-bit field contains the integer 0
 ************************/
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb)
{
        if (width == 0) { return 0; }
        assert(width <= 64);
        assert((width + lsb) <= 64);

        /* create a mask of all 1's */
        uint64_t mask = complement(0); 

        /* put 0's everywhere else but the desired field */
        mask = leftshift(rightshift(mask, 64 - width), lsb); 

        /* AND the word with the mask, and it down to the 0's place */
        uint64_t extract = rightshift(word & mask, lsb);

        return extract;
}

/********** Bitpack_gets ********
 *
 * field-extraction function to get the signed, "width"-bit value at position 
 * lsb in the provided word
 *
 * Parameters:
 *      uint64_t word:          64-bit integer to extract from
 *      unsigned width:         width (# of bits) of the field
 *      unsigned lsb:           lsb of the field within word
 *
 * Return: the extracted, 64-bit signed value
 *
 * Expects:
 *      width is less than or equal to 64 bits (out of bounds)
 *      width + lsb does not exceed 64 bits (out of bounds)
 * Notes:
 *      a 0-bit field contains the integer 0
 ************************/
int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb)
{
        if (width == 0) { return 0; }
        assert(width <= 64);
        assert((width + lsb) <= 64);

        /* create a mask of all 1's */
        uint64_t mask = complement(0); 

        /* put 0's everywhere else but the desired field */
        mask = leftshift(rightshift(mask, 64 - width), lsb); 

        /* AND the word with the mask, and it down to the 0's place */
        int64_t extract = rightshift(word & mask, lsb);

        /* if the sign bit is 1, flip all the bits and add 1 */
        if (rightshift(extract, width - 1)) {
                int64_t flipped = -1 * ((complement(extract) & 
                rightshift(mask, lsb)) + (uint64_t)1);
                return flipped;
        }

        return extract;
}

/********** Bitpack_newu ********
 *
 * field-update function to insert a width-bit unsigned value at position lsb 
 * in the provided word
 *
 * Parameters:
 *      uint64_t word:          64-bit integer to update
 *      unsigned width:         width (# of bits) of the field
 *      unsigned lsb:           lsb of the field within word
 *      uint64_t value          64-bit unsigned value to insert
 *
 * Return: the new word with unsigned "value" inserted at position lsb
 *
 * Expects:
 *      width is less than or equal to 64 bits (out of bounds)
 *      width + lsb does not exceed 64 bits (out of bounds)
 *      provided value can be represented in "width" unsigned bits
 * Notes:
 *      a 0-bit field contains the integer 0
 ************************/
uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, 
uint64_t value)
{
        if (width == 0) { return 0; }
        assert(width <= 64);
        assert((width + lsb) <= 64);

        /* can the provided fit into "width" bits? */
        if (!Bitpack_fitsu(value, width)) {
                RAISE(Bitpack_Overflow);
        }

        uint64_t new_word = word;

        /* create a mask with 0's ONLY in the desired field */
        uint64_t mask = complement(0); 
        mask = leftshift(rightshift(mask, 64 - width), lsb);
        mask = complement(mask);

        /* clear out the current field */
        new_word = new_word & mask;

        /* shift the value to the left by lsb bits to align with the field */
        value = leftshift(value, lsb);

        /* OR the value with the word to put the new value into the field */
        new_word = new_word | value;

        return new_word;
}

/********** Bitpack_news ********
 *
 * field-update function to insert a width-bit signed value at position lsb 
 * in the provided word
 *
 * Parameters:
 *      uint64_t word:          64-bit integer to update
 *      unsigned width:         width (# of bits) of the field
 *      unsigned lsb:           lsb of the field within word
 *      int64_t value           64-bit signed value to insert
 *
 * Return: the new word with signed "value" inserted at position lsb
 *
 * Expects:
 *      width is less than or equal to 64 bits (out of bounds)
 *      width + lsb does not exceed 64 bits (out of bounds)
 *      provided value can be represented in "width" unsigned bits
 * Notes:
 *      a 0-bit field contains the integer 0
 ************************/

uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb, 
int64_t value)
{
        if (width == 0) { return 0; }
        assert(width <= 64);
        assert((width + lsb) <= 64);

        /* can the provided fit into "width" bits? */
        if (!Bitpack_fitss(value, width)) {
                RAISE(Bitpack_Overflow);
        }

        uint64_t new_word = word;

        /* create a mask with 0's ONLY in the desired field */
        uint64_t mask = complement(0); 
        mask = leftshift(rightshift(mask, 64 - width), lsb);
        mask = complement(mask);

        /* clear out the current field */
        new_word = new_word & mask;

        /* cast value to an unsigned */
        value = (uint64_t)value;

        /* left shift to get all 0's on the low end */
        value = leftshift(value, (64 - width));

        /* right shift to get all 0's on the high end */
        value = rightshift(value, (64 - width));

        /* shift the value to the left by lsb bits to align with the field */
        value = leftshift(value, lsb);

        /* OR the value with the word to put the new value into the field */
        new_word = new_word | value;

        return new_word;
}

/********************** HELPER FUNCTIONS ***********************/

/********** leftshift ********
 *
 * helper function that performs an arithmetic left shift on a 64-bit 
 * unsigned value
 *
 * Parameters:
 *      uint64_t value:             unsigned 64-bit integer to shift
 *      unsigned shift_amt:         amount to shift by
 *
 * Return: 64-bit integer shifted leftwards by [shift_amt] bits
 *
 ************************/
uint64_t leftshift(uint64_t value, unsigned shift_amt) 
{
        if (shift_amt == 64) { return value; }
        return value << shift_amt;
}

/********** rightshift ********
 *
 * helper function that performs an arithmetic right shift on a 64-bit 
 * unsigned value
 *
 * Parameters:
 *      uint64_t value:             unsigned 64-bit integer to shift
 *      unsigned shift_amt:         amount to shift by
 *
 * Return: 64-bit integer shifted rightwards by [shift_amt] bits
 *
 ************************/
uint64_t rightshift(uint64_t value, unsigned shift_amt)
{
        if (shift_amt == 64) { return value; }
        return value >> shift_amt;
}

/********** complement ********
 *
 * helper function that performs a bitwise complement on the provided 64-bit 
 * value
 *
 * Parameters:
 *      uint64_t value:             unsigned 64-bit integer to complemented
 *
 * Return: 64-bit integer with all bits complemented (0 -> 1, 1->0)
 *
 ************************/
uint64_t complement(uint64_t value)
{
        return (~value);
}
