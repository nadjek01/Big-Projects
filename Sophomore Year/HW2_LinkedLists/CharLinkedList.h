/*
 *  CharLinkedList.h
 *  Nana Adjekum
 *  Sept 26th
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  Declares (functions) and Initialises (variables) the Char_Linked_List
 *
 */

#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H
#include <string>
using namespace std;

class CharLinkedList 
{
    public:

    CharLinkedList();
    CharLinkedList(char c);
    CharLinkedList(char arr[], int size);
    CharLinkedList(const CharLinkedList &other);

    ~CharLinkedList();
    CharLinkedList &operator=(const CharLinkedList &other);

    bool isEmpty() const;
    void clear();
    int size() const;
    char first() const;
    char last() const;
    char elementAt(int index) const;
    std::string toString() const;
    std::string toReverseString() const;

    void pushAtBack(char c);
    void pushAtFront(char c);
    void insertAt(char c, int index);
    void insertInOrder(char c);
    void popFromFront();
    void popFromBack();
    void removeAt(int index);
    void replaceAt(char c, int index);
    void concatenate(CharLinkedList *other);


    private:

    struct Node {
        char element;
        Node *next; 
        Node *prev;
    };
    
    Node *front;
    Node *boot;
    Node *r_help(int r_count, int index, Node *curr) const;
    int list_length;

};

#endif
