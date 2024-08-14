/*
 *  restoration.c- "the Implementation"
 *  Harsh Sinha (hsinha02) and Nana Adjekum (nadjek01)
 *  
 *  19-Sept
 *
 *  CS 40 HW 1
 *
 *  
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "restoration.h"
#include "readaline.h"
#include "except.h"
#include "mem.h"
#include "table.h"
#include <atom.h>
#include <seq.h>

#define T Table_T
#define INIT_BYTES 200

Except_T Open_E = {"error while opening file"};
Except_T OverOne_E = {"client provided more than one file"};
Except_T NoInput_E = {"input expected but not provided"};
Except_T NullParam_E = {"one or more parameters supplied are NULL"};
Except_T File_E = {"error encounter while reading from the file"};
Except_T ReadMalloc_E = {"error allocating memory"};

int main(int argc, char *argv[])
{
   
    if (argc == 1)
    {
        RAISE(NoInput_E);
    }
    if (argc != 2)
    {
        RAISE(OverOne_E);
    }

    FILE *fp = fopen(argv[1], "r");

    
    if (fp == NULL)
    {  
        RAISE(Open_E);
    }

    char *line = NULL;
    size_t line_length = 0;

    Table_T hashtable = Table_new(100, NULL, NULL);

    int **imageRaster = NULL;
    int currentHeight = -1;
    int rasterWidth = 0;
    int *digits = NULL;
    char *nonDigits = NULL;

    const char *abcKey = NULL;
    int digitsInLine = 0;
    int *firstLine;
    int found = 0;
    while (!feof(fp))
    {
        line_length = readaline(fp, &line);
       
        if (!digits)
        {
            digits = (int *)malloc(line_length * sizeof(int));
        }
        if (!nonDigits)
        {
            nonDigits = (char *)malloc(line_length * sizeof(char) + 2);
        }
        // memory allocation error check
        if (digits == NULL || nonDigits == NULL || line == NULL)
        {
            RAISE(ReadMalloc_E);
        }

        digitsInLine = splitDigitsAndNonDigits(line, digits, 
        nonDigits, (int)line_length);
       
        if (nonDigits != NULL)
        {
            //use atom_new for /0 char edge case
            abcKey = Atom_new(nonDigits, strlen(nonDigits));
        }

        //create new string bc C doesn't alloc as we liked bc no operator
        //overloading
        int *newDigits = deepcopy(digits, digitsInLine * sizeof(int));
        if (Table_get(hashtable, abcKey) != NULL)
        {
            currentHeight++;
            //found a flag
            //if equal to 1 then have found the infusion
            //if not keep inserting into the table
            if (found == 0)
            {
                rasterWidth = digitsInLine;
                firstLine = Table_get(hashtable, abcKey);
                found = 1;
            }

            imageRaster = extendImageRaster(imageRaster, newDigits, 
                                            currentHeight);
        }

        if (Table_get(hashtable, abcKey) == NULL)
        {
            Table_put(hashtable, abcKey, newDigits);
        }

        newDigits = NULL;
        
        free(nonDigits);
        nonDigits = NULL;

        free(line);
        line = NULL;

        if (digits != NULL)
        {
            free(digits);
            digits = NULL;
        }
    }

    printImageRaster(imageRaster, currentHeight, rasterWidth, firstLine);

    Table_map(hashtable, free_digits, NULL);
    Table_free(&hashtable);
    for (int i = 0; i < (currentHeight + 2); i++)
    {
        free(imageRaster[i]);
    }
    free(imageRaster);
    
    fclose(fp);
    exit(EXIT_SUCCESS);
}

/*****************************************************************
 *
 *                          deepcopy
 *
 *   Parameters: an array of ints (src) and a size_t
 *               corresponding to the length of the array
 *               (len)
 *
 *   Returns: a resized array
 *
 *   Purpose:
 *              deep copies over values of an array
 *              into a resized array--so we allocate
 *              enough space
 *   Exceptions:
 *              Raises exception when there is an
 *              error when reallocating memory
 *
 *****************************************************************/
int *deepcopy(const int *src, size_t len)
{
    if (src == NULL)
        return NULL;

    // Allocate new memory for the deep copy
    int *copy = malloc(len);
    if (copy == NULL)
    {
        RAISE(ReadMalloc_E);
    }

    memcpy(copy, src, len);
    return copy;
}

/*****************************************************************
 *
 *                          free_digits
 *
 *   Parameters: 2 void pointers (key) & (cl) and a pointer to
 *               a undisclosed element
 *
 *   Returns: nothing (void)
 *
 *   Purpose:
 *              frees the digit array
 *   Exceptions:
 *              None
 *
 *****************************************************************/
