/*
 *  CharArrayList.cpp
 *  Nana Adjekuum
 *  14-Sept-2022
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  FILE PURPOSE: Defines and initializes the functions 
 *                declared in the CharArrayList File
 *               
 *
 */

#include "CharArrayList.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

/*
 * default constructor
 * Name: CharArrayList
 * Purpose: Intializes an empty array list
 * Parameters: None
 * Returns: Nothing
 *
 */
CharArrayList::CharArrayList()
{
    letter = nullptr;
    currSize = 0;
    capacity = 0;
}

/*
 * secondary constructor
 * Name: CharArrayList
 * Purpose: Takes in single character as parameter and creates
 * one element array list consisting of that character
 * Parameters: a char called c
 * Returns: nothing
 *
 */
CharArrayList::CharArrayList(char c)
{
    capacity = 1;
    letter = new char[capacity];

    letter[0] = c;
    currSize = 1;
}

/*
 * third constructor
 * Name: CharArrayList
 * Purpose: Initializes a new array list containing the array
 * of chars that are passed into the function
 * Parameters: an array of chars (char arr[]) and the size of said
 * array (int size)
 * Returns: Nothing
 *
 */
CharArrayList::CharArrayList(char arr[], int size)
{
    capacity = size;
    letter = new char[capacity];

    for (int i = 0; i < size; i++) {
        letter[i] = arr[i];
    }

    currSize = size;
}

/*
 * copy constructor
 * Name: CharArrayList
 * Purpose: Deep copies instance of given array
 * Parameters: the address of a char array list called other                        
 * (a constant instance of said list)
 * Returns: Nothing
 *
 */
CharArrayList::CharArrayList(const CharArrayList &other)
{
    letter = new char;
    *letter = *other.letter;
    currSize = other.currSize;
    capacity = other.capacity;
}

/*
 * operator constructor
 * Name: CharArrayList
 * Purpose: Recycles the storage associated with the instance
 *          on the left of the assignment and makes a deep copy 
 *          of the instance on the right hand side into the instance
 *          on the left hand side
 * Parameters: the address of a char array list called other 
 *             (a constant instance of said list)
 * Returns: A pointer to a CharArrayList (*this)
 *
 */
CharArrayList &CharArrayList::operator=(const CharArrayList &other) 
{
    //(ln 109) checks first to see if the stuff on the 
    //the lhs of the operator is the same
    if (this == &other) {
        return *this;
    }
     //(ln 113) dels letter bc we need to over-write
     //with what on the the rhs
    delete [] letter;

    //(ln 117) reassigning
    capacity = other.currSize;
    currSize = other.currSize;
    letter = new char[capacity];

    //(ln 122) copying
    for (int i = 0; i < currSize; i++) {
        letter[i] = other.letter[i];
    }
    return *this;
}

    
/*
 * destructor function
 * Name: ~CharArrayList
 * Purpose: Deletes all instances of letter (data) on the heap;
 *          Runs after the program is over
 * Parameters: N/A
 * Returns: an int of the current size of the ArrayList
 *
 */
CharArrayList::~CharArrayList(void)
{
    delete[] letter;
}

/*
 * size function
 * Name: size
 * Purpose: Allows for the private data member of currSize
 *          to be accessed
 * Parameters: N/A
 * Returns: an int of the current size of the ArrayList
 *
 */
int CharArrayList::size() const
{
    return currSize;
}

/*
 * is empty function
 * Name: isEmpty
 * Purpose: Checks if the instance of an ArrayList is empty
 * Parameters: N/A
 * Returns: true if the arraylist is empty and false if it's not
 *
 */
bool CharArrayList::isEmpty() const
{
    return (currSize == 0);
}

/*
 * clear function
 * Name: clear
 * Purpose: Clears out an instance of a CharArrayList that would
 *          have values by making the arraylist size equal to zero so the
 *          client can just overwrite the former slots in memory
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void CharArrayList::clear()
{
    currSize = 0;
}

/*
 * return first function
 * Name: first
 * Purpose: returns the first char in the arraylist
 *          or throws a runtime error in the case that
 *          the first element cannot be accessed
 * Returns: a char (the first one in the list)
 * Notes:
 */
char CharArrayList::first() const
{
    //(ln 197) the exception thrown for when the list is empty
    if (currSize == 0) {
        throw std::runtime_error("cannot get first of empty ArrayList");
    }
    return letter[0];
}

char CharArrayList::last() const
{
    //(ln 206) the exception thrown when the list is empty
    if (currSize == 0) {
        throw runtime_error("cannot get last of empty ArrayList");
    }
    else {
        return letter[currSize - 1];
    }
}

