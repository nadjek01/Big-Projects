/*
 *  RPNCalc.cpp- "the Implementation"
 *  Nana Adjekum
 *  Oct 26
 *
 *  CS 15 Proj 2 RPNCalc
 *
 *  Defines data members (public and private) in RPNCalc
 *     -These definitions allows for the client to manipulate
 *      things while they use the RPN Calculator
 *     -For example if the user wants to execute a binary operation
 *      (+,-,/,*) this is the file for doing so
 *
 */

#include "RPNCalc.h"
#include "parser.cpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
using namespace std;

/*
 * 
 * Name: RPNCalc()
 * Purpose: the Constructor for RPNCalc
 *          -nothing in there because there are no member
 *           elements to initialise
 * Parameters: None
 * Returns: Nothing
 *
 */
RPNCalc::RPNCalc()
{
    //
}

/*
 * 
 * Name: RPNCalc()
 * Purpose: the destructor for RPNCalc
 *          -nothing in there because there are nothing
 *           elements to delete
 * Parameters: None
 * Returns: Nothing
 *
 */
RPNCalc::~RPNCalc()
{
    //
}

/*
 * 
 * Name: run()
 * Purpose: starts up the cmdloop for RPNCalc
 *          -reads in stuff from cin and then
 *           executes certain things within
 *           the RPNCalc class
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::run()
{
    std::string a_cmd;
    bool input = true;
    while (input == true and a_cmd != "quit") {
        if (cin >> a_cmd) {
            if (a_cmd == "{") {
                store_rstring(cin);
            } else {
                cmdloop(a_cmd);
                input = true;
            }
        } else {
            quit();
            input = false;
        }
            
    }
    
}

/*
 * 
 * Name: cmdloop(string input)
 * Purpose: the actual cmdloop for RPNCalc
 *          -passed stuff from cin and then
 *           executes certain things within
 *           the RPNCalc class
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::cmdloop(string input)
{
    int i_temp;
    if (input == "quit") {
        
        quit();
        return;
    }

    if (input == "print") {
        
        print();

    } else if (input == "clear") {
       
        clear();

    } else if (input == "#f") {
        
        push_fbool();

    } else if (input == "#t") {
        
        push_tbool();

    } else if (input == "not") {
        
        string error_message;

        try {
            rpn_not();
        }
        catch (const std::runtime_error &e) {
            error_message = e.what();
            std::cerr << "Error: " << error_message << endl;
        }

    } else if (input == "swap") {
        
        swap();

    } else if (input == "dup") {
        
        dup();

    } else if (input == "drop") {
        
        drop();

    } else if (got_int(input, &i_temp)) {
        
        push_num(i_temp);

    } else if (input == "/" or input == "-" or input == "+" 
               or input == "mod" or input == "*") {
        
        binaryops(input);

    } else if (input == "<" or input == "<=" or input == "==" or 
               input == ">" or input == ">=") {
       
        comparingops(input);

    } else if (input == "exec") {
       

        string error_message;
        try {
            execute();
        }
        catch (const std::runtime_error &e) {
            error_message = e.what();
            std::cerr << "Error: " << error_message << endl;
        }

    } else if (input == "file") {

        string error_message;
        try {
            file_help();
        }
        catch (const std::runtime_error &e) {
            error_message = e.what();
            std::cerr << "Error: " << error_message << endl;
        }

    } else if (input == "if") {
        
        string error_message;
        
        try {
            ifif();
        } catch (const std::runtime_error &e) {
            error_message = e.what();
            std::cerr << "Error: " << error_message << endl;
        }

    } else {
        cerr << input << ": unimplemented" << endl;
    }
    
}

/*
 * 
 * Name: push_num(int num)
 * Purpose: pushes a Datum with int value to the top of the DatumStack        
 * Parameters: an int num (the value of the Datum int)
 * Returns: Nothing
 *
 */
void RPNCalc::push_num(int num)
{
    CalcStack.push(Datum(num));
}

