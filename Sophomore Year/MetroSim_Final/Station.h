/*
 *  Station.h
 *  Nana Adjekum
 *  13-Oct
 *
 *  CS 15 Proj1 MetroSim
 *
 *  Declare functions in the Station struct
 *
 */

#ifndef __STATION_H__
#define __STATION_H__

#include "PassengerQueue.h"
using namespace std;

struct Station
{
    int station_num;                //index of the station
    string station_name;            //name of the station
    PassengerQueue pa_station;       //passengers at the station
    void st_print(std::ostream &output);
};

#endif