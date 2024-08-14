/* readcodewords.h
*
* by Ayah Harper and Nana Adjekum, 10/19/23
*
* This file contains the interface for the readcodewords module, which covers 
* steps (6) and (7) of the decompressor in the arith spec.
*/

#ifndef READCODEWORDS_H_INCLUDED
#define READCODEWORDS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <uarray2.h>

UArray2_T readCodeWords(FILE *PBMfile);

#endif