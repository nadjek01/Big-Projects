/* HW3 Locality
 * File Name: UArray2.h
 * File Purpose:
 *      This in the implementation for UArray2b 
 * 
 * Author: Henry Tindall (htinda01) & Nana Adjekum (nadjek01)
 *
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "assert.h"
#include "mem.h"
#include "uarray.h"
#include "UArray2.h"
#include "uarray2b.h"



#define T UArray2b_T

/*personal choice to define AND and OR*/
#define AND &&
#define OR ||

const int DEFAULT_BLOCK_SZ = 2;

struct T {
    int width, height;
    int bwidth, bheight;
    int size, blocksize;
    UArray2_T bigBlock;
};

//apply functions to help us alloc and dealloc space for small array
void init_small(int col, int row, UArray2_T blockArray, void *elem, void *cl);
void free_small(int col, int row, UArray2_T blockArray, void *elem, void *cl);


/*A. Alloc Functions*/
/* UArray2b_new
 * Purpose: 
 *      To initialize the 2 dimensional blocked array. Allocates the proper 
 *      amount of memory to hold the entire array and elements. 
 *
 * Parameters:
 *      int width: Number of columns in the array
 *      int height: Number of rows in the array
 *      int size: Size of the individual elements
 *      int blocksize: Size of the blocks in the blocked 2D array
 *
 * Return: 
 *      returns a pointer to a UArray2b_T struct
 *
 * Expects:
 *      Width and height are non-negative numbers
 *      Size is a positive number
 *
 * Notes: 
 *      No need to assert that width height and size are non-negative because
 *      we use them to create our UArray2 which will raise a hanson exeption
 *      and quit from the program for us. Blocksize needs to be checked though
 *      because it is not a part of the UArray2
*/
T UArray2b_new (int width, int height, int size, int blocksize)
{
    assert(blocksize >= 1);
    T blockArray;
    NEW(blockArray);
    
    blockArray->width = width;
    blockArray->height = height;
    blockArray->size = size;
    blockArray->blocksize = blocksize;
    
    if (width % blockArray->blocksize != 0) {
        blockArray->bwidth = (width/blockArray->blocksize) + 1;
    } else {
        blockArray->bwidth = (width/blockArray->blocksize);
    }

    if (height % blockArray->blocksize != 0) {
        blockArray->bheight = (height/blockArray->blocksize) + 1;
    } else {
        blockArray->bheight = (height/blockArray->blocksize);
    }
    
    /* using our UArray2 implementation to help us
     * map and alloc space for small array
    */
    blockArray->bigBlock = 
    UArray2_new(blockArray->bwidth, blockArray->bheight, sizeof(UArray2_T));

    UArray2_map_row_major(blockArray->bigBlock, init_small, blockArray);
    return blockArray;
}

/* UArray2b_new_64K_block
 * Purpose: 
 *      To initialize the 2 dimensional blocked array. Allocates the proper 
 *      amount of memory to hold the entire array and elements. 
 *
 * Parameters:
 *      int width: Number of columns in the array
 *      int height: Number of rows in the array
 *      int size: Size of the individual elements
 *
 * Return: 
 *      returns a pointer to a UArray2b_T struct through a
 *      function call to the new function
 *
 * Expects:
 *      Width and height are non-negative numbers
 *      Size is a positive number
 *
 * Notes: 
 *      No need to assert that width height and size are non-negative because
 *      we use them to create our UArray2 which will raise a hanson exeption
 *      and quit from the program for us. Blocksize needs to be checked though
 *      because it is not a part of the UArray2
*/
T UArray2b_new_64K_block (int width, int height, int size)
{

    int blocksize = floor(sqrt(DEFAULT_BLOCK_SZ/size));
    if (blocksize < 1) {
        blocksize = 1;
    }

    return UArray2b_new(width, height, size, blocksize);

}


/* UArray2b_free
 * 
 * Purpose:  
 *      to free all of the previously allocated memory for uarray2b
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
void  UArray2b_free(T *array2b)
{
    void *cl = NULL;
    assert(array2b && *array2b);
    UArray2_map_row_major((*array2b)->bigBlock, free_small, cl);
    UArray2_free(&(*array2b)->bigBlock);
    FREE(*array2b);
}

/* init_small
 * 
 * Purpose:  
 *      Apply function to be called in the UArray2b_new function that will
 *      initialize all our small arrays that hold actual data
 *
 * Parameters:  
 *      int col: column of the big 2D array that we are currently at
 *      int row: row of the big 2D array that we are currently at
 *      UArray2_T blockArray: pointer to the big 2D array
 *      void *elem: unused void pointer
 *      void *cl: unused void pointer
 *      
 * Return: 
 *      nothing
 *      
 * Expects:
 *      expects blockArray to not be NULL
 *      
 * Notes:
 *      No need to CRE if blockArray is NULL because UArray2_new will handle
 *      the case where there is not enough space to initiatize the 2D array
 */    
void init_small(int col, int row, UArray2_T blockArray, void *elem, void *cl)
{
    (void)elem;
    UArray_T *small = UArray2_at(blockArray, col, row);
    *small = UArray_new(((T)cl)->blocksize * ((T)cl)->blocksize, 
    ((T)cl)->size);
}

