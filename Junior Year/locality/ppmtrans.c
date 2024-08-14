/**************************************************************************
 * sudoku.c
 * Authors: Henry Tindall   htinda01
 *          Nana Adjekum    nadjek01
 * 
 * Date:    October 11, 2023
 * 
 * CS40 HW3 - Locality - part c
 * 
 * Purpose: To read in an image and rotate as the client commands.
 *          Will be able to handle rotations 0, 90, 180, 270, flip vertical
 *          flip horizontal using row_major access, col_major access and
 *          block_major access. If the user desires it will also print
 *          information about the time taken to an output file.
 * 
 * Assumes: 
 * 
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pnm.h>

#include "pnmrdr.h"
#include "cputiming.h"
#include "assert.h"
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"

const int VERT = 1;
const int HORZ = 2;

Pnm_ppm applyRotation(int rotation, A2Methods_T methods, Pnm_ppm ogImage, 
                     A2Methods_mapfun *map, double *time_elapsed);
Pnm_ppm transform_diff_dim(int rotation, A2Methods_T methods, Pnm_ppm ogImage,
                           A2Methods_mapfun *map, A2Methods_UArray2 ogPix, 
                           double *time_elapsed);
Pnm_ppm transform_same_dim(int rotation, A2Methods_T methods, Pnm_ppm ogImage, 
                           A2Methods_mapfun *map, A2Methods_UArray2 ogPix, 
                           double *time_elapsed);
void print_time_to_file(double *time, Pnm_ppm ogPix, char *image_file_name, 
                         char *timeFileName, int rotation, char *map_type);
void rotate90(int col, int row, A2Methods_UArray2 ogPix, 
               A2Methods_Object *ptr, void *cl);  
void rotate180(int col, int row, A2Methods_UArray2 arr, 
               A2Methods_Object *ptr, void *cl);       
void rotate270(int col, int row, A2Methods_UArray2 arr, 
               A2Methods_Object *ptr, void *cl);
void flip_vert(int col, int row, A2Methods_UArray2 arr, 
               A2Methods_Object *ptr, void *cl);
void flip_horz(int col, int row, A2Methods_UArray2 arr, 
               A2Methods_Object *ptr, void *cl);     

#define SET_METHODS(METHODS, MAP, WHAT) do {                    \
        methods = (METHODS);                                    \
        assert(methods != NULL);                                \
        map = methods->MAP;                                     \
        if (map == NULL) {                                      \
                fprintf(stderr, "%s does not support "          \
                                WHAT "mapping\n",               \
                                argv[0]);                       \
                exit(1);                                        \
        }                                                       \
} while (false)

static void
usage(const char *progname)
{
        fprintf(stderr, "Usage: %s [-rotate <angle>] "
                        "[-{row,col,block}-major] [filename]\n",
                        progname);
        exit(1);
}

/* main
 * 
 * Purpose: 
 *      To update methods so that it matches what the user inputed to the
 *      command line (Not done by us). Next it either opens the image
 *      file or sets the input stream to STDIN. Finally it calls the rotation
 *      function and writes to an output file if the user desires.  
 *
 * Parameters:
 *      int argc: stores the number of arguments on the command line
 *      char *argv[]: stores a pointer to the arguments themselves on the 
 *                    command line
 *      
 * Return: 
 *      Nothing
 *      
 * Expects:
 *      
 * Notes:
 *      
 */
