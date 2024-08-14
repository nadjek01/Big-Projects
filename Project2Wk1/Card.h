#ifndef CARD_H
#define CARD_H

//
//                          Card.h
//
//             Represents a single playing card
//
//               Tufts University, Fall 2021 
//                    CS 11: Project 2
//
//  Modified by: Nana Adjekum
//  Date: 04/13/22

#include <string>

const int NO_CARD_HERE = (-1);
const int DEBUG_PRINT_CARD_WIDTH = 4;     // Width of each card in debug print
                                          // Must be an even number
const std::string DEBUG_PRINT_NO_CARD_STRING = "NC"; // must be 2 chars long

class Card {
public:
    Card();              // Default constructor (NO_CARD_HERE)
    Card(int value);     // Construct card with given value
    ~Card();

    int value();

    void debug_print();  // prints card value for debugging. 
                         // No newline at the end.

private:
    //
    // Legal face values run from 0 up. 
    //
    // The reserved value NO_CARD_HERE is used for a card with no assigned 
    // value. Cards with this value may be used either prior to 
    // initialization, or when functions that are to retrieve a card 
    // can't fine one.
    //
    int m_value;

    friend class CardTester;  // A friend class for testing

    //
    // NOTE FOR THOSE INTERESTED IN DETAILS (if you're not or you're
    // too busy, you can skip reading this comment):
    //
    // In many other classes we define private copy constructors and
    // assignment operation overloads. That's because it's not safe to
    // copy the members of, for example, a linked list class without
    // also allocating space for and making copies of all the
    // nodes. The situation here is different: Cards contain just an
    // integer, and it's handy to be able to make copies of them in
    // local variables, to return them from functions, etc.
    // So...that's why we >don't< make private copy constructors here.
    // The defaults that C++ gives you do fine...they make copies of
    // m_value for the new Card.
    //

    /*******************************************************************/
    /*   DO NOT CHANGE ANYTHING ABOVE THIS LINE.                       */
    /*   Students MAY add their own private member functions below     */
    /*   this block and above the next comment block. Do not add data  */
    /*   members.                                                      */
    /*******************************************************************/


};

#endif
