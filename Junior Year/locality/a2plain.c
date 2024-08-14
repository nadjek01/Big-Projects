#include <string.h>

#include <a2plain.h>
#include "uarray2.h"

/************************************************/
/* Define a private version of each function in */
/* A2Methods_T that we implement.               */
/************************************************/

typedef A2Methods_UArray2 A2;

static A2 new(int width, int height, int size)
{
        
        return UArray2_new(width, height, size);
}

static A2Methods_UArray2 new_with_blocksize(int width, int height, int size,
                                            int blocksize)
{
        (void) blocksize;
        return UArray2_new(width, height, size);
}
/* TODO: ...many more private (static) definitions follow */

/* static void a2free(A2 * array2p)
 *
 * Purpose:  Frees the memory associated with the 2D array.
 * Parameters: array2p - A pointer to a pointer to the 2D array.
 * Return: 
 *      N/A
 * Expects: 
 *      N/A
 * 
*/
static void a2free(A2 * array2p)
{
        UArray2_free((UArray2_T *) array2p);
}

/* static int height(A2 array2)
 *
 * Purpose: Returns the height (number of rows) of the 2D array.
 * Parameters: array2 - The 2D array.
 * Return: 
 *      height of UArray passed in
 * Expects:
 *      Throws whatever is caught in UArray
 * 
 * 
*/
static int height(A2 array2)
{
        return UArray2_height(array2);
}

/* static int size(A2 array2)
 *
 * Purpose: Returns the total number of elements in the 2D array.
 * Parameters: array2 - The 2D array.
 * Return: 
 *      size of UArray passed in
 * Expects: N/A
 *      Whatever is thrown by UArray
 * 
*/
static int size(A2 array2)
{
        return UArray2_size(array2);
}

/* static int width(A2 array2)
 *
 * Purpose: Returns the width (number of columns) of the 2D array.
 * Parameters: array2 - The 2D array.
 * Return:
 *      width of UArray passed in
 * Expects:
 *      Whatever is thrown by UArray
 * 
 * 
*/
static int width(A2 array2)
{
        return UArray2_width(array2);
}

/* static int blocksize(A2 array2)
 *
 * Purpose: Returns the block size (assumed to be 1 in the provided code).
 * Parameters: array2 - The 2D array.
 * Return: 1 (no such thing as blocksize in UArray2)
 * Expects: N/A
 * 
 * 
*/
static int blocksize(A2 array2)
{
        (void) array2;
        return 1;
}


/* static A2Methods_Object *at(A2 array2, int i, int j)
 *
 * Purpose: Returns a pointer to the element at position (i, j) in the 2D array.
 * Parameters:
 *      array2 - The 2D array.
 *       i - Row index.
 *       j - Column index.
 * Returns:
 *      object at index of UArray passed in
 * Expects:
 *      Whatever is thrown by UArray2b
 * 
*/
static A2Methods_Object *at(A2 array2, int i, int j)
{
        return UArray2_at(array2, i, j);
}


typedef void applyfun(int i, int j, UArray2_T array2b, void *elem, void *cl);

/* static void map_row_major(A2 uarray2, A2Methods_applyfun apply, void *cl)
 *
 * Purpose: Applies the given function apply to each element of the 2D array 
            in row-major order.
 * Parameters:
 *      uarray2 - The 2D array.
 *      apply - Function pointer to the apply function.
 *      cl - Client data.
 * Returns:
 *      N/A
 * Expects:
 *      Whatever is thrown by UArray2
 * 
*/
static void map_row_major(A2 uarray2, A2Methods_applyfun apply, void *cl)
{
        UArray2_map_row_major(uarray2, (UArray2_applyfun*)apply, cl);
}

/*static void map_col_major(A2 uarray2, A2Methods_applyfun apply, void *cl)
 * Purpose: Applies the given function apply to each element of the 2D array 
            in column-major order.
 * Parameters:
 *      uarray2 - The 2D array.
 *      apply - Function pointer to the apply function.
 *      cl - Client data.
 * Returns:
 *      N/A
 * Expects:
 *      Whatever is thrown in UArray2
 * 
*/
static void map_col_major(A2 uarray2, A2Methods_applyfun apply, void *cl)
{
        UArray2_map_col_major(uarray2, (UArray2_applyfun*)apply, cl);
}

/* A structure to hold a small apply function and its client data.*/
struct small_closure {
        A2Methods_smallapplyfun *apply; 
        void                    *cl;
};

/* static void apply_small(int i, int j, UArray2_T uarray2, void *elem, 
 *                                                              void *vcl)
 * Purpose: Applies a small apply function to each element of the 2D array.
 * Parameters:
 *      i, j - Indices.
 *      uarray2 - The 2D array.
 *      elem - Element at position (i, j).
 *      vcl - Pointer to a struct small_closure.
 * Returns:
 *      N/A
 * Expects:
 *      Whatever is thrown in UArray2
*/
static void apply_small(int i, int j, UArray2_T uarray2,
                        void *elem, void *vcl)
{
        struct small_closure *cl = vcl;
        (void)i;
        (void)j;
        (void)uarray2;
        cl->apply(elem, cl->cl);
}

/* static void small_map_row_major(A2 a2, A2Methods_smallapplyfun apply,
                                                                void *cl)
 * Purpose: Applies the small apply function to each element of the 
            2D array in row-major order.
 * Parameters:
 *      a2 - The 2D array.
 *      apply - Small apply function.
 *      cl - Client data.
 * Returns:
 *      N/A
 * Expects:
 *      Whatever is thrown in UArray2
 * 
 * 
*/
static void small_map_row_major(A2 a2, A2Methods_smallapplyfun apply,
                                void *cl)
{
        struct small_closure mycl = { apply, cl };
        UArray2_map_row_major(a2, apply_small, &mycl);
}

/* static void small_map_col_major(A2 a2, A2Methods_smallapplyfun apply, 
                                                               void *cl)
 * Purpose: Applies the small apply function to each element of the 2D 
             array in col-major order.
 * Parameters:
 *      a2 - The 2D array.
 *      apply - Small apply function.
 *      cl - Client data.
 * Return:
 *      N/A
 * Expects:
 *      Whatever is thrown in UArray2
 * 
*/
static void small_map_col_major(A2 a2, A2Methods_smallapplyfun  apply,
                                void *cl)
{
        struct small_closure mycl = { apply, cl };
        UArray2_map_col_major(a2, apply_small, &mycl);
}

/*holds function pointers for various A2 methods.*/
static struct A2Methods_T uarray2_methods_plain_struct = {
        new,
        new_with_blocksize,
        a2free,
        width,
        height,
        size,
        blocksize,
        at,
        map_row_major,                   // map_row_major
        map_col_major,                   // map_col_major
        NULL,
        map_row_major,                   // map_default
        small_map_row_major,             // small_map_row_major
        small_map_col_major,             // small_map_col_major
        NULL,
        small_map_row_major,                            // small_map_default
};

// finally the payoff: here is the exported pointer to the struct

A2Methods_T uarray2_methods_plain = &uarray2_methods_plain_struct;
