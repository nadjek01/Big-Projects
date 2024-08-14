/*
 *
 */

#include "PassengerQueue.h"

//To FC
int PassengerQueue::size()
{
    return(PassengerQueue.size());
}

//To FC
void PassengerQueue::print(std::ostream &output)
{
    for (auto passenger:PassengerQueue) {
        passenger.print(output);
    }
}

//To FC
void PassengerQueue::enqueue(const Passenger &passenger)
{
   PassengerQueue.push_back(passenger);
}

//TD FC
void PassengerQueue::dequeue()
{
    PassengerQueue.pop_front();
}

//TD FC
Passenger PassengerQueue::front()
{
    return (PassengerQueue.front());
}