void free_digits(const void *key, void **value, void *cl)
{
    (void)cl;
    (void)key;
    free(*value);
}

/*****************************************************************
 *
 *                          printImageRaster
 *
 *   Parameters: pointer to the values of the image which are held in
 *               in an int array (imageRaster), int that represents the
 *               values of the height and width of the image
 *
 *   Returns: nothing (void)
 *
 *   Purpose:
 *              Prints out the restored image with the correct values
 *              of the photo and the correct formatting
 *   Exceptions:
 *              None
 *
 *****************************************************************/
void printImageRaster(int **imageRaster, int currentHeight, 
                        int rasterWidth, int *firstLine)
{
    //if there is nothing in the file, this is where
    //we raise the exception
    //also currentHeight is set to -1
    if (rasterWidth == 0 && (currentHeight + 1) == 0) {
        RAISE(NullParam_E);
    }

    printf("P5 %d %d %d\n", rasterWidth, currentHeight + 1, 255);

    for (int i = 0; i < rasterWidth; i++)
    {
        printf("%c", firstLine[i]);
    }
    printf("\n");

    for (int i = 0; i < currentHeight + 1; i++)
    {
        for (int j = 0; j < rasterWidth; j++)
        {
            printf("%c", imageRaster[i][j]);
        }

    }
}

/*****************************************************************
 *
 *                          extendImageRaster
 *
 *   Parameters: a pointer to a char array (linedubp) and an array of
 *               ints (bytesalloc)
 *
 *   Returns: int newimageraster which is extended
 *
 *   Purpose:
 *              Extends the 2d array representing the
 *              output of the image by calling realloc
 *              and reallocating space
 *   Exceptions:
 *              The function raises one exception when there
 *              is an is an issue allocating memory
 *
 *****************************************************************/
int **extendImageRaster(int **imageRaster, int *digits, int currentHeight)
{
    int **newImageRaster = (int **)realloc(imageRaster, 
                            sizeof(int *) * (currentHeight + 2));

    if (newImageRaster == NULL)
    {
        RAISE(ReadMalloc_E);
    }

    newImageRaster[currentHeight] = digits;
    newImageRaster[currentHeight + 1] = NULL;
    return newImageRaster;
}

/*****************************************************************
 *
 *                          splitDigitsAndNonDigits
 *
 *   Parameters: a char array which represents the line from the file,
 *               (line), two pointers to distinct arrays--one for
 *               the digits representing the vals of the t
 *
 *   Returns: nothing (void)
 *
 *   Purpose:
 *              Called in readaline when there needs to be more
 *              bytes allocated to the char array (line) (i.e. resizes 
 *                the array)
 *   Exceptions:
 *              The function raises one exception when there is an issue
 *              reallocation memory for the char array
 *
 *****************************************************************/
int splitDigitsAndNonDigits(const char *line, int *digits, 
                            char *nonDigits, int line_length)
{

    int digitIndex = 0;
    int nonDigitIndex = 0;

    int i = 0;
    while (i < line_length)
    {
        if (!(line[i] >= '0' && line[i] <= '9'))
        {
            nonDigits[nonDigitIndex++] = line[i];
            i++;
        }
        else if (isdigit(line[i]) || (line[i] >= '0' && line[i] <= '9'))
        {
            // Check if the character is a printable non-digit character
            int result = 0;
            while (isdigit(line[i]))
            {
                result = result * 10 + (line[i] - (int)('0'));
                i++;
                
            }

            digits[digitIndex++] = result;
        }
    }
    
    nonDigits[nonDigitIndex] = '\0';
    return digitIndex;
}

/*****************************************************************
 *
 *                          realloc_string
 *
 *   Parameters: a pointer to a char array (linedubp) and
 *               ints (bytesalloc)
 *
 *   Returns: char* newlinedubp--the reallocated string
 *
 *   Purpose:
 *              Called in restoration when there needs to be more
 *              bytes allocated to the char array (line) 
 *              (i.e. resizes the array)
 *              
 *   Exceptions:
 *              The function raises two exception when the
 *              linedubp is null and newlinedubp is null 
 *              
 *
 *****************************************************************/
char *realloc_string(char *linedubp, int bytes_alloc)
{
    if (linedubp == NULL)
    {
        RAISE(NullParam_E);
    }

    char *newlinedubp = realloc(linedubp, bytes_alloc);

    if (newlinedubp == NULL)
    {
        RAISE(ReadMalloc_E);
    }
    return newlinedubp;
}
