/* mainum.c
*
* by Ayah Harper and Nana Adjekum
*
* purpose: main file for the um program. processes
* command line arguments, then calls functions to initialize
* the emulator and execute the instructions in the provided file
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "processfile.h"
#include "execute.h"

int main (int argc, char *argv[])
{

        /* check command line + open the file */
        FILE *fp;
        assert(argc == 2);
        char *filename = argv[1];
        fp = fopen(filename, "rb");

        if (fp == NULL) {
                fprintf(stderr, "Error opening file: %s\n", filename);
                return(EXIT_FAILURE);
        }

        /* intialize the segmented memory */
        Seq_T segmented_memory = processFile(fp);

        /* start executing instructions!*/
        execute_program(segmented_memory);

        fclose(fp);

        return(EXIT_SUCCESS);
}