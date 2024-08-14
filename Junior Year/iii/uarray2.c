/*
 * HW: iii
 * File: uarray2.c
 * Names: Nana Adjekum (nadjek01) and Harsh Sinha (hsinha02)
 * Date: 28-Sept
 * Purpose: Using Hanson 1D Uarray set up a Uarray2 interface
 * for 2d UArrays
*/
#include <stdlib.h>
#include <stdbool.h>
#include "assert.h"
#include "mem.h"
#include "uarray.h"
#include "uarray2.h"

#define T UArray2_T

struct T
{
    int width;
    int height;
    int size;
    UArray_T all_rows;
};

int UArray2_height(T uarray2)
{
    assert(uarray2);
    return uarray2->height;
}

int UArray2_width(T uarray2)
{
    assert(uarray2);
    return uarray2->width;
}

int UArray2_size(T uarray2)
{
    assert(uarray2);
    return uarray2->size;
}

T UArray2_new(int width, int height, int size)
{
    assert(width > 0 && height > 0 && size > 0);
    T uarray2 = (T)malloc(sizeof(*uarray2));
    assert(uarray2);

    uarray2->width = width;
    uarray2->height = height;
    uarray2->size = size;
    //container array
    uarray2->all_rows = UArray_new(height, sizeof(UArray_T));

    //array of width
    for (int row = 0; row < height; row++) {
        UArray_T *currRow = UArray_at(uarray2->all_rows, row);
        *currRow = UArray_new(width, size);
    }
    assert(uarray2);

    return uarray2;
}

void UArray2_free(T *uarray2)
{
    assert(uarray2);
    assert(*uarray2);

    UArray_T all_rowsp = (*uarray2)->all_rows;
    int height = (*uarray2)->height;

    for (int i = 0; i < height; i++) {
        UArray_T *curRow = UArray_at(all_rowsp, i);
        UArray_T curr = *curRow;
        UArray_free(&curr);
    }

    UArray_free(&all_rowsp);
    FREE(*uarray2);
}

void *UArray2_at(T uarray2, int col, int row)
{
    assert(uarray2 && col >= 0 && row >= 0);
    UArray_T *currArray = UArray_at(uarray2->all_rows, row);
    return UArray_at(*currArray, col);
}

void UArray2_map_row_major(T uarray2,
                           void apply(int i, int j, T uarray2,
                                      void *elem, void *cl),
                           void *cl)
{
    assert(uarray2 != NULL);
    int height = uarray2->height;
    int width = uarray2->width;

    for (int row = 0; row < height; row++) {
        /*pointer to current row*/
        UArray_T *curRow = UArray_at(uarray2->all_rows, row);
        /*dereference result to pass into apply*/
        UArray_T curr = *curRow;
        for (int col = 0; col < width; col++)
        {
            apply(col, row, uarray2, UArray_at(curr, col), cl);
        }
    }
}

void UArray2_map_col_major(T uarray2,
                           void apply(int col, int row, T a,
                                      void *elem, void *cl),
                           void *cl)
{
    assert(uarray2 != NULL);
    int height = uarray2->height;
    int width = uarray2->width;

    for (int col = 0; col < width; col++) {
        for (int row = 0; row < height; row++) {
            /*pointer to current row*/
            UArray_T *currR = UArray_at(uarray2->all_rows, row);
            /*dereference result to pass into apply*/
            UArray_T curr = *currR;
            apply(col, row, uarray2, UArray_at(curr, col), cl);
        }
    }
}

