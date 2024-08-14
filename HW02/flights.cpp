/*
 * guess.cpp
 * 
 * Purpose: find the layover and total flight time from the
 *          user inputs of departure and arrival time
 * 
 * Name: Nana Adjekum
 * Credits: HW02 Guidelines
 * Any Bugs/Issues:
 * Date: 02/06/2022
 */

#include <iostream>

using namespace std;

/*this function changes the hours to minutes and adds the converted hours to 
*minutes*/
int flighttime (int departhour, int departmin, int arrivehour, int arrivemin);
int main()
{
    /*variables for the hour and minutes of the flight departure and 
    *arrival. this is done for both of the flights */
    int hdepartureone, mdepartureone, harrivalone, marrivalone;
    int hdeparturetwo, mdeparturetwo, harrivaltwo, marrivaltwo;
    
    cout << "Flight 1: ";
    cin >> hdepartureone >> mdepartureone >> harrivalone >> marrivalone;
    /*calls the flighttime function and inputs the userinput of
    *the first flight into the function */
    int firstflightmin = flighttime(hdepartureone, mdepartureone,  
                                    harrivalone, marrivalone);
    
    cout << "Flight 2: ";
    cin >> hdeparturetwo >> mdeparturetwo >> harrivaltwo >> marrivaltwo;
    int secondflightmin = flighttime(hdeparturetwo, mdeparturetwo,
                                    harrivaltwo, marrivaltwo);
    
    /*finds the layover time in minutes by inputting the arrival
    *of the first flight and departure of the second flight */
    int layovermins = flighttime(harrivalone, marrivalone, 
    hdeparturetwo, mdeparturetwo);
    
    //takes the mins found earlier converts them to hours
    int tlayoverhour = layovermins / 60;
    //find the mins of the layover time (if applicable)
    if((tlayoverhour % 60) != 0) {
        int tlayovermin = layovermins - (tlayoverhour * 60);
        cout << "Layover: " << tlayoverhour << " hr ";
        cout << tlayovermin << " min" << endl;
    } else {
        cout << "Layover: " << tlayoverhour << " hr ";
        cout << "0 min" << endl;
    }
    
    //conditional for if the flight spans overnight
    if(hdepartureone > harrivalone or hdeparturetwo > harrivaltwo) {
        int flightmin = firstflightmin + secondflightmin + layovermins + 1440;
        int tflighthour = flightmin / 60;
        if((flightmin % 60) != 0) {
            int tflightmin = flightmin - (tflighthour * 60);
            cout << "Total: " << tflighthour << " hr ";
            cout << tflightmin << " min" << endl;
        } else {
            cout << "Total: " << tflighthour << " hr ";
            cout << "0 min" << endl;
        }
    }
    
    //this else statement is for when the flight does not go overnight
    else {
        int flightmin = firstflightmin + secondflightmin + layovermins;
        int tflighthour = flightmin / 60;
        /*this if statement is for when there is a remainder of minutes
         *and the statement body computes the amount of 
         *minutes for the flight */
        if((flightmin % 60) != 0) {
            int tflightmin = flightmin - (tflighthour * 60);
            cout << "Total: " << tflighthour << " hr ";
            cout << tflightmin << " min" << endl;
        //this else statement is for when there are no leftover minutes
        } else {
            cout << "Total: " << tflighthour << " hr ";
            cout << "0 min" << endl;
        }
    }
            
    return 0;
}
int flighttime (int departhour, int departmin, int arrivehour, int arrivemin)
{
    int cdepartmin = (departhour * 60) + departmin;
    int carrivemin = (arrivehour * 60) + arrivemin;
    int cflighttime = carrivemin - cdepartmin;
    return cflighttime;
}