/*
 * pushAtBack function
 * Name: pushAtBack
 * Purpose: Takes in an element and inserts it at the end of the ArrayList
 * Parameters: N/A
 * Returns: nothing
 * Notes:
 */
void CharArrayList::pushAtBack(char c)
{
    //(ln 225) expands when the size is equal to capacity
    if (currSize == capacity) {
        expand();
    }

    //returns the char at currSize bc that's technically
    //the end of the list
    letter[currSize] = c;
    currSize++;
    shrink();
}

/*
 * expand function
 * Name: expand
 * Purpose: Expands the capacity of the arrayList when called by 
 *          creating a new arrayList with 2x + 2 the capacity
 *          and copying all the info over, then deleting the temp
 *          and increasing the capacity
 * Parameters: N/A
 * Returns: nothing
 * Notes:
 */
void CharArrayList::expand()
{
    //declaring temp char for copying everything in letter
    //has a bigger capacity 
    //that's why it's called the expand function
    char *temp = new char[2 + capacity * 2];
    for (int i = 0; i < currSize; i++) { 
        temp[i] = letter[i];
    }

    //deletes letter bc memoryleaks 
    //and we don't need it anymore 
    //bc we reassign temp to letter
    delete[] letter;
    letter = temp;
    capacity = 2 * capacity + 2;
}

/*
 * pushAtFront
 * Name: pushAtFront
 * Purpose: Takes in an element and inserts it at the front of the ArrayList
 * Returns: nothing
 * Notes:
 */
void CharArrayList::pushAtFront(char c)
{
    //expansion called when needed
    //when size of the AL is equal to the capacity
    if (currSize == capacity) {
        expand();
    }

    //overwrites everything one over in the list (backwards)
    //bc to the client it looks the same
    //don't have to acc make a new array
    //w/o the first element
    for (int i = currSize; i > 0; i--) {
        letter[i] = letter[i - 1];
    }

    //puts char c into the first index
    letter[0] = c;
    currSize++;
}

/*
 * re element at index
 * Name: elementAt
 * Purpose: Returns an element at a specific index
 * Parameters: N/A
 * Notes:
 */
