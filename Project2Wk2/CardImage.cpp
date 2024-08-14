//****************************************************************
//
//                         CardImage.cpp
//
//     Methods to support the CardImage class, which represents
//     a single playing CardImage.
//
//     Author: Noah Mendelsohn
//
//     Tufts University, Fall 2021
//     CS 11: Project 2
//
//****************************************************************

#include <iostream>
#include <iomanip>             // gets setw for debug printing
#include "Card.h"
#include "CardImage.h"
#include "GraphicsCanvas.h"
#include "all_card_images.h"   // images of all the cards for printing

using namespace std;

//****************************************************************
//                 Constructor
//****************************************************************

CardImage::CardImage(Card card)
{
    int value = card.value();      // Probably not needed except for debugging
    if (value == NO_CARD_HERE) {
        cerr << "ERROR: CardImage constructor called for card with no value."
             << endl;
        exit(1);
    }
    m_card = card;                 // remember the Card
    m_image_strings_p = &(CARD_IMAGES[value]);
}

//****************************************************************
//                     card
//
//      Get the Card for which this is the image
//****************************************************************

Card CardImage::card()
{
    return m_card;
}

//****************************************************************
//                     print
//
//      Print image of card directly to cout
//****************************************************************

void CardImage::print()
{
    cout << endl;                 // Start a new line
    for (unsigned int i = 0; i < CARD_HEIGHT; i++) {
        cout << raster_line(i) << endl;
    }
}

//****************************************************************
//                 draw_image_to_canvas
//****************************************************************

void CardImage::draw_image_to_canvas(GraphicsCanvas *gc_p,
                                     unsigned int row, unsigned int col)
{
    for (unsigned int i = 0; i < CARD_HEIGHT; i++) {
        gc_p->render_string(row + i, col,  raster_line(i));
    }
}

//****************************************************************
//                   graphic_print
//
//      Print the image of the card using a GraphicsCanvas
//      to prepare the image.
//
//      Includes a border with a label
//****************************************************************

void CardImage::graphic_print(std::string label)
{
    // Leave four extra rows and columns for the border
    // and blank space

    GraphicsCanvas gc(CARD_HEIGHT + 4, CARD_WIDTH + 4);
    gc.border('#');            // Make a border
    
    // Put the label over the border, centered
    gc.render_string(0, ((gc.width() - label.length()) / 2) - 1,
                     string(" ") + label + string(" "));

    draw_image_to_canvas(&gc, 2, 2);  // offset to avoid border

    gc.print_to_cout();
}

//****************************************************************
//                   raster_line
//
// This function returns a string containing the requested
// line from the card image. Linenum = 0 is the top of the card image.
// The largest linenum allowed is CARD_HEIGHT - 1.
//****************************************************************

const std::string CardImage::raster_line(unsigned int linenum)
{
    if (linenum >= CARD_HEIGHT) {
            cerr << "CardImage::raster_line(" << linenum << ")"
                 << " called but CARD_HEIGHT is " << CARD_HEIGHT
                 << endl;
        exit(1);
    }
    return (*m_image_strings_p)[linenum];
}

//****************************************************************
//                     Destructor
//****************************************************************

CardImage::~CardImage()
{
    // No destructor code needed
}
