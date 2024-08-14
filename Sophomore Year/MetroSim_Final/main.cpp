/*
 *  main.cpp
 *  Nana Adjekum
 *  13-Oct
 *
 *  CS 15 Proj1 MetroSim
 *
 *  main function for the MetroSim
 *
 */

#include <iostream>

#include <string>

#include "MetroSim.h"

using namespace std;

int main(int argc, char *argv[])
{
	//ensures that the argument count is
	//efficient enough to start the sim
	if (argc >= 2) {
		MetroSim metro;
		
		metro.Start_Sim(argc, argv);
	} else {
		cerr << "Not enough arguments" << endl;
	}
    return 0;
}
