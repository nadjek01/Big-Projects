/*
 *  CharArrayList.h
 *  Nana Adjekum
 *  14-Sept-2022
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  Purpose: Create the private and public sections of the CharArrayList
 *  class
 *
 */
#ifndef CHAR_ARRAY_LIST_H
#define CHAR_ARRAY_LIST_H
#include <string>

class CharArrayList 
{
    public:

    //default constructor
    CharArrayList();

    //default destructor
    ~CharArrayList(void);

    //constructor where char is init   
    CharArrayList(char c);  
   
   //constructor where char and int are init
    CharArrayList(char arr[], int size);    

    //copy constructor for deep copy
    CharArrayList(const CharArrayList &other);

    //gives access to private member var--size
    int size() const; 

    //changes the "=" operator to copy stuff from the 
    //left side to the right side
    CharArrayList &operator=(const CharArrayList &other);

    //checks to see if the instance of the class is empty
    //returns true if it is, returns false if not
    bool isEmpty() const;

    //makes turns an instance of a CharArrayList into an 
    //empty CharArrayList
    void clear();

    //returns the first char in the arraylist
    char first() const;

    //return the last chat in the array
    char last() const;

    // puts char at the back of the arrraylist
    void pushAtBack(char c);

    //puts char at the front of the arraylist
    void pushAtFront(char c);

    //checks the element at a specific index
    char elementAt(int index) const;

    //inserts an element at a specific index
    void insertAt(char c, int index);

    //inserts an element into the array at a specific ascii index
    void insertInOrder(char c);
    
    //removes element from front of list
    void popFromFront();

    //removes element from back of list
    void popFromBack();

    //removes element from a specific index
    void removeAt(int index);

    //merges two CharArrayLists
    void concatenate(CharArrayList *other);

    //shrinks the CharArrayList
    void shrink();

    //add and makes the chars in the arrayList into a string
    std::string toString() const;

    //add and makes the chars in the arrayList into a string, but reversed
    std::string toReverseString() const;

    //replaces an element at an index
    void replaceAt(char c, int index);






    private:

    char *letter;
    int currSize;
    int capacity;

    //expands size of the array
    void expand();

};

#endif