/*
 * 
 * Name: push_tbool()
 * Purpose: pushes a Datum bool with a true value to the top of the DatumStack
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::push_tbool()
{
    CalcStack.push(Datum(true));
}

/*
 * 
 * Name: push_fbool()
 * Purpose: pushes a Datum bool with a false to the top of the DatumStack
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::push_fbool()
{
    CalcStack.push(Datum(false));
}

/*
 * 
 * Name: push_fbool()
 * Purpose: reads the top of the stack, makes sure its a bool,
 *          drops the top of the DatumStack, and adds bool with 
 *          the opposite value
 *          -true gets false and false get true
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::rpn_not()
{
    string error_message;
    try {
            if (CalcStack.top().toString() == "#t") {
            drop();
            push_fbool();
        } else if (CalcStack.top().toString() == "#f") {
            drop();
            push_tbool();
        }
    } catch (const std::runtime_error &e) {
            error_message = e.what();
            std::cerr << "Error: " << error_message << endl;
    }
}

/*
 * 
 * Name: print()
 * Purpose: prints the top of the Datum Stack
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::print()
{
    string error_message;

    try {
        std::cout << CalcStack.top().toString() << std::endl;
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }
    
}

/*
 * 
 * Name: clear()
 * Purpose: clears the stack
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::clear()
{   
    string error_message;

    try {
            CalcStack.clear();
    } catch (const std::runtime_error &e) {
            error_message = e.what();
            std::cerr << "Error: " << error_message << endl;
    }
    
}

/*
 * 
 * Name: drop()
 * Purpose: drops the first thing in the DatumStack
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::drop()
{
    string error_message;
    try {
        CalcStack.pop();
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }
}

/*
 * 
 * Name: dup()
 * Purpose: duplicates the first thing in the DatumStack
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::dup()
{
    string error_message;

    try {
        Datum temp = CalcStack.top();
        CalcStack.push(temp);
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }
}

/*
 * 
 * Name: swap()
 * Purpose: swaps the first thing in the DatumStack with the "deeper"
 *          thing in the DatumStack
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::swap()
{
    string error_message;
    
    try {
        Datum a_temp = CalcStack.top();
        drop();
        Datum b_temp = CalcStack.top();
        drop();

        CalcStack.push(a_temp);
        CalcStack.push(b_temp);
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }
}

/*
 * 
 * Name: quit()
 * Purpose: quits the program
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::quit()
{
    std::cerr << "Thank you for using CalcYouLater." << endl;
    return;
}

/*
 * 
 * Name: add_operator()
 * Purpose: add the first thing in the DatumStack with the "deeper"
 *          thing in the DatumStack
 *          pushes the value of the operation onto the top of the stack
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::add_operator()
{

    string error_message;
    
    try {
        Datum a_temp = CalcStack.top();
        drop();
        Datum b_temp = CalcStack.top();
        drop();
        Datum added(b_temp.getInt() + a_temp.getInt());
        CalcStack.push(added);
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }

}

/*
 * 
 * Name: sub_operator()
 * Purpose: subtracts the first thing in the DatumStack with the "deeper"
 *          thing in the DatumStack
 *          pushes the value of the operation onto the top of the stack
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::sub_operator()
{
    string error_message;
    
    try {
        Datum a_temp = CalcStack.top();
        drop();
        Datum b_temp = CalcStack.top();
        drop();
        Datum subbed((b_temp.getInt()) - (a_temp.getInt()));
        CalcStack.push(subbed);
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }
}

/*
 * 
 * Name: div_operator()
 * Purpose: divides the first thing in the DatumStack with the "deeper"
 *          thing in the DatumStack
 *          pushes the value of the operation onto the top of the stack
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::div_operator()
{
    string error_message;

    try {
        Datum a_temp = CalcStack.top();
        drop();
        Datum b_temp = CalcStack.top();
        drop();
        if (a_temp.getInt() == 0) {
            throw std::runtime_error("division by 0.");
        }
        Datum divd((b_temp.getInt()) / (a_temp.getInt()));
        CalcStack.push(divd);
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }
}

/*
 * 
 * Name: mult_operator()
 * Purpose: multiplies the first thing in the DatumStack with the "deeper"
 *          thing in the DatumStack
 *          pushes the value of the operation onto the top of the stack
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::mult_operator()
{
    string error_message;
    
    try {
        Datum a_temp = CalcStack.top();
        drop();
        Datum b_temp = CalcStack.top();
        drop();
        Datum multd((b_temp.getInt()) * (a_temp.getInt()));
        CalcStack.push(multd);
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }
}

/*
 * 
 * Name: mod_operator()
 * Purpose: mods the first thing in the DatumStack with the "deeper"
 *          thing in the DatumStack
 *          pushes the value of the operation onto the top of the stack
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::mod_operator()
{
    string error_message;
    
    try {
        Datum a_temp = CalcStack.top();
        drop();
        Datum b_temp = CalcStack.top();
        drop();
        if (a_temp.getInt() == 0) {
            throw std::runtime_error("division by 0.");
        }
        Datum modded((b_temp.getInt()) % (a_temp.getInt()));
        CalcStack.push(modded);
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }
}

/*
 * 
 * Name: lthan_operator()
 * Purpose: sees if the first thing in the DatumStack if less than the "deeper"
 *          thing in the DatumStack 
 *          pushes the true value onto the top of the stack if it is
 *          or a false value if its not
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::lthan_operator()
{
    
    string error_message;
    
    try {
        Datum a_temp = CalcStack.top();
        drop();
        Datum b_temp = CalcStack.top();
        drop();
        if (b_temp.getInt() < a_temp.getInt()) {
            push_tbool();
        } else {
            push_fbool();
        }
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }
}

/*
 * 
 * Name: gthan_operator()
 * Purpose: sees if the first thing in the DatumStack if greater
 *          than the "deeper" thing in the DatumStack 
 *          pushes the true value onto the top of the stack if it is
 *          or a false value if its not
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::gthan_operator()
{
    string error_message;
    
    try {
        Datum a_temp(CalcStack.top());
        drop();
        Datum b_temp(CalcStack.top());
        drop();
        if (b_temp.getInt() > a_temp.getInt()) {
            push_tbool();
        } else {
            push_fbool();
        }
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }
}

/*
 * 
 * Name: lEthan_operator()
 * Purpose: sees if the first thing in the DatumStack if less than or equal
 *          to the "deeper" thing in the DatumStack 
 *          pushes the true value onto the top of the stack if it is
 *          or a false value if its not
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::lEthan_operator()
{
    string error_message;
    
    try {
        Datum a_temp(CalcStack.top());
        drop();
        Datum b_temp(CalcStack.top());
        drop();
        if (b_temp.getInt() <= a_temp.getInt()) {
            push_tbool();
        } else {
            push_fbool();
        }
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }
}

/*
 * 
 * Name: gEthan_operator()
 * Purpose: sees if the first thing in the DatumStack if greater
 *          than or equal to the "deeper" thing in the DatumStack 
 *          pushes the true value onto the top of the stack if it is
 *          or a false value if its not
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::gEthan_operator()
{
    
    string error_message;
    
    try {
        Datum a_temp(CalcStack.top());
        drop();
        Datum b_temp(CalcStack.top());
        drop();
        if (b_temp.getInt() >= a_temp.getInt()) {
            push_tbool();
        } else {
            push_fbool();
        }
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }
}

/*
 * 
 * Name: store_rstring()
 * Purpose: stores an rstring to be executed at a later point
 *          -form: { 1 2 + }
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::store_rstring(istream &input)
{
    std::string r_string(parseRString(input));
    Datum dr_string(r_string);
    CalcStack.push(dr_string);
}

/*
 * 
 * Name: got_int())
 * Purpose: checks if something (a char) in a string is equal to a int
 *          if it is, returns a bool (true) and the value of the convert
 *          to int char
 *          if not, it returns a bool (false)
 * Parameters: None
 * Returns: Nothing
 *
 */
