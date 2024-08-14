//****************************************************************
//
//                         RackoPlayer.cpp
//
//     Methods to support the RackoPlayer class, which represents
//     the state of the game for and handles interaction with a 
//     Racko player.
//
//     Author: Noah Mendelsohn
//
//     Tufts University, Fall 2021
//     CS 11: Project 2
//
//     Modified by: Nana Adjekum
//     Date: 04/20/2022
//
//****************************************************************

#include <iostream>
#include <cstdlib>   // for system call to clear the screen

#include "Deck.h"
#include "Hand.h"
#include "RackoPlayer.h"

#include "CardImage.h"

using namespace std;

//************************************************************************
//
//                            Constructor
//
//   * Records the game deck and discard pile pointers, and player's name
//   * Draws cards from the game deck to fill initial hand for the player
//   * Checks for the odd case that the hand wins immediately, in which
//     case we exit the whole came and declare success NEEDSWORK: is
//     that what we want?
//
//  Remember: the member variables we set here are available to all
//  the member functions of this class. This becomes the shared state of
//  what we know about this player, and also allows us to easily find
//  things like the game deck that are needed to play the game.
//
//  NOTE TO STUDENTS: WE WROTE MOST OF THIS FOR YOU, BUT THERE IS
//  ONE IMPORTANT PIECE OF THE CODE YOU HAVE TO ADD...SEE COMMENTS
//  IN THE CODE BELOW.
//
//************************************************************************

RackoPlayer::RackoPlayer(std::string player_name, unsigned int num_cards,
                           Deck *game_deck_arg, Deck *discard_pile_arg,
                           bool graphics_on)
{
    // Make local copies of pointers to the game deck, the discard pile, etc.
    // Note the player's name, and whether graphics is on
    m_game_deck_p    = game_deck_arg;
    m_discard_pile_p = discard_pile_arg;

    m_player_name = player_name;
    m_graphics_on = graphics_on;

    // Initialize the player's hand by adding the appropriate
    // number of cards to m_hand by drawing from the game deck.
    // So that everyone plays the same way and we can test the results,
    // the cards are always added in order, with the first card drawn
    // winding up first in the hand.

    unsigned int i = 0;
    while (i < num_cards) {
        Card i_card = m_game_deck_p->draw_top_card();
        m_hand.add_card_at(i, i_card);
        i++;
    }

    // Check for super-unlikely case that initial hand is a winner.
    // Just give up)
    if (has_winning_hand()) {
        cout << "AMAZING!! Player " << player_name
             << " drew a winning hand at the start of the game!" << endl;
        cout << "The game is over before it starts." << endl;
        exit(0);
    }
}

//************************************************************************
//                            Destructor
//************************************************************************

RackoPlayer::~RackoPlayer()
{
    // No explicit destruction needed for this class.
    // The automatic member destruction will clean up the deck object
}

//************************************************************************
//                             player_name
//************************************************************************

std::string RackoPlayer::player_name()
{
    return m_player_name;
}

