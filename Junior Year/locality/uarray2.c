/* HW3 Locality
 * File Name: UArray2.h
 * File Purpose:
 *      This in the implementation for UArray2 
 * 
 * Author: Comp40 Solutions (Noah Mendelson)
 *
 * Note: 
 *      Though we implemented a UArray2 in the
 *      past homework, we considered it a better
 *      decision to use the solutions as they
 *      are most likely to have been better
 *      implemented in regards to memory leaks
 *      and other bugs
*/

#include <stdlib.h>
#include <stdio.h>
#include <uarray2.h>

#include "assert.h"
#include "mem.h"
#include "uarray.h"

#define T UArray2_T

/* 
 * Element (i, j) in the world of ideas maps to
 * rows[j][i] where the square brackets stand for access
 * to a Hanson UArray_T
 */
struct T {
        int width, height;
        int size;
        UArray_T rows; /* UArray_T of 'height' UArray_Ts,
                          each of length 'width' and size 'size' */
};

//private functions
/* 
 * Function Name: UArray_T row
 * Parameters: a uarray (a) and an integer (j)
 * Returns: a pointer to the 'extracted' row
 * Purpose:
 *      Use Hanson at function to take a given index
 *      and extract the row at said index
 * Exceptions:
 *      None
 *
*/
static inline UArray_T row(T a, int j) 
{    
        
    UArray_T *prow = UArray_at(a->rows, j);
    return *prow;
}

/* 
 * Function Name: int is_ok
 * Parameters: a uarray (a)
 * Purpose:
 *      N/A
 * Exceptions:
 *      None
 *
*/
static int is_ok(T a)
{
    return a && UArray_length(a->rows) == a->height &&
    UArray_size(a->rows) == sizeof(UArray_T) &&
    (a->height == 0 || (UArray_length(row(a, 0)) == a->width
                        && UArray_size(row(a, 0)) == a->size));
}

//public functions
//A. Memory Management
/* UArray2_new
 * 
 * Purpose: 
 *      To initialize the 2 dimensional array. Allocates the proper amount
 *      of memory to hold the entire array and elements. 
 *
 * Parameters:
 *      int width: Number of columns in the array
 *      int height: Number of rows in the array
 *      int size: Size of the individual elements
 *
 * Return: 
 *      returns a pointer to a UArray2_T struct
 *
 * Expects:
 *      Width and height are non-negative numbers
 *      Size is a positive number
 *
 * Notes:
 *      Will CRE if malloc fails
 *      Will CRE if width or height are negative or size is non-positive
 */
T UArray2_new(int width, int height, int size)
{
        int i;  /* interates over row number */
        T array;
        NEW(array);
        array->width  = width;
        array->height = height;
        array->size   = size;
        array->rows   = UArray_new(height, sizeof(UArray_T));
        for (i = 0; i < height; i++) {
                UArray_T *rowp = UArray_at(array->rows, i);
                *rowp = UArray_new(width, size);
        }
        assert(is_ok(array));
        return array;
}


/* UArray2_free
 * 
 * Purpose:  
 *      to free all of the previously allocated memory for uarray2
 *
 * Parameters:  
 *      T uarray2: Pointer to the already initialized UArray2_T struct
 *      
 * Return: 
 *      nothing
 *      
 * Expects:
 *      expects uarray2 to not be NULL
 *      
 * Notes:
 *      Will CRE if uarray2 is NULL
 *      sets uarray2 to NULL after freeing memory
 */               
void UArray2_free(T *array2)
{
    int i;
    assert(array2 && *array2);
    for (i = 0; i < (*array2)->height; i++) {
        UArray_T p = row(*array2, i);
        UArray_free(&p);
    }
    UArray_free(&(*array2)->rows);
    FREE(*array2);
}

//B. Location function
/* UArray2_at
 * 
 * Purpose:  
 *      Give the client access to a specific index in the 2D array. The client 
 *      can then cast the returned void pointer and then dereference said cast
 *      pointer to manipulate the data
 *
 * Parameters:  
 *      T uarray2: Pointer to the already initialized UArray2_T struct
 *      int i: the column of the desired index that the client
 *                       is trying to access
 *      int j: the row of the desired index that the client
 *                       is trying to access
 *
 * Return: 
 *      returns a void pointer that points to the data at the given index
 *
 * Expects:
 *      col and row to be non-negative
 *      expects uarray2 to not be NULL
 *      col to be less than width and row to be less than height
 *
 * Notes:
 *      Will CRE if col or row are negative
 *      Will CRE if uarray2 is NULL
 *      Will CRE if col >= than width or row >= height
 */
void *UArray2_at(T array2, int i, int j)
{
        assert(array2);
        return UArray_at(row(array2, j), i);
}

