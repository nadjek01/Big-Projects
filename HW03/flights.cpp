/*
 * guess.cpp
 * 
 * Purpose: find the layover and total flight time from the
 *          user inputs of departure and arrival time
 * 
 * Name: Nana Adjekum
 * Credits: HW03 Guidelines
 * Any Bugs/Issues:
 * Date: 02/10/2022
 */

#include <iostream>

using namespace std;

/*this function changes the hours to minutes and adds the converted hours to 
*minutes*/
int flighttime (int dhour, int dmin, int ahour, int amin);
void flightprint (int totalflightmins);
void layover (int dhour, int dmin, int ahour, int amin);
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
    
    cout << "Flight 2: ";
    cin >> hdeparturetwo >> mdeparturetwo >> harrivaltwo >> marrivaltwo;
    
    layover(hdeparturetwo, mdeparturetwo, harrivalone, marrivalone);
    int totalflightmins = flighttime(hdepartureone, mdepartureone, 
        harrivaltwo, marrivaltwo);
            if(hdepartureone > harrivalone or hdeparturetwo > harrivaltwo) {
                flightprint(totalflightmins + 1440);
            } else {
                flightprint(totalflightmins);
            }                        
    return 0;
    
}
int flighttime (int dhour, int dmin, int ahour, int amin)
{
    int cdepartmin = (dhour * 60) + dmin;
    int carrivemin = (ahour * 60) + amin;
    int cflighttime = carrivemin - cdepartmin;
    return cflighttime;
    
}
void flightprint (int totalflightmins)
{
    int tflighthr = totalflightmins / 60;
    int tflightmins = totalflightmins - (tflighthr * 60);
    cout << "Total: " << tflighthr << " hr ";
    cout << tflightmins << " min" << endl;
}
void layover (int ahour, int amin, int dhour, int dmin)
{
    int totallayover = flighttime(dhour, dmin, ahour, amin);
    int tlayoverhr = totallayover / 60;
    int tlayovermin = totallayover - (tlayoverhr * 60);
    cout << "Layover: " << tlayoverhr << " hr ";
    cout << tlayovermin << " min" << endl;
}