/* convertandwrite.h
*
* by Ayah Harper and Nana Adjekum, 10/19/23
*
* This file contains the interface for the convertandwrite module, which 
* comprises steps (11), (12) and (13) of decompression in the arith spec.
*/

#ifndef CONVERTANDWRITE_H_INCLUDED
#define CONVERTANDWRITE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <uarray2b.h>

void convertandWrite(UArray2b_T cvModel);

#endif