/*
 *  Passenger.cpp
 *  Nana Adjekum
 *  13-Oct
 *
 *  CS 15 Proj1 MetroSim
 *
 *  Declare and init functions in the Passenger struct
 *
 */

#include <iostream>
#include <string>
#include "Passenger.h"

/*
 * print pass
 * Name: print
 * Purpose: Print the goings-on of an instance of 
 *          a passenger
 * Parameters: None
 * Returns: Nothing
 *
 */
void Passenger::print(std::ostream &output)
{
        output << "[" << id << ", " << from << "->" << to << "]";
}
