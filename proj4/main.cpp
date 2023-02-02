/*
 *  main.cpp- ""
 *  Max Samuels and Nana Adjekum
 *  5-Dec
 *
 *  CS 15 Proj 4 GERP
 *
 *  TD FC
 *
 */

#include "HashTable.h"
using namespace std;

int main (int argc, char *argv[])
{
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        exit(EXIT_FAILURE);
    } else {
        HashTable search;
        search.run(argv); 
    }
}