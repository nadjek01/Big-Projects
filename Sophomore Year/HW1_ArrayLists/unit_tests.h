/*
 * unit_tests.h
 *
 * CS 15 homework 1
 * by Tyler Calabrese, January 2021
 *
 * edited by: Milod Kazerounian, January 2022
 * further edited by: Nana Adjekum, September 2022
 *
 * Uses Matt Russell's unit_test framework to test the CharArrayList class.
 *
 * Instructions for using testing framework can be found at in CS 15's lab
 * 1 -- both in the spec and in the provided ArrayList_tests.h and Makefile.
 * More in-depth information for those who are curious as to how it works can
 * be found at http://www.github.com/mattrussell2/unit_test.
 */

#include "CharArrayList.h"
#include <cassert>
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std;


/********************************************************************\
*                       CHAR ARRAY LIST TESTS                        *
\********************************************************************/


/*
 * default constructor works
 * Name: default_works
 * Purpose: Tests that the default constructor functions
 *          and an instance of an empty CharArrayList is made
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void default_works()
{
    CharArrayList testing;
}


/*
 * default constructor size correct
 * Name: default_works_size
 * Purpose: Tests that the default constructor functions
 *          and an instance of an empty CharArrayList is made
 *          also affirms that the size is zero
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void default_works_size()
{
    CharArrayList testing;
    assert(testing.size() == 0);
}


/*
 * second constructor works
 * Name: secondary_works
 * Purpose: Tests that the secondary constructor functions
 *          and an instance of a CharArrayList with a char is made
 *          with the correct current size
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void secondary_works() 
{
    char c_test = 'c';
    CharArrayList testing(c_test);

}


/*
 * size works 
 * Name: size_works
 * Purpose: Tests that the size function works and returns the 
 *          correct number of chars currently in the list
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void size_works()
{
    //running through the possible combinations
    //of when the size function could be called
    CharArrayList a_testing;
    assert(a_testing.size() == 0);

    CharArrayList b_testing('b');
    assert(b_testing.size() == 1);

    char arr[3] = {'h', 'i', 'm'};
    CharArrayList c_testing(arr, 3);
    assert(c_testing.size() == 3);

}


/*
 * empty works 
 * Name: isEmpty_works
 * Purpose: Tests that the isEmpty function works and returns the 
 *          right bool value
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void isEmpty_works() 
{
    //checking that the AL is empty when 
    //it should be (when the AL is initialised) 
    CharArrayList a_testing;
    assert(a_testing.isEmpty() == true);

    char s_char = 'r';
    CharArrayList b_testing(s_char);
    assert(b_testing.isEmpty() == false);
}


/*
 * clear works 
 * Name: clear_works
 * Purpose: Tests that the clear function works and checks by using isEmpty 
 *          function
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void clear_works() 
{
    //makes an AL instance w/ 3 elements
    char arr[3] = {'h', 'e', 'r'};
    CharArrayList testing(arr, 4);

    //calls clear and uses the isEmpty function to
    //check that the job was actually finished
    //ie current AL size is now zero
    testing.clear();
    assert(testing.isEmpty());
}


/*
 * first works 
 * Name: first_works
 * Purpose: Tests that the first function works
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void first_works()
{
    char arr [4] = {'t', 'h', 'e', 'y'};

    CharArrayList b_testing(arr, 4);
    
    //asserting that the first element
    //is acc what was hardcoded
    assert(b_testing.first() == 't');

}


/*
 * nun in here works 
 * Name: zero_first_works
 * Purpose: Tests the situation where the first function wouldn't 
 *          ie when there is nothing in the list
 *          Catches a runtime error when it fails (like it should)
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void zero_first_works() 
{
    bool runtime_error_thrown = false;

    CharArrayList b_testing;
    std::string error_message = "";

    try {
        assert(b_testing.first() == 'y');
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    //asserting that the error was thrown
    //and caught
    //this makes sure edge case is tested
    assert(runtime_error_thrown);
    assert(error_message == "cannot get first of empty ArrayList");
   
}


/*
 * last works 
 * Name: last_works
 * Purpose: Tests that the last function 
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void last_works()
{
    //testing last with numerous 
    //sizes making sure its not
    //stopping for certain ones
    char arr [4] = {'x', 'i', 'e', 'r'};

    CharArrayList b_testing(arr, 4);

    assert(b_testing.last() == 'r');

    char a_arr [5] = {'a','x', 'i', 'e', 'o'};

    CharArrayList a_testing(a_arr, 5);

    assert(a_testing.last() == 'o');
    
}

/*
 * nun in here works 
 * Name: empty_last_works
 * Purpose: Tests the situation where the last function would
 *          not work; ie when the list is empty
 *          Catches runtime error when failed
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void empty_last_works()
{
    bool runtime_error_thrown = false;

    CharArrayList b_testing;
    std::string error_message = "";

    try {
       char c = b_testing.last();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    //asserting that 
    assert(runtime_error_thrown);
    assert(error_message == "cannot get last of empty ArrayList");
}


/*
 * single works 
 * Name: single_pushAtFront_works
 * Purpose: Tests that push at front function is working for when
 *          there is nothing in the ArrayList
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void single_pushAtFront_works() 
{
    CharArrayList testing;
    char test = 'o';
    testing.pushAtFront(test);

    assert(testing.first() == 'o');
    

}

/*
 * multiple works 
 * Name: mult_pushAtFront_works
 * Purpose: Tests that push at front function is working for when
 *          there is one element in the ArrayList
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void mult_pushAtFront_works() 
{
    CharArrayList testing('o');
    char test = 'y';
    testing.pushAtFront(test);

    assert(testing.first() == 'y');
    assert(testing.toString() == "[CharArrayList of size 2 <<yo>>]");
}


/*
 * insert in alpha order 
 * Name: insertInOrder_works
 * Purpose: Tests that the insertInOrder function
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void insertInOrder_works() 
{
    char arr [3] = {'a', 'b', 'd'};
    CharArrayList testing(arr, 3);
    
    testing.insertInOrder('c');
    for (int i = 0; i < 4; i++) {
        cerr << testing.elementAt(i);
    }
    cerr << "entering element at with char c" << endl;
    assert(testing.elementAt(2) == 'c'); 
    cerr << testing.toString() << endl;

}

/*
 * remove from front 
 * Name: popFromFront_testing
 * Purpose: Tests the popFromFront function
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void popFromFront_testing()
{
    char arr [4] = {'a', 'b', 'c', 'd'};
    CharArrayList testing(arr, 4);

    testing.popFromFront();
    assert(testing.first() == 'b');

    
}

/*
 * remove from back 
 * Name: popFromBack
 * Purpose: Tests that the popFromBack function works
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void popFromBack_works() 
{
    char arr [4] = {'a', 'b', 'c', 'd'};
    CharArrayList testing(arr, 4);

    testing.popFromBack();
    assert(testing.last() == 'c');

}

/*
 * nun to remove 
 * Name: empty_removeAt_works
 * Purpose: Tests the removeAt function throws an exception when
 *          the list is empty
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void empty_removeAt_works() 
{
    bool range_error_thrown = false;
    CharArrayList testing;
    std::string error_message = "";

    try {
        testing.removeAt(0);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "cannot remove from empty list");
}

/*
 * acc remove
 * Name: removeAt_works
 * Purpose: Tests the that removeAt function works
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void removeAt_works() 
{
    char arr [4] = {'a', 'b', 'c', 'd'};
    CharArrayList testing(arr, 4);
    std::string error_message = "";


    cerr << testing.toString() << endl;
    testing.removeAt(2);
        
    cerr << testing.toString() << endl;
    assert(testing.elementAt(2) == 'd');
    
}


/*
 * zusammen
 * Name: concatenete_works
 * Purpose: Tests that the concatenate function works
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void concatenate_works() 
{
    char a_arr [2] = {'a', 'b'};
    CharArrayList a_testing(a_arr, 2);

    char b_arr [2] = {'c', 'd'};
    CharArrayList b_testing(b_arr, 2);

    char c_arr [4] = {'a', 'b', 'c', 'd'};
    CharArrayList c_testing(c_arr, 4);

    a_testing.concatenate(&b_testing);

    for (int i = 0; i < a_testing.size(); i++) {
        cerr << a_testing.elementAt(i);
        assert(a_testing.elementAt(i) == c_testing.elementAt(i));
    }

}

/*
 * gemini but on the same line
 * Name: same_concatenate_works
 * Purpose: Tests the concatenate function works when the 
 *          ArrayList passed in is the same
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void same_concatenate_works() 
{
    char a_arr [2] = {'a', 'b'};
    CharArrayList a_testing(a_arr, 2);


    char c_arr [4] = {'a', 'b', 'a', 'b'};
    CharArrayList c_testing(c_arr, 4);

    a_testing.concatenate(&a_testing);

    cerr << a_testing.toString();
    assert(a_testing.toString() == c_testing.toString());


}

/*
 * bbl
 * Name: shrink_works
 * Purpose: Tests that the shrink function works
 * Parameters: N/A
 * Returns: Nothing
 * Notes: I assume shrink is working bc its supposed to 
 *        make the size and capacity eqivalent
 *
 */
