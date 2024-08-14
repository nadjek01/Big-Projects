//****************************************************************
//
//                          racko.cpp
//
//     Implementation of a Racko game for CS 11
//
//     Author: Noah Mendelsohn
//
//     Tufts University, Fall 2021
//     CS 11: Project 2
//
//     Modified by:
//     Date:
//
//****************************************************************

#include <iostream>
#include <fstream>

#include "Card.h"
#include "Deck.h"
#include "RackoPlayer.h"

using namespace std;

const unsigned int NUMBER_OF_PLAYERS    = 2;
const unsigned int CARDS_IN_PLAYER_HAND = 5;
const string       WELCOME_MESSAGE      = "Let's play Racko!!\n";

const string       GRAPHICS_SWITCH      = "--graphics";   // for command line

//***************************************************************
//                   State of the Game
//***************************************************************

struct RackoGameState {
    bool graphics_on;
    string filename;
    Deck *game_deck_p;     // Input cards
    Deck *discard_pile_p;
    // Note the following is an array of pointers to RackoPlayer objects
    // ...so, each entry in the array is a pointer
    RackoPlayer *players[NUMBER_OF_PLAYERS];

    // ADD YOUR OWN DECLARATIONS BELOW FOR VARIABLES YOU USE
    // TO TRACK THE STATE OF THE GAME...IF YOU NEED ANY
};

//***************************************************************
//                     Function Prototypes
//***************************************************************

void initialize_game(RackoGameState *gs_p,
                     int argc, char *argv[]);
void parse_cmdline(RackoGameState *gs_p,
                     int argc, char *argv[]);
void initialize_card_decks(RackoGameState *gs_p);
void initialize_players(RackoGameState *gs_p);
void clean_up_game(RackoGameState *gs_p);
void play_the_game(RackoGameState *gs_p);
void delete_players(RackoGameState *gs_p);
void welcome_message();

//***************************************************************
//                     Helper Function
//***************************************************************

char end_game(RackoGameState *gs_p); 

//***************************************************************
//                          main
//
//      THIS FUNCTION IS COMPLETE. YOU SHOULD NOT HAVE
//      TO MODIFY IT.
//
//***************************************************************

int
main(int argc, char *argv[])
{
    // All data needed to play the game
    RackoGameState gs;

    //********************************************************
    // Initialize game deck, create and initialize discard pile &
    // player objects Note whether --graphics specfied on 
    //  command line
    //********************************************************

    // (note, we pass &gs rather than gs so that the functions
    // like initialize_game can update the game state)
    initialize_game(&gs, argc, argv);

    //********************************************************
    // Play the game
    //********************************************************
    
    
    welcome_message();
    play_the_game(&gs);

    //********************************************************
    // Clean up and exit
    //********************************************************

    clean_up_game(&gs);
    return 0;
}


//***************************************************************
//          Functions to Play the Game
//***************************************************************

//************************************************************
//
//                    welcome_message
//
//      THIS FUNCTION IS COMPLETE. YOU SHOULD NOT HAVE
//      TO MODIFY IT.
//
//************************************************************

void welcome_message()
{
    cout << WELCOME_MESSAGE << endl;
}

//************************************************************
//
//                    play_the_game
//
//      Purpose: Play the whole game and report results, calls 
//               the helper function end game in a loop when 
//               end_game returns a char that ends the game
//               the loop terminates and the game ends
//      Parameters: A pointer to a struct of type RackoGameState
//      Returns: N/A
//
//************************************************************
//
// 
//
//************************************************************

void play_the_game(RackoGameState *gs_p)
{
    while (end_game(gs_p) == 'c') {     //empty for loop for the game
        
    }
}


//***************************************************************
//             Initialization and cleanup functions
//***************************************************************

//************************************************************
//                parse_cmdline
//
//      THIS FUNCTION IS COMPLETE. YOU SHOULD NOT HAVE
//      TO MODIFY IT.
//
//************************************************************

void parse_cmdline(RackoGameState *gs_p,
                     int argc, char *argv[])
{
    // Graphics mode switch from command line
    if (argc == 3) {
        if (argv[1] == GRAPHICS_SWITCH) {
            gs_p->graphics_on = true;
        } else {
            cerr << "racko: invalid --graphics switch on command line: "
                 << argv[1] << endl;
            exit(1);
        }
        // If there was a --graphics switch, filename is 2nd argument
        gs_p->filename = argv[2];
    } else if (argc != 2) {
        cerr << "Usage: racko <filename> " << endl
             << "       racko --graphics <filename>" << endl;
            exit(1);
    } else {
        // argc == 2
        // There was no --graphics switch, filename is 1st argument
        gs_p->graphics_on = false;
        gs_p->filename = argv[1];
    }
}

