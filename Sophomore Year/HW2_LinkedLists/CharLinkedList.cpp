/*
 *  CharLinkedList.cpp
 *  Nana Adjekum
 *  Sept 26
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  Define and Declare functions in the CharLinkedList
 *
 */


#include "CharLinkedList.h"
#include <iostream>
#include <sstream>
using namespace std;

/*
 * default constructor
 * Name: CharLinkedList
 * Purpose: Intializes an empty array list
 * Parameters: None
 * Returns: Nothing
 *
 */
CharLinkedList::CharLinkedList() 
{
    front = nullptr;
    boot = nullptr;
    list_length = 0;
}

/*
 * char constructor
 * Name: CharLinkedList (char c)
 * Purpose: Intializes an array list with a single char
 * Parameters: a char
 * Returns: Nothing
 *
 */
CharLinkedList::CharLinkedList(char c) 
{
    front = nullptr;
    boot = nullptr;
    list_length = 0;
    pushAtFront(c);
}

/*
 * copy constructor
 * Name: CharLinkedList
 * Purpose: Deep copies the vals of one 
 * Parameters: A given instance of another CharLinkedList
 * Returns: Nothing
 *
 */
CharLinkedList::CharLinkedList(const CharLinkedList &other)
{
        //list should be zero
        //front null and boot null
    front = nullptr;
    boot = nullptr;
    list_length = 0;
    //Node *o_node = other.front;

    for (int i = 0; i < other.size(); i++) {
        pushAtFront(other.elementAt(i));
    }
    list_length = other.list_length;

} 

/*
 * copy constructor
 * Name: CharLinkedList
 * Purpose: Deep copies the vals of one 
 * Parameters: A given instance of another CharLinkedList
 * Returns: Nothing
 *
 */
void CharLinkedList::clear()
{
    while (front != nullptr) {
        popFromFront();
    }

    list_length = 0;
    front = nullptr;
    boot = nullptr;

}

 /*
 * operator constructor
 * Name: CharLinkedList
 * Purpose: Recycles the storage associated with the instance
 *          on the left of the assignment and makes a deep copy 
 *          of the instance on the right hand side into the instance
 *          on the left hand side
 * Parameters: the address of a char linked list called other 
 *             (a constant instance of said list)
 * Returns: A pointer to a CharLinkedList (*this)
 *
 */
CharLinkedList &CharLinkedList::operator=(const CharLinkedList &other)
{
    if (this == &other) {
        return *this;
    }

    clear();
    front = nullptr;
    boot = nullptr;
    list_length = 0;
    //Node *o_node = other.front;
    int sz = other.size();

    for (int i = sz - 1; i >= 0; i--) {
        pushAtFront(other.elementAt(i));
    }
    list_length = other.list_length;
    return *this;

}


/*
 * pushAtFront
 * Name: pushAtFront
 * Purpose: Takes in an element and inserts it at the front of the LinkedList
 * Returns: nothing
 * Notes:
 */
void CharLinkedList::pushAtFront(char c) 
{
    Node *temp = new Node;
    
    temp->prev = nullptr;
    temp->next = front;
    temp->element = c;
    
    if (!isEmpty()) {
        front->prev = temp;
    }
    
    front = temp;
    list_length++;
    if (size() == 1) {
        boot = temp;
    }
    
}


/*
 * pushAtBack function
 * Name: pushAtBack
 * Purpose: Takes in an element and inserts it at the end of the LinkedList
 * Parameters: N/A
 * Returns: nothing
 * Notes:
 */
void CharLinkedList::pushAtBack(char c)
{
    
    Node *temp= new Node;
    temp->element = c;

    if (isEmpty()) {
        temp->next = nullptr;
        temp->prev = nullptr;
        front = temp;
        boot = temp;
    } else {
        boot->next = temp;
        temp->prev = boot;
        boot = temp;
        temp->next = nullptr;
    }
    
    list_length++;

}