int main(int argc, char *argv[]) 
{
        char *time_file_name = NULL;
        char *image_file_name = NULL;
        int   rotation       = 0;
        int   i;
        double time_elapsed;
        char *map_type = "Row-Major";
        Pnm_ppm ogImage;


        FILE *input_stream = NULL;
        /* default to UArray2 methods */
        A2Methods_T methods = uarray2_methods_plain; 
        assert(methods);

        /* default to best map */
        A2Methods_mapfun *map = methods->map_default; 
        assert(map);

        for (i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-row-major") == 0) {
                        SET_METHODS(uarray2_methods_plain, map_row_major, 
                                    "row-major");
                        map_type = "Row-Major";
                } else if (strcmp(argv[i], "-col-major") == 0) {
                        SET_METHODS(uarray2_methods_plain, map_col_major, 
                                    "column-major");
                        map_type = "Col-Major";
                } else if (strcmp(argv[i], "-block-major") == 0) {
                        SET_METHODS(uarray2_methods_blocked, map_block_major,
                                    "block-major");
                        map_type = "Block-Major";
                } else if (strcmp(argv[i], "-rotate") == 0) {
                        if (!(i + 1 < argc)) {      /* no rotate value */
                                usage(argv[0]);
                        }
                        char *endptr;
                        rotation = strtol(argv[++i], &endptr, 10);
                        if (!(rotation == 0 || rotation == 90 ||
                            rotation == 180 || rotation == 270)) {
                                fprintf(stderr, 
                                        "Rotation must be 0, 90 180 or 270\n");
                                usage(argv[0]);
                        }
                        if (!(*endptr == '\0')) {    /* Not a number */
                                usage(argv[0]);
                        }
                } else if (strcmp(argv[i], "-flip") == 0) {
                       if (!(i + 1 < argc)) {      /* no flip value */
                                usage(argv[0]);
                        }
                        if (!strcmp(argv[++i], "vertical")) {
                                rotation = VERT;
                        } else if (!strcmp(argv[i], "horizontal")) {
                                rotation = HORZ;
                        } else {
                                fprintf(stderr, "Flipping must be either "
                                        "vertical or horizontal\n");
                                usage(argv[0]);
                        }        
                } else if (strcmp(argv[i], "-transpose") == 0) {
                        fprintf(stderr, "Transpose not supported\n");
                        exit(EXIT_FAILURE);
                } else if (strcmp(argv[i], "-time") == 0) {
                        time_file_name = argv[++i];
                } else if (*argv[i] == '-') {
                        fprintf(stderr, "%s: unknown option '%s'\n", argv[0],
                                argv[i]);
                        usage(argv[0]);
                } else if (argc - i > 1) {
                        fprintf(stderr, "Too many arguments\n");
                        usage(argv[0]);
                } else if (input_stream == NULL) {
                        image_file_name = argv[i];
                        input_stream = fopen(argv[i], "rb");
                        if (input_stream == NULL) {
                                fprintf(stderr, "Unable to open file.\n"); 
                                
                                exit(EXIT_FAILURE);
                        }
                } else {
                        break;
                }
        }

        /* If there is no image file then input_stream is set to NULL */
        if (input_stream == NULL) {
                image_file_name = "STDIN";
                input_stream = stdin;
        }

        /* Read in the ppm image using pnm.h */
        ogImage = Pnm_ppmread(input_stream, methods);

        ogImage = applyRotation(rotation, methods, ogImage, map, &time_elapsed);

        if(time_file_name != NULL) {
                print_time_to_file(&time_elapsed, ogImage, image_file_name, 
                                   time_file_name, rotation, map_type);
        }
        Pnm_ppmwrite(stdout, ogImage);
        
        fclose(input_stream);
        Pnm_ppmfree(&ogImage);

        exit(EXIT_SUCCESS);

}

/* applyRotation
 * 
 * Purpose: 
 *      To handle 3 cases: the rotation results in different dimensions than
 *      the original, the rotation results in the same dimensions as the
 *      original, or the rotation is 0.
 *
 * Parameters:
 *      int rotation: The degree of rotation that the client desires
 *      A2Methods_T methods: Either a2plain.c or a2blocked.c
 *      Pnm_ppm ogImage: original image still in its ppm format
 *      A2Methods_mapfun *map: The mapping function as dictated by the user
 *      double *time_elapsed: To keep track of the time each rotation takes
 *      
 * Return: 
 *      A Pnm_ppm that will hold the full rotated image that the user desires
 *      
 * Expects:
 *      rotation to be either 0, 90, 180, 270, VERT, or HORZ
 *      methods to be either a2plain or a2blocked (as client dictates)
 *      ogImage not to be NULL
 *      map to be the correct mapping function (as client dictates)
 *      
 * Notes:
 *      rotation will be an expected value or else the for loop in main will
 *      call the usage function and exit the program
 *      methods will be either a2plain or a2blocked as client dictates because
 *      the for loop in main will assign it properly
 *      ogImage will not be NULL as it is initialized right before being passed
 *      in
 *      map will be the correct mapping function (as client dictates) because
 *      the for loop in main will assign it properly
 *      
 */
