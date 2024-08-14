/*
 *  unit_test.h
 *  Nana Adjekum
 *  13-Oct
 *
 *  CS 15 Proj1 MetroSim
 *
 *  Tester for MetroSim
 *
 */

#include "Passenger.h"
#include "PassengerQueue.h"
#include "MetroSim.h"
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

/*
 * no passengers
 * Name: null_ppass_works
 * Purpose: Checks that an uninit 
 *          passenger prints correctly
 * Parameters: None
 * Returns: Nothing
 *
 */
void null_ppass_works() 
{
    Passenger a;
    a.print(cout);
}

/*
 * one passenger
 * Name: single_ppass_works
 * Purpose: Checks that an instance
 *          passenger prints correctly
 * Parameters: None
 * Returns: Nothing
 *
 */
void single_ppass_works() 
{
    Passenger b(1, 2, 3);
    b.print(cout);
}


/*
 * mo passengers
 * Name: two_passqueue_works
 * Purpose: Checks that a passenger
 *          queue is queueing correctly
 * Parameters: None
 * Returns: Nothing
 *
 */
void two_passqueue_works()
{
    Passenger a(1,2,3);
    Passenger b(2,4,5);
    PassengerQueue pq;

    pq.enqueue(a);
    pq.enqueue(b);
    pq.print(cout);

}

/*
 * fron passengers
 * Name: front_passqueue_works
 * Purpose: Checks that the
 *          front function for 
 *          passqueue is returning
 *          the right instance of
 *          a passenger
 * Parameters: None
 * Returns: Nothing
 *
 */
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



/*
 * one passengers in pq
 * Name: one_passqueue_works
 * Purpose: Checks that the passqueue of one
 *          passenger is correct
 * Parameters: None
 * Returns: Nothing
 *
 */
void one_passqueue_works()
{
    Passenger a(1,2,3);
    PassengerQueue pq;
    pq.enqueue(a);
    pq.print(cout);
}

/*
 * empty pq
 * Name: empty_size
 * Purpose: Checks that the passengerqueue
 *          with no passengers is acc empty
 * Parameters: None
 * Returns: Nothing
 *
 */
void empty_size()
{
    PassengerQueue no;
    assert(no.size()==0);
}

/*
 * noempty pq
 * Name: nempty_size
 * Purpose: Checks that the passengerqueue
 *          with passengers is not empty
 * Parameters: None
 * Returns: Nothing
 *
 */
void nempty_size()
{
    Passenger a(1,2,3);
    PassengerQueue pq;
    pq.enqueue(a);
    assert(pq.size()!=0);
}


/*
 * single dq
 * Name: single_dequeue
 * Purpose: Checks that the dequeue function
 *          is correct with one passenger
 * Parameters: None
 * Returns: Nothing
 *
 */
void single_dequeue()
{
    Passenger a(1,2,3);
    PassengerQueue pq;
    pq.enqueue(a);
    pq.dequeue();
    assert(pq.size()==0);
    pq.print(cout);
}

/*
 * 2x dq
 * Name: double_dequeue
 * Purpose: Checks that the dequeue function
 *          is correct with 2 passenger
 * Parameters: None
 * Returns: Nothing
 *
 */
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
