/*
 *
 */
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

std::string parseRString(std::istream &input)
{
    string r_string = "{ ";
    string temp = "";

    input >> temp;

    int count = 1;
    bool there = true;

    while (there) {

        if (temp == "{") {
            count ++;

        } else if (temp == "}") {
            count --;

        }

        if (count == 0) {
            r_string += temp;
            there = false;

        } else {
            r_string += temp + " ";
            input >> temp;
            
        }
    }

    return r_string;
}