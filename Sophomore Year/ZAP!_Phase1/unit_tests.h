/*
 *  unit_test.h
 *  Nana Adjekum
 *  8-Nov
 *
 *  CS 15 Proj3 ZAP
 *
 *  Tester for ZAP
 *
 */

#include "phaseOne.h"
using namespace std;
#include <iostream>
#include <sstream>
#include <cassert>

//TD FC
void testingcountfreq() {

    std::stringstream a_stream;
    string temp = "Banana";
    a_stream >> temp;
    count_freqs(a_stream);

}