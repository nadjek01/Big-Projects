/* transform.h
*
* by Ayah Harper and Nana Adjekum, 10/20/23
*
* This file defines the interfaces of the transform module, which comprises 
* step (4) of compression described in the arith spec */

#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <a2methods.h>
#include <a2blocked.h>
#include <a2plain.h>
#include <uarray2b.h>
#include <uarray2.h>

UArray2_T shrinkToTransform(UArray2b_T CVfloats);

#endif