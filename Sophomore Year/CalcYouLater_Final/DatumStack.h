/*
 *  DatumStack.h- "the Interface"
 *  Nana Adjekum
 *  Oct 26
 *
 *  CS 15 Proj 2 RPNCalc
 *
 *  Declares data members (public and private) in DatumStack class
 *
 */

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include "Datum.h"
#include <list>

class DatumStack {
    
    public:

    //the basic constructor
    DatumStack();
    //the constructor that takes stuff
    DatumStack(Datum arr[], int size);

    //checks to see if empty
    bool isEmpty();
    //clears the datum stack
    void clear();
    //checks the datum stack size
    int size();

    //returns the top of the datum stack w/o 
    //removing it
    Datum top();
    //pops the first Datum
    void pop();
    //pushes a datum on the stack
    void push(Datum to_push);

    private:
    std::list<Datum> stack;

    //says that an instance of the datum stack has been made
    bool init;

};
#endif