/*
 *  DatumStack.cpp- "the Implementation"
 *  Nana Adjekum
 *  Oct 26
 *
 *  CS 15 Proj 2 RPNCalc
 *
 *  Defines data members (public and private) in DatumStack class
 *  -data members to manipulate the way data is stored in the 
 *  -Datum Stack
 *
 */

#include "DatumStack.h"
#include <stdexcept>
using namespace std;


/*
 * 
 * Name: DatumStack()
 * Purpose: inits an empty DatumStack
 * Parameters: None
 * Returns: Nothing
 *
 */
DatumStack::DatumStack()
{
    init = true;
}


/*
 * 
 * Name: DatumStack(Datum arr[], int size)
 * Purpose: inits an DatumStack with an array
 * Parameters: None
 * Returns: Nothing
 *
 */
DatumStack::DatumStack(Datum arr[], int size)
{
    for (int i = 0; i < size; i++) {
        stack.push_front(arr[i]);
    }
    init = true;
    
}

/*
 * 
 * Name: isEmpty()
 * Purpose: returns a bool (true) if the DatumStack is empty
 * Parameters: None
 * Returns: Nothing
 *
 */
bool DatumStack::isEmpty()
{
    return (stack.size() == 0);
}

/*
 * 
 * Name: clear()
 * Purpose: clears the DatumStack
 * Parameters: None
 * Returns: Nothing
 *
 */
void DatumStack::clear()
{
    while (stack.size() != 0) {
        stack.pop_front();
    }
}

/*
 * 
 * Name: size()
 * Purpose: returns the size of the DatumStack
 * Parameters: None
 * Returns: Nothing
 *
 */
int DatumStack::size()
{
    return (stack.size());
}

/*
 * 
 * Name: size()
 * Purpose: returns the top of the DatumStack
 * Parameters: None
 * Returns: Nothing
 *
 */
Datum DatumStack::top()
{
    if (stack.size()== 0) {
        throw std::runtime_error("empty_stack");
    } else {
        return (stack.front());
    }
     
}

/*
 * 
 * Name: size()
 * Purpose: pops the first element of the DatumStack
 * Parameters: None
 * Returns: Nothing
 *
 */
void DatumStack::pop()
{
    if (stack.size() == 0) {
        throw std::runtime_error("empty_stack");
    } else {
        stack.pop_front();
    }
}

/*
 * 
 * Name: push()
 * Purpose: push a element on the DatumStack
 * Parameters: None
 * Returns: Nothing
 *
 */
void DatumStack::push(Datum to_push)
{
    stack.push_front(to_push);
}

