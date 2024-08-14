/*
 *  MetroSim.h
 *  Nana Adjekum
 *  13-Oct
 *
 *  CS 15 Proj1 MetroSim
 *
 *  Declare functions and other variables in the MetroSim
 *
 */
#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "PassengerQueue.h"
#include "Station.h"
#include <vector>
#include <string>

using namespace std;

// Put any other necessary includes here


// Put any other structs you need here
// struct Train
// {
//     PassengerQueue a_Train;
// };




class MetroSim
{
    public:

        //the sim starter
        void Start_Sim(int argc, char *argv[]);

    
    private:
        
        //the actual metro
        std::vector<Station> Transit;

        //the train
        std::vector<PassengerQueue> t_train;

        //returns the train size
        int train_size();

        //initialises the stations
        void initStations(int argc, char *argv[]);
        
        //opens the file
        template<typename streamtype>
        void open_or_kaput(streamtype &stream, string file_name);
        
        //makes a channel for reading in commands and printing the sim state
        void channel(istream &input, ostream &output);

    

        //functions for terminal commands
        void move_metro(ostream &output);
        void add_pass(int arr, int dep);
        void metro_finish();

        //prints the metro
        void print_metro();

        //the current station
        int curr_station;

        //the num of passengers
        int num_pass;

        //the number of stations
        int num_Stations;

};

#endif
