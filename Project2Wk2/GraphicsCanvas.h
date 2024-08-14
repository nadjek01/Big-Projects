#ifndef GRAPHICS_CANVAS_H
#define GRAPHICS_CANVAS_H

//****************************************************************
//
//                        GraphicsCanvas.h
//
//     GraphicsCanvas class, which represents the display of a two
//     dimensional area on the user's screen.  This also defines the
//     helper class Canvas_Stream.
//
//     Author: Noah Mendelsohn
//
//     Tufts University, Fall 2021
//     CS 11: Project 2
//
//****************************************************************

#include <string>
#include <sstream> // Stringstreams are like cout, 
                   // but you can get the string out.


class GraphicsStream;

//*******************************************************************
//*******************************************************************
//
//                  GraphicsCanvas Class
//
//*******************************************************************
//*******************************************************************

class GraphicsCanvas {
public:
    //***********************************************
    // Constructor/Destructor
    //***********************************************

    GraphicsCanvas(unsigned int height, unsigned int width);
    ~GraphicsCanvas();

    //***********************************************
    // Dimensions
    //***********************************************

    unsigned int height();
    unsigned int width();

    //***********************************************
    // Functions and gout data member to update 
    // the in-memory canvas buffer
    //***********************************************

    void clear_canvas();
    void render_string(int row, int col, std::string s);
    void horizontal_line(int row, int col, int len, char c);
    void vertical_line(int row, int col, int len, char c);
    void rectangle(int row, int col, int height, int width, char c);
    void border(char c);

    //***********************************************
    // Functions to update the user's screen
    //***********************************************
    void print_to_cout();
    
private:

    // Private member vars

    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_canvas_area;
 

    // points to a rasterized buffer of size m_area = m_width x m_height.
    // canvas is stored row major as a single array of chars.
    // (We do our own 2d subscripting because C++ doesn't like
    // 2D arrays in which both bounds are variables at run time).
    char *m_canvas_array;

    // Private member functions
    unsigned int row_col_to_canvas(unsigned int y, unsigned int x) \
            {return (y * m_width) + x;}

    //
    // Making copy constructor and assignment operator private
    // to prevent their inadvertent use from compiling.
    //
    GraphicsCanvas(GraphicsCanvas &other);
    GraphicsCanvas &operator=(GraphicsCanvas &rhs);

    friend GraphicsStream;
};

//*******************************************************************
//*******************************************************************
//
//                    Canvas_Stream Class
//
//     Helper class that implements <<, but that also 
//     provides for writing to a canvas. The constructor takes
//     the row and column at which writing will begin, as well
//     as the Canvas object. Writing beyond the edge of the canvas
//     or below the bottom row is quietly truncated.
//
//     C++ experts will recognize that this can be done even better by
//     doing something called "overloading the << operator", but
//     that's somewhat beyond what we want to do in CS 11!
//
//******************************************************************
//*******************************************************************

class GraphicsStream : public std::stringstream
{
public:
    GraphicsStream(GraphicsCanvas *gc_p, unsigned int row, unsigned int col);
    // advanced C++ here...move constructor.. don't worry about it.
    GraphicsStream(GraphicsStream &&gs);
    ~GraphicsStream();

    void render();         // write to the console
private:
    GraphicsCanvas *m_gc_p;
    unsigned int    m_row;
    unsigned int    m_col;
};



#endif
