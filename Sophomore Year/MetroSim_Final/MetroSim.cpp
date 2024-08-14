/*
 *  MetroSim.cpp
 *  Nana Adjekum
 *  13-Oct
 *
 *  CS 15 Proj1 MetroSim
 *
 *  Defines functions in the MetroSim
 *
 */

#include "MetroSim.h"
#include "Station.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*
 * sim starter
 * Name: Start_Sim
 * Purpose: take command line arguments into program
 * 			opens files when needed and closes them
 * 			when the program is over
 * Parameters: 
 * 			an int argc (the count of the command line arguments)
 * 			a char pointer array 
 * 			(the substance of the command line arguments)
 * Returns: Nothing
 *
 */
void MetroSim::Start_Sim(int argc, char *argv[])
{
    ifstream stations;
	string s_file;
	s_file = argv[1];
	open_or_kaput(stations, s_file);
	
	string curr_line;
	int st_num = 0;
	num_Stations = 0;
	
	//init the stations of the program
	while(getline(stations, curr_line)) {
		Station temp;
		PassengerQueue t_temp;
		
		temp.station_num = st_num;
		temp.station_name = curr_line;

		Transit.push_back(temp);
		t_train.push_back(t_temp);
		
		st_num++;
		num_Stations++;
		
	}


	curr_station = 0;
	num_pass = 0;

	//init the output file
	ofstream output;
	string o_file;
	o_file = argv[2];
	open_or_kaput(output, o_file);


	//init and opens the cmd file when needed
	//also sends the cmd statements to the cmd loop (channel)
	if (argc == 4) {
		ifstream cmd;
		string c_file;
		c_file = argv[3];
		open_or_kaput(cmd, c_file);
		channel(cmd, output);

		//closes the file
		cmd.close();

	} else if (argc == 3) {
		channel(cin, output);
		
	}

	//closes the files
	stations.close();
	output.close();

}


/*
 * opens or kaputs
 * Name: open_or_kaput
 * Purpose: Opens the file or returns to main
 * Parameters: a streamtype instance (&stream)
 *			   -the file to be opened
			   a string (file_name) --> the name of the file
 * Returns: Nothing
 *
 */
template<typename streamtype>
void MetroSim::open_or_kaput(streamtype &stream, string file_name)
{
	stream.open(file_name);
	if (not stream.is_open()) {
		cerr << "Cannot open " << file_name << endl;
		exit(EXIT_FAILURE);
	}
}


/*
 * chanel
 * Name: channel
 * Purpose: Runs the command loop, calls functions
 * 			when terminal calls and prints when needed
 * Parameters: the address of an istream instance
 * 			   the address of a ostream instance
 * 			   (basically allows the function to handle
 * 			   from a file or cin/cout)
 * Returns: Nothing
 *
 */
void MetroSim::channel(istream &input, ostream &output)
{
	print_metro();
	char a_cmd;
	char b_cmd = '\0';

	while (b_cmd != 'f') {
		input >> a_cmd;

		if (a_cmd == 'm') {
			input >> b_cmd;

			if (b_cmd == 'm') {
				move_metro(output);
			}

			if (b_cmd == 'f') {
				metro_finish();
				return;
			}
		}

		if (a_cmd == 'p') {
			int parr;
			int pdep;

			input >> parr >> pdep;
			add_pass(parr, pdep);
			
		}

		print_metro();
	}
    
}

/*
 * metro dunzo
 * Name: metro_finish
 * Purpose: Prints the finish statement 
 * 			when mf is called in terminal
 * Parameters: None
 * Returns: Nothing
 *
 */
void MetroSim::metro_finish()
{
	cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
}


/*
 * add passenger
 * Name: add_pass
 * Purpose: adds a passenger at the stop where they got on
 * 			within the Transit system of MetroSim
 * Parameters: two ints that are the arr and depature
 * Returns: Nothing
 *
 */
void MetroSim::add_pass(int arr, int dep)
{
    num_pass++;
    Passenger temp(num_pass, arr, dep);

    Transit.at(arr).pa_station.enqueue(temp);
	

}

/*
 * chooo-choo
 * Name: move_metro
 * Purpose: Moves the metro and reports to the output file
 * 			who got off the train
 * 			Also adds and removes people from the train
 * Parameters: the address of an ostream instance
 * Returns: Nothing
 *
 */
void MetroSim::move_metro(ostream &output)
{
	//move from station passque to train passque
	while (Transit.at(curr_station).pa_station.size() != 0) {
		Passenger add_temp = Transit.at(curr_station).pa_station.front();

		t_train.at(add_temp.to).enqueue(add_temp);
		Transit.at(curr_station).pa_station.dequeue();

	}

	//updates currstation
	if (curr_station == num_Stations - 1) {
		curr_station = 0;
	} else {
		curr_station++;
	}

	//move from train passqueue to station passqueue
	while (t_train.at(curr_station).size() != 0) {
		output << "Passenger " 
			   << to_string(t_train.at(curr_station).front().id)
			   << " left train at station " 
			   << Transit.at(curr_station).station_name
			   << endl;

		t_train.at(curr_station).dequeue();

	}
}


/*
 * print
 * Name: print_metro
 * Purpose: Prints the current state of the metro
 * 			after a terminal call is executed
 * Parameters: None
 * Returns: Nothing
 *
 */
void MetroSim::print_metro()
{
	//prints pass on the train
	cout << "Passengers on the train: {";
	for (int i = 0; i < train_size(); i++) {
		t_train.at(i).print(cout);
	}
	cout << "}";
	cout << endl;

	//prints the metro
	for (int i = 0; i < num_Stations; i++) {
		if (Transit.at(i).station_num == curr_station) {
			cout << "TRAIN: ";
			Transit.at(i).st_print(cout);
		} else {
			cout << "       ";
			Transit.at(i).st_print(cout);
		}
		
	}

	//asks user for another command
	cout << "Command? ";
}

/*
 * train size
 * Name: train_size
 * Purpose: Returns the size of the train vector
 * Parameters: None
 * Returns: Nothing
 *
 */
int MetroSim::train_size()
{
	return t_train.size();
}