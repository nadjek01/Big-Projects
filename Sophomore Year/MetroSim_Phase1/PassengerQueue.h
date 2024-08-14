/*
 *
 */

#include "Passenger.h"
#include <iostream>
#include <list>


class PassengerQueue
{
    public:

    //gets the passenger at the front
    Passenger front();

    //gets dequeues the passenger at the last of the list
    void dequeue();

    //add passenger to the front of the list
    void enqueue(const Passenger &passenger);

    //gets the size of the list
    int size();

    //prints the Passenger Queue
    void print(std::ostream &output);

    private:

    std::list<Passenger> PassengerQueue;
    

};

