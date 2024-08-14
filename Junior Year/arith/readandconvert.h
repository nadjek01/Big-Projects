/* readandconvert.h
*
* by Ayah Harper and Nana Adjekum, 10/20/23
*
* This file defines the interface for the readandconvert module, which covers
* steps (1), (2) and (3) of the compressor in the arith spec.
*/

#ifndef READANDCONVERT_H_INCLUDED
#define READANDCONVERT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <a2methods.h>
#include <a2blocked.h>
#include <uarray2b.h>

UArray2b_T readandConvert(FILE *file);

#endif