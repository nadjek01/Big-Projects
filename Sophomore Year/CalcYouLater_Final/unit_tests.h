/*
 *  unit_test.h
 *  Nana Adjekum
 *  19-Oct
 *
 *  CS 15 Proj2 CalcYouLater
 *
 *  Tester for CalcYouLater--more so check that the DatumStack is all good
 *
 */
#include "DatumStack.h"
#include "RPNCalc.h"

#include <cassert>

/*
 * 
 * Name: sec_construct_works()
 * Purpose: checks if the secondary contructor is working correctly
 * Parameters: None
 * Returns: Nothing
 *
 */
void sec_construct_works()
{
    Datum data[3] = {Datum(1), Datum(2), Datum(3)};
    DatumStack test(data, 3);

    assert(test.size() == 3);

}

/*
 * 
 * Name: empty_works()
 * Purpose: checks if the empty function of the DatumStack is working correctly
 * Parameters: None
 * Returns: Nothing
 *
 */
void empty_works()
{
    DatumStack test;
    assert(test.isEmpty() == true);
}

/*
 * 
 * Name: a_nempty_work()
 * Purpose: checks if the empty function of the DatumStack is working correctly
 *          (when theres something in there should return false)
 * Parameters: None
 * Returns: Nothing
 *
 */
void a_nempty_work()
{
    Datum data[3] = {Datum(1), Datum(2), Datum(3)};
    DatumStack test(data, 3);

    assert(test.isEmpty() == false);
}

/*
 * 
 * Name: clear_work()
 * Purpose: checks if the clear function of the DatumStack is working correctly
 *          -DatumStack empties correctly
 * Parameters: None
 * Returns: Nothing
 *
 */
void clear_work()
{
    Datum data[3] = {Datum(1), Datum(2), Datum(3)};
    DatumStack test(data, 3);

    test.clear();
    assert(test.isEmpty() == true);
}


/*
 * 
 * Name: size_work()
 * Purpose: checks if the size function of the DatumStack is working correctly
 *          -size funct of DS class supposed to return size
 * Parameters: None
 * Returns: Nothing
 *
 */
void size_work()
{
    Datum data[3] = {Datum(1), Datum(2), Datum(3)};
    DatumStack test(data, 3);

    assert(test.size() == 3);
}

/*
 * 
 * Name: empty_top_work()
 * Purpose: checks if the top function of the DatumStack is working correctly
 *          -top funct of DS class supposed to return the top of the stack
 *          -catches error if needed
 * Parameters: None
 * Returns: Nothing
 *
 */
void empty_top_work()
{
    bool runtime_error_thrown = false;

    DatumStack b_testing;
    std::string error_message = "";
    Datum test(1);

    try {
        assert(b_testing.top() == test);
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    //asserting that the error was thrown
    //and caught
    //this makes sure edge case is tested
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
   
}

/*
 * 
 * Name: full_top_work()
 * Purpose: checks if the top function of the DatumStack is working correctly
 *          -top funct of DS class supposed to return the top of the stack
 * Parameters: None
 * Returns: Nothing
 *
 */
void full_top_work()
{
    Datum a(1);
    Datum b(2);
    Datum c(3);

    Datum data[3] = {a,b,c};
    DatumStack test(data, 3);

    assert(test.top() == c);

}

/*
 * 
 * Name: full_pop_work()
 * Purpose: checks if the pop function of the DatumStack is working correctly
 *          -pop funct of DS class supposed to return the top of the stack
 *           and remove it from the top of the stack
 * Parameters: None
 * Returns: Nothing
 *
 */
void full_pop_work()
{
    Datum a(1);
    Datum b(2);
    Datum c(3);
    
    Datum data[3] = {a,b,c};
    DatumStack test(data, 3);

    test.pop();
    assert(test.size() == 2);
    assert(test.top() == b);

}

/*
 * 
 * Name: empty_pop_work()
 * Purpose: checks if the pop function of the DatumStack is working correctly
 *          -pop funct of DS class supposed to return the top of the stack
 *           and remove it from the top of the stack
 *          -this test is specifically supposed to check an edge case where
 *           an error is thrown
 * Parameters: None
 * Returns: Nothing
 *
 */
void empty_pop_work()
{
    bool runtime_error_thrown = false;

    DatumStack b_testing;
    std::string error_message = "";

    try {
        b_testing.pop();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    //asserting that the error was thrown
    //and caught
    //this makes sure edge case is tested
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
   
}
