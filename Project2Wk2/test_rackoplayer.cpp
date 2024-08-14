//****************************************************************
//
//                       test_rackoplayer.cpp
//
//     A testing program that creates a RackoPlayer object.
//
//     The version we give you here initializes a discard pile and game
//     deck much as the real game would, but instead of reading in
//     a file with card values, we "hard wire" constants here.
//     We've chosen ones that match what you'd get in the real Racko
//     game by using sample file shuffled_deck2.txt, which contains the
//     following 20 card values:
//
//     6, 1, 18, 9, 15, 14, 16, 17, 8, 3, 7, 13, 12, 10, 11, 20, 5, 2, 4, 19
//
//     (you are welcome to modify this to read from another file, or use
//     other legal card values, but make sure there are no duplicates.
//
//    BUG: Discovered 12/1/2021...the order of some of the
//         put_card_on_top calls below is wrong, so the deck does NOT
//         quite match shuffled_deck2. The fix is in comments in the
//         create_and_initialize_decks function.
//
//     Once the decks are initialized, a single RackoPlayer object is created.
//     That is then called repeatedly to play the game until a winning hand
//     is reached or quit is requested.
//
//     Note that, unlike the real game, only one player is playing in
//     these tests.
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
#include "Card.h"
#include "RackoPlayer.h"

using namespace std;

void usage(int argc, char* argv[]);
void parse_command_line(int argc, char *argv[], bool *graphics_mode_on);

// Yes, this uses pointers to pointers to game_deck and discard_pile.
// So, we are passing the pointers themselves by reference, which
// allows initialize deck to "new" the actual decks.
//
// It's good if you understand this, but not essential...we've
// written this bit of the code for you.
void create_and_initialize_decks(Deck **game_deck_pp, Deck **discard_pile_pp);

const string PLAYER_NAME = "TestPlayer";
const unsigned int CARDS_PER_HAND = 5;

//****************************************************************
//                            main
//****************************************************************

int
main(int argc, char *argv[])
{
    bool graphics_mode_on;
    Deck *discard_pile_p;    // First card in shuffled_deck2.txt
    Deck *game_deck_p;
    bool keep_on_playing = true;

    //**************************************************************
    //
    //                     parse the command line
    //
    //  Set graphics_mode_on based on command line.
    //  (note we pass the address of the variable
    //  so that the parse function can update it...
    //  ...a simple example of Call By Reference (CBR))
    //
    //**************************************************************

    parse_command_line(argc, argv, &graphics_mode_on);

    //
    //  You are welcome to replace this code with some that will
    //  read from a file of your choice, but this is an easy way
    //  of getting some data into the discard pile and game deck.
    //
    //  These card values match those in shuffled_deck2.txt
    //
    create_and_initialize_decks(&game_deck_p, &discard_pile_p);

    //
    // Make a new RackoPlayer who will play using the
    // game deck and discard piles we've created.
    //
    RackoPlayer rp(PLAYER_NAME, CARDS_PER_HAND,
                   game_deck_p, discard_pile_p, graphics_mode_on);


    //
    // Play until a winning hand is created, or the user types q for quit
    //

    cout << "TEST PLAY IS STARTING FOR PLAYER NAMED "
         << rp.player_name() << endl;

    while (keep_on_playing and not rp.has_winning_hand()) {
        keep_on_playing = rp.play();
    }

    //
    //  Give final report on what happened
    //
    cout << endl;
    if (not keep_on_playing) {
        cout << rp.player_name() << " asked to quit. Test terminated." << endl;
    } else {
        cout << rp.player_name() << " has a winning hand!." << endl;
    }

    cout << endl << "Final contents of the hand are: " << endl << endl;

    rp.print_hand();

    // Free the decks
    delete game_deck_p;
    delete discard_pile_p;

    return 0;
}

//****************************************************************
//                        initialize_decks
//
//    Initializes game deck and discard pile with cards values
//    that happen to match the shuffled_deck2.txt sample file.
//
//    BUG: Discovered 12/1/2021...the order of some of the put_card_on_top
//         calls below is wrong, so the deck does NOT quite match
//         shuffled_deck2. The fix is in comments below.
//
//****************************************************************

void create_and_initialize_decks(Deck **game_deck_pp, Deck **discard_pile_pp)
{

    // Create discard pile
    Deck *discard_pile_p = new Deck(Card(6));

    // Create a game deck
    Deck *game_deck_p = new Deck(Card(19));

    // Push 18 others in order onto game deck. We push them in
    // reverse order...first card we'll draw is last one we
    // add here.

    game_deck_p->put_card_on_top(Card(4));
    game_deck_p->put_card_on_top(Card(2));
    game_deck_p->put_card_on_top(Card(5));
    game_deck_p->put_card_on_top(Card(20));
    game_deck_p->put_card_on_top(Card(11));
    game_deck_p->put_card_on_top(Card(10));
    game_deck_p->put_card_on_top(Card(12));
    game_deck_p->put_card_on_top(Card(13));
    game_deck_p->put_card_on_top(Card(7));
    game_deck_p->put_card_on_top(Card(3));
    game_deck_p->put_card_on_top(Card(17));
    game_deck_p->put_card_on_top(Card(8));
    game_deck_p->put_card_on_top(Card(16));
    game_deck_p->put_card_on_top(Card(14));
    game_deck_p->put_card_on_top(Card(15));
    //
    // BUG: TO MATCH shuffled_deck2.txt the calls should be in
    // this order:  If you want to actually have
    // the deck in the same order as shuffled_deck2, then
    // uncomment these two lines and use them to replace
    // the two below
    // game_deck_p->put_card_on_top(Card(9));
    // game_deck_p->put_card_on_top(Card(18));

    // COMMENT the next two lines if you are uncommenting the ones above

    game_deck_p->put_card_on_top(Card(18));
    game_deck_p->put_card_on_top(Card(9));
    game_deck_p->put_card_on_top(Card(1));
    cerr<<"lol"<<endl;

    // Set the deck pointers in the caller
    *game_deck_pp = game_deck_p;
    *discard_pile_pp = discard_pile_p;
}


//****************************************************************
//                      usage
//
//  Helper function to remind users of the correct format
//  if arguments are wrong and then exit.
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
//    If invoked like this set graphics_mode_on to false:
//
//      test_rackoplayer
//
//    If invoked like this set graphics_mode_on to true:
//
//      test_rackoplayer --graphics
//
//    and confirm to user.
//
//    Calls usage() to remind user of correct format and exit(1)
//      if command line is invalid.
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