Pnm_ppm applyRotation(int rotation, A2Methods_T methods, Pnm_ppm ogImage, 
                     A2Methods_mapfun *map, double *time_elapsed) 
{
        A2Methods_UArray2 ogPix = ogImage->pixels;                

        if (rotation == 90 || rotation == 270) {
                return transform_diff_dim(rotation, methods, ogImage, map,
                                            ogPix, time_elapsed);
        }

        if (rotation == 180 || rotation == HORZ || rotation == VERT) {
                return transform_same_dim(rotation, methods, ogImage, map, 
                                            ogPix, time_elapsed);
        }

        /* If it got this far than rotation = 0 */
        *time_elapsed = 0;
        return ogImage;


}

/* transform_diff_dim
 * 
 * Purpose: 
 *      To apply the correct rotation to our pnm image and time how long it
 *      takes to finish. This function also handles switching the width and
 *      height of the resulting images because all of the rotations in this
 *      function result in the bounds switching
 *
 * Parameters:
 *      int rotation: The degree of rotation that the client desires
 *      A2Methods_T methods: Either a2plain.c or a2blocked.c
 *      Pnm_ppm ogImage: original image still in its ppm format
 *      A2Methods_mapfun *map: The mapping function as dictated by the user
 *      A2Methods_UArray2 ogPix: The original 2D array of pixels
 *      double *time_elapsed: To keep track of the time each rotation takes
 *      
 * Return: 
 *      A Pnm_ppm that will hold the full rotated image that the user desires
 *      
 * Expects:
 *      rotation to be either 90, or 270
 *      methods to be either a2plain or a2blocked (as client dictates)
 *      ogImage not to be NULL
 *      map to be the correct mapping function (as client dictates)
 *      
 * Notes:
 *      rotation will be an expected value or else the for loop in main will
 *      call the usage function and exit the program
 *      methods will be either a2plain or a2blocked as client dictates because
 *      the for loop in main will assign it properly
 *      ogImage will not be NULL as it is initialized right before being passed
 *      in
 *      map will be the correct mapping function (as client dictates) because
 *      the for loop in main will assign it properly
 *      
 */
Pnm_ppm transform_diff_dim(int rotation, A2Methods_T methods, Pnm_ppm ogImage,
          A2Methods_mapfun *map, A2Methods_UArray2 ogPix, double *time_elapsed)
{
        /* initialize the timer and new height */
        CPUTime_T timer = CPUTime_New();
        int newH;

        /* create a new pnm image because we cannot rotate in place */
        ogImage->pixels = 
               methods->new_with_blocksize(methods->height(ogImage->pixels), 
               methods->width(ogImage->pixels), methods->size(ogImage->pixels),
               methods->blocksize(ogImage->pixels));

        assert(ogImage);
        if (rotation == 90) {
                CPUTime_Start(timer);
                map(ogPix, rotate90, ogImage);
                *time_elapsed = CPUTime_Stop(timer);
        }

        if (rotation == 270) {
                CPUTime_Start(timer);
                map(ogPix, rotate270, ogImage);
                *time_elapsed = CPUTime_Stop(timer);
        }

        /* switch the width and the height and free */
        newH = ogImage->width;
        ogImage->width = ogImage->height;
        ogImage->height = newH;
        methods->free(&ogPix);
        CPUTime_Free(&timer);
        return ogImage;
}