//************************************************************************
//                               play
//
//    Purpose: This handles a turn for the player, including both user 
//             interaction  and updating the state of the game. It does 
//             NOT check whether the result is a winning hand.
//
//     What you must do and how to get it right
//     ----------------------------------------
//
//     This function and the private helper functions it calls embody
//     all the logic for one player's turn...FOR FULL CREDIT YOU WILL
//     NEED TO GET THIS FUNCTION TO EXACTLY MATCH, IN ALL CASES, THE
//     SPECIFICATIONS WE GIVE YOU IN THE INSTRUCTIONS.
//
//     TO MAKE DOING THIS EASIER, WE GIVE YOU A RUNNABLE REFERENCE
//     IMPLEMENTATION OF THE racko EXECUTABLE THAT WE BELIEVE TO BE
//     CORRECT. Anytime you are not sure what this code should do, use
//     the reference executable we give you to play with the same
//     input card deck, and of course the same choices by each
//     users. IF YOUR OUTPUT MATCHES WHAT THE CORRECT EXECUTABLE DOES
//     IN ALL CASES, YOU WILL RECEIVE FULL CREDIT.
//
//     Overview of Function Logic
//     --------------------------
//
//     Of course, in all cases the exact specifications for prompting
//     text, error handling etc., but roughly what you must do for
//     each call to play() is:
//
//
//     * Tell the player it's their turn. We urge you to use the
//       its_your_turn function that we've written for you, as it
//       gets the formatting exactly right (and clears the screen
//       first in graphics mode.)
//
//     * Show them what's in their hand. Run the sample executable
//       to see exactly what this should look like.
//
//     * Ask them whether they want to draw from the game deck, or the
//       discard pile, or whether they prefer to quit the whole game.
//        Again, the sample executable shows how this should look.
//
//     * If the user says to quit, just return false immediately. That's the
//       signal to the caller of play() that quit was requested.
//
//     * ONLY WHEN YOU GET TO HANDLING GRAPHICS: add a step here to
//       print the user's hand again (Why? In graphics mode things tend
//       to scroll off the screen and the user will want to see their
//       hand before makign a choice. In normal mode only a few lines
//       are written and the hand is usually still visible.) DON'T WORRY
//       ABOUT THIS UNLESS YOU GET TO DOING GRAPHICS.
//
//     * Depending on whether the user selected game deck (g) or discard
//       pile (d), draw a new card from the appropriate deck.
//
//     * Ask the user which card they would like to discard, and do
//       it. They can either choose the value of a card already in
//       their hand, in which case you must take that card out of
//       their hand and put it on the discard pile, and put the new
//       card in their hand in place of the old.  Or, the user may
//       choose to discard the new card (even if it just came off the
//       discard pile...put the new_card on the discard pile. In that
//       case, no changes are needed to the user's hand.
//
//       Parameters: N/A
//       Returns: true from play(), because the user did not ask to quit,
//                and play() has successfully played the users' turn.
//
//
//
//************************************************************************


bool RackoPlayer::play()
{
    its_your_turn();
    print_hand();
    show_top_discard_card();
    char p_choice = discard_gamedeck_or_quit();
    if (p_choice != 'q') {
        Card p_card = get_new_card(p_choice);
        replace_card_in_hand(p_card);
        return true; 
    } else {
        return false;
    }     
}


//************************************************************************
//                            its_your_turn
//
//   Purpose: Called to announce start of a player's turn (or end game in
//            unlikely case that game deck is empty).
//   Parameters: N/A
//   Returns: N/A
//
//************************************************************************

void RackoPlayer::its_your_turn()
{
    // Tell new player it's their turn
    // Start each player's display at the top of the terminal
    
    clear_screen();
    cout << "========================================" << endl;
    cout << "         Player " << m_player_name << " it's your turn!" << endl;
    cout << "========================================" << endl << endl;


    // Bail out if there are no cards in the deck
    if (m_game_deck_p->number_of_cards() <= 0) {
        cerr << "Player " << m_player_name
             << " cannot take turn because game deck is empty" << endl;
        exit(1);
    }
}

//************************************************************************
//                         has_winning_hand
//
//    Purpose: Checks if a player has a winning hand.
//             A hand wins only if all the cards are in order
//    from low to high.
//    Parameters: N/A
//    Returns: Return true if player is holding a winning hand, otherwise
//             false.
//
//************************************************************************

bool RackoPlayer::has_winning_hand()
{
    bool has_won = false;       //set to false in beginning bc havent check yet
    unsigned int w_count = 0;
    
    //for loop that checks when the next card (i+1) is greater than the 
    //current card (i)
    for (unsigned int i = 0; i < m_hand.num_cards() - 1; i++) {
        Card c_card = m_hand.get_card_at(i);
        Card d_card = m_hand.get_card_at(i+1);
        if (c_card.value() < d_card.value()) {
            w_count++;
        }
    }
    
    //sets has won to true when the number of possible wins is equal to the 
    //counter variable. number of variable wins the number of possible 
    //comparisons (which happens to be num_cards - 1)
    if (w_count == (m_hand.num_cards() - 1)) {      //logic check
        has_won = true;
        return has_won;
    } else {
        return has_won;
    }    
}


//************************************************************************
//                    show_top_discard_card
//
//   Purpose: Display the value of the top card of deck
//   Parameters: N/A    
//   Returns: N/A
//
//************************************************************************

