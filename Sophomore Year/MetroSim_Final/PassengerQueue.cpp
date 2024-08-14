/*
 *  PassengerQueue.cpp
 *  Nana Adjekum
 *  13-Oct
 *
 *  CS 15 Proj1 MetroSim
 *
 *  Define functions in the PassengerQueue
 *
 */

#include "PassengerQueue.h"

/*
 * size
 * Name: size
 * Purpose: Returns the size of the passengerqueue
 * Parameters: None
 * Returns: Nothing
 *
 */
int PassengerQueue::size()
{
    return(PassengerQueue.size());
}

/*
 * print
 * Name: print
 * Purpose: Prints the passengerqueue
 *          by calling the passenger 
 *          print function in a for loop
 * Parameters: None
 * Returns: Nothing
 *
 */
void PassengerQueue::print(std::ostream &output)
{
    for (auto passenger:PassengerQueue) {
        passenger.print(output);
    }
}

/*
 * get on
 * Name: enqueue
 * Purpose: Pushes the address of a passenger 
 *          onto a passenger queue (at the back)
 * Parameters: None
 * Returns: Nothing
 *
 */
void PassengerQueue::enqueue(const Passenger &passenger)
{
   PassengerQueue.push_back(passenger);
}

/*
 * get off
 * Name: dequeue
 * Purpose: Removes a passenger from
 *          the passenger queue (at the back)
 * Parameters: None
 * Returns: Nothing
 *
 */
void PassengerQueue::dequeue()
{
    PassengerQueue.pop_front();
}

/*
 * front
 * Name: front
 * Purpose: Returns the front of the passengerqueue
 * Parameters: None
 * Returns: Nothing
 *
 */
Passenger PassengerQueue::front()
{
    return (PassengerQueue.front());
}
