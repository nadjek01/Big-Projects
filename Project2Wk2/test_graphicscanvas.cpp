//****************************************************************
//
//                   test_graphicscanvas.cpp
//
//     A testing program that creates a Deck object and tries the
//     basic operations on it, using debug_print to report on the
//     internal state of all objects as it goes.
//
//     YOU CAN MODIFY THIS IF YOU LIKE FOR FUN, BUT YOU WILL NOT
//     BE SUBMITTING IT.
//
//     Author: Noah Mendelsohn
//
//     Tufts University, Fall 2021
//     CS 11: Project 2
//
//****************************************************************

#include <iostream>

#include "GraphicsCanvas.h"
#include "Card.h"
#include "CardImage.h"


using namespace std;

//****************************************************************
//               CONSTANTS TO SET THE DISPLAY LAYOUT
//****************************************************************

//****************************************************************
//      Locations at which to write test text messages:
//****************************************************************

const int MSG1_COL = 15;
const int MSG1_ROW = 2;

const int MSG2_COL = MSG1_COL;
const int MSG2_ROW = MSG1_ROW + 2;    // Leave a blank line between messages


//****************************************************************
//     Upper left corner location of first card
//****************************************************************

const  int FIRST_CARD_COL = 3;
const  int FIRST_CARD_ROW = MSG2_ROW + 2;   // 2 blank lines between 
                                            // msgs and cads

//****************************************************************
//     Left-right spacing between the two cards
//****************************************************************

const  int INTER_CARD_SPACING = 2;

//****************************************************************
//                       CANVAS_WIDTH
//
// Canvas is wide enough for two cards with two spaces in between
// plus 4 extra rows and colums to allow for a border
// and blank space inside the border
//
//****************************************************************

const unsigned int CANVAS_WIDTH = FIRST_CARD_COL + INTER_CARD_SPACING +
                                  (CARD_WIDTH * 2) + 2;

//****************************************************************
//                       CANVAS_HEIGHT
//
// Note: FIRST_CARD_ROW is already below the top border, so
// here we only need to allow two rows for the bottom.
//
//****************************************************************

const unsigned int CANVAS_HEIGHT = FIRST_CARD_ROW + CARD_HEIGHT + 2;

//****************************************************************
//                            main
//****************************************************************

int
main()
{

    GraphicsCanvas gc(CANVAS_HEIGHT, CANVAS_WIDTH);

    gc.border('*');            // put border on top, bottom, left, right

    // Draw the card images onto the canvas...note, even though we
    // draw these first, their positions put them below the test text
    CardImage img37(Card(37));
    img37.draw_image_to_canvas(&gc, FIRST_CARD_ROW, FIRST_CARD_COL);

    CardImage img14(Card(14));
    img14.draw_image_to_canvas(&gc,  FIRST_CARD_ROW,
                               FIRST_CARD_COL + CARD_WIDTH + 2);

    // Write the two text messages to the canvas
    // Note: we could have also used "Graphics_Canvas::render_string"
    // which might have been easier, but this illustrates how we
    // can use the << operator to format strings for the canvas.

    GraphicsStream hello_stream(&gc, MSG1_ROW, MSG1_COL);
    hello_stream << "Hello there!";
    hello_stream.render();

    GraphicsStream hello_stream2(&gc, MSG2_ROW, MSG2_COL);
    hello_stream2 << "Hello again!";
    hello_stream2.render();

    gc.print_to_cout();

    return 0;
}
