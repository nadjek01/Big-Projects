/* detransform.h
*
* by Ayah Harper and Nana Adjekum 10/20/23
*
* This file contains the interface for the detransform module which handles 
* steps (8), (9) and (10) of decompression in the arith spec.
*/

#ifndef DETRANSFORM_H_INCLUDED
#define DETRANSFORM_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <a2methods.h>
#include <a2blocked.h>
#include <uarray2b.h>
#include <uarray2.h>

UArray2b_T growToTransform(UArray2_T CodeWords);

#endif