bool RPNCalc::got_int(string s, int *resultp)
{
    char extra;
    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;

}

/*
 * 
 * Name: equals_operator()
 * Purpose: sees if the first thing in the DatumStack if equals
 *          to the "deeper" thing in the DatumStack 
 *          pushes the true value onto the top of the stack if it is
 *          or a false value if its not
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::equals_operator()
{
    string error_message;
    
    try {
        Datum a_temp(CalcStack.top());
        drop();
        Datum b_temp(CalcStack.top());
        drop();
        if (b_temp.getInt() == a_temp.getInt()) {
            push_tbool();
        } else {
            push_fbool();
        }
    }
    catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    }
}

/*
 * 
 * Name: equals_operator()
 * Purpose: starts the exec function by checking the top of the stack 
 *          is an r_string, pops the top of the stack if it is,
 *          and passing the r_string to the actual exec function
 * Parameters: None
 * Returns: Nothing
 *
 */
void RPNCalc::execute()
{
    Datum temp = CalcStack.top();
    drop();
    string error_message = "";

    if (temp.isRString() == false) {
        throw std::runtime_error("cannot execute non rstring");
    } else {
        std::string e_string = temp.getRString();
        c_exec(e_string);
    }

}

/*
 * 
 * Name: c_exec(string e_string)
 * Purpose: the actual exec function, takes in a string and then calls
 *          the specified function
 *          this continues as long as it is getting input from the  
 *          string (in a while loop)
 *          -ex: when the string is equal to file it calls the file function
 * Parameters: a string (carries the commands)
 * Returns: Nothing
 *
 */
void RPNCalc::c_exec(string e_string)
{
    e_string.erase(0,1);
    e_string.pop_back();
    istringstream exec(e_string);

    string temp;

    while (exec >> temp) {
        if (temp == "{") {
            store_rstring(exec);

        } else {
            cmdloop(temp);
        }
        
    }
      
}