/* transform_same_dim
 * 
 * Purpose: 
 *      To apply the correct rotation to our pnm image and time how long it
 *      takes to finish. This function does not handl switching the width and
 *      height of the resulting images because all of the rotations in this
 *      function result in the bounds staying the same.
 *
 * Parameters:
 *      int rotation: The degree of rotation that the client desires
 *      A2Methods_T methods: Either a2plain.c or a2blocked.c
 *      Pnm_ppm ogImage: original image still in its ppm format
 *      A2Methods_mapfun *map: The mapping function as dictated by the user
 *      A2Methods_UArray2 ogPix: The original 2D array of pixels
 *      double *time_elapsed: To keep track of the time each rotation takes
 *      
 * Return: 
 *      A Pnm_ppm that will hold the full rotated image that the user desires
 *      
 * Expects:
 *      rotation to be either 180, VERT, or HORZ
 *      methods to be either a2plain or a2blocked (as client dictates)
 *      ogImage not to be NULL
 *      map to be the correct mapping function (as client dictates)
 *      
 * Notes:
 *      rotation will be an expected value or else the for loop in main will
 *      call the usage function and exit the program
 *      methods will be either a2plain or a2blocked as client dictates because
 *      the for loop in main will assign it properly
 *      ogImage will not be NULL as it is initialized right before being passed
 *      in
 *      map will be the correct mapping function (as client dictates) because
 *      the for loop in main will assign it properly
 *      
 */
Pnm_ppm transform_same_dim(int rotation, A2Methods_T methods, Pnm_ppm ogImage,
          A2Methods_mapfun *map, A2Methods_UArray2 ogPix, double *time_elapsed)
{

        /* initialize the timer and new height */
        CPUTime_T timer = CPUTime_New();

        /* create a new pnm image because we cannot rotate in place */
        ogImage->pixels = 
              methods->new_with_blocksize(methods->width(ogImage->pixels), 
              methods->height(ogImage->pixels), methods->size(ogImage->pixels),
              methods->blocksize(ogImage->pixels));
        
        assert(ogImage);
        if (rotation == 180) {
                CPUTime_Start(timer);
                map(ogPix, rotate180, ogImage);
                *time_elapsed = CPUTime_Stop(timer);
        }

        if (rotation == VERT) {
                CPUTime_Start(timer);
                map(ogPix, flip_vert, ogImage);
                *time_elapsed = CPUTime_Stop(timer);
        }

        if (rotation == HORZ) {
                CPUTime_Start(timer);
                map(ogPix, flip_horz, ogImage);
                *time_elapsed = CPUTime_Stop(timer);
        }

        /* free timer and old 2D array that held the pre-rotated image */
        methods->free(&ogPix);
        CPUTime_Free(&timer);
        return ogImage;
}

/* print_time_to_file
 * 
 * Purpose: 
 *      To print out the neccessary information to an output file
 *
 * Parameters:
 *      double *time: To keep track of the time the rotation took
 *      Pnm_ppm ogPix: 2D array of pixels that make up our image
 *      char *image_file_name: the file name of the origional image
 *      char *timeFileName: the files name of the time file
 *      int rotation: degree of rotation that occured
 *      char *map_type: name of the type of mapping function called
 *      
 * Return: 
 *      A Pnm_ppm that will hold the full rotated image that the user desires
 *      
 * Expects:
 *      rotation to be either 180, VERT, or HORZ
 *      methods to be either a2plain or a2blocked (as client dictates)
 *      ogImage not to be NULL
 *      map to be the correct mapping function (as client dictates)
 *      
 * Notes:
 *      rotation will be an expected value or else the for loop in main will
 *      call the usage function and exit the program
 *      methods will be either a2plain or a2blocked as client dictates because
 *      the for loop in main will assign it properly
 *      ogImage will not be NULL as it is initialized right before being passed
 *      in
 *      map will be the correct mapping function (as client dictates) because
 *      the for loop in main will assign it properly
 *      
 */
