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

//functions to be used will be described below
string int_to_string(int num);
char converter (int left);
void testing(int tnum, string tword);

/*
 * main function tests the string_to_int function
 */
int main()
{
        //declares and defines the (hardcoded) testing variables 
        int test1 = 123;
        int test2 = 9876;
        int test3 = 12;
        int test4 = -5;
        
        testing(test1, "123");
        testing(test2, "9876");
        testing(test3, "12");
        testing(test4, "-5");
        
                
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

/*takes the int and converts it to a string 
 *by div the num by 10 and mod 10 (to get the digit by itself
 *and sends it to the converter)and concatanating it 
 *to the other converted digits */
string int_to_string(int num) {
    if (num == 0) {
        return "";
    } else if (num < 0) {
        return "-" + int_to_string (-1 * num);
    } else {
        return ((int_to_string (num / 10)) + converter (num % 10));
    }
}
/*the actual converter, takes the value of mod 10
 *and adds it to the value of the char 0 */
char converter (int left) {
    char letter = '0' + left;
    return letter;
}
/*the testing function: prints out the test case
 *and calls the int_to_string function */
void testing(int tnum, string tword) {
    cout << "TESTING: " << tnum << endl;
    if (int_to_string(tnum) == tword) {
        cout << "SUCCESS: " << int_to_string(tnum) << endl;
    } else {
        cout << "FAILURE: " << int_to_string(tnum) << endl;
    }
    
}
