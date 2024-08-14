#include <math.h>
#include "assert.h"
#include "mem.h"
#include <uarray.h>
#include "uarray2.h"
#include "uarray2b.h"
#include <stdio.h>  /* include so we can print diagnostics */

#define T UArray2b_T

struct T { /* represents a 2D array of cells each of size 'size' */
        int width, height;
        unsigned blocksize;
        unsigned size;
        UArray2_T blocks;
        /*
         * matrix of blocks, each blocksize * blocksize 
         *
         * matrix dimensions are width and height divided by blocksize,
         * rounded up
         *
         * a block is an Array_T of length blocksize * blocksize 
         * and size 'size'
         *
         * invariant relating cells in blocks to cells in the abstraction
         *  described in section on coordinate transformations below
         */
};

T UArray2b_new(int width, int height, int size, int blocksize)
{
        assert(blocksize > 0);
        T array;
        NEW(array);
        array->width  = width;
        array->height = height;
        array->size   = size;
        array->blocksize = blocksize;
        array->blocks = UArray2_new((width  + blocksize - 1) / blocksize,
                                    (height + blocksize - 1) / blocksize,
                                    sizeof(UArray_T));
        int xblocks = UArray2_width (array->blocks); 
        int yblocks = UArray2_height(array->blocks);
        for (int i = 0; i < xblocks; i++) {
                for (int j = 0; j < yblocks; j++) {
                        UArray_T *block = UArray2_at(array->blocks, i, j);
                        *block = UArray_new(blocksize * blocksize, size);
                }
        }
        return array;
}

void UArray2b_free(T *array2b)
{
        int i;
        assert(array2b && *array2b);
        T array = *array2b;
        int xblocks = UArray2_width (array->blocks);
        int yblocks = UArray2_height(array->blocks);
        assert(UArray2_size(array->blocks) == sizeof(UArray_T));
        for (i = 0; i < xblocks; i++) {
                for (int j = 0; j < yblocks; j++) {
                        UArray_T *p = UArray2_at(array->blocks, i, j);
                        UArray_free(p);
                }
        }
        UArray2_free(&(*array2b)->blocks);
        FREE(*array2b);
}

T UArray2b_new_64K_block(int width, int height, int size)
{
        int blocksize = (int) floor(sqrt((double) (64 * 1024)
                                         / (double) size));
        if (blocksize == 0) {
                blocksize = 1;
        }
        /*  assert as big as possible */
        assert((blocksize + 1) * (blocksize + 1) * size > 64 * 1024);
        if (size <= 64 * 1024) { /* but no bigger */
                assert(blocksize * blocksize * size <= 64 * 1024); 
        }
        return UArray2b_new(width, height, size, blocksize);
}

void *UArray2b_at(T array2b, int i, int j)
{
        assert(i >= 0 && j >= 0);
        /* avoid unused cells */
        assert(i < array2b->width && j < array2b->height);
        int b  = array2b->blocksize;
        int bx = i / b;   /* block x coordinate */
        int by = j / b;   /* block y coordinate */
        UArray_T *blockp = UArray2_at(array2b->blocks, bx, by);
        return UArray_at(*blockp, (i % b) * b + j % b);
}

void UArray2b_map(T array2b, 
                  void apply(int col, int row, T array2b,
                             void *elem, void *cl),
                  void *cl)
{
        assert(array2b);
        int       h      = array2b->height;
        int       w      = array2b->width;
        int       b      = array2b->blocksize;
        UArray2_T blocks = array2b->blocks;
        int       bw     = UArray2_width(blocks);
        int       bh     = UArray2_height(blocks);

        for (int bx = 0; bx < bw; bx++) {
                for (int by = 0; by < bh; by++) {
                        UArray_T *blockp = UArray2_at(blocks, bx, by);
                        UArray_T  block  = *blockp;
                        int       len    = UArray_length(block);
                        /* (i0, j0) correspond to upper left */
                        /* corner of block (bx, by)          */
                        int i0 = b * bx; 
                        int j0 = b * by; 
                        for (int cell = 0; cell < len; cell++) {
                                int i = i0 + cell / b;
                                int j = j0 + cell % b;
                                /* measured overhead 0.5% to 1.5% */
                                if (i < w && j < h) {
                                        apply(i, j, array2b, 
                                              UArray_at(block, cell), cl);
                                }
                        }
                }
        }
}

int UArray2b_height(T array2b)
{
        assert(array2b);
        return array2b->height;
}
int UArray2b_width(T array2b)
{
        assert(array2b);
        return array2b->width;
}

int UArray2b_size(T array2b)
{
        assert(array2b);
        return array2b->size;
}

int UArray2b_blocksize(T array2b)
{
        assert(array2b);
        return array2b->blocksize;
}