void print_time_to_file(double *time, Pnm_ppm ogPix, char *image_file_name, 
                        char *timeFileName, int rotation, char *map_type)
{
        int w = ogPix->width;
        int h = ogPix->height;
        double time_per_pixel = (*time / (w * h));

        /* open the time file and check that it opened */
        FILE *time_stream = fopen(timeFileName, "a");
        assert(time_stream != NULL);

        fprintf(time_stream, "File Name: %s\n", image_file_name);
        
        /* under the hood VERT is 1 and HORZ is 2 so when printing rotation */
        /* we must account for this                                         */
        if (rotation == VERT) {
                fprintf(time_stream, "Rotation: Flipped Vertically\n");
        } else if (rotation == HORZ) {
                fprintf(time_stream, "Rotation: Flipped Horizonally\n");
        } else {
                fprintf(time_stream, "Rotation: %d\n", rotation);
        }

        fprintf(time_stream, "Map type: %s\n", map_type);
        fprintf(time_stream, "Number of Pixels: %d\n", w * h);
        fprintf(time_stream, "Image Dimensions \nWidth: %d X Height: %d\n",
                 w, h);
        fprintf(time_stream, 
        "Time for entire image rotation: %.0f nanoseconds\n", *time);
        fprintf(time_stream, 
        "Time per pixel of image rotation: %.0f nanoseconds\n", 
        time_per_pixel);
        
        
        fclose(time_stream);
        
        
}


/* rotate90
 * 
 * Purpose: 
 *      To handle to math of placing a pixel in the current image into the 
 *      correct spot of an image that has been rotated 90 degrees
 *
 * Parameters:
 *      int col: column of the element we are currently at
 *      int row: row of the element we are currently at
 *      A2Methods_UArray2 arr: 2D array of either UArray2 or UArray2b
 *      A2Methods_Object *ptr: pointer to a pixel in the original image
 *      void *cl: pointer to the original pnm image
 *      
 * Return: 
 *      nothing
 *      
 * Expects:
 *      *ptr to not be NULL
 *      *cl to not be NULL
 *      
 * Notes:
 *      Neither pointer will ever be null at this point because our mapping
 *      function works correctly where ptr will never be out of bounds, and 
 *      we set cl to the original image
 *      
 */
void rotate90(int col, int row, A2Methods_UArray2 arr, 
                        A2Methods_Object *ptr, void *cl)
{
        (void)arr;
        Pnm_ppm ogPix = (Pnm_ppm)cl;
        int col90 = ogPix->height - row - 1;
        int row90 = col;

        *(Pnm_rgb)(ogPix->methods->at(ogPix->pixels, col90, row90)) 
                                                    = *(Pnm_rgb)ptr;

}

/* rotate180
 * 
 * Purpose: 
 *      To handle to math of placing a pixel in the current image into the 
 *      correct spot of an image that has been rotated 180 degrees
 *
 * Parameters:
 *      int col: column of the element we are currently at
 *      int row: row of the element we are currently at
 *      A2Methods_UArray2 arr: 2D array of either UArray2 or UArray2b
 *      A2Methods_Object *ptr: pointer to a pixel in the original image
 *      void *cl: pointer to the original pnm image
 *      
 * Return: 
 *      nothing
 *      
 * Expects:
 *      *ptr to not be NULL
 *      *cl to not be NULL
 *      
 * Notes:
 *      Neither pointer will ever be null at this point because our mapping
 *      function works correctly where ptr will never be out of bounds, and 
 *      we set cl to the original image
 *      
 */
void rotate180(int col, int row, A2Methods_UArray2 arr, A2Methods_Object *ptr,
                                                                      void *cl)
{
        (void)arr;
        Pnm_ppm ogPix = (Pnm_ppm)cl;
        int col180 = ogPix->width - col - 1;
        int row180 = ogPix->height - row - 1;
        
        *(Pnm_rgb)(ogPix->methods->at(ogPix->pixels, col180, row180)) 
                                                       = *(Pnm_rgb)ptr;
}

