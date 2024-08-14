/*
 *  stringProcessing.cpp- "the Implementation"
 *  Max Samuels and Nana Adjekum
 *  30-Nov
 *
 *  CS 15 Proj 4 GERP
 *
 *  TD FC
 *
 */

#include "stringProcessing.h"
#include <iostream>
using namespace std;

//TD FC
std::string stripNonAlphaNum (std::string input)
{
    while ((not isalnum(input[0])) and (not input.empty())) {
        input.erase(0,1);
    }

    while ((not isalnum(input[input.size() - 1])) and (not input.empty())) {
        input.pop_back();
    }

    return input;
}