/* UArray2_height
 * 
 * Purpose:  
 *      return the height (number of rows) in the UArray2_T
 *
 * Parameters:  
 *      T uarray2: Pointer to the already initialized UArray2_T struct
 *      
 * Return: 
 *      the height (number of rows) in the UArray2_T
 *      
 * Expects:
 *      expects uarray2 to not be NULL
 *      
 * Notes:
 *      Will CRE if uarray2 is NULL
 *      
 */
int UArray2_height(T array2)
{
    assert(array2);
    return array2->height;
}

/* UArray2_width
 * 
 * Purpose:  
 *      return the width (number of columns) in the UArray2_T
 *
 * Parameters:  
 *      T uarray2: Pointer to the already initialized UArray2_T struct
 *      
 * Return: 
 *      the width (number of columns) in the UArray2_T
 *      
 * Expects:
 *      expects uarray2 to not be NULL
 *      
 * Notes:
 *      Will CRE if uarray2 is NULL
 *      
 */
int UArray2_width(T array2)
{
    assert(array2);
    return array2->width;
}

/* UArray2_size
 * 
 * Purpose:  
 *      return the size of one element in the UArray2_T
 *
 * Parameters:  
 *      T uarray2: Pointer to the already initialized UArray2_T struct
 *      
 * Return: 
 *      returns the size of one element in the UArray2_T
 *      
 * Expects:
 *      expects uarray2 to not be NULL
 *      
 * Notes:
 *      Will CRE if uarray2 is NULL
 *      
 */
int UArray2_size(T array2)
{
    assert(array2);
    return array2->size;
}

//D. Mapping functions
/* UArray2_map_row_major
 * 
 * Purpose:  
 *      Iterates through every index of uarray2 and calls an apply 
 *      function for each element in the array. Column indices vary more 
 *      rapidly than the row indicies.
 *      
 * Parameters:  
 *      T uarray2: Pointer to the already initialized UArray2_T struct
 *      void apply(): Function to be called on every element
 *              int i: column of the element that apply function is acting on
 *              int j: row of the element that apply function is acting on
 *              T uarray2: Pointer to the already initialized UArray2_T struct
 *              void *elem: Pointer to a single element of the uarray2
 *              void *cl: Pointer to a closure argument
 *      void *cl: Pointer to a closure argument
 *      
 * Return: 
 *      Nothing directly but may alter the uarray2 being pointed to and the
 *      other pointer variables being passed in
 *      
 * Expects:
 *      uarray2 to not be NULL
 *      *cl to be casted a type other than void
 *      
 * Notes:
 *      Will CRE if uarray2 is NULL
 *      
 */
void UArray2_map_row_major(T array2, 
                           void apply(int i, int j, T array2, 
                                      void *elem, void *cl), 
                           void *cl)
{
        assert(array2);
        int h = array2->height;  /* keeping height and width in registers */
        int w = array2->width;   /* avoids extra memory traffic           */
        for (int j = 0; j < h; j++) {
                /* don't want row/UArray_at in inner loop */
                UArray_T thisrow = row(array2, j); 
                for (int i = 0; i < w; i++) {
                        //printf("i: %d, j: %d\n", i , j);
                        apply(i, j, array2, UArray_at(thisrow, i), cl);
                }
                
        }
}

/* UArray2_map_col_major
 * 
 * Purpose:  
 *      Iterates through every index of uarray2 and calls an apply 
 *      function for each element in the array. Row indices vary more 
 *      rapidly than the column indicies.
 *      
 * Parameters:  
 *      T uarray2: Pointer to the already initialized UArray2_T struct
 *      void apply(): Function to be called on every element
 *              int col: column of the element that apply function is acting on
 *              int row: row of the element that apply function is acting on
 *              T uarray2: Pointer to the already initialized UArray2_T struct
 *              void *elem: Pointer to a single element of the uarray2
 *              void *cl: Pointer to a closure argument
 *      void *cl: Pointer to a closure argument
 *      
 * Return: 
 *      Nothing directly but may alter the uarray2 being pointed to and the
 *      other pointer variables being passed in
 *      
 * Expects:
 *      uarray2 to not be NULL
 *      *cl to be casted a type other than void
 *      
 * Notes:
 *      Will CRE if uarray2 is NULL
 *      
 */
void UArray2_map_col_major(T array2, 
                           void apply(int i, int j, T array2, 
                                      void *elem, void *cl), 
                           void *cl)
{
        assert(array2);
        int h = array2->height;  /* keeping height and width in registers */
        int w = array2->width;   /* avoids extra memory traffic           */
        for (int i = 0; i < w; i++)
                for (int j = 0; j < h; j++)
                        apply(i, j, array2, UArray_at(row(array2, j), i), cl);
}