void RackoPlayer::show_top_discard_card()
{
    if (m_graphics_on) {
        CardImage img(m_discard_pile_p->inspect_top_card());
        img.graphic_print(DISCARD_GRAPHIC_LABEL);
    } else {
        cout << "The top card on the discard pile is: "
             << m_discard_pile_p->inspect_top_card().value()
             << endl;
    }
}


//************************************************************************
//                      discard_gamedeck_or_quit
//
//   Purpose: Repeatedly asks the user to enter a character 
//            representing a choice of:
//           g - draw from game deck
//           d - draw from game discard pile
//           q - quit the game
//
//   Once the user enters a char consisting of one of the three single
//   characters above (lowercase only), return that character. Otherwise,
//   prompt again until the user enters one of the three.
//   Parameters: N/A
//   Returns: N/A
//   
//
//************************************************************************

const string CHOICE_PROMPT = "Would you like to draw from the game "
                             "deck (g) discard pile (d) or quit (q)?: ";

char RackoPlayer::discard_gamedeck_or_quit()
{
    char choice;
    cout << CHOICE_PROMPT;
    cin >> choice;
    if (choice == 'g' or choice == 'd' or choice == 'q') {
        return choice;
    } else {
        return discard_gamedeck_or_quit();
    }
}

//************************************************************************
//                          get_new_card
//
//   Purpose: Get the new card from either the game deck or the 
//            discard pile depending on whether "choice" parameter
//            is 'g' or 'd'. Also displays the chosen card.
//
//   Parameters: A char which is the choice of the user
//   Returns: A card from either the game deck or discard pile. Also
//            returns 0 because of syntax, but there is no instance
//            where anything but g or d will be passed
//
//************************************************************************

Card RackoPlayer::get_new_card(char choice)
{
    if (choice == 'g') {
        Card g_card = m_game_deck_p->draw_top_card();
        cout << "You drew card " << g_card.value();
        cout << " from the game deck." << endl;
        return g_card;
    } else if (choice == 'd') {
        Card d_card = m_discard_pile_p->draw_top_card();
        cout << "You drew card " << d_card.value();
        cout << " from the discard pile." << endl;
        return d_card;
    }
    return 0;
}

//************************************************************************
//                          replace_card_in_hand
//
//   Purpose: When this function is called, a new card has already been chosen.
//            The user now gets to decide which card to 
//            put on the discard pile.
//
//   Parameters: new_card - A Card which may be placed in the m_hand
//
//   Returns: N/A
//
//
//************************************************************************

const string REPLACE_CARD_PROMPT = "What is the face value of the card"
                                   " you would like to discard? ";

void RackoPlayer::replace_card_in_hand(Card new_card)
{
    int value_to_drop;
    bool discarded_a_card = false;
    Card r_card;
    // LOOP until the card chosen is one that's in the hand and discard it
    do {
        // Ask the user which card they would like to drop
        cout << REPLACE_CARD_PROMPT;

        //reads in val to drop from user input; ensures acc an int
        value_to_drop = read_int_from_cin();
        if (new_card.value() == value_to_drop) {
            m_discard_pile_p->put_card_on_top(new_card);
            discarded_a_card = true;
        } else {
            for (unsigned int i = 0; i < m_hand.num_cards(); i++) {
                r_card = m_hand.get_card_at(i);
                if (r_card.value() == value_to_drop) {
                    m_discard_pile_p->put_card_on_top(r_card);
                    discarded_a_card = true;    
                }
            }
        }   
        if (not discarded_a_card) {
            cout << value_to_drop
                 << " was not the value of the drawn card and was not in "
                 << "your hand. Try again..." << endl;
        }
    } while (not discarded_a_card);
    discarded_a_card = card_replaced_in_hand(new_card, value_to_drop);    
}

//************************************************************************
//
//                        read_int_from_cin
//
//  Mostly this is easy to do, but things get tricky if a user
//  enters something other than a number (like q for quit, which is
//  an easy mistake to make.) Recovering this in C++ is a little tricky,
//  as you have to reset an error marker on cin (using clear) and reread
//  to pull out the unread text (e.g. q).
//
//  SINCE THIS IS TRICKY AND NOT VERY INTERESTING, WE GIVE YOU THIS CODE
//  YOU CAN TRUST THAT IT WORKS.
//
//************************************************************************

