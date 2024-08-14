/*
 * guess.cpp
 * 
 * Purpose: plays Rock Paper Scissors with user
 * 
 * Name: Nana Adjekum
 * Credits: cplusplus.com, HW02 Guidelines
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

/*line 26 declares and initializes a function to convert
*the char input by the user to a number. each number is 
*equal to rock, paper, or scissors. rock is 0, paper is 2
*and scissors is 2 */
int userinput(char userchar);
/*line 29 declares and initializes a function that chooses
*the winner of the game*/
void chosewinner(int userchoice, int computerchoice);
int main()
{
    // Leave the following line as the first line of main.
    // Do not call srand() again.  This is enough to enable
    // you to get a different random number each time you
    // call the program. DO NOT EDIT IT
    srand(time(nullptr));
    //this variable is for the og user input
    char rpsuserletter;
    //this variable is for the converted char variable
    int rpsuserinput; 
    
    int rpssecret = (rand() % 3);
    
    cout << "Enter rock (r), paper (p), or scissors (s): ";
    cin >> rpsuserletter;
    /*line 48 makes the letter lower case if
    *if the letter is inputted as an upper case */
    rpsuserletter = tolower(rpsuserletter);
    /*rpsuserinput is equal to the result of calling the userinput
    *function */
    rpsuserinput = userinput(rpsuserletter);
    
    
    
    //calls function that prints out the results of the game
    chosewinner(rpsuserinput, rpssecret);
    
    return 0;
}
int userinput(char userchar)
{
    /*conditionals for when the userinput is equal to certain
    *characters */
    if(userchar == 'r') {
        int cuserinput = 0;
        return cuserinput;
    } if(userchar == 'p') {
        int cuserinput = 1;
        return cuserinput;
    } if(userchar == 's') {
        int cuserinput = 2;
        return cuserinput;
    }
    return 0;
}
void chosewinner(int userchoice, int computerchoice)
{
    //conditionals for when the userchoice is equal to 0 or rock
    if(userchoice == 0 and computerchoice == 0) {
        cout << "It's a tie. The computer also chose rock." << endl;
    } else if(userchoice == 0 and computerchoice == 1) {
        cout << "You lost. The computer chose paper." << endl;
    } else if(userchoice == 0 and computerchoice == 2) {
        cout << "You won! The computer chose scissors." << endl;
    }

    //conditionals for when the userchoice is equal to 1 or paper
    else if(userchoice == 1 and computerchoice == 1) {
        cout << "It's a tie. The computer also chose paper." << endl;
    } else if(userchoice == 1 and computerchoice == 0) {
        cout << "You won! The computer chose rock." << endl;
    } else if(userchoice == 1 and computerchoice == 2) {
        cout << "You lost. The computer chose scissors." << endl;
    }
    
    //conditionals for when the userchoice is equal to 2 or scissors
    else if(userchoice == 2 and computerchoice == 2) {
        cout << "It's a tie. The computer also chose scissors." << endl;
    } else if(userchoice == 2 and computerchoice == 1) {
        cout << "You won! The computer chose paper." << endl;
    } else if(userchoice == 2 and computerchoice == 0) {
        cout << "You lost. The computer chose rock." << endl;
    }
}
