
//---------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "readaline.h"
#include "except.h"

#define INIT_BYTES 200

Except_T NullParam_ER = {"one or more readaline() parameters supplied"
                         "are NULL"};
Except_T Open_ER = {"error while opening file"};
Except_T File_ER = {"error encounter while reading from the file"};
Except_T ReadMalloc_ER = {"error allocating memory"};

void realloc_line(char **linedubp, int *bytes_alloc);
void create_string(char **linedubp, char currchar, int i);

/*****************************************************************
 *
 *                          readaline
 *
 *   Parameters: pointer to a file (inputfd) and a pointer to a
 *               char array (datapp)
 *   Returns: the number of characters in the file (unsigned element size_t)
 *
 *   Purpose:
 *              Called in the main function, main purpose is
 *              to read in the lines of the corrupted PGM
 *              and return the size of the corrupted file
 *   Exceptions:
 *              The function raises 3 exceptions: null parameters
 *              error when reading in the file, error allocating
 *              memory when reallocating space in the char array
 *
 *****************************************************************/

size_t readaline(FILE *inputfd, char **datapp)
{

    char currchar;
    int num_curr_char = 0;
    int bytes_alloc = INIT_BYTES;

    if (inputfd == NULL)
    {
        RAISE(Open_ER);
    }
    

    assert(datapp != NULL);
    // assert(!ferror(inputfd));

    if (feof(inputfd))
    {
        *datapp = NULL;
        return 0;
    }

    char *mergedline = (char *)malloc(INIT_BYTES);
    if (mergedline == NULL)
    {
        RAISE(ReadMalloc_ER);
    }

    while (!feof(inputfd) && !ferror(inputfd))
    {
        // printf("inwhilecallcs\n");

        currchar = fgetc(inputfd);

        create_string(&mergedline, currchar, num_curr_char);

        if (currchar == '\n')
        {
            break;
        }
        // printf("inwhileaftercallcs\n");
        if (num_curr_char >= bytes_alloc - 1)
        {
            // printf("inwhilecallrealloc\n");
            realloc_line(&mergedline, &bytes_alloc);
        }
        num_curr_char++;
    }

    if (ferror(inputfd))
    {
        RAISE(File_ER);
    }

    // mergedline[num_curr_char] = currchar;
    *datapp = mergedline;
    // free(mergedline);
    // printf("done\n");
    return num_curr_char;
}

/*****************************************************************
 *
 *                          realloc_line
 *
 *   Parameters: a pointer to a char array (linedubp) and an array of
 *               ints (bytesalloc)
 *
 *   Returns: nothing (void)
 *
 *   Purpose:
 *              Called in readaline when there needs to be more
 *              bytes allocated to the char array (line)
 *              (i.e. resizes the array)
 *   Exceptions:
 *              The function raises one exception when there is an issue
 *              reallocation memory for the char array
 *
 *****************************************************************/
void realloc_line(char **linedubp, int *bytes_alloc)
{
    if (linedubp == NULL || bytes_alloc == NULL)
    {
        RAISE(NullParam_ER);
    }
    *bytes_alloc = (*bytes_alloc * 2) + 1;
    *linedubp = realloc(*linedubp, *bytes_alloc);
    if (*linedubp == NULL)
    {
        RAISE(ReadMalloc_ER);
    }
}

/*****************************************************************
 *
 *                          create_string
 *
 *   Parameters: a pointer to the char array that is the line
 *               being read in (linedubp), a character that is
 *               the current char to be added to the line (currchar), and
 *               and an int which tells the line at what point
 *               concatenate (i)
 *
 *   Returns: nothing (void)
 *
 *   Purpose:
 *              Creates the string representation of the line
 *              so we then can parse it and whatnot
 *
 *   Exceptions:
 *              The function raises one exception when the line
 *              is NULL
 *
 *****************************************************************/
void create_string(char **linedubp, char currchar, int i)
{
    if (linedubp == NULL)
    {
        RAISE(NullParam_ER);
    }
    *(*linedubp + i) = currchar;
}

#undef INIT_BYTES
