#ifndef CARDLINKEDLIST_H
#define CARDLINKEDLIST_H

//
//                     CardLinkedList.h
//
//        A class that manages a linked list of cards
//
//               Tufts University, Fall 2021 
//                    CS 11: Project 2
//
//  Modified by: Nana Adjekum
//  Date: 04/13/22
//

#include "Card.h"

class CardLinkedList
{
public:
    CardLinkedList();
    ~CardLinkedList();

    unsigned int num_cards();

    //
    //               add_card_at
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
    // Print information about the number of cards and the card
    // values. This method must be implemented but it will not be
    // tested. You can use any reasonable format you like.  This
    // method should call Card::debug_print to print individual
    // cards.
    //
    void debug_print();  // prints all cards in the list

private:
    struct Node {
        Card  card;
        Node  *next;
    };

    Node *m_front;               // pointer to first node in list or nullptr
    unsigned int m_list_length;  // number of cards currently stored in list

    /*******************************************************************/
    /*   DO NOT CHANGE ANYTHING ABOVE THIS LINE.                       */
    /*   Students MAY add their own private member functions below     */
    /*   this block and above the next comment block. Do not add data  */
    /*   members.                                                      */
    /*******************************************************************/

    Node *newNode(Card a_card, Node *next); // makes linked list
    Node *newNode(Card a_card);             // ends/starts linked list
    void addToFront(Card a_card);           // adds card to front
    void removeFirst();                     // removes card at front
    void addToBack(Card z_card);            // adds card at back
    
    /*******************************************************************/
    /*              Students MAKE NO CHANGES BELOW HERE                */
    /*******************************************************************/

    friend class CardTester;  // A friend class for testing

    //
    // Making copy constructor and assignment operator private
    // to prevent their inadvertent use from compiling.
    // Students do NOT implement these
    //
    CardLinkedList(CardLinkedList &other);
    CardLinkedList &operator=(CardLinkedList &rhs);
};

#endif
