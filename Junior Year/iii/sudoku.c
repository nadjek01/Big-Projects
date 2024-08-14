/*
 * HW: iii
 * File: Sudoku.c
 * Names: Nana Adjekum (nadjek01) and Harsh Sinha (hsinha02)
 * Date: 28-Sept
 * Purpose: tests whether the sudoku is solved or not
*/
#include <stdlib.h>
#include <stdbool.h>
#include "assert.h"
#include "mem.h"
#include "uarray.h"
#include "uarray2.h"
#include "pnmrdr.h"

typedef long number;

const int DIM1 = 9;
const int DIM2 = 9;
const int ELEMENT_SIZE = sizeof(number);
const int MARKER = 99;

void readsudoku(FILE *fp);
void check_duplicates_c(int i, int j, UArray2_T a, void *p1, void *p2);
void check_duplicates_r(int i, int j, UArray2_T a, void *p1, void *p2);

int main(int argc, char *argv[])
{
    //opens the file
    assert(argc <= 2);
    FILE *fp;
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        assert(fp != NULL);
        readsudoku(fp);
    } else if (argc == 1) {
        fp = stdin;
        assert(fp != NULL);
        readsudoku(fp);
    }
    fclose(fp);
    return 0;
}

/*****************************************************************
 *
 *                          readsudoku
 *
 *   Parameters: a pointer to a file (fp) which
 *               holds the data for the sudoku
 *               puzzle
 *
 *   Returns: nothing void
 *
 *   Purpose:
 *              reads in the file and store it into
 *              a pgm image
 *   Exceptions:
 *              Asserts that the made pgm image is valid,
 *              the made pgm map is valid, the width and
 *              height are 9 and the max val is 9.
 *      
 *
 *****************************************************************/
void readsudoku(FILE *fp)
{
    //bool in charge of tracking the
    //validity of the sudoku puzzle
    bool solved = true;

    Pnmrdr_T graymap = Pnmrdr_new(fp);
    Pnmrdr_mapdata sudoku = Pnmrdr_data(graymap);
    

    assert(&sudoku != NULL);
    UArray2_T sudoku_array = UArray2_new(sudoku.width, sudoku.height, 
                                        sizeof(int));

    /* these asserts check if the various invalid
     * cases that may arise when creating the
     * 2D array, we use if statements to free
     * the allocated items
     */
    if (sudoku.type != Pnmrdr_gray) {
        UArray2_free(&sudoku_array);
        Pnmrdr_free(&graymap);
        fclose(fp);
        assert(sudoku.type == Pnmrdr_gray);
    }

    if (sudoku.width != 9 && sudoku.height != 9) {
        UArray2_free(&sudoku_array);
        Pnmrdr_free(&graymap);
        fclose(fp);
        assert(sudoku.width == 9 && sudoku.height == 9);
    }
    
    if (sudoku.denominator != 9) {
        UArray2_free(&sudoku_array);
        Pnmrdr_free(&graymap);
        fclose(fp);
        assert(sudoku.width == 9 && sudoku.height == 9);
    }

    
    // solved = (UArray2_width(sudoku_array) == DIM1) &&
    //          (UArray2_height(sudoku_array) == DIM2);

    /* creates an int array of the nums to 2x check and
     * keep track of the nums
    */
    for (int r = 0; r < UArray2_width(sudoku_array); r++) {
        for (int c = 0; c < UArray2_height(sudoku_array); c++) {
            int num = Pnmrdr_get(graymap);
            int *temp = UArray2_at(sudoku_array, r, c);
            *temp = num;
        }
    }

    /* we use the apply funct to go through the rows and
     * and cols to find dups of the nums
    */
    UArray2_map_col_major(sudoku_array, check_duplicates_c, &solved);
    UArray2_map_row_major(sudoku_array, check_duplicates_r, &solved);
    UArray2_free(&sudoku_array);
    Pnmrdr_free(&graymap);
    fclose(fp);

    if (solved == false) {
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

/*****************************************************************
 *
 *                          check_duplicates_c
 *
 *   Parameters: two ints i and j corresponding to the row and col,
 *               the 2d array that will be checked, and void
 *               pointers corresponding to the bool
 *
 *   Returns: nothing void
 *
 *   Purpose:
 *              iterates through the given 2D array in col
 *              major order and checks for duplicates
 *   Exceptions:
 *              None
 *      
 *
 *****************************************************************/
void check_duplicates_c(int i, int j, UArray2_T a, void *p1, void *p2)
{
    (void)p1;
    (void)p2;
    (void)i;
    (void)j; 

    bool seen_array[9] = {false};
    for (int i = 0; i < UArray2_width(a); i++) {
        int *num = (int *)UArray2_at(a, i, j);
        int val = *num;

        if (val < 1 || val > 9) {
            *((bool *)p2) = false;
            break;
        }

        if (seen_array[val - 1] == false) {
            seen_array[val - 1] = true;
        } else {
            *((bool *)p2) = false;
            break;
        }
    }
}

/*****************************************************************
 *
 *                          check_duplicates_r
 *
 *   Parameters: two ints i and j corresponding to the row and col,
 *               the 2d array that will be checked, and void
 *               pointers corresponding to the bool
 *
 *   Returns: nothing void
 *
 *   Purpose:
 *              goes through the array in row major order
 *              and checks for duplicates
 *
 *   Exceptions:
 *              None
 *      
 *
 *****************************************************************/
void check_duplicates_r(int i, int j, UArray2_T a, void *p1, void *p2)
{
    (void)p1;
    (void)p2;
    (void)i;
    (void)j;

    bool seen_array[9] = {false};
    for (int i = 0; i < UArray2_width(a); i++) {
        int *num = (int *)UArray2_at(a, j, i);
        int val = *num;
        if (val < 1 || val > 9) {
            *((bool *)p2) = false;
            break;
        }

        if (seen_array[val - 1] == false) {
            seen_array[val - 1] = true;
        } else {
            *((bool *)p2) = false;
            break;
        }
    }
}