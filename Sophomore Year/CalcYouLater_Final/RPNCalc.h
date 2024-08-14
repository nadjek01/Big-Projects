/*
 *  RPNCalc.h- "the Interface"
 *  Nana Adjekum
 *  Oct 26
 *
 *  CS 15 Proj 2 RPNCalc
 *
 *  Declares data members (public and private) in RPNCalc
 *  Names the data members to be defined for client use
 *
 */


#ifndef _RPNCALC_H_
#define _RPNCALC_H_

#include "DatumStack.h"
#include "Datum.h"
using namespace std;

class RPNCalc {
    
    public:

    //constructor
    RPNCalc();
    //desctructor
    ~RPNCalc();
    //starts the calculator
    void run();

    private:

    //the stack for the calculator
    DatumStack CalcStack;


    //pushes num to top of stack
    void push_num(int num);
    //pushes true bool to the top of the stack
    void push_tbool();
    //pushes false bool to the top of the stack
    void push_fbool();
    //causes the opposite instance of the bool to be pushed on the stact
    void rpn_not();    //not being weird
    
    
    //prints the curr state
    void print();
    //clears out the calculator
    void clear();
    //drops the first elem of the stack
    void drop();
    //duplicates the first elems
    void dup();
    //swaps the top 2 elements on the stack
    void swap();
    //quits the calculator
    void quit();

    
    //add operator
    void add_operator();
    //subtract operator
    void sub_operator();
    //divide operator
    void div_operator();
    //mod operator
    void mod_operator();
    //TD
    void mult_operator();


    //less-than operator
    void lthan_operator();
    //greater-than operator
    void gthan_operator();
    //less-than or equal to operator
    void lEthan_operator();
    //greater-than or equal to operator
    void gEthan_operator();
    //equals operator
    void equals_operator();


    //conditionals for calling binary ops
    void binaryops(string op);
    //conditionals for calling comparing ops
    void comparingops(string op);

    void cmdloop(string input);
    //stores r_strings
    void store_rstring(istream &input);
    //executes the r_string
    void execute();
    //executes r_string with a filename
    void file(string filename);
    //helper for fle
    void file_help();

    //does the if operation
    void ifif();
    //checks if the stuff inside string is an int
    bool got_int(string s, int *resultp);
    //opens the file
    template<typename streamtype>
    bool open_or_kaput(streamtype &stream, string file_name);
    //the execute helper function
    void c_exec(string e_string);


};

#endif