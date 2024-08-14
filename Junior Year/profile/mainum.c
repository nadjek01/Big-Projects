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
#include <bitpack.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stack.h>

#define WIDTH 8

/************* OPCODES ****************/
typedef enum opcodes {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, MAP, UNMAP, OUT, IN, LOADP, LOADV
} opcodes;

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

        /* grab the size of the input file */
        struct stat umfile;

        if (stat(filename, &umfile) == -1) {
                perror("stat");
                exit(EXIT_FAILURE);
        }

        off_t numbytes = umfile.st_size;

        int numinstructs = numbytes / 4;

        /* CALLOC: initialize segmented memory space (initially 10 segments) */
        uint32_t **segmentIDs;
        segmentIDs = calloc(10, sizeof(uint32_t *));

        /* build a (NON-CALLOC'D) array for the 0 segment */
        // uint32_t zerosegment[numinstructs];
        uint32_t *zerosegment;
        zerosegment = calloc(numinstructs, sizeof(uint32_t));

        /* Pull instructions from input file to 0 segment */
        int index = 0; 
        int byte = getc(fp); /* get the first byte */
        while (byte != EOF)
        {
                uint32_t word = 0;
                unsigned lsb = 24;
                
                /* grab 4 bytes at a time and pack into a 32-bit word */
                for (int i = 0; i < 4; i++) {
                        word = Bitpack_newu(word, WIDTH, lsb, byte);
                        lsb -= 8;
                        byte = getc(fp);
                }

                /* insert the word into the zero segment */
                zerosegment[index] = word;
                index++;
        }

        /* place the zero segment in the 0th index of segmented memory */
        segmentIDs[0] = zerosegment;

        /* initialize the registers */
        uint32_t registers[8] = {0};

        /* initialize program counter */
        int pcount = 0;

        /* CALLOC: initialize an array for segment sizes*/
        uint32_t *segLengths = calloc(10, sizeof(uint32_t)); 
        segLengths[0] = numinstructs; // NEW

        uint32_t instruction;
        uint32_t code = 0;
        bool exit = false;      
        uint32_t length = 10;        /* current size of segmented memory */
	uint32_t curr_segID = 0;     /* current segment ID # */
        uint32_t totalsegments = 1;  /* number of actually mapped segments */

        /* initialize the arary for available ID #'s */
        uint32_t *freedIDs;
        freedIDs = calloc(length, sizeof(uint32_t));
        // int maxFreeID = numinstructs;
        int stackPointer = -1;
                                
        uint32_t ra = 0;
        uint32_t rb = 0;
        uint32_t rc = 0;
        
        /* opcode mask */
        uint32_t maskOC = ~0;
        maskOC = maskOC >> 28;
        maskOC = maskOC << 28;

        /* register A mask */
        uint32_t maskA = ~0;
        maskA = maskA >> 29;
        maskA = maskA << 6;

        /* register B mask */
        uint32_t maskB = ~0;
        maskB = maskB >> 29;
        maskB = maskB << 3;

        /* register C mask */
        uint32_t maskC = ~0;
        maskC = maskC >> 29;

        /* load mask for register */
        uint32_t loadmask = ~0;
        loadmask = loadmask >> 29;
        loadmask = loadmask << 25;

        /* load value mask for value */
        uint32_t valuemask = ~0;
        valuemask = valuemask >> 7;

        
        do {
                instruction = segmentIDs[0][pcount]; /* grab current instruction */

                code = (instruction & maskOC) >> 28;

                
                if (code != LOADV) { /* three-register instructions */
                        ra = (instruction & maskA) >> 6;
                        rb = (instruction & maskB) >> 3;
                        rc = (instruction & maskC);
                        

                        if (code == CMOV) {
                                if (registers[rc] != 0) {
                                                (registers[ra] = registers[rb]);
                                }
                        } else if (code == SLOAD) {
                                registers[ra] = segmentIDs[registers[rb]][registers[rc]];
                        } else if  (code == SSTORE) {  /* register to segment */
                                segmentIDs[registers[ra]][registers[rb]] = registers[rc];
                        } else if  (code == ADD) {
                            	registers[ra] = registers[rb] + registers[rc];
                        } else if  (code == MUL) {
                            	registers[ra] = registers[rb] * registers[rc];
                        } else if  (code == DIV) {
                            	registers[ra] = registers[rb] / registers[rc];
                        } else if  (code == NAND) {
                            	registers[ra] = ~(registers[rb] & registers[rc]);
                        } else if  (code == MAP) {
                                /* first, check for available segment IDs */
                                if (stackPointer >= 0) {
                                        curr_segID = freedIDs[stackPointer];
                                        stackPointer -= 1;
				} else {
					curr_segID++;
                                        totalsegments = curr_segID;
				}
				/* then, check if we need more segment space */ 
				if (curr_segID >= length) {
                                        length *= 2;
					size_t new_size = length * sizeof(uint32_t *);
					segmentIDs = (uint32_t **)realloc(segmentIDs, new_size);
                                        segLengths = (uint32_t *)realloc(segLengths, new_size);
                                        freedIDs = (uint32_t *)realloc(freedIDs, new_size);
				}

                                uint32_t numwords = registers[rc];

                                uint32_t *nextsegment = calloc(numwords, sizeof(uint32_t));

                                segmentIDs[curr_segID] = nextsegment;
                                segLengths[curr_segID] = numwords;

				registers[rb] = curr_segID;     /* save the segment ID in a register */
                        }else if  (code == UNMAP) {
				uint32_t unmapID = registers[rc];

				stackPointer++;
                                freedIDs[stackPointer] = unmapID;

                                free(segmentIDs[unmapID]);

                                segmentIDs[unmapID] = NULL;
                                segLengths[unmapID] = 0;

                        } else if (code == OUT) {
                                uint32_t value = registers[rc];
                                fprintf(stdout, "%c", value);
                        } else if (code == IN) {
                                
                                char value = 0;
                                int result = scanf("%c", &value);
                                if (result == EOF) {
                                        registers[rc] = ~0;

                                } else {
                                        registers[rc] = (uint32_t)value;

                                }

                        } else if  (code == LOADP) {

                                if (registers[rb] != 0) {
                                        /* grab the old segment & its length*/
                                        uint32_t *newZero = segmentIDs[registers[rb]];
                                        uint32_t newLength = segLengths[registers[rb]];

                                        /* resize the old zero segment so it's the size of the new segment */
                                        size_t newsize = newLength * sizeof(uint32_t);
                                        segmentIDs[0] = realloc(segmentIDs[0], newsize );

                                        /* copy into the new array */
                                        memcpy(segmentIDs[0], newZero, newsize);

                                        /* reassign 0 segment pointer to the new 0 segment */
                                        /* update the lengths array */
                                        segLengths[0] = newLength;
                                }

                                /* update the program counter */
                                pcount = registers[rc];


                                continue;
                                
                        } else if (code == HALT) {
                                exit = true;
                        }
                } else if (code == LOADV) {
                        
                        ra = (instruction & loadmask) >> 25;
                        uint32_t value = (instruction & valuemask);
                        registers[ra] = value;

                } else {
                        return(EXIT_FAILURE);
                }
                        
                pcount++;


        } while (exit == false);
        
        fclose(fp);


        for (unsigned i = 0; i <= totalsegments; i++) {
                if (segLengths[i] != 0) {
                        free(segmentIDs[i]);
                }
        }


        free(segmentIDs);
        free(segLengths);
        free(freedIDs);

        return(EXIT_SUCCESS);
}