void shrink_works() 
{
    char arr[4] = {'d', 'c', 'd', 'a'};
    CharArrayList testing;
    for (int i = 0; i < 4; i++) {
        testing.pushAtFront(arr[i]);
    }
    testing.shrink();
    assert(testing.size() == 4);
    
}


/*
 * move to the back
 * Name: pushAtBack_works 
 * Purpose: Tests the pushAtBack function works 
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void pushAtBack_works() 
{
    CharArrayList testing('y');
    testing.pushAtBack('t');

    assert(testing.last() == 't');

}

/*
 * are u here
 * Name: pos_elementAt_working
 * Purpose: Tests that the elementAt function is working
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void pos_elementAt_working() 
{

    char arr[3] = {'h', 'i', 'm'};
    CharArrayList testing(arr, 3);

    assert(testing.elementAt(1) == 'i');

}


/*
 * not in range
 * Name: neg_elementAt_working
 * Purpose: Tests that the element_At function correctly
 *          throws an exception when the index passed in
 *          is out of range
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void neg_elementAt_working() 
{
    bool range_error_thrown = false;
    char arr[3] = {'s', 'h', 'e'};
    CharArrayList testing(arr, 3);
    std::string error_message = "";

    try {
        assert(testing.elementAt(7));
    }
     catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "index (7) not in range [0..3]");
}


/*
 * not in range (but zero)
 * Name: zerp_elementAt_working
 * Purpose: Tests that the element_At function correctly
 *          throws an exception when the index passed in
 *          is out of range
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void zero_elementAt_working() 
{
    bool range_error_thrown = false;
    CharArrayList testing;
    std::string error_message = "";

    try {
        assert(testing.elementAt(7));
    }
     catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "index (7) not in range [0..0]");
}

// /* To give an example of thorough testing, we are providing
//  * the unit tests below which test the insertAt function. Notice: we have
//  * tried to consider all of the different cases insertAt may be
//  * called in, and we test insertAt in conjunction with other functions!
//  *
//  * You should emulate this approach for all functions you define.
//  */



