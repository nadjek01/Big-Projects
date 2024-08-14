//
//                         CardLinkedList.cpp
//
//           A class that manages a linked list of cards
//
//  The data are stored as a singly-linked sequence of nodes accessed
//  from a single pointer (in the data member 'm_front') to the first
//  node in the list (or the nullptr if the list is empty). Each node
//  has a Card instance named card.
//
//  Author: Noah Mendelsohn
//
//  Tufts University, Fall 2021
//  CS 11: Project 2
//
//  Modified by: Nana Adjekum
//  Date: 04/11/22
//
//  Anything else you would like to include:
//

/**********************************************************/
/***      Students: Fill in the TODO items below        ***/
/***  You may add additional private member functions   ***/
/**********************************************************/

#include <iostream>
#include <iomanip>     // gets setw for debug printing
#include <string>

#include "CardLinkedList.h"

using namespace std;

/*------------------------------------------------------------------
 *                    Private Helper Functions
 *----------------------------------------------------------------*/

// Purpose: Creates a Node to be added to the linked list 
//          (pointer) on the heap
// Parameters: A Card (a_card) and a Node pointer (next)
// Returns: A card (n_card)
//
CardLinkedList::Node *CardLinkedList::newNode(Card a_card, Node *next)
{
    Node *n_card = new Node;

    n_card->card = a_card;
    n_card->next = next;
         
    return n_card;
}

// Purpose: Basically does the same thing as the one above, but is for when
//          making the first item in the linked list (or any other instance
//          where a nullptr is needed for the next item in the list)   
// Parameters: A card (a_card)
// Returns: A call to the function above with the parameters of
//          a_card and nullptr
//
CardLinkedList::Node *CardLinkedList::newNode(Card a_card)
{
    return newNode(a_card, nullptr);
}

// Purpose: Add a card to the front of the linked list
// Parameters: A card (a_card)
// Returns: n/a (void)
//
void CardLinkedList::addToFront(Card a_card)
{
    Node *a_node = newNode(a_card);
    a_node->next = m_front;
    m_front = a_node;
}

// Purpose: Removes the first card in the linked list
// Parameters: n/a
// Returns: n/a
//
void CardLinkedList::removeFirst()
{
    //the card to be deleted
    Node *to_delete = m_front;
    
    //m_front gets the following card so dont lose link
    m_front = m_front->next;
         
    delete to_delete;                 
}

// Purpose: Adds to the back of the linked list
// Parameters: A card (z_card)
// Returns: n/a
//
void CardLinkedList::addToBack(Card z_card)
{
    Node *b_node = m_front;
    
    while (b_node->next != nullptr) {
        b_node = b_node->next;
    } 
    
    if (b_node->next == nullptr) {
        b_node->card = z_card;
        b_node->next = nullptr;
    }    
}
 /*------------------------------------------------------------------
  *                    Constructor(s) and Destructor
  *----------------------------------------------------------------*/
//
// Purpose:  Constructor initializes an empty list
//
CardLinkedList::CardLinkedList()
{
    m_front = nullptr;
    m_list_length = 0;
}

//
// Purpose:  Destructor recycles the space associated with all nodes
//           in the list
//
CardLinkedList::~CardLinkedList()
{
    while (m_front != nullptr) {
        removeFirst();
    }
}

/*------------------------------------------------------------------
 *          Public functions to manipulate and query the list
 *----------------------------------------------------------------*/

//
// Purpose:  Return the current size of the list
//           i. e., the number of words/nodes in the list
// Parameters: n/a
//
// Returns: An unsigned int (l_count)
unsigned int CardLinkedList::num_cards()
{
    unsigned int l_count = 0;
    Node *c_node = m_front;
    
    while (c_node != nullptr) {
        l_count++;
        c_node = c_node->next;
    }
    
    return l_count;
}

//
// Purpose:  Add Card node to the list at the specified position.
//           If index is out of range then return quietly
// Parameters: An unsigned int (index) and a Card class (c)
// Returns: n/a
//
void CardLinkedList::add_card_at(unsigned int index, Card c)
{   
    //conditional for if out of range 
    if (index > m_list_length) {
        return;
    } else if (index == 0) {    //condition for if want to add to front
        addToFront(c);
        m_list_length++;
    } else if (index == m_list_length - 1) {    //condition for if add to back
        cout << m_list_length - 1 << endl;
        addToBack(c);
        m_list_length++;
    } else {                   //condition for all other indices
        Node *b_node = m_front;
        index--;               //so stops before so can add at correct index
        for (unsigned int i = 0; i < index; i++) {  
            b_node = b_node->next;   
        }
        
        //new card node to be added to the list
        Node *c_node = newNode(c);
        c_node->next = b_node->next;
        b_node->next = c_node; 
        
        m_list_length++;  
    }
}

//
// Purpose:  Remove word from the list.  That is, it removes and
//           recycles the node containing the word (and its count)
// Parameters: An unsigned int (index)
// Returns: n/a
//
void CardLinkedList::remove_card_at(unsigned int index)
{
    //basically the same code as above but instead deletes a node
    if (index > m_list_length) {
        return;
    } else if (index == 0) {
        removeFirst();
        m_list_length--;
    } else {
        unsigned int i = 0;
        Node *b_node = m_front; 
        index--;
        
        while (i < index) {
            b_node = b_node->next;
            i++;
        }
        
        //makes sure the linked list stays intact
        Node *c_node = b_node->next->next; 
        delete b_node->next;
        b_node->next = nullptr;
        b_node->next = c_node;
        
        m_list_length--;
    }    
}


//
// Purpose:  Return the index-th element of the list
// Params:   index must be in range [0 .. size) where
//           size is the number of words stored in the list
// Effects:  if index is out of range, prints error message and returns
//           NO_CARD_HERE
//
Card CardLinkedList::get_card_at(unsigned int index)
{
    unsigned int i = 0;
    Node *b_node = m_front;
    
    //gets the first card
    if (index == 0) {
        return b_node->card;
    } else {                //goes through the list and finds the index
        while (i < index and b_node != nullptr) {
            b_node = b_node->next;
            i++;
        }
        if (b_node == nullptr) {     //for when there's no card
            cerr << "Error: Index out of range" << endl;
            return NO_CARD_HERE;
        } else {                    //for when there's a card
            return b_node->card;
        }
    }    
}

//
// Purpose:  Print out the underlying list to cout
// Effects:  Prints to cout
// Notes:    This function is here for debugging purposes.
//           It will not be called in the final version of the program.
//           Still LEAVE IT AS-IS:  WE WILL USE IT FOR TESTING.
//
void CardLinkedList::debug_print()
{
    int index_num = 0;

    cout << "DEBUG: CardLinked List (num_cards = " << num_cards()
         << ") ["  << endl;
    cout <<  "  Index_num   Node Address  Face Value" << endl;
    for (Node *curr_p = m_front; curr_p != nullptr; curr_p = curr_p->next) {
        cout <<  setw(9) << index_num++;
        cout <<  setw(16) << curr_p;
        cout <<  "       ";
        curr_p->card.debug_print();
        cout << endl;
    }
    cout << "]" << endl;
}
