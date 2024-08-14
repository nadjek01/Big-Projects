/*
 *  main.cpp- "the Client"
 *  Nana Adjekum
 *  19-Oct
 *
 *  CS 15 Proj2 CalcYouLater
 *
 *  main function for the CalcYouLater
 *  -this is where the RPNCalc class is
 *   made available to the client
 *
 */

#include <iostream>
#include <string>
#include "DatumStack.h"
#include "RPNCalc.h"

using namespace std;

int main()
{
    RPNCalc Calculate;
    Calculate.run();

    return 0;
}
