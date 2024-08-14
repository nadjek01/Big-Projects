/* writecodewords.h
*
* by Ayah Harper and Nana Adjekum, 10/19/23
*
* This file contains the interface for writecodewords module, which comprises
* step (5) of compression detailed in the arith spec.
*/

#ifndef WRITECODEWORDS_H_INCLUDED
#define WRITECODEWORDS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <uarray2.h>

void writeCodeWords(UArray2_T CodeWordStructs);

#endif