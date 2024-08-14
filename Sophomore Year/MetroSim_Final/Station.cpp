/*
 *  Station.cpp
 *  Nana Adjekum
 *  13-Oct
 *
 *  CS 15 Proj1 MetroSim
 *
 *  Define functions in the Station struct
 *
 */

#include "Station.h"

/*
 * print
 * Name: st_print
 * Purpose: Prints the makings of the station
 *          ie station number, name, and passengers
 *          at the station
 * Parameters: the address of an instance of 
 *             of ostream
 * Returns: Nothing
 *
 */
void Station::st_print(std::ostream &output)
{

    output << "[" << station_num << "] ";
    output << station_name << " {";

    pa_station.print(output);
    output << "}" << endl;

}