/*
 * 
 * Name: binaryops(string op)
 * Purpose: a helper function which calls the binary functions
 * Parameters: a string (carries the operator)
 * Returns: Nothing
 *
 */
void RPNCalc::binaryops(string op)
{
    if (op == "/") {
        std::string error_message = "";
            try {
                div_operator() ;
            } 
            catch (const std::runtime_error &e) {
                error_message = e.what();
                std::cerr << "Error: " << error_message << endl;
            }

    } else if (op == "+") {
        add_operator();
    } else if (op == "-") {
        sub_operator();
    } else if (op == "mod") {
            std::string error_message = "";
            try {
                mod_operator() ;
            }
            catch (const std::runtime_error &e) {
                error_message = e.what();
                std::cerr << "Error: " << error_message << endl;
            }

    } else if (op == "*") {
        mult_operator();
    }
}

/*
 * 
 * Name: comparingops(string op)
 * Purpose: a helper function which calls the comparatory functions
 * Parameters: a string (carries the operator)
 * Returns: Nothing
 *
 */
void RPNCalc::comparingops(string op)
{
    if (op == "==") {
        equals_operator();
    } else if (op == "<") {
        lthan_operator();
    } else if (op == ">") {
        gthan_operator();
    } else if (op == "<=") {
        lEthan_operator();
    } else if (op == ">=") {
        gEthan_operator();
    }
}

/*
 * 
 * Name: file(string filename)
 * Purpose: opens files and has a cmdloop (of sorts)
 *          the cmdloop takes commands from the files
 * Parameters: a string (carries the file name)
 * Returns: Nothing
 *
 */
void RPNCalc::file(string filename)
{
    ifstream operateme;
    string o_file;
    o_file = filename;
    string error_message;
    bool input = open_or_kaput(operateme, o_file);

    
    while (input == true) {
        string f_cmd;
        operateme >> f_cmd;
        if (f_cmd == "{") {
            store_rstring(operateme);
            
        } else if (f_cmd == "") {
            //cerr << "empty space" << endl;
            //the needs to be here because the current state
            //of the code reads in and passes an empty string
        } else {
            cmdloop(f_cmd);
            input = true;
        } 
        
        if (operateme.eof()) {
            input = false;
        }

    }
    operateme.close();

}

/*
 * 
 * Name: template<typename streamtype>
         void RPNCalc::open_or_kaput(streamtype &stream, string file_name)
 * Purpose: the function that actually opens the files
 * Parameters: a streamtype and a string
 * Returns: Nothing
 *
 */
template<typename streamtype>
bool RPNCalc::open_or_kaput(streamtype &stream, string file_name)
{
    stream.open(file_name);
    if (stream) {
        return true;
    } else {
        cerr << "Unable to read " << file_name << endl;
        return false;
    }
}

/*
 * 
 * Name: ifif()
 * Purpose: the if function, is supposed to take three things from the
 *          stack the first a test condition (is a bool or returns a bool) and
 *          the second a true case (execute if the test condition is true) and
 *          the third a false case (execute if the test condition is false)
 * Parameters:
 * Returns: Nothing
 *
 */
void RPNCalc::ifif() {
    string error_message;

    if (CalcStack.size() <= 2) {
        throw std::runtime_error("empty_stack");
    }

    try {
        Datum fals = CalcStack.top();
        drop();

        Datum tru = CalcStack.top();
        drop();

        Datum tof = CalcStack.top();
        drop();
            
        if (not fals.isRString() or not tru.isRString()) {
            throw std::runtime_error("expected rstring in if branch");
        }

        if (not tof.isBool()) {
            throw std::runtime_error("expected boolean in if test"); 
        }
        
        if (tof.getBool() == true) {
            string t_exec = tru.getRString();
            c_exec(t_exec);

        } else if (tof.getBool() == false) {
            string f_exec = fals.getRString();
            c_exec(f_exec);
     
        } 

    } catch (const std::runtime_error &e) {
        error_message = e.what();
        std::cerr << "Error: " << error_message << endl;
    } 
}

/*
 * 
 * Name: file_help()
 * Purpose: the function that actually opens the files
 * Parameters: a streamtype and a string
 * Returns: Nothing
 *
 */
void RPNCalc::file_help()
{

    Datum d_temp = CalcStack.top();
    drop();

    if (d_temp.isRString() == false) {
        throw std::runtime_error("file operand not rstring");    
    } else {
        std::string f_temp = d_temp.getRString();
        f_temp.pop_back();
        f_temp.pop_back();
        f_temp.erase(0, 2);
        file(f_temp);
    }

}