/* rotate270
 * 
 * Purpose: 
 *      To handle to math of placing a pixel in the current image into the 
 *      correct spot of an image that has been rotated 2700 degrees
 *
 * Parameters:
 *      int col: column of the element we are currently at
 *      int row: row of the element we are currently at
 *      A2Methods_UArray2 arr: 2D array of either UArray2 or UArray2b
 *      A2Methods_Object *ptr: pointer to a pixel in the original image
 *      void *cl: pointer to the original pnm image
 *      
 * Return: 
 *      nothing
 *      
 * Expects:
 *      *ptr to not be NULL
 *      *cl to not be NULL
 *      
 * Notes:
 *      Neither pointer will ever be null at this point because our mapping
 *      function works correctly where ptr will never be out of bounds, and 
 *      we set cl to the original image
 *      
 */
void rotate270(int col, int row, A2Methods_UArray2 arr, A2Methods_Object *ptr,
                                                                     void *cl)
{
        (void)arr;
        Pnm_ppm ogPix = (Pnm_ppm)cl;

        int col270 = row;
        int row270 = ogPix->width - col - 1;
        
        *(Pnm_rgb)(ogPix->methods->at(ogPix->pixels, col270, row270)) 
                                                      = *(Pnm_rgb)ptr;
}

/* flip_vert
 * 
 * Purpose: 
 *      To handle to math of placing a pixel in the current image into the 
 *      correct spot of an image that has been flipped vertically
 *
 * Parameters:
 *      int col: column of the element we are currently at
 *      int row: row of the element we are currently at
 *      A2Methods_UArray2 arr: 2D array of either UArray2 or UArray2b
 *      A2Methods_Object *ptr: pointer to a pixel in the original image
 *      void *cl: pointer to the original pnm image
 *      
 * Return: 
 *      nothing
 *      
 * Expects:
 *      *ptr to not be NULL
 *      *cl to not be NULL
 *      
 * Notes:
 *      Neither pointer will ever be null at this point because our mapping
 *      function works correctly where ptr will never be out of bounds, and
 *      we set cl to the original image
 *      
 */
void flip_vert(int col, int row, A2Methods_UArray2 arr, A2Methods_Object *ptr, 
                                                                     void *cl)
{
        (void)arr;
        Pnm_ppm ogPix = (Pnm_ppm)cl;

        int colvert = col;
        int rowvert = ogPix->height - row - 1;
        
        *(Pnm_rgb)(ogPix->methods->at(ogPix->pixels, colvert, rowvert)) 
                                                        = *(Pnm_rgb)ptr;
}

/* flip_horz
 * 
 * Purpose: 
 *      To handle to math of placing a pixel in the current image into the 
 *      correct spot of an image that has been flipped horizontally
 *
 * Parameters:
 *      int col: column of the element we are currently at
 *      int row: row of the element we are currently at
 *      A2Methods_UArray2 arr: 2D array of either UArray2 or UArray2b
 *      A2Methods_Object *ptr: pointer to a pixel in the original image
 *      void *cl: pointer to the original pnm image
 *      
 * Return: 
 *      nothing
 *      
 * Expects:
 *      *ptr to not be NULL
 *      *cl to not be NULL
 *      
 * Notes:
 *      Neither pointer will ever be null at this point because our mapping
 *      function works correctly where ptr will never be out of bounds, and 
 *      we set cl to the original image
 *      
 */
void flip_horz(int col, int row, A2Methods_UArray2 arr, A2Methods_Object *ptr,
                                                                     void *cl)
{
        (void)arr;
        Pnm_ppm ogPix = (Pnm_ppm)cl;


        int colhorz = ogPix->width - col - 1;
        int rowhorz = row;
        
        *(Pnm_rgb)(ogPix->methods->at(ogPix->pixels, colhorz, rowhorz)) 
                                                        = *(Pnm_rgb)ptr;
}