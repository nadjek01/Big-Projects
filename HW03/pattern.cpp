/*
 * guess.cpp
 * 
 * Purpose: print out a pattern of repeating strings based on user input
 * 
 * Name: Nana Adjekum
 * Credits: HW03 Guidelines
 * Any Bugs/Issues:
 * Date: 02/10/2022
 */

#include <iostream>

using namespace std;

//functions to be used will be explained below
void output_pattern(string s1, string s2, int n);
void oddoutput_pattern(string s1, string s2, int n);
void oneprintline (string a1, string a2, int c);
void twoprintline (string z1, string z2, int c);
int main()
{
    //variables for user input
    string oneword, twoword;
    int number;
    cin >> oneword >> twoword >> number;
    
    /*if the users number input is even the og output_pattern 
    *function is called */
    if (number % 2 == 0) {
        output_pattern (oneword, twoword, number);
    /*if users number input is odd the odd output_pattern
    *function is called */
} else if (number % 2 != 0){
        oddoutput_pattern (oneword, twoword, number);
    }
    
    return 0;
}
void output_pattern(string s1, string s2, int n)
{
    //if n is 0 it returns to main
    if (n <= 0) {
        return;
    /*these conditionals are for what order the words
     *will be printed out. the word order is dependent on if
     *the value of n is even or odd */
    } else if (n % 2 == 0) {           
        oneprintline(s1, s2, 5);       
        output_pattern(s1, s2, (n - 1)); 
    } else if (n % 2 != 0) {                
        twoprintline(s2, s1, 5);
        output_pattern(s1, s2, (n - 1));
    }
}
void oddoutput_pattern(string s1, string s2, int n)
{
    if (n <= 0) {
        return;
    } else if (n % 2 == 0) {
        twoprintline(s2, s1, 5);
        oddoutput_pattern(s1, s2, (n - 1));
    } else if (n % 2 != 0) {
        oneprintline(s1, s2, 5);
        oddoutput_pattern(s1, s2, (n - 1));
    }
}
//this prints out oneword and twoword (in that order)
void oneprintline(string a1, string a2, int c)
{
    if (c <= 0) {
        cout << endl;
    } else {
        cout << a1;
        cout << a2; 
        oneprintline(a1, a2, (c - 1));
    }
}
//this prints out twoword and oneword (in that order)
void twoprintline(string z1, string z2, int c)
{
    if (c <= 0) {
        cout << endl;
    } else {
        cout << z1;
        cout << z2; 
        twoprintline(z1, z2, (c - 1));
    }
}