int RackoPlayer::read_int_from_cin()
{
    int num;
    bool done = false;
    while (not done) {
       cin >> num;
       if (cin.fail()) {
           string scrap;
           cin.clear();     // clear the error state
           cin >> scrap;    // read the bad input
           cout << "Sorry, you should have entered a number but you entered: "
                << scrap << "." << endl;
           cout << "Please try again...: ";
       } else {
          done = true;
       }
    }

    return num;
}


//************************************************************************
//
//                         print_hand
//
//   At various points in the game you will want to show the player
//   the contents of their hand. Exactly how that's done depends on
//   whether we're in graphics mode or not.
//
//   Here's what this function does:
//
//     * If NOT in graphics mode it prints a message like:
//
//               Mark's hand: 3, 5 12, 13, 2
//
//     * If in graphics mode it uses Hand.graphi_print to print
//       a lovely looking visual display of the hand, with a nice
//       border etc.
//
//   SO YOU WON'T HAVE TO WORRY ABOUT GRAPHICS MODE, WE GIVE YOU ALL
//   THE CODE YOU NEED HERE FOR print_hand, BUT...
//
//   WHEN IN THE USUAL NON-GRAPHIC MODE, THIS CALLS Hand::print() AND
//   YOU >DO< HAVE SOME CODE TO COMPLETE FOR THAT. SO, IF YOU WANT
//   THIS FUNCTION TO WORK PROPERLY, MAKE SURE THAT Hand::print() is
//   properly coded.
//
//************************************************************************

void RackoPlayer::print_hand()
{
    if (m_graphics_on) {
        // On top of graphic display put label like Mary's Hand
        m_hand.graphic_print(player_name() + "'s" + HAND_GRAPHIC_SUFFIX);
    } else {
        cout << player_name() << "'s hand: ";
        m_hand.print();
    }
    cout << endl;
}


//************************************************************************
//
//                           debug_print
//
//   The assumption is that most printing will be handled by users of
//   this class, but being able to print in a standard way when
//   debugging is handy.
//
//************************************************************************

void RackoPlayer::debug_print()
{
    cout << endl;
    cout << "RackoPlayer::debug_print for player " << m_player_name << endl;
    cout << "Graphics mode is: ";
    if (m_graphics_on) {
        cout << "ON" << endl;
    } else {
        cout << "OFF" << endl;
    };
    cout << "Player's hand is: " << endl;
    m_hand.debug_print();
}


//************************************************************************
//                        clear_screen (GRAPHICS MODE ONLY)
//
//     Clears the user's terminal so next cout prints on top line
//     of display.
//
//     (Usable, for example, to make sure each user's turn is played on a clear
//     screen).
//
//     DO NOT WORRY ABOUT THIS UNLESS YOU GET TO TRYING GRAPHICS MODE,
//     EVEN THEN, YOU CAN ASSUME THIS WORKS RIGHT, AND WE CALL IT
//     FOR YOU IN THE RIGHT PLACE IN THE its_your_turn FUNCTION.
//
//************************************************************************

void
RackoPlayer::clear_screen()
{
    if (m_graphics_on) {
        system("clear");
    }
}


//************************************************************************
//                    helper functions for play function
//
//     All the functions added to help condense the play function and 
//     make it easier to work with
//
//************************************************************************

//************************************************************************
//                          card_replaced_in_hand
//
//   Purpose: To add a card within the players hand while removing the 
//            card the player wanted removed
//            (done by matching the value of the card and 
//            the passed in value to drop)
//            when the values are matched does it's thing and returns a bool
//            which ensures that the card was actually replaced
//            Also meant to condense the replace and card function
//
//   Parameters: new_card - A Card which may be placed in the m_hand and 
//               and int value_to_drop which is the value of the card to 
//               drop
//
//   Returns: a bool card_added (ensures the card was acc replaced)
//
//
//************************************************************************
bool RackoPlayer::card_replaced_in_hand(Card new_card, int value_to_drop) 
{
    bool card_added = false;
    for (unsigned int i = 0; i < m_hand.num_cards(); i++) {
        Card d_card = m_hand.get_card_at(i);
        if (d_card.value() == value_to_drop) {
        m_hand.remove_card_at(i);      
        m_hand.add_card_at(i, new_card);
        return card_added = true; 
        }
    }
    return card_added;
}

