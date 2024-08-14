#ifndef RESTORATION_H
#define RESTORATION_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "except.h"
#include "readaline.h"


extern Except_T Open_E;
extern Except_T OverOne_E;
extern Except_T NoInput_E;
extern Except_T NullParam_E;
extern Except_T File_E;
extern Except_T ReadMalloc_E;

char *realloc_string(char *linedubp, int bytes_alloc);
void printImageRaster(int **imageRaster, int currentHeight, 
                        int rasterWidth, int *firstLine);
int** extendImageRaster(int** imageRaster, int *digits, int currentIndex);
int splitDigitsAndNonDigits(const char *line, int *digits, 
                            char *nonDigits, int line_length);
void free_digits(const void *key, void **value, void *cl);
int* deepcopy(const int* src, size_t len);

#endif