/*
 * size function
 * Name: size
 * Purpose: Allows for the private data member of list_length
 *          to be accessed
 * Parameters: N/A
 * Returns: an int of the current size of the LinkedList
 *
 */
int CharLinkedList::size() const 
{
    return list_length;
}

/*
 * destructor function
 * Name: ~CharLinkedList
 * Purpose: Deletes all instances of letter (data) on the heap;
 *          Runs after the program is over
 *          Dels by removing from the front
 * Parameters: N/A
 * Returns: N/A
 */
CharLinkedList::~CharLinkedList()
{
    while (front != nullptr) {
        popFromFront();
    }

}

/*
 * remove from from function
 * Name: popFromFront
 * Purpose: Removes elements from the from of the list
 * Parameters: N/A
 * Returns: Nothing
 * Notes:
 */
void CharLinkedList::popFromFront() 
{
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty LinkedList");
    }

    if (front == nullptr) {
        return;
    }

    Node *deletion = front;
    front = front->next;
    if (size() !=1) {
        front->prev = nullptr;
    }

    delete deletion;
    list_length--;
}

/*
 * return first function
 * Name: first
 * Purpose: returns the first char in the linkedlist
 *          or throws a runtime error in the case that
 *          the first element cannot be accessed
 * Returns: a char (the first one in the list)
 * Notes:
 */
char CharLinkedList::first() const
{
    if (isEmpty() == true) {
        throw std::runtime_error("cannot get first of empty LinkedList");
    } else {
        return (front->element);
    }
}

char CharLinkedList::last() const
{
    if (isEmpty() == true) {
        throw std::runtime_error("cannot get last of empty LinkedList");
    } else {
        return (boot->element);
    }
}

/*
 * is empty function
 * Name: isEmpty
 * Purpose: Checks if the instance of an LinkedList is empty
 * Parameters: N/A
 * Returns: true if the LinkedList is empty and false if it's not
 *
 */
bool CharLinkedList::isEmpty() const
{
    return (front == nullptr); 
}

/*
 * third constructor
 * Name: CharLinkedList(char arr[], int size)
 * Purpose: Initializes a new linked list containing the array
 *          of chars that are passed into the function
 * Parameters: an array of chars (char arr[]) and the size of said
 *             linked list (int size)
 * Returns: Nothing
 *
 */
CharLinkedList::CharLinkedList(char arr[], int size)
{
    front = nullptr;
    boot = nullptr;
    list_length = 0;

    for (int i = size-1; i >= 0; i--) {
        pushAtFront(arr[i]);
    }
    
}

std::string CharLinkedList::toString() const
{ 
    std::stringstream ss;
    ss << "[CharLinkedList of size ";
    ss << list_length << " <<";
    
    Node *temp = front;
    
    while (temp != nullptr) {
        ss << temp->element;
        temp = temp->next;
    }

    ss << ">>]";
    return ss.str();

}

/*
 * insert element at index
 * Name: insertAt
 * Purpose: Insert an element at a specific index
 * Parameters: N/A
 * Returns: Nothing (but also throws an exception
 *          when the index is invalid)
 * Notes:
 */
void CharLinkedList::insertAt(char c, int index)
{
     if (isEmpty() and index > list_length) {
        throw std::range_error("index (" + to_string(index)
         + ") not in range [0.." + to_string(list_length) + "]");
    } else if (index < 0 or index > list_length) {       
        throw std::range_error("index (" + to_string(index)
         + ") not in range [0.." + to_string(list_length) + "]");
    } else if (index == 0) {
        pushAtFront(c);
    } else if (index == size()) {
        pushAtBack(c);
    } else {
        Node *temp = front;
        Node *at = new Node;
        at->element = c;
    
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }

        at->next = temp->next;
        temp->next = at;
        list_length++;
    }
   
}

/*
 * insert in order function
 * Name: insertInOrder
 * Purpose: Inserts an element in alphabetical order 
 *          (think a < c)
 * Parameters: N/A
 * Returns: Nothing
 * Notes:
 */
