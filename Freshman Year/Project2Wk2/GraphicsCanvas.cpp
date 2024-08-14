//****************************************************************
//
//                        GraphicsCanvas.cpp
//
//     Methods to support the GraphicsCanvas class, which represents
//     the display of a two dimensional area on the user's screen.
//
//     Author: Noah Mendelsohn
//
//     Tufts University, Fall 2021
//     CS 11: Project 2
//
//****************************************************************

#include <iostream>
#include <cstdlib>   // for system call to clear the screen
#include "GraphicsCanvas.h"

using namespace std;

//****************************************************************
//****************************************************************
//
//                  GraphicsCanvas Class
//
//****************************************************************
//****************************************************************

//****************************************************************
//                   Constructor
//
//   * Records the game deck and discard pile pointers, and player's name
//   * Draws cards from the game deck to fill initial hand for the player
//   * Checks for the odd case that the hand wins immediately, in which
//     case we exit the whole came and declare success NEEDSWORK: is
//     that what we want?
//****************************************************************

GraphicsCanvas::GraphicsCanvas(unsigned int height, unsigned int width)
{
    m_width        = width;
    m_height       = height;
    m_canvas_area  = width * height;
    m_canvas_array = new char[m_canvas_area];

    clear_canvas();   // Start whole canvas with blanks
}

//****************************************************************
//                     Destructor
//****************************************************************

GraphicsCanvas::~GraphicsCanvas()
{
    delete [] m_canvas_array;
}

unsigned int GraphicsCanvas::height()
{
    return m_height;
}

unsigned int GraphicsCanvas::width()
{
    return m_width;
}

void GraphicsCanvas::render_string(int row, int col, string s)
{
    // next index we will update in canvas array
    char *next_char_position = m_canvas_array + row_col_to_canvas(row, col);

    // write length of string, but not off end of canvas
    unsigned len=std::min((unsigned int)s.length(), m_width - col);

    // Do to some complicated ways that C++ casts streams to bools
    // this loop will stop when we can't pull any more chars from the stream
    // The max_to_write forces us not to write off end of current canvas row
    for (unsigned int i = 0; i < len; i++) {
        *(next_char_position++) = s[i];   // Update canvas
                                          // and point to next char
    }
}

//****************************************************************
//                   clear_canvas
//
//      Clear the canvas array, but don't display it.
//      Reset origin as well.
//****************************************************************

void GraphicsCanvas::clear_canvas()
{
    for (unsigned int i = 0; i < m_canvas_area ; i++) {
        m_canvas_array[i] = ' ';
    }
}

//****************************************************************
//                   print_to_cout
//
//      Write the contents of the canvas to cout
//****************************************************************

void GraphicsCanvas::print_to_cout()
{
    char *next_row_p = m_canvas_array;   // first char of first row
    for (unsigned int row = 0; row < m_height; row++) {
        string row_data(next_row_p, m_width); // string constructor
                                              // takes a width
        cout << row_data << endl;
        next_row_p += m_width;
    }
}

// Draw lines using character c
void GraphicsCanvas::horizontal_line(int row, int col, int len, char c)
{
    for (int i = 0; i < len; i++) {
        m_canvas_array[row_col_to_canvas(row, col + i)] = c;
    }
}

void GraphicsCanvas::vertical_line(int row, int col, int len, char c)
{
    for (int i = 0; i < len; i++) {
        m_canvas_array[row_col_to_canvas(row + i, col)] = c;
    }
}

void GraphicsCanvas::rectangle(int row, int col, int height, int width, char c)
{
    horizontal_line(row, col, width, c);                      // top line
    horizontal_line(row + height - 1, col, width, c);         // bottom line

    vertical_line(row + 1, col, height - 2, c);               // left side
    vertical_line(row + 1, col + width - 1, height - 2, c);   // right side
}

void GraphicsCanvas::border(char c)
{
    rectangle(0, 0, m_height, m_width, c);
}

//****************************************************************
//****************************************************************
//
//                  GraphicsStream Class
//
//        This is a helper that uses some C++ tricks to
//        let you prepare a string using <<, which can be handy.
//
//        C++ experts will recognize that this can be done
//        even better by doing something called "overloading
//        the << operator", but that's somewhat beyond what
//        we want to do in CS 11!
//
//****************************************************************
//****************************************************************

//****************************************************************
//                   Constructor
//****************************************************************

GraphicsStream::GraphicsStream(GraphicsCanvas *gc_p,
                                 unsigned int row, unsigned int col)
{
    m_gc_p = gc_p;
    m_row  = row;
    m_col  = col;
}

// Move constructor used when returning these from a function
GraphicsStream::GraphicsStream(GraphicsStream &&gs)
{
    (void)gs;
}

//****************************************************************
//                     Destructor
//****************************************************************

GraphicsStream::~GraphicsStream()
{
}

void GraphicsStream::render()
{
    m_gc_p->render_string(m_row, m_col, str());
}
