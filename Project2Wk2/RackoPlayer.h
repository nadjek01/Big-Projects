#ifndef RACKO_PLAYER_H
#define RACKO_PLAYER_H

//****************************************************************
//
//                         RackoPlayer.h
//
//     Represents a player of the Racko game.
//
//     Holds the only copy of the state of the player's hand, and
//     also for convenience keeps local pointer references to the
//     game deck and discard pile.
//
//     The most significant methods are:
//
//          player_name          returns name of player
//          play                 handles interaction for one round of play
//          has_winning_hand     returns true if player's hand wins
//
//     Author: Noah Mendelsohn
//
//     Tufts University, Fall 2021
//     CS 11: Project 2
//
//     Modified by: Nana Adjekum
//     Date: 4/20/22
//
//****************************************************************

#include <string>

#include "Deck.h"
#include "Card.h"
#include "Hand.h"

const string HAND_GRAPHIC_SUFFIX    = " Hand";
const string DISCARD_GRAPHIC_LABEL  = "Discard Pile";
const string NEW_CARD_GRAPHIC_LABEL = "New Card";

class RackoPlayer {
public:
    RackoPlayer(std::string player_name, unsigned int num_cards_per_hand,
                 Deck *game_deck_arg, Deck *discard_pile_arg,
                 bool graphics_on);
    ~RackoPlayer();

    // Member functions for playing the game
    bool play();             // take a turn; return false if user says quit
    bool has_winning_hand();

    // Utility functions
    std::string player_name();
    void print_hand();
    void debug_print();      // prints deck value for debugging.
                             // No newline at the end.
    bool card_replaced_in_hand(Card new_card, int value_to_drop);   
                                    //acc replaces the card in the hand
                                    //condenses replace card function

private:
    //********************************************************************
    //                   Private member vars
    //********************************************************************

    bool m_graphics_on;
    std::string m_player_name;
    Hand m_hand;
    Deck *m_game_deck_p;
    Deck *m_discard_pile_p;

    /*********************************************************************/
    /*     DO NOT CHANGE ANYTHING ABOVE THIS LINE.                       */
    /*     Students MAY add their own private member functions below     */
    /*     this block and above the next comment block.  Do not add data */
    /*     members.                                                      */
    /*********************************************************************/

    //********************************************************************
    //                       Private member functions
    //
    //  We give you some or all of the implementation for these
    //  because we think they may be useful, but you can make your own
    //  private helper functions if you prefer. Do NOT make new public
    //  helper functions.
    //
    //  For more information on these, see the comments near their
    //  definitions in RackoPlayer.cpp
    // ********************************************************************


    void its_your_turn();
    void clear_screen();
    void show_top_discard_card();
    char discard_gamedeck_or_quit();
    Card get_new_card(char choice);
    void replace_card_in_hand(Card new_card);
    int read_int_from_cin();

    /*******************************************************************/
    /*              Students MAKE NO CHANGES BELOW HERE                */
    /*******************************************************************/

    friend class CardTester;  // A friend class for testing
    friend class RackoPlayerTester;  // A friend class for testing
    friend class HandTester;  // A friend class for testing
    friend class DeckTester;  // A friend class for testing

    /*
     * Making copy constructor and assignment operator private
     * to prevent their inadvertant use from compiling.
     * Students do NOT implement these
     */
    RackoPlayer(RackoPlayer &other);
    RackoPlayer &operator=(RackoPlayer &rhs);
};

#endif