void CharLinkedList::insertInOrder(char c)
{
    Node *temp = front;
    int count = 0;

    while (temp != nullptr) {
    
        if (temp->element >= c) {
            break;
        }
        count++;
        temp = temp->next;
    }
    insertAt(c, count);

}


void CharLinkedList::popFromBack()
{
    if(isEmpty()) {
       throw std::runtime_error("cannot pop from empty LinkedList"); 
    } 

    Node *to_del = boot;

    boot = to_del->prev;
    boot->next = nullptr;

    delete to_del;
    
    
    
    list_length--;

}


/*
 * put to together function
 * Name: concatenete
 * Purpose: Inserts another linkedLists elements on
 *          the back of the primary elements list
 * Parameters: 
 * Returns: Nothing
 * Notes:
 */
void CharLinkedList::concatenate(CharLinkedList *other)
{
    int o_size = other->size();
    Node *o_temp = other->front;

    for (int i = 0; i < o_size; i++)
    {
        pushAtBack(o_temp->element);
        o_temp = o_temp->next;
    }

}

/*
 * re element at index
 * Name: elementAt
 * Purpose: Returns an element at a specific index
 * Parameters: N/A
 * Notes:
 */
char CharLinkedList::elementAt(int index) const
{
    if (isEmpty() or index < 0 or index > list_length) {
        throw std::range_error("index (" + to_string(index) + ")" 
                   " not in range [0.." + to_string(list_length) + "]");
    }
    int count = 0;
    Node *temp = front;
    if (index == 0) {
        return (first());
    } else if (index == list_length-1) {
        return (last());
    } else {
        temp = (r_help(++count, index, temp->next));
        return (temp->element);
    }
    
}

/*
 * helper recursive
 * Name: r_help(int r_count, int index, Node *curr)
 * Purpose: Recursises through the list until count 
 *          is equal to the index
 *          ATP it returns the Node at the index
 * Parameters: N/A
 * Notes:
 */
CharLinkedList::Node *CharLinkedList::r_help(int r_count, 
int index, Node *curr) const
{
    if (r_count == index) {
        return curr;
    } else {
        curr = curr->next;
        r_count++;
        return (r_help(r_count, index, curr));
    }
    
}

void CharLinkedList::replaceAt (char c, int index)
{
    if (isEmpty() or index > list_length) {
        throw std::range_error("index (" + to_string(index)
         + ") not in range [0.." + to_string(list_length) + "]");
    }
    int count = 0;
    Node *temp = front;

    Node *to_replace = r_help(count, index, temp);
    to_replace->element = c;

}



/*
 * remove at specific index function
 * Name: removeAt
 * Purpose: Removes an element at a specific index or throws a range
 *          error if the index is smaller or larger than the current
 *          size
 * Parameters: an int (the index that the element should be inserted at)
 * Returns: Nothing
 * Notes:
 */
void CharLinkedList::removeAt(int index)
{
    if (index > list_length or isEmpty()) {
        throw std::range_error("index (" + to_string(index) 
        + ") not in range [0.." + to_string(list_length) + "]");
    } else if (index == 0) {
        popFromFront();
    } else if (index == list_length - 1) {
        popFromBack();
    } else {
        int i = 0;
        Node *curr = front;

        while (i != index - 1) {
            curr = curr->next;
            i++;
        }

        Node *after = curr->next->next;
        after->prev = curr;

        delete curr->next;
        curr->next = nullptr;
        curr->next = after;

        list_length--;

    }
}

std::string CharLinkedList::toReverseString() const
{
    std::stringstream ss;
    ss << "[CharLinkedList of size ";
    ss << list_length << " <<";
    
    Node *temp = boot;
    
    while (temp != nullptr) {
        ss << temp->element;
        temp = temp->prev;
    }

    ss << ">>]";
    return ss.str();
}

