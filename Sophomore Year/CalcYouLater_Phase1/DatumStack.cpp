#include "DatumStack.h"
#include <stdexcept>
using namespace std;


//TD FC
//I dont need to set stuff
DatumStack::DatumStack()
{
    init = true;
}

//TD FC
DatumStack::DatumStack(Datum arr[], int size)
{
    for (int i = 0; i < size; i++) {
        stack.push_front(arr[i]);
    }
    init = true;
    
}

//TD FC
bool DatumStack::isEmpty()
{
    return (stack.size() == 0);
}

//TD FC
void DatumStack::clear()
{
    while (stack.size() != 0) {
        stack.pop_front();
    }
}

//TD FC
int DatumStack::size()
{
    return (stack.size());
}

//TD FC
Datum DatumStack::top()
{
    if (stack.size()== 0) {
        throw std::runtime_error("empty_stack");
    } else {
        return (stack.front());
    }
     
}

//TD FC
void DatumStack::pop()
{
    if (stack.size() == 0) {
        throw std::runtime_error("empty_stack");
    } else {
        stack.pop_front();
    }
}

//TD FC
void DatumStack::push(Datum to_push)
{
    stack.push_front(to_push);
}

