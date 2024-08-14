/*
 *  unit_test.h
 *  Nana Adjekum
 *  19-Oct
 *
 *  CS 15 Proj2 CalcYouLater
 *
 *  Tester for CalcYouLater
 *
 */
#include "DatumStack.h"
#include <cassert>

//TD FC
void sec_construct_works()
{
    Datum data[3] = {Datum(1), Datum(2), Datum(3)};
    DatumStack test(data, 3);

    assert(test.size() == 3);

}

//TD FC
void empty_works()
{
    DatumStack test;
    assert(test.isEmpty() == true);
}

//TD FC
void a_nempty_work()
{
    Datum data[3] = {Datum(1), Datum(2), Datum(3)};
    DatumStack test(data, 3);

    assert(test.isEmpty() == false);
}

//TD FC
void clear_work()
{
    Datum data[3] = {Datum(1), Datum(2), Datum(3)};
    DatumStack test(data, 3);

    test.clear();
    assert(test.isEmpty() == true);
}


//TD FC
void size_work()
{
    Datum data[3] = {Datum(1), Datum(2), Datum(3)};
    DatumStack test(data, 3);

    assert(test.size() == 3);
}

//TD FC
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

//TD FC
void full_top_work()
{
    Datum a(1);
    Datum b(2);
    Datum c(3);

    Datum data[3] = {a,b,c};
    DatumStack test(data, 3);

    assert(test.top() == c);

}

//TD FC
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

//TD FC
//TD FC
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