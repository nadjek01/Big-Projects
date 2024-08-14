/*
 * HW: iii
 * File: bit2.c
 * Names: Nana Adjekum (nadjek01) and Harsh Sinha (hsinha02)
 * Date: 28-Sept
 * Purpose: Using Hansen Bit interface set up a Bit2 interface
 * for 2d bit arrays
*/
#include <stdlib.h>
#include <stdbool.h>
#include "assert.h"
#include "mem.h"
#include "uarray.h"
#include "bit2.h"
#include "bit.h"

#define T Bit2_T

struct T
{
    int width;
    int height;
    UArray_T all_rows;
};

int Bit2_height(T bitarray2)
{
    assert(bitarray2);
    return bitarray2->height;
}


int Bit2_width(T bitarray2)
{
    assert(bitarray2);
    return bitarray2->width;
}

T Bit2_new(int width, int height)
{
    assert(width > 0 && height > 0);
    T bitarray2 = (T)malloc(sizeof(*bitarray2));
    assert(bitarray2);

    bitarray2->width = width;
    bitarray2->height = height;

    bitarray2->all_rows = UArray_new(height, sizeof(Bit_T));

    for (int row = 0; row < height; row++) {
        Bit_T *currRow = UArray_at(bitarray2->all_rows, row);
        *currRow = Bit_new(width);
    }
    assert(bitarray2);

    return bitarray2;
}

void Bit2_free(T *bitarray2)
{
    assert(bitarray2);
    assert(*bitarray2);

    int height = (*bitarray2)->height;

    for (int i = 0; i < height; i++) {
        Bit_T *curr = UArray_at((*bitarray2)->all_rows, i);
        Bit_free(curr);
    }
    UArray_free(&(*bitarray2)->all_rows);
    FREE(*bitarray2);
}

int Bit2_get(T bitarray2, int i, int j)
{
    assert(bitarray2 != NULL);
    assert(i >= 0);
    assert(i <= bitarray2->width);
    assert(j >= 0);
    assert(j <= bitarray2->height);
    Bit_T *currBit = UArray_at(bitarray2->all_rows, j);
    Bit_T currB = *currBit;
    return Bit_get(currB, i);
}

int Bit2_put(T bitarray2, int i, int j, int bit)
{
    assert(bitarray2 && i >= 0 && j >= 0);
    Bit_T *currBit = UArray_at(bitarray2->all_rows, j);
    Bit_T currB = *currBit;
    return Bit_put(currB, i, bit);
}

void Bit2_map_row_major(T bitarray2,
                        void apply(int row, int col, T bitarray2,
                                   int bit, void *cl),
                        void *cl)
{
    assert(bitarray2);
    int height = bitarray2->height;
    int width = bitarray2->width;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int curr = Bit2_get(bitarray2, col, row);
            apply(col, row, bitarray2, curr, cl);
        }
    }
}

void Bit2_map_col_major(T bitarray2,
                        void apply(int col, int row, T a,
                                   int bit, void *cl),
                        void *cl)
{
    assert(bitarray2);
    int height = bitarray2->height;
    int width = bitarray2->width;

    for (int col = 0; col < width; col++) {
        for (int row = 0; row < height; row++) {
            int curr = Bit2_get(bitarray2, col, row);
            apply(col, row, bitarray2, curr, cl);
        }
    }
}