/*
 * insert when empty 
 * Name: insertAt_empty_correct
 * Purpose: Tests correct insertion into an empty AL.
 *          Afterwards, size should be 1 and element at index 0
 *          should be the element we inserted.
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void insertAt_empty_correct() { 
        
    CharArrayList test_list;
    test_list.insertAt('a', 0);
    cerr << test_list.toString() << endl;
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');
                               
}


/*
 * insert when empty (but not really)
 * Name: insertAt_empty_incorrect
 * Purpose: Tests incorrect insertion into an empty AL.
 *          Attempts to call insertAt for index larger than 0.
 *          This should result in an std::range_error being raised.
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void insertAt_empty_incorrect() {

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
        // insertAt for out-of-range index
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        // if insertAt is correctly implemented, a range_error will be thrown,
        // and we will end up here
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");

}


/*
 * insert at front one-list
 * Name: insertAt_empty_incorrect
 * Purpose: Tests correct insertAt for front of 1-element list.
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void insertAt_front_singleton_list() {

    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'a');

}


/*
 * insert at back one-list
 * Name: insertAt_back_singleton_list
 * Purpose: Tests correct insertAt for back of 1-element list.
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void insertAt_back_singleton_list() {
    
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    
}


/*
 * insert at (but with many elements)
 * Name: insertAt_many_elements
 * Purpose: Tests calling insertAt for a large number of elements.
            Not only does this test insertAt, it also checks that
            array expansion works correctly.
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void insertAt_many_elements() {
    
    CharArrayList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }

    assert(test_list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i) == 'a');
    }
    
}


/*
 * insert at (but with in the front back and middle)
 * Name: insertAt_front_back_middle()
 * Purpose: Tests insertion into front, back, and middle of a larger list.
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void insertAt_front_back_middle() {
    
        char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
        CharArrayList test_list(test_arr, 8);
        

        // insertAt middle
        test_list.insertAt('z', 3);

        assert(test_list.size() == 9);
        assert(test_list.elementAt(3) == 'z');
        cerr << test_list.toString();

        assert(test_list.toString() == 
        "[CharArrayList of size 9 <<abczdefgh>>]");

        // insertAt front
        test_list.insertAt('y', 0);

        assert(test_list.size() == 10);
        assert(test_list.elementAt(0) == 'y');
        assert(test_list.toString() == 
        "[CharArrayList of size 10 <<yabczdefgh>>]");

        // insertAt back
        test_list.insertAt('x', 10);

        assert(test_list.size() == 11);
        assert(test_list.elementAt(10) == 'x');
        assert(test_list.toString() == 
        "[CharArrayList of size 11 <<yabczdefghx>>]");
        
}


/*
 * insert at (but its empty)
 * Name: insertAt_nonempty_incorrect
 * Purpose: Tests out-of-range insertion for a non-empty list.
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void insertAt_nonempty_incorrect() 
{
    
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8]");
    
}


/*
 * to string (but backwards)
 * Name: insertAt_nonempty_incorrect
 * Purpose: //testing if toReverseString() works
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void toReverseString_works () 
{
    char arr[4] = {'a', 'b', 'c', 'd'};
    CharArrayList f_testing(arr, 4);
    string f_test = f_testing.toReverseString();
    cerr << f_test << endl;

    char b_arr[4] = {'d', 'c', 'b', 'a'};
    CharArrayList b_testing(b_arr, 4);
    string b_test = b_testing.toString();
    cerr << b_test << endl;


    assert(f_testing.toReverseString() == b_testing.toString());
}   

/*
 * insertInOrder but they r equal
 * Name: equal_insertInOrder_works(char c)
 * Purpose: testing if the insert in order works
 *          when the char to be added is equal to
 *          one of the chars in the list
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void equal_insertInOrder_works() 
{
    char arr [3] = {'a', 'b', 'd'};
    CharArrayList testing(arr, 3);
    
    testing.insertInOrder('b');
    for (int i = 0; i < 4; i++) {
        cerr << testing.elementAt(i);
    }
    cerr << "entering element at with char b" << endl;
    assert(testing.elementAt(2) == 'b'); 
    cerr << testing.toString() << endl;

}

/*
 * overload operator works
 * Name: overload_works
 * Purpose: Tests that the overload operator constructor functions
 *          so that two lists are equivalent
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void overload_works() 
{
    char a_arr[2] = {'a', 'b'};
    CharArrayList a_testing(a_arr, 2);

    char b_arr[2] = {'c', 'd'};
    CharArrayList b_testing(b_arr, 2);

    a_testing.operator=(b_testing);
    assert(a_testing.toString() == b_testing.toString());

    cerr << a_testing.toString() << endl;
    cerr << b_testing.toString() << endl;
    cerr << &a_testing << endl;
    cerr << &b_testing << endl;


}

/*
 * replace at works (but acc)
 * Name: replaceAt_works
 * Purpose: Tests that the replace at function is replacing
 *          at the correct index
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void replaceAt_works()
{
    char arr[4] = {'a', 'b', 'c', 'd'};
    CharArrayList f_testing(arr, 4);

    f_testing.replaceAt('t', 2);
    assert(f_testing.toString() == "[CharArrayList of size 4 <<abtd>>]");
    cerr << f_testing.toString() << endl;
    assert(f_testing.size() == 4);
}

/*
 * replace at works (but when the AL is empty)
 * Name: zero_replaceAt_works
 * Purpose: Tests that the replace at function is replacing
 *          at the correct index
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void zero_replaceAt_works()
{
    CharArrayList f_testing;

        // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";
    try {
       f_testing.replaceAt('c', 2);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (2) not in range [0..0]");
}


/*
 * replace at works (but when the index is invalid)
 * Name: invalid_replaceAt_works
 * Purpose: Tests that the correct exception is thrown and caught
 *          in the case of when the index is larger
 *          than the current size of the AL
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void invalid_replaceAt_works()
{
    char arr[4] = {'a', 'b', 'c', 'd'};
    CharArrayList f_testing(arr, 4);

        // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";
    try {
       f_testing.replaceAt('c', 9);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (9) not in range [0..4]");
}
