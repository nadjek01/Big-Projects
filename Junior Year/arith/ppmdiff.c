#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "assert.h"
// #include "compress40.h"
// #include "pnmrdr.h"
#include "pnm.h"
// #include "arith40.h"
// #include "a2methods.h"
#include "uarray2.h"
#include "a2plain.h"

FILE *openfile(const char *filename);
void checkDims(Pnm_ppm imageA, Pnm_ppm imageB);
float calculateRMSD(Pnm_ppm imageA, Pnm_ppm imageB);

int main(int argc, char *argv[]) 
{
    assert(argc >= 2);

    FILE *firstFile; 
    FILE *secondFile;
    
    /* attempt to open the two files */
    firstFile = openfile(argv[1]);
    secondFile = openfile(argv[2]);

    /* set methods (default)*/
    A2Methods_T methods = uarray2_methods_plain;

    /* */
    Pnm_ppm image0 = Pnm_ppmread(firstFile, methods);
    Pnm_ppm image1 = Pnm_ppmread(secondFile, methods);

    // fprintf(stderr, "finished reading both files\n");

    /* */
    checkDims(image0, image1);
    
    float RMSD = calculateRMSD(image0, image1);

    fprintf(stdout, "%0.4f\n", RMSD);
    
    Pnm_ppmfree(&image0);
    Pnm_ppmfree(&image1);

    fclose(firstFile);
    fclose(secondFile);

}

FILE *openfile(const char *filename)
{
    FILE *fp = NULL;

    if (filename != NULL) {
        fp = fopen(filename, "rb");
    } else {
        fp = stdin;
    }
    
    return fp;
}

/* check image dimensions (width & height) */
void checkDims(Pnm_ppm imageA, Pnm_ppm imageB)
{
    int widthA = imageA->width;
    int widthB = imageB->width;
    if (abs(widthA - widthB) > 1) {
        fprintf(stderr, "Width differs by more than 1!\n");
        printf("1.0\n");
    } 

    int heightA = imageA->height;
    int heightB = imageB->height;
    if (abs(heightA - heightB) > 1) {
        fprintf(stderr, "Height differs by more than 1!\n");
        printf("1.0\n");
    }

}

/* calculates the RMSD of the two pixels */
float calculateRMSD(Pnm_ppm imageA, Pnm_ppm imageB) 
{
    int width = fmin((int)imageA->width, (int)imageB->width);
    fprintf(stderr, "width: %d\n", width);
    int height = fmin((int)imageA->height, (int)imageB->height);
    fprintf(stderr, "height: %d\n", height);

    float redsum = 0;
    float greensum = 0;
    float bluesum = 0;
    float denomA = imageA->denominator;
    float denomB = imageB->denominator;

    struct Pnm_rgb *ptrA;
    struct Pnm_rgb *ptrB;

    for (int col = 0; col < width; col++) {
        for (int row = 0; row < height; row++) {
            ptrA = (struct Pnm_rgb *)(imageA->methods->at(imageA->pixels, col, row));
            ptrB = (struct Pnm_rgb *)(imageB->methods->at(imageB->pixels, col, row));

            redsum += pow(((*ptrA).red/denomA - (*ptrB).red/denomB), 2);
            greensum += pow(((*ptrA).green/denomA - (*ptrB).green/denomB), 2);
            bluesum += pow(((*ptrA).blue/denomA - (*ptrB).blue/denomB), 2);

        }
    }

    float RMSD = sqrt((redsum + bluesum + greensum) / (3 * width * height));
    return RMSD;

}

