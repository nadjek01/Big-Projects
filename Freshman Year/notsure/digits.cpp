// digits.cpp
//      purpose: report the number of digits in an integer
//        shows: use of output, input, conditional statements
//         note: has bugs, needs work
//
//  modified by: Nana Adjekum
//         date: January 22nd 2022
//

#include <iostream>

using namespace std;

int main()
{
        int input;
    
        cout << "Enter a number: ";
        cin  >> input;
        
        //these are the conditionals for if the integer is positive
        if (input >= 100) 
        {
            cout << "input has three or more digits" << endl;
        } 
        else if ( input >= 10) 
        {
            cout << "input has two digits" << endl;
        } 
        else if (input >= 0 ) 
        {
            cout << "input has one digit" << endl;
        }
        
        //these are the conditionals for if the integer is negative
        if (input <= -100) 
        { 
            cout << "input has three or more digits" << endl;
        }
        else if ( input <= -10)
        {
            cout << "input has two digits" << endl;
        } 
        else if (input < 0) 
        {
            cout << "input has one digit" << endl;
        } 
        /*this conditional will print if the input is negative*/
        if ( input < 0) 
        {
            cout << " and input is negative" << endl;
        }
        
        return 0;
}
