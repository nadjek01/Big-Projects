/*
 * HW: iii
 * File: Unblackedges.c
 * Names: Nana Adjekum (nadjek01) and Harsh Sinha (hsinha02)
 * Date: 28-Sept
 * Purpose: Identifies and removes black edges from pbm files
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "assert.h"
#include "mem.h"
#include "pnmrdr.h"
#include <bit2.h>
#include <stack.h>
#include <seq.h>

const int MARKER = 1; /* can only be 1 or 0 */

//keeps track of the coordinates
struct coord
{
    int xc;
    int yr;
} coord;

Bit2_T readfile(FILE *fp);
void writefile(FILE *outputfp, Bit2_T bitmap);
void blackedge_processor(Bit2_T image);
bool is_blackedge(Bit2_T blackedge_map, int col, int row);
void blackedge_removal(Bit2_T blackedge_map, Bit2_T image);
bool check_inbounds(int xc, int yr, int width, int height);

int main(int argc, char *argv[])
{

    if(argc > 2)
    {
        fprintf(stderr, "Too many arguments provided. Exiting program\n");
        exit(EXIT_FAILURE);
    }
    FILE *fp;
    FILE *outputfp;
    outputfp = stdout;
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        if(fp == NULL)
        {
            fprintf(stderr, "File could not be opened. Exiting program\n");
            exit(EXIT_FAILURE);   
        }
        Bit2_T image = readfile(fp);
        blackedge_processor(image);
        writefile(outputfp, image);
        Bit2_free(&image);
    } else if (argc == 1) {
        fp = stdin;
        Bit2_T image = readfile(fp);
        writefile(outputfp, image);
        Bit2_free(&image);
    }
    fclose(fp);
    return 0;
}

/*****************************************************************
 *
 *                    bit2_T readfile(FILE *fp)
 *
 *   Parameters: FILE pointer (fp) to be read in to the program
 *
 *   Returns: Bit2_T object with file contents
 *
 *   Purpose:
 *             Reads in the file into a PBM image, creates
 *             a datamap based on the data in the file.
 *             from there creates a 2d bitarray from the
 *             the datamap
 *
 *   Exceptions:
 *              Asserts the the map created is not NULL
 *              and the 2D bitarray is also not NULL
 *      
 *
 *****************************************************************/
Bit2_T readfile(FILE *fp)
{
    Pnmrdr_T originalFile = Pnmrdr_new(fp);
    Pnmrdr_mapdata dataMap = Pnmrdr_data(originalFile);
    assert(&dataMap != NULL);

    int height = dataMap.height;
    int width = dataMap.width;

    Bit2_T temp = Bit2_new(width, height);
    assert(&temp != NULL);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int currBit = Pnmrdr_get(originalFile);
            Bit2_put(temp, j, i, currBit);
        }
    }
    Pnmrdr_free(&originalFile);
    return temp;
}

/*****************************************************************
 *
 *                   blackedge_processor(Bit2_T image)
 *
 *   Parameters: the 2D bit array holding the vals of the
 *               image to be processed
 *
 *   Returns: nothing void
 *
 *   Purpose:
 *              Processes the image by creating a map of blackedges.
 *              Using a DFS, create a visited map to only visit
 *              a coordinate in the image once. The stack adds all 
 *              the outer edges with black to start and searches
 *              inward for adjacent black edges. Then converts the
 *              original image to cleaned by removing.
 *   Exceptions:
 *              Throws if any memory failure is detected when 
 *              initiating objects.
 *      
 *
 *****************************************************************/
void blackedge_processor(Bit2_T image)
{
    assert(image);
    Bit2_T blackedge_map = Bit2_new(Bit2_width(image), Bit2_height(image));
    Bit2_T visited_map = Bit2_new(Bit2_width(image), Bit2_height(image));
    assert(blackedge_map);
    assert(visited_map);
    
    Seq_T queue = Seq_new(Bit2_height(image) * Bit2_width(image));
    assert(queue);

    int w = Bit2_width(image);
    int h = Bit2_height(image);

    // Add all outer edges with black to the queue.
    for (int col = 0; col < w; col++) {
        int row = 0;
        struct coord k = {col, row};
        int temp = Bit2_get(image, col, row);

        if (temp == 1) {
            Bit2_put(blackedge_map, col, row, 1);
            Seq_addlo(queue, &k);
        }
    }

    for (int col = 0; col < w; col++) {
        struct coord k = {col, Bit2_height(image) - 1};
        int temp = Bit2_get(image, col, Bit2_height(image) - 1);
        if (temp == 1) {
            Bit2_put(blackedge_map, col, Bit2_height(image) - 1, 1);
            Seq_addlo(queue, &k);
        }
    }

    for (int row = 0; row < h; row++) {
        int col = 0;
        struct coord k = {0, row};
        int temp = Bit2_get(image, col, row);
        if (temp == 1) {
            Bit2_put(blackedge_map, col, row, 1);
            Seq_addlo(queue, &k);
        }
    }

    for (int row = 0; row < h; row++) {
        int col = w - 1;
        struct coord k = {col, row};
        int temp = Bit2_get(image, col, row);
        if (temp == 1) {
            Bit2_put(blackedge_map, col, row, 1);
            Seq_addlo(queue, &k);
        }
    }

    struct coord *left = malloc(sizeof(struct coord));
    struct coord *right = malloc(sizeof(struct coord));
    struct coord *up = malloc(sizeof(struct coord));
    struct coord *down = malloc(sizeof(struct coord));
    
    // DFS loop to add coord, check visited, add neighbours
    while (Seq_length(queue) > 0) {
        struct coord *curr = Seq_remlo(queue);
        int col = curr->xc;
        int row = curr->yr;
        
        // check visited
        if (Bit2_get(visited_map, col, row) == 1) {
            continue;
        } else {
            Bit2_put(visited_map, col, row, 1);
        }

        // update blackedge map
        if (Bit2_get(image, col, row) == 1 
            && is_blackedge(blackedge_map, col, row) == 1) {
            Bit2_put(blackedge_map, col, row, 1);
        }

        // add l/r/up/down neighbours that are valid to the queue
        if (0 <= col - 1) {
            left->xc = col - 1;
            left->yr = row;
            if (check_inbounds(left->xc, left->yr, w, h)) {
                Seq_addlo(queue, left);
            }
        }

        if (col + 1 < w) {
            right->xc = col + 1;
            right->yr = row;
            if (check_inbounds(right->xc, right->yr, w, h)) {
                //Stack_push(queue, right);
                Seq_addlo(queue, right);
            }
        }

        if (0 <= row - 1) {
            up->xc = col;
            up->yr = row - 1;
            if (check_inbounds(up->xc, up->yr, w, h)) {
                Seq_addlo(queue, up);
            }
        }

        if (row + 1 < h) {
            down->xc = col;
            down->yr = row + 1;
            if (check_inbounds(down->xc, down->yr, w, h)) {
                Seq_addlo(queue, down);
            }
        }
    }

    blackedge_removal(blackedge_map, image);

    Seq_free(&queue);
    FREE(left);
    FREE(right);
    FREE(up);
    FREE(down);
    Bit2_free(&blackedge_map);
    Bit2_free(&visited_map);
}

