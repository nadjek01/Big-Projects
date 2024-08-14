// 
// add8.cpp
// purpose: find the sum of 8 numbers that are inputted by the user
//  author: Nana Adjekum
//    date: 2/1/22
//
/* alternative stategies: made to variables as you go down you add 2 to the
variable. It works for this assignment, but does not actually calculate
the sum of the 8 numbers inputted by the user. Will further explore */
/* shopworked the previously mentioned stragety. created two variables 
one for the input and the other that served as a storage for the 
addition of the new numbers. */
//
#include <iostream>

using namespace std;

int main ()
{
    //line 21 identifies and initializes the variables to be used.
    float storage(0), userinput, sum(0);
    
    /*lines 27 to 57 prompt users to input a floating point number. they also
    save each input and add it to the previous input. in the beginning the
    variable storage is set to zero but as it goes down the line it changes
    to whatever the previous input is plus the current input */
    cout << "Enter a floating point number: ";
    cin >> userinput;
    storage = storage + userinput;
    
    cout << "Enter a floating point number: ";
    cin >> userinput;
    storage = storage + userinput;
    
    cout << "Enter a floating point number: ";
    cin >> userinput;
    storage = storage + userinput;
    
    cout << "Enter a floating point number: ";
    cin >> userinput;
    storage = storage + userinput;
    
    cout << "Enter a floating point number: ";
    cin >> userinput;
    storage = storage + userinput;
    
    cout << "Enter a floating point number: ";
    cin >> userinput;
    storage = storage + userinput;
    
    cout << "Enter a floating point number: ";
    cin >> userinput;
    storage = storage + userinput;
    
    cout << "Enter a floating point number: ";
    cin >> userinput;
    storage = storage + userinput;
    
    //line 61 allows for the sum variable to get the last storage calculated
    //line 62 prints this sum
    sum = storage;
    cout << "The sum is: " << sum << endl;
    
        
    return 0;
}