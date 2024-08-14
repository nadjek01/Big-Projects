/*
 * bicycles.cpp
 * 
 * Purpose: to organise bike parts and calculate how many parts
 *           (wheels, frames, links) are leftover after manufacturing
 *           said bike.
 *
 * Name: Nana Adjekum
 * Credits: HW02 Guidelines, Office Hours
 * Any Bugs/Issues: N/A
 * Date: 02/07/2022
 */
#include <iostream>

using namespace std;

int main ()
{
    //variables to be used
    int wheels, frames, links;
    
    cout << "Enter the number of wheels: ";
    cin >> wheels;
    
    cout << "Enter the number of frames: ";
    cin >> frames;
    
    cout << "Enter the number of links: ";
    cin >> links;
    
    /* this set of conditionals is for when wheels is the limiting
    component of the bike function */
    if ((wheels / 2) < (frames) and (wheels / 2) < (links / 50)) {
        /*these functions find the number of bikes to be made
         *and the amount of each component is to be left over */
        int bikes = wheels / 2;                 
        int leftwheels = wheels - (bikes * 2);
        int leftframes = frames - bikes;
        int leftlinks = links - (50 * bikes);
        
        //conditionals for singularity and plurality
        if(bikes == 1) {
            cout << "You can make " << bikes << " bike. ";
        } else {
                cout << "You can make " << bikes << " bikes. ";
            } if(leftwheels == 1) {
            cout << "There are " << leftwheels << " wheel, ";
        } else {
                cout << "There are " << leftwheels << " wheels, ";
            } if(leftframes == 1) {
            cout << leftframes << " frame, ";
        } else {
                cout << leftframes << " frames, ";
            } if(leftlinks == 1) {
            cout << leftlinks << " link leftover." << endl;
        } else {
                cout << leftlinks << " links leftover." << endl;
        }
    }
    
    /*this set of conditionals is for when the limiting component
     *of the bike function are the frames */
    if(frames < (wheels / 2) and frames < (links / 50)) {
        int bikes = frames;
        int leftwheels = wheels - (frames * 2);
        int leftframes = bikes - frames;
        int leftlinks = links - (frames * 50);
        
        if(bikes == 1) {
            cout << "You can make " << bikes << " bike. ";
        } else {
            cout << "You can make " << bikes << " bikes. ";
        } if(leftwheels == 1) {
            cout << "There are " << leftwheels << " wheel, ";
        } else {
                cout << "There are " << leftwheels << " wheels, ";
            } if(leftframes == 1) {
            cout << leftframes << " frame, ";
        } else {
                cout << leftframes << " frames, ";
            } if(leftlinks == 1) {
            cout << leftlinks << " link leftover." << endl;
        } else {
                cout << leftlinks << " links leftover." << endl;
        }
    }
    
    /*this set of conditionals is for when the limiting component
     *are the links. this conditional differs (and instead of or) 
     *as half of the condition has been mentioned before and 
     *will reprint */
    if((links / 50) < frames and (links / 50) < (wheels / 2)) {
        int bikes = links / 50;
        int leftwheels = wheels - (2 * bikes);
        int leftframes = frames - bikes;
        int leftlinks = links - (50 * bikes);
        if(bikes == 1) {
            cout << "You can make " << bikes << " bike. ";
        } else {
            cout << "You can make " << bikes << " bikes. ";
        } if(leftwheels == 1) {
            cout << "There are " << leftwheels << " wheel, ";
        } else {
                cout << "There are " << leftwheels << " wheels, ";
            } if(leftframes == 1) {
            cout << leftframes << " frame, ";
        } else {
                cout << leftframes << " frames, ";
            } if(leftlinks == 1) {
            cout << leftlinks << " link leftover." << endl;
        } else {
                cout << leftlinks << " links leftover." << endl;
        }
    }
    
    /*set of conditionals for when the numbers are equal to each other
     *had to be made because sometimes the components put are equal and 
     *also bigger than another (3, 2, 51) */
    if((wheels / 2) == frames or (wheels / 2) == (links / 50)) {
        int bikes = wheels / 2;
        int leftwheels = wheels - (bikes * 2);
        int leftframes = frames - bikes;
        int leftlinks = links - (50 * bikes);
        
        if(bikes == 1) {
            cout << "You can make " << bikes << " bike. ";
        } else {
                cout << "You can make " << bikes << " bikes. ";
            } if(leftwheels == 1) {
            cout << "There are " << leftwheels << " wheel, ";
        } else {
                cout << "There are " << leftwheels << " wheels, ";
            } if(leftframes == 1) {
            cout << leftframes << " frame, ";
        } else {
                cout << leftframes << " frames, ";
            } if(leftlinks == 1) {
            cout << leftlinks << " link leftover." << endl;
        } else {
                cout << leftlinks << " links leftover." << endl;
        }
    }
    
    return 0;
}



