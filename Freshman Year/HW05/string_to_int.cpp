/*
 * string_converter.cpp
 * Program to test the string_to_int function, whose contract appears below
 * Essential idea:  extract digits from a string and return the integer that
 *                  results.  E. g., "a1b2c3" should produce the integer 123
 *
 * By:  Nana Adjekum
 * Credits: HW05
 * Any Bugs/Issues:
 * Date: 03/01/22
 */

#include <iostream>

using namespace std;

//the functions for the program, defined below
int string_to_int(string s);
void testing (string y, int x);

/*
 * main function tests the string_to_int function
 */
int main()
{
    //declares and defines the variables to be tested
    string test1 = "123ab6";
    string test2 = "cs11issoc00L";
    string test3 = "ericmetajisgr8";
    string test4 = "cann0L15";
    
    //call the testing function
    testing (test1, 1236);
    testing (test2, 1100);
    testing (test3, 8);
    testing (test4, 15);
        
                
        return 0;
}

/*
 * Purpose:   extract an integer from the digit characters in a string
 * Arg:       string that may or may not contain digit characters ('0' -- '9')
 * Returns:   the integer that result from extracting digits from string s
 * Notes:     only digit characters are considered.  
 *            Sign characters ('+', '-') are non-digits and are ignored
 * Examples:  "123abc56"   => 12356
 *            "   2times3" => 23
 *            "help me!"   => 0
 *            ""           => 0
 */

/*function converts ints to strings by taking the numbers
 *one by one, subtracts by the value of the char 0 and 
 *multiplies by 10 */
int string_to_int(string s) {
    int total = 0;
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] >= '0' and s[i] <= '9') {
            int num = s[i] - '0';
            total = total * 10 + num;
        } 
    } return total;
    return 0;
}
/*function prints out the testing string
 *and its results and calls the function above
 *it also checks if the test case works */
void testing (string tword, int tnum) {
    cout << "TESTING: " << tword << endl;
    if (string_to_int(tword) == tnum) {
        cout << "SUCCESS: " << string_to_int(tword) << endl;
    } else {
        cout << "FAILURE: " << string_to_int(tword) << endl;
    }
}