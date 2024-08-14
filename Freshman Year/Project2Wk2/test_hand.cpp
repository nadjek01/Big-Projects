//****************************************************************
//
//                         test_hand.cpp
//
//     A testing program that creates a Hand object.
//
//     For this one, we give you some useful starter code, but you
//     will want to adapt it to be sure to test different cases and 
//     operations.
//
//     Author: Noah Mendelsohn
//
//     Tufts University, Fall 2021
//     CS 11: Project 2
//
//     Modified by: Nana Adjekum
//     Date: 04/20/22
//
//****************************************************************

#include <iostream>

#include "Card.h"
#include "Hand.h"

using namespace std;

void usage(int argc, char* argv[]);
void parse_command_line(int argc, char *argv[], bool *graphics_mode_on);


//****************************************************************
//                            main
//****************************************************************

int
main(int argc, char *argv[])
{
    bool graphics_mode_on;

    //  Set graphics_mode_on based on command line.
    //  (note we pass the address of the variable
    //  so that the parse function can update it...
    //  ...a simple example of Call By Reference (CBR))
    parse_command_line(argc, argv, &graphics_mode_on);

    cout << "Starting to create winning hand:" << endl;

    Hand winning_hand;
    // Put in 5 cards in order -- a winning hand!
    winning_hand.add_card_at(0, Card(1));
    winning_hand.add_card_at(1, Card(2));
    winning_hand.add_card_at(2, Card(3));
    winning_hand.add_card_at(3, Card(4));
    winning_hand.add_card_at(4, Card(5));

    cout << "Created winning_hand: " << endl;
    winning_hand.debug_print();

    // Try the non-graphic print command
    cout << endl << "Printing winning hand using Hand::print(): ";
    winning_hand.print();

    // Try graphic printing if graphic mode is requested
    // on the command line
    if (graphics_mode_on) {
        cout << endl << "Printing winning hand using Hand::graphic_print(): "
             << endl;
        winning_hand.graphic_print("Winning Hand");
    }

    cout << endl << endl << "Starting to create losing hand:" << endl;
    Hand losing_hand;
    // Put in 5 cards in order -- a losing hand!
    losing_hand.add_card_at(0, Card(1));
    losing_hand.add_card_at(1, Card(2));
    losing_hand.add_card_at(2, Card(4));
    losing_hand.add_card_at(3, Card(3));
    losing_hand.add_card_at(4, Card(5));

    cout << "Created losing_hand: " << endl;
    losing_hand.debug_print();

    // Try the non-graphic print command
    cout << endl  << "Printing losing hand using Hand::print(): ";
    losing_hand.print();

    // Try graphic printing if graphic mode is requested
    // on the command line
    if (graphics_mode_on) {
        cout << endl << "Printing losing hand using Hand::graphic_print(): "
             << endl;
        losing_hand.graphic_print("Losing Hand");
    }
    
    cout << endl << endl << "Extra check of the print function: " << endl;
    Hand empty; 
    
    cout << "Created empty list: " << endl;
    empty.print();
    
    Hand more_than;
    more_than.add_card_at(0, Card(1));
    more_than.add_card_at(1, Card(2));
    more_than.add_card_at(2, Card(4));
    more_than.add_card_at(3, Card(3));
    more_than.add_card_at(4, Card(5));
    more_than.add_card_at(5, Card(6));
    more_than.add_card_at(6, Card(7));
    more_than.add_card_at(7, Card(8));
    more_than.add_card_at(8, Card(9));
    
    cout << "Created a list with more than 5 cards: " << endl;
    more_than.print();
    
    return 0;
}

//****************************************************************
//                       usage
//
//     Helper function to remind users of the correct format if
//     arguments are wrong and then exit.
//
//****************************************************************

void usage(int argc, char* argv[])
{
    (void)argc;
    cerr << "Usage: " << argv[0] << " [--graphics]" << endl;
    exit(1);
}


//****************************************************************
//
//                parse the command line.
//
//     If invoked like this set graphics_mode_on to false:
//
//            test_hand
//
//     If invoked like this set graphics_mode_on to true:
//
//            test_hand --graphics
//
//     ...and confirm to user that graphics mode is on.
//
//     Calls usage() to remind user of correct format and exit(1)
//     if command line is invalid.
//
//****************************************************************

void parse_command_line(int argc, char *argv[], bool *graphics_mode_on)
{
    // No more than one arg is legal
    if (argc > 2) {
        usage(argc, argv);
    }
    if (argc == 2) {
        if (string(argv[1]) == "--graphics") {
        *graphics_mode_on = true;
        cout << "Graphics mode is ON" << endl;
        } else {
            // An argument is provided but it's not --graphics
            usage(argc, argv);
        }
    } else {
        // No arguments provided
        *graphics_mode_on = false;
    }
    return;
}