/*****************************************************************
 *
 *     is_blackedge(Bit2_T blackedge_map, int col, int row)
 *
 *   Parameters: a 2D bit array, and 2 ints corresponding
 *               to the col and row (indx)
 *
 *   Returns: bool (corresponding to if the found indx
 *            is a black edge pixel)
 *
 *   Purpose:
 *              iterates through the 2D bitarray to find
 *              black edge pixels
 *   Exceptions:
 *              None
 *      
 *
 *****************************************************************/
bool is_blackedge(Bit2_T blackedge_map, int col, int row) {
    int h = Bit2_height(blackedge_map);
    int w = Bit2_width(blackedge_map);
    if (check_inbounds(col - 1, row, w, h) 
        && Bit2_get(blackedge_map, col - 1, row) == 1) return true;
    if (check_inbounds(col + 1, row, w, h) 
        && Bit2_get(blackedge_map, col + 1, row) == 1) return true;
    if (check_inbounds(col, row - 1, w, h) 
        && Bit2_get(blackedge_map, col, row - 1) == 1) return true;
    if (check_inbounds(col, row + 1, w, h) 
        && Bit2_get(blackedge_map, col, row + 1) == 1) return true;
    return false;
}

/*****************************************************************
 *
 *           writefile(FILE *outputfp, Bit2_T bitmap)
 *
 *   Parameters: File pointer (outputfp) and the
 *               2D bitmap
 *
 *   Returns: nothing void
 *
 *   Purpose:
 *              Prints out the bitmap with the removed
 *              black edge pixels
 *   Exceptions:
 *              None
 *      
 *
 *****************************************************************/
void writefile(FILE *outputfp, Bit2_T bitmap)
{
    int width = Bit2_width(bitmap);
    int height = Bit2_height(bitmap);
    assert(bitmap);
    assert(outputfp);

    fprintf(outputfp, "P1\n");
    fprintf(outputfp, "%d %d\n", width, height);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int pixel = Bit2_get(bitmap, col, row);

            fprintf(outputfp, "%d", pixel);
            if (col % width == 0 && col > 0) {
                fprintf(outputfp, "\n");
            }
        }
        fprintf(outputfp, "\n");
    }
}

/*****************************************************************
 *
 *   bool check_inbounds(int xc, int yr, int width, int height)
 *
 *   Parameters: ints for the col, row, width, and heights
 *
 *   Returns: bool
 *
 *   Purpose:
 *              compares the col and rows to the width and
 *              heights of the bitmap and returns a boolean
 *              for the comparison check
 *   Exceptions:
 *              None
 *      
 *
 *****************************************************************/
bool check_inbounds(int xc, int yr, int width, int height)
{
    if (xc < 0 || yr < 0) {
        return false;
    } 
    if (xc + 1 > width || yr + 1 > height) {
        return false;
    }
    return true;
}

/*****************************************************************
 *
 *     blackedge_removal(Bit2_T blackedge_map, Bit2_T image)
 *
 *   Parameters: 2 2D bitmaps (one for blackedges and the og image)
 *
 *   Returns: nothing void
 *
 *   Purpose:   Takes our map of blackedge and removes any black
 *              pixel at a coord from the original image
 *   Exceptions:
 *              none
 *      
 *
 *****************************************************************/
void blackedge_removal(Bit2_T blackedge_map, Bit2_T image)
{
    int width = Bit2_width(blackedge_map);
    int height = Bit2_height(blackedge_map);

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            int pixel = Bit2_get(blackedge_map, c, r);
            if (pixel == 1) {
                Bit2_put(image, c, r, 0);
            }
        }
    }
}