//************************************************************
//                initialize_game
//
//      THIS FUNCTION IS COMPLETE. YOU SHOULD NOT HAVE
//      TO MODIFY IT UNLESS YOU WANT TO HAVE IT
//      USE DIFFERENT HELPER FUNCTIONS.
//
//************************************************************

void initialize_game(RackoGameState *gs_p,
                     int argc, char *argv[])
{
    parse_cmdline(gs_p, argc, argv);
    initialize_card_decks(gs_p);
    initialize_players(gs_p);
}

//************************************************************
//                  initialize_card_decks
//
//    Purpose: Create the game deck and the discard pile, Both are of class
//             Deck.
//
//    Parameters: A pointer to a struct of type RackoGameState
//
//    Returns: N/A
//
//************************************************************

void initialize_card_decks(RackoGameState *gs_p)
{
    //int game deck
    Deck *game_deck = new Deck (gs_p->filename);
    gs_p->game_deck_p = game_deck;
    
    //gets the first card after game_deck is made
    Deck *discard_pile = new Deck (gs_p->game_deck_p->draw_top_card());
    gs_p->discard_pile_p = discard_pile;

}

//************************************************************
//                        initialize_players
//
//      Purpose: Populate players array with RackoPlayer objects
//
//          Starting with subscript 0 in the players array, creates a
//          new RackoPlayer object for that named person, and puts a
//          pointer to that object into the players array in the game
//          state. Thus the pointer to the RackoPlayer object for the
//          player listed as #1 in the prompt above goes into
//          players[0], etc.
//     Parameters: A pointer to a struct of type RackoGameState
//     Returns: N/A
//
//************************************************************

void initialize_players(RackoGameState *gs_p)
{
    string a_player_name;
    unsigned int j = 0;
    
    //goes through the array and adds a player at each index less than the 
    //NUMBER_OF_PLAYERS
    while (j < NUMBER_OF_PLAYERS) {
        cout << "Enter the name for player " << j + 1 << ": ";
        cin >> a_player_name;
        RackoPlayer *s_player = new RackoPlayer(a_player_name, 
            CARDS_IN_PLAYER_HAND, gs_p->game_deck_p, 
            gs_p->discard_pile_p, gs_p->graphics_on);
        gs_p->players[j] = s_player;
        j++;
    }
}

//************************************************************
//                       clean_up_game
//
//      Purpose: Return to the heap any objects that were allocated by
//      initialize_game (or by functions called by initialize_game).
//      
//      Parameters: A pointer to a struct of type RackoGameState
//
//      Returns: N/A
//
//************************************************************

void clean_up_game(RackoGameState *gs_p)
{
    //deletes game_deck
    delete gs_p->game_deck_p;
    gs_p->game_deck_p = nullptr;
    
    //deletes discard_pile
    delete gs_p->discard_pile_p;
    gs_p->discard_pile_p = nullptr;
    
    //for loop that deletes the players in each index
    for (unsigned int i = 0; i < NUMBER_OF_PLAYERS; i++) {
        delete gs_p->players[i];
        gs_p->players[i] = nullptr;
    }
}
//************************************************************
//                       end_game
//
//      Purpose: The facilitator of the games loop; returns a char
//               that kills the loop. has conditionals to facilite
//               the goings on of the loop
//      
//      Parameters: A pointer to a struct of type RackoGameState
//
//      Returns: A char that kills the loop
//
//************************************************************
char end_game(RackoGameState *gs_p) 
{
    char game_over = 'c';           //keeps loop going

    for (unsigned int i = 0; i < NUMBER_OF_PLAYERS; i++) {
        
        //for when user quits the game
        if (gs_p->players[i]->play() == false) {
            cout << "User asked to end the game. Leaving now." << endl;
            game_over = 'q';
            return game_over;
        
        //for when a user wins the game
        } else if (gs_p->players[i]->has_winning_hand() == true) {
            cout << "Congratulations " << gs_p->players[i]->player_name()
                 << ", you've won!!" << endl;
            game_over = 'w';
            return game_over;
        
        //for when out of cards
        }  else if (gs_p->game_deck_p->number_of_cards() == 0) {
            cout << "The game stopped because we ran out of cards" << endl;
            game_over = 'n';
            return game_over;
        }
    }
    return game_over;
}