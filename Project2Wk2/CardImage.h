#ifndef CARD_IMAGE_H
#define CARD_IMAGE_H

//****************************************************************
//
//                         CardImage.h
//
//     Represents a single playing card image
//
//     Note that all_card_images.h defines the two constants:
//     CARD_HEIGHT, CARD_WIDTH: the number of rows and cols in 
//                             each card image.
//
//     Author: Noah Mendelsohn
//
//     Tufts University, Fall 2021
//     CS 11: Project 2
//
//****************************************************************

#include <string>
#include "Card.h"
#include "GraphicsCanvas.h"
#include "all_card_images.h"


class CardImage {
public:
    CardImage(Card card);
    ~CardImage();

    //
    //  Return the Card for which this is an image
    //
    Card card();

    //
    //  Print the card image to directly to cout, starting on a new line
    //
    void print();

    //
    //  Print the image of the card to cout using a GraphicsCanvas
    //  to prepare the image. Includes a border and label.
    //
    void graphic_print(std::string label);

    //
    //  Card images are in raster lines for printing.
    //  Return pointer to array of the requested lines
    //
    void draw_image_to_canvas(GraphicsCanvas *gc_p,
                              unsigned int row, unsigned int col);

    //
    // Return a string with requested line of image of card
    // Useful building block for code that does its own graphics
    //
    const std::string raster_line(unsigned int linenum);


private:
    //
    //  Image strings is an array of pointers.
    //  Each pointer is to a string representing one row of the CardImage
    //
    Card m_card;              // The Card for which this is an image
        const std::string (*m_image_strings_p)[CARD_HEIGHT];
                              // Ptr to first image string

    friend class CardTester;  // A friend class for testing

    //
    // Making copy constructor and assignment operator private
    // to prevent their inadvertent use from compiling.
    //
    CardImage(CardImage &other);
    CardImage &operator=(CardImage &rhs);
};

#endif
