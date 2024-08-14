#ifndef DECK_H
#define DECK_H

//
//                         Deck.h
//
//  Represents a deck of cards from which the top card may be drawn.
//  (The debug_print shows the whole deck, but otherwise only
//  the top card is accessible.)
//
//  The constructor takes an array of ints representing the card values.
//  These wind up in the deck in the order provided, so the one at
//  the beginning of the supplied array is the first one drawn from the deck.
//
//               Tufts University, Fall 2021 
//                    CS 11: Project 2
//
//  Modified by: 
//

#include "Card.h"
#include "CardLinkedList.h"
#include <fstream>
#include <string>

using namespace std;

class Deck {
public:
    Deck(Card card);                // Default Constructor
    Deck(string filename);          // Parameterized Constructor
    ~Deck();                        // Destructor

    int number_of_cards();
    Card inspect_top_card();        // Leaves Card in place
    Card draw_top_card();
    void put_card_on_top(Card c);
    void debug_print();             // Prints deck value for debugging. 
                                    // No newline at the end.

private:
    //
    //  Legal Card values run from 0 up.
    //
    //  The reserved value NO_DECK_HERE is used for Cards with no 
    //  assigned value.
    //
    CardLinkedList m_deck;

    //
    //  Making copy constructor and assignment operator private
    //  to prevent their inadvertent use from compiling.
    //  Students do NOT implement these.
    //
    Deck(Deck &other);
    Deck &operator=(Deck &rhs);

    friend class CardTester;  // A friend class for testing

    /*******************************************************************/
    /*   DO NOT CHANGE ANYTHING ABOVE THIS LINE.                       */
    /*   Students MAY add their own private member functions below     */
    /*   this block and above the next comment block. Do not add data  */
    /*   members.                                                      */
    /*******************************************************************/


};

#endif