/* free_small
 * 
 * Purpose:  
 *      Apply function to be called in the UArray2b_free function that will
 *      free all our small arrays that hold actual data
 *
 * Parameters:  
 *      int col: column of the big 2D array that we are currently at
 *      int row: row of the big 2D array that we are currently at
 *      UArray2_T blockArray: pointer to the big 2D array
 *      void *elem: unused void pointer
 *      void *cl: unused void pointer
 *      
 * Return: 
 *      nothing
 *      
 * Expects:
 *      expects blockArray to not be NULL
 *      
 * Notes:
 *      No need to CRE if blockArray is NULL because UArray2_new will handle
 *      the case where there is not enough space to initiatize the 2D array
 */  
void free_small(int col, int row, UArray2_T blockArray, void *elem, void *cl)
{
    (void)elem;
    (void)cl;
    UArray_T *small = UArray2_at(blockArray, col, row);
    UArray_free(small);
}

/*B. Map Functions*/
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
extern void  UArray2b_map(T array2b,
                          void apply(int col, int row, T array2b,
                                     void *elem, void *cl),
void *cl)
{
    assert(array2b);
    int w = array2b->bwidth;
    int h = array2b->bheight;
    int b = array2b->blocksize;
    int imageWidth = array2b->width;
    int imageHeight = array2b->height;
    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            UArray_T *small_block = UArray2_at(array2b->bigBlock, col, row);
            for (int indx = 0; indx < UArray_length(*small_block); indx++) {
                /* we use this math to make sure the we are
                 * visiting an index that contains elements
                 * not an initialised but not defined index
                */
                if (((b * col) + (indx % b)) < imageWidth &&
                    ((b * row) + floor((indx / b))) < imageHeight) {
                    
                    apply(col, row, array2b, UArray_at(*small_block, indx), 
                          cl);
                } else {
                    continue;
                }
                
            }
        }
    }
}

/*C. Location function*/
/* UArray2_at
 * 
 * Purpose:  
 *      Give the client access to a specific index in the 2D 
 *      blockedarray. The client 
 *      can then cast the returned void pointer and then dereference said cast
 *      pointer to manipulate the data
 *
 * Parameters:  
 *      T uarray2: Pointer to the already initialized UArray2b_T struct
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
void *UArray2b_at(T array2b, int column, int row)
{
    assert(array2b);
    int bsize = array2b->blocksize;

    /* to find the small block within the big block
     * given by spec
    */
    UArray_T *temp = UArray2_at(array2b->bigBlock, (column / bsize),
                                (row / bsize));
    
    int indx = bsize * (column % bsize) + (row % bsize);
    return UArray_at(*temp, indx);
}

//D. Getter Functions
/* UArray2b_size
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
int UArray2b_size(T array2b)
{
    assert(array2b);
    return array2b->size;
}

/* UArray2b_width
 * 
 * Purpose:  
 *      return the width of the image in the UArray2b_T
 *
 * Parameters:  
 *      T uarray2b: Pointer to the already initialized UArray2b_T struct
 *      
 * Return: 
 *      the width of the image in the UArray2b_T
 *      
 * Expects:
 *      expects uarray2b to not be NULL
 *      
 * Notes:
 *      Will CRE if uarray2b is NULL
 *      
 */
int UArray2b_width(T array2b)
{
    assert(array2b);
    return array2b->width;
}

/* UArray2b_blocksize
 * 
 * Purpose:  
 *      return the blocksize of the UArray2b_T
 *
 * Parameters:  
 *      T uarray2b: Pointer to the already initialized UArray2b_T struct
 *      
 * Return: 
 *      the blocksize of the image in the UArray2b_T
 *      
 * Expects:
 *      expects uarray2b to not be NULL
 *      
 * Notes:
 *      Will CRE if uarray2b is NULL
 *      
 */
int UArray2b_blocksize(T array2b)
{
    assert(array2b);
    return array2b->blocksize;
}

/* UArray2b_height
 * 
 * Purpose:  
 *      return the height of the image in the UArray2b_T
 *
 * Parameters:  
 *      T uarray2b: Pointer to the already initialized UArray2b_T struct
 *      
 * Return: 
 *      the height of the image in the UArray2b_T
 *      
 * Expects:
 *      expects uarray2b to not be NULL
 *      
 * Notes:
 *      Will CRE if uarray2b is NULL
 *      
 */
int UArray2b_height(T array2b)
{
    assert(array2b);
    return array2b->height;
}

/* UArray2_bwidth
 * 
 * Purpose:  
 *      return the width (number of blocks) in the UArray2b_T
 *
 * Parameters:  
 *      T uarray2b: Pointer to the already initialized UArray2b_T struct
 *      
 * Return: 
 *      the width (number of blocks) in the UArray2b_T
 *      
 * Expects:
 *      expects uarray2b to not be NULL
 *      
 * Notes:
 *      Will CRE if uarray2b is NULL
 *      
 */
int UArray2b_bwidth(T array2b)
{
    assert(array2b);
    return array2b->bwidth;
}

/* UArray2b_bheight
 * 
 * Purpose:  
 *      return the height (number of blocks) in the UArray2b_T
 *
 * Parameters:  
 *      T uarray2b: Pointer to the already initialized UArray2b_T struct
 *      
 * Return: 
 *      the height (number of blocks) in the UArray2b_T
 *      
 * Expects:
 *      expects uarray2b to not be NULL
 *      
 * Notes:
 *      Will CRE if uarray2b is NULL
 *      
 */
int UArray2b_bheight(T array2b)
{
    assert(array2b);
    return array2b->bheight;
}
#undef T
