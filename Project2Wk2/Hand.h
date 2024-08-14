#ifndef HAND_H
#define HAND_H

//****************************************************************
//
//                         Hand.h
//
//     Represents a single hand with 0 or more cards.
//     This is a thin wrapper around Card_Linked_List, but Hands
//     can draw themselves either as a string on cout using "print"
//     or on a canvas using "draw".
//
//     Author: Noah Mendelsohn
//
//     Tufts University, Fall 2021
//     CS 11: Project 2
//
//     Modified by: Nana Adjekum
//     Date: 4/20/22
//
//****************************************************************

#include <string>

#include "Card.h"
#include "CardImage.h"
#include "CardLinkedList.h"
#include "GraphicsCanvas.h"

//****************************************************************
//                        Class Hand
//****************************************************************

class Hand {
public:
    Hand();
    ~Hand();

    //
    //  Return number of cards in the hand
    //
    unsigned int num_cards();

    // Indices are 0-based. First card in the list is 0

    //
    //               add_card
    //
    // Insert a card at the specified position.
    // For an empty list, the only sensible index
    // is 0. If the index is out of range on any insertion,
    // make no changes and quietly return.
    //
    void add_card_at(unsigned int index, Card c);

    //
    // Remove a card at the specified position.
    // If the list is empty or index is out of range,
    // quietly do nothing.
    //
    void remove_card_at(unsigned int index);

    //
    // Return a copy of a card at the specified position.  If the
    // list is empty or index is out of range, return a card with
    // value NO_CARD_HERE.
    //
    Card get_card_at(unsigned int index);

    //
    // Calls debug_print on the underlying CardLinkedList
    //
    void debug_print();  // prints all cards in the list

    //
    //   Print the card numbers to cout in the form:
    //       32, 13, 15, 12 ...
    //
    void print();

    //
    //  Print the deck as a 2D presentation...uses GraphicsCanvas
    //  to do its work.
    //
    void graphic_print(std::string label);

private:

    //
    // A linked list to hold the Cards in the hand.
    //
    CardLinkedList m_card_list;

    /*******************************************************************/
    /*   DO NOT CHANGE ANYTHING ABOVE THIS LINE.                       */
    /*   Students MAY add their own private member functions below     */
    /*   this block and above the next comment block.  Do not add data */
    /*   members.                                                      */
    /*******************************************************************/

//=========================================================
//
//          THE FOLLOWING CODE IS USED ONLY
//          IN GRAPHICS MODE. DON'T WORRY ABOUT
//          IT UNTIL YOU GET TO THAT.
//
//=========================================================

    unsigned int divide_round_up(unsigned int dividend, unsigned int divisor);
    void draw_card_row(GraphicsCanvas *gc_p, unsigned int first_card_index,
                       int row, int col, int spacing);
    void draw_hand_to_canvas(GraphicsCanvas *gc_p);

    /*******************************************************************/
    /*              Students MAKE NO CHANGES BELOW HERE                */
    /*******************************************************************/

    friend class CardTester;  // A friend class for testing
    friend class HandTester;  // A friend class for testing

    //
    // Making copy constructor and assignment operator private
    // to prevent their inadvertent use from compiling.
    //
    Hand(Hand &other);
    Hand &operator=(Hand &rhs);
};


//****************************************************************
//
//           Constants describing size and layout and display of
//                    graphical Hand display.
//
//    (This is a classic technique in graphics, where you compute
//    layout characteristics from a few inputs and preferences.
//
//    In this case we start with CARD_WIDTH and CARD_HEIGHT, which
//    come from CardImage.h, and the preferences expressed immediately
//    below, such as CARDS_PER_DISPLAY_ROW, which we can change here
//    to affect the layout.)
//
//****************************************************************

const std::string NO_CARDS_IN_HAND_MESSAGE = "Hand is emtpy";

//
//   Layout of cards on the Canvas
//
const unsigned int CARDS_PER_DISPLAY_ROW = 3;
const unsigned int CARD_HORIZ_SPACING    = 2;  // Blank spaces between cards
const unsigned int CARD_VERT_SPACING     = 1;  // Blank lines  between cards
const unsigned int HORIZ_BORDER_OVERHEAD = 3;  // Margins from left and right
                                               //    border
const unsigned int VERT_BORDER_OVERHEAD  = 2;  // Margins from top and bottom
                                               //    border

//
//   Border
//
const char BORDER_CHAR = '*';                  // Use this char to draw border

//****************************************************************
//                 Computed Constants for Graphics Layout
//
//    These computed values may be useful in implementing your
//   drawing. Don't assume you need all of these.
//
//****************************************************************

//  Row and col in the canvas where the top line of the first card in
//  first row is drawn

const unsigned int FIRST_CARD_ROW = VERT_BORDER_OVERHEAD;
const unsigned int FIRST_CARD_COL = HORIZ_BORDER_OVERHEAD;


// Distances from upper left corner of one card to an adjacent card
const unsigned int CARD_HORIZ_OFFSET = CARD_WIDTH + CARD_HORIZ_SPACING;
                   // Leaves two message lines plus border, etc.
const unsigned int CARD_VERT_OFFSET = CARD_HEIGHT + CARD_VERT_SPACING;
                   // Leaves two message lines plus border, etc.

// Total Width of the canvas on which we draw the hand
// The height will be computed dymanically once we know the number of cards

// Width allows for left and right border, n cars,
// and n - 1 sets of space between 
const unsigned int CANVAS_WIDTH = (HORIZ_BORDER_OVERHEAD * 2) +
                                  (CARD_WIDTH * CARDS_PER_DISPLAY_ROW) +
                                  CARD_HORIZ_SPACING *
                                  (CARDS_PER_DISPLAY_ROW - 1);

#endif
