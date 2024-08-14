#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "compress40.h"

static void (*compress_or_decompress)(FILE *input) = compress40;

int main(int argc, char *argv[])
{
        (void)argc;
        char *filename = argv[1];

        FILE *file = NULL;

        if (filename != NULL) {
                file = fopen(filename, "r");
        } else {
                file = stdin;
        }

        compress_or_decompress(file);

        fclose(file);
        
        return EXIT_SUCCESS; 
}