/*
 * dictionary.cpp
 * 
 * Purpose: provide the user with a dictionary definition without prompting
 *          them
 * 
 * Name: Nana Adjekum
 * Credits: HW03 Guidelines
 * Any Bugs/Issues:
 * Date: 02/10/2022
 */

#include <iostream>

using namespace std;

//functions to be used
void dictionary ();
void definevar ();
void definefunct ();
void definerecursion ();
void definepseudo ();
void definecondt ();
void definecs11 ();
void defineparameter ();

int main()
{

    dictionary ();
    
    return 0;
}
/*this function takes the user input and calls the
 *respective function for the definition of the user input */ 
void dictionary ()
{
    /*line 41-44 defines and declares the variables
     *and lowers the first 2 letters (tolower wasnt)
     *working for the entire word */
    string word;
    cin >> word;
    word [0] = tolower (word [0]);
    word [1] = tolower (word [1]);
    
    /*conditionals for when the users input is equal 
     *to a specific string of words*/
    if (word == "variable") {
        definevar ();
    } else if (word == "function") {
        definefunct ();
    } else if (word == "recursion") {
        definerecursion ();
    } else if (word == "pseudocode") {
        definepseudo ();
    } else if (word == "conditional") {
        definecondt ();
    } else if (word == "cs11") {
        definecs11 ();
    } else if (word == "parameter") {
        defineparameter ();
    } else {
        cout << "Definition Not Found" << endl;
    }
}
//lines 66-103 print out the definition for the word
void definevar ()
{
    cout << "A location in the computer's memory ";
    cout <<  "that can store a value" << endl;
}
void definefunct ()
{
    cout << "A named block of code that can be invoked as ";
    cout << "a statement or within an expression" << endl;
}
void definerecursion ()
{
    cout << "A situation in which a definition refers to ";
    cout << "the term it is defining" << endl;
}
void definepseudo ()
{
    cout << "A way to describe the steps of an algorithm ";
    cout << "in a human language like English or French" << endl;
}

void definecondt ()
{
    cout << "A method to execute a block of code depending ";
    cout << "on the outcome of an expression" << endl;
}
void definecs11 ()
{
    cout << "The intro level class for Computer Science at Tufts";
    cout << " with the goal of equipping students";
    cout << " with pertinent programming skills" << endl;
}
void defineparameter ()
{
    cout << "In brackets next to the function with the purpose of ";
    cout << "defining the variables to be used in the function " << endl;
    cout << "and recieving arguments passed when " << endl; 
    cout << "the function is called" << endl;
}