char CharArrayList::elementAt(int index) const
{
    //throws exception when the index is negative
    //or larger tha size of the AL
    //ie whenever the index is invalid
    if (index < 0 or index > currSize) {
        throw std::range_error("index (" + to_string(index) + ")" 
                   " not in range [0.." + to_string(currSize) + "]");
    } else {
        return letter[index];
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
void CharArrayList::insertInOrder(char c)
{
    int i = 0;
    expand();

    //loop checks that i stays w/i bounds
    //and increments only until when
    //the char ascii is larger than
    //or equal to the letter at i
    while (i < currSize and c >= letter[i]) {
        i++;
    }

    //when the while conditional is reached
    //then the i is inserted into the array
    insertAt(c, i);
    shrink();
    
}

/*
 * remove from from function
 * Name: popFromFront
 * Purpose: Removes elements from the from of the list by overwriting
 *          the element at the first index (and so on)
 *          Throws a range error if the element is empty
 * Parameters: N/A
 * Returns: Nothing
 * Notes:
 */
void CharArrayList::popFromFront()
{
    //exception when index is out of bounds
    if (currSize == 0) {
        throw std::runtime_error("cannot pop from empty ArrayList");
    }

    //overwrites the first array
    for (int i = 0; i < currSize - 1; i++) {
        letter[i] = letter[i + 1];
    }

    //always need to decrement when removing
    //from the list
    currSize--;
}

/*
 * remove from back function
 * Name: popFromBack
 * Purpose: Removes a element from the back of the list by decreasing currSize
 *          so, to the client, it looks like the list is one less
 *          and they are unable to access that last element
 * Parameters: N/A
 * Returns: Nothing
 * Notes:
 */
void CharArrayList::popFromBack()
{
    //exception when the size is 0
    if (currSize == 0) {
        throw std::runtime_error("cannot pop from empty ArrayList");
    }

    //size decrementation
    //bc to the client it j needs to look like we are acc 
    //getting rid of sumthing
    currSize--;
    shrink();
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
void CharArrayList::removeAt(int index)
{
    //throw exception conditionals for when 
    //the index is out of bounds or
    //when the list is empty
    if (currSize == 0) {
        throw std::range_error("cannot remove from empty list");;
    } else if (index < 0 or index > currSize) {
        throw std::range_error("index (" + to_string(index) 
        + ") not in range [0.." + to_string(currSize) + "]");
    }
    
    //diff conditionals for where the element
    //is being removed from
    if (index == 0) {
        popFromFront();
    } else if (index == currSize) {
        popFromBack();
    } else {
        int i = index;
        expand();
        while (i < currSize)
        {
            letter[i] = letter[i + 1];
            i++;
        }
    }
    //decrementation of the size and the list
    currSize--;
    shrink();
}

/*
 * put to together function
 * Name: concatenete
 * Purpose: Inserts another CharArrayLists elements on
 *          the back of the primary elements list
 * Parameters: 
 * Returns: Nothing
 * Notes:
 */
void CharArrayList::concatenate(CharArrayList *other)
{
    //sets the size of the passed in AL
    //to some int (t_size)
    //did this bc ran into bugs
    //with the AL size always changing
    int t_size = other->size();

    //loop that adds the passed in AL to the back of 
    //the current AL
    for (int i = 0; i < t_size; i++) {
        pushAtBack(other->elementAt(i));
    }

}

/*
 * shrinks the curr Array
 * Name: shrink()
 * Purpose: Insert an element at a specific index
 * Parameters: an int (the index that the element should be inserted at)
 * and a char (the element to be inserted)
 * Returns: Nothing
 * Notes:
 */
void CharArrayList::shrink()
{
    capacity = currSize;
    char *temp = new char[capacity];
    
    for (int i = 0; i < capacity; i++) {
        temp[i] = letter[i];
    }

    delete [] letter;
    letter = temp;
    
}

/*
 * makes the AL into a string
 * Name: toString()
 * Purpose: Turns the ArrayList into a list to be compared, printed, 
 *          and anything else you could possibly want with a string
 * Parameters: N/A
 * Returns: A string (f_sentence)
 * Notes:
 */
std::string CharArrayList::toString() const 
{
    string b_letters = "<<";

    //adds the elements in letters to a string
    for (int i = 0; i < currSize; i++) {
        b_letters = b_letters + letter[i];
    }

    //the end of the statement
    string e_letters = ">>]";

    //i'm calling this string algebra
    //bc i'm j adding all of the strings together
    string f_sentence = "[CharArrayList of size " + 
                        to_string(currSize) + " " + b_letters + e_letters;
    
    return f_sentence;
}

/*
 * makes the AL into a reverse string
 * Name: toReverseString()
 * Purpose: Turns the ArrayList into a list to be compared, printed, 
 *          and anything else you could possibly want with a string
 *          But get this, it's backwards!
 * Parameters: N/A
 * Returns: A string (r_sentence)
 * Notes:
 */
 std::string CharArrayList::toReverseString() const 
 {
    //had to use stringstream here for some reason
    //i asked a TA and they said they didn't know 
    //either all ik is that it doesn't work
    //when its a normal string
    stringstream s_letters;
    s_letters << "<<";


    //same thing as above but backwards
    for (int i = currSize; i > 0; i--) {
        s_letters << letter[i-1];
    }

    string t_letters = ">>]";

    string r_sentence = "[CharArrayList of size " +
                        to_string(currSize) + " " + 
                        s_letters.str() + t_letters;
    return r_sentence;

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
void CharArrayList::insertAt(char c, int index)
{
    //exceptions for invalid indices
        //(ln 478-481) exception for when the AL is 0 and the client 
        //is trying to add at an index that doesn't exist

        //(ln 481-484) exception for when the the index is less
        //than zero or the current size of the AL
    if (currSize == 0 and index > currSize) {
        throw std::range_error("index (" + to_string(index)
         + ") not in range [0.." + to_string(currSize) + "]");
    } else if (index < 0 or index > currSize) {       
        throw std::range_error("index (" + to_string(index)
         + ") not in range [0.." + to_string(currSize) + "]");
    }

    //(ln 487) expands the AL when currSize is equal to capacity
    if (currSize == capacity) {
        expand();
    }
    

    //(ln 496-498) actual insertion
    //goes to the end of the AL and copies
    //backwards until the index is reached
    //and then at that point the index is added
    for (int i = currSize; i > index; i--) {
        letter[i] = letter[i - 1];
    }
    
    //NOTE: I had this function with the creation
    //of another AL but decided that too much 
    //heap allocation was messy and came with too
    //many bugs

    //insertion of the letter at the index
    letter[index] = c;
    currSize++;

    shrink();
    
}
 
/*
 * replace at function
 * Name: replaceAt
 * Purpose:Replaces the char at the given index
 * Parameters: 
 * Returns: Nothing
 * Notes:
 */
void CharArrayList::replaceAt(char c, int index) 
{
    //the exceptions for when the index
    //is invalid
     if (currSize == 0 and index > currSize) {
        throw std::range_error("index (" + to_string(index)
         + ") not in range [0.." + to_string(currSize) + "]");
    } else if (index < 0 or index > currSize) {       
        throw std::range_error("index (" + to_string(index)
         + ") not in range [0.." + to_string(currSize) + "]");
    }

    //replacement of the char in the index
    letter[index] = c;
}