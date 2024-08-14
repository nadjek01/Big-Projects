/*
 *
 */

#include "Passenger.h"
#include "PassengerQueue.h"
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

//TO FC
void null_ppass_works() 
{
    Passenger a;
    a.print(cout);
}

//To FC
void single_ppass_works() 
{
    Passenger b(1, 2, 3);
    b.print(cout);
}


//To FC
void two_passqueue_works()
{
    Passenger a(1,2,3);
    Passenger b(2,4,5);
    PassengerQueue pq;

    pq.enqueue(a);
    pq.enqueue(b);
    pq.print(cout);

}

void front_passqueue_works()
{
    Passenger a(1,2,3);
    Passenger b(2,4,5);
    PassengerQueue pq;

    pq.enqueue(a);
    pq.enqueue(b);
    pq.print(cout);

    Passenger temp = pq.front();
    temp.print(cout);


}

//void back_passqueue_works()
// {
//     Passenger a(1,2,3);
//     Passenger b(2,4,5);
//     PassengerQueue pq;

//     pq.enqueue(a);
//     pq.enqueue(b);
//     pq.print(cout);

//     Passenger temp = pq.back();
//     temp.print(cout);

// }

//To FC
void one_passqueue_works()
{
    Passenger a(1,2,3);
    PassengerQueue pq;
    pq.enqueue(a);
    pq.print(cout);
}

//To FC
void empty_size()
{
    PassengerQueue no;
    assert(no.size()==0);
}

//To FC
void nempty_size()
{
    Passenger a(1,2,3);
    PassengerQueue pq;
    pq.enqueue(a);
    assert(pq.size()!=0);
}


//To FC
void single_dequeue()
{
    Passenger a(1,2,3);
    PassengerQueue pq;
    pq.enqueue(a);
    pq.dequeue();
    assert(pq.size()==0);
    pq.print(cout);
}

//To FC
void double_dequeue()
{
    Passenger a(1,2,3);
    Passenger b(2,2,3);
    PassengerQueue pq;
    pq.enqueue(a);
    pq.enqueue(b);
    pq.dequeue();
    assert(pq.size()==1);
    pq.print(cout);
}