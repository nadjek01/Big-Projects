// make_change.cpp
//  purpose: find the number of quarters, dimes, nickels, and pennies
//          to dispense for a specified amount of change, using the minimum
//         amount of coins
//  author: Nana Adjekum
//   date: 2/1/22
//
#include <iostream>

using namespace std;

int main ()
{
    int cents(1);
    
    //prints out Amount of change in cents for user input
    cout << "Amount of change in cents: ";
    cin >> cents;
    
    /*the value of the variable quarters is set to the value of 
    cents divided by 25*/
    int quarters = cents / 25;
    cout << quarters << " quarters, ";
    /*quarterleftover references the amount of cents left from the user input
    to be converted into dimes (if applicable) */
    int quarterleftover = cents - (quarters * 25);
    
    /*the value of the variable dimes is set to the value of 
    quarterleftover divided by 10*/
    int dimes = quarterleftover / 10;
    cout << dimes << " dimes, ";
    /*dimeleftover references the amount of cents left from the user input
    to be converted into nickels (if applicable)*/
    int dimeleftover = quarterleftover - (dimes * 10);
    
    /*the value of the variable nickels is set to the value of 
    dimeleftover divided by 5*/       
    int nickels = dimeleftover / 5;
    cout << nickels << " nickels, ";
    /*nickelleftover references the amount of cents left from the user input
    to be converted into pennies (if applicable)*/
    int nickelleftover = dimeleftover - (nickels * 5);
    
    /*the value of the variable pennies is set to the value of 
    nickelleftover divided by 10*/            
    int pennies = nickelleftover / 1;
    cout << pennies << " pennies" << endl;
     
    return 0;
}