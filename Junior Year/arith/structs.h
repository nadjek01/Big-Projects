/* structs.h
*
* by Ayah Harper and Nana Adjekum, 10/23/23
*
* This file contains all of the struct definitions for structs commonly used 
* throughout the program. 
*
*/
#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct RGB_float
{
        float red, green, blue;

} RGB_float;

typedef struct CV_float {
        float y, pb, pr;
} CV_float;

typedef struct CodeWord {
        unsigned Pb, Pr, a;
        signed b, c, d;
} CodeWord;

typedef struct FourPixelFloat {
        float Pb, Pr;
        float yVals[4];
        int y_index;
} FourPixelFloat;

#endif