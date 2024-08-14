//
//                         Card.cpp
//
//    Methods to support the Card class, which represents a single
//    playing card.
//
//               Tufts University, Fall 2021 
//                    CS 11: Project 2
//
//    Modified by: Nana Adjekum
//    Date: 4/13/22

/**********************************************************/
/***      Students: Fill in the TODO items below        ***/
/***  You may add additional private member functions   ***/
/**********************************************************/

#include <iostream>
#include <iomanip>     // gets setw for debug printing
#include "Card.h"

using namespace std;

//
// Constructors
//
Card::Card()
{
    m_value = NO_CARD_HERE;
}

Card::Card(int new_value)
{
    m_value = new_value;
}

//
// Destructor
//
Card::~Card()
{
    // TODO (if needed)
}

//
// Value
//
int Card::value()
{
    return m_value;
}

// debug_print
//
// The assumption is that most printing will be handled by
// users of this class, but being able to print in a standardized
// way when debugging is handy.
//
const int _DEBUG_CARD_PRINT_NUMBER_WIDTH = 2; // Width of the number itself
const string _DEBUG_PRINT_CARD_PADDING = 
                    std::string((DEBUG_PRINT_CARD_WIDTH - \
                                _DEBUG_CARD_PRINT_NUMBER_WIDTH) / 2, ' ');

void Card::debug_print()
{
    if (m_value == NO_CARD_HERE) {
        cout << _DEBUG_PRINT_CARD_PADDING
             << DEBUG_PRINT_NO_CARD_STRING
             << _DEBUG_PRINT_CARD_PADDING;
    } else {
        cout << _DEBUG_PRINT_CARD_PADDING 
             << setw(_DEBUG_CARD_PRINT_NUMBER_WIDTH) 
             << m_value 
             << _DEBUG_PRINT_CARD_PADDING;
    }
}
