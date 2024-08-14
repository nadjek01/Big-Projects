/*
 * guess.cpp
 * 
 * Purpose: to generate a random integer between 5
 *          and 15 then have the use guess what it is.
 *          the program will then tell the user if their 
 *          guess is higher or lower. the user gets 3 chances.
 * 
 * Name: Nana Adjekum
 * Credits: cplusplus.com, HW02 Guidelines, simplilearn.com
 * Any Bugs/Issues:
 * Date: 02/06/2022
 */

#include <iostream>

// The following are for srand() and time()
// for random numbers. Leave them 
// in your program.
#include <cstdlib>
#include <ctime>

using namespace std;

 
int main()
{
    // Leave the following line as the first line of main.
    // Do not call srand() again.  This is enough to enable
    // you to get a different random number each time you
    // call the program. DO NOT EDIT IT
    srand(time(nullptr));
    //varibles for the program
    int nsecret, firstguess, secondguess, thirdguess;
    
    //nsecret is the computer generated random number
    /*to make sure range was 5-15, I ran the code until I saw
     *it generated both 5 and 15 and nothing above or below*/
    nsecret = 5 + (rand() % 11);
    cout << "Enter a guess: ";
    cin >> firstguess;
    
    //conditional for if guess is correct on the first try
    if(firstguess == nsecret) {
        cout << "You guessed it! ";
        cout << "Good job!" << endl;
    }
    
    //conditional for if guess is too big on first try
    if(firstguess > nsecret) {
        cout << "That was too high. Enter a guess: ";
        cin >> secondguess;
        //conditional for if guess too big on second try
        if(secondguess > nsecret) {
             cout << "That was too high. Enter a guess: ";
             cin >> thirdguess;
            //conditional for if guess equals nsecret on third try
            if(thirdguess == nsecret) {
                 cout << "You guessed it! ";
                 cout << "Good job!" << endl;
            //conditional for if guess doesn't equal nsecret on third try
            } else {
                cout << "The number was " << nsecret << ". ";
                cout << "Better luck next time!" << endl; 
            }
        //conditional for if guess is too small on second try
        } if(secondguess < nsecret) {
            cout << "That was too low. Enter a guess: ";
            cin >> thirdguess;
            if(thirdguess == nsecret) {
                cout << "You guessed it! ";
                cout << "Good job!" << endl;
            } else {
                cout << "The number was " << nsecret << ". ";
                cout << "Better luck next time!" << endl; 
            }
        //conditional for if guess equals nsecret on second try
        } if(secondguess == nsecret) {
            cout << "You guessed it! ";
            cout << "Good job!" << endl;
        } 
    }
    
    //conditional for if guess too small on first try
    /*basically has the same conditionals as the first set but different 
     *because it starts different */
    if(firstguess < nsecret) {
        cout << "That was too low. Enter a guess: ";
        cin >> secondguess;
        if(secondguess == nsecret) {
            cout << "You guessed it! ";
            cout << "Good job!" << endl;
        } if(secondguess > nsecret) {
            cout << "That was too high. Enter a guess: ";
            cin >> thirdguess;
            if(thirdguess == nsecret) {
                cout << "You guessed it! ";
                cout << "Good job!" << endl;
            } else {
                cout << "The number was " << nsecret << ". ";
                cout << "Better luck next time!" << endl; 
            }
        }
        if(secondguess < nsecret) {
            cout << "That was too low. Enter a guess: ";
            cin >> thirdguess;
            if(thirdguess == nsecret) {
                cout << "You guessed it! ";
                cout << "Good job!" << endl;
            }
            else {
                cout << "The number was " << nsecret << ". ";
                cout << "Better luck next time!" << endl; 
            }
        }
    }

    return 0;
}

