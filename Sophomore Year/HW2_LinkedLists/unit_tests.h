/*
 *  unit_tests.h
 *  YOUR NAME HERE
 *  DATE CREATED
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  FILE PURPOSE HERE
 *
 */

#include "CharLinkedList.h"
#include <cassert>
#include <iostream>
using namespace std;

/*
 * default constructor works
 * Name: default_works
 * Purpose: Tests that the default constructor functions
 *          and an instance of an empty CharLinkedList is made
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void default_works()
{
    CharLinkedList testing;
}

/*
 * default constructor size correct
 * Name: first_works_size
 * Purpose: Tests that the default constructor functions
 *          and an instance of an empty CharLinkedList is made
 *          also affirms that the size is zero
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void first_constructor_works() 
{
    CharLinkedList a_list;
    assert(a_list.size() == 0);
}

/*
 * second constructor works
 * Name: secondary_works
 * Purpose: Tests that the secondary constructor functions
 *          and an instance of a CharLinkedList with a char is made
 *          with the correct current size
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void second_constructor_works()
{
    char pass = 't';
    CharLinkedList list(pass);
    assert(list.size() == 1);
    assert(list.first() == 't');
    assert(list.last() == pass);
    //cerr << "2con list: " << list.toString() << endl;
}

/*
 * isEmpty works
 * Name: isEmpty_works
 * Purpose: Tests that the isEmpty functions when the list is 
 *          actually empty
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void isEmpty_works()
{
    CharLinkedList a_list;
    assert(a_list.isEmpty() == true);   
}

/*
 * is size works p1
 * Name: size_works()
 * Purpose: Tests that the size function works and returns the 
 *          correct number of chars currently in the list when
 *          size is 0
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void size_works()
{
    CharLinkedList a_testing;
    assert(a_testing.size() == 0);
}
/*
 * is size works p2
 * Name: full_size()
 * Purpose: Tests that the size function works and returns the 
 *          correct number of chars currently in the list
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void full_size_works()
{
    CharLinkedList b_testing('b');
    assert(b_testing.size() == 1);

    char arr[3] = {'h', 'i', 'm'};
    CharLinkedList c_testing(arr, 3);
    assert(c_testing.size() == 3);

}

/*
 *
 * Name: single_pushAtFront_works
 * Purpose: Tests that push at front function is working for when
 *          there is nothing in the LinkedList
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void single_pushAtFront_works()
{
    char pass = 'p';
    CharLinkedList a_list(pass);
    assert(a_list.size() == 1);
    assert(a_list.isEmpty() == false);
    assert(a_list.first() == pass);
    assert(a_list.last() == pass);
    //cerr << "sPAF list: " << a_list.toString() << endl;

}

/*
 *
 * Name: third_constructor_works
 * Purpose: Tests that the third constructor works
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void third_constructor_works()
{
    char arr[4] = {'h', 'e', 'r', 'e'};
    CharLinkedList a_list(arr, 4);
    assert(a_list.size() == 4);
    assert(a_list.first() == 'h');
    assert(a_list.last() == 'e');
    //cerr << "3con list: " << a_list.toString() << endl;
    assert(a_list.toString() == "[CharLinkedList of size 4 <<here>>]");
}

/*
 * to string 
 * Name: toString_works()
 * Purpose: testing if toString() works by creating
 *          an instance of a list, calling the function,
 *          and then asserting that the string is
 *          eq to what it should be
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void toString_works()
{
    char arr[4] = {'h', 'e', 'r', 'e'};
    CharLinkedList a_list(arr, 4);

    //cerr << "list: " << a_list.toString() << endl;
    assert(a_list.toString() == "[CharLinkedList of size 4 <<here>>]");
    
}

/*
 * multiple works 
 * Name: full_pushAtFront_works
 * Purpose: Tests that push at front function is working for when
 *          there is more than one element in the LinkedList
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void full_pushAtFront()
{
    char arr[4] = {'h', 'e', 'r', 'e'};
    CharLinkedList a_list(arr, 4);
    char there = 't';

    a_list.pushAtFront(there);
    assert(a_list.toString() == "[CharLinkedList of size 5 <<there>>]");
    assert(a_list.last() == 'e');
    assert(a_list.first() == 't');

}

/*
 * move to the back
 * Name: full_pushAtBack_works 
 * Purpose: Tests the pushAtBack function works 
 *          when the function has something
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void full_pushAtBack_works()
{
    char arr[4] = {'b', 'l', 'o', 'n'};
    CharLinkedList a_list(arr, 4);
    char blond = 'd';

    a_list.pushAtBack(blond);
    //cerr << "list: " << a_list.toString() << endl;
    assert(a_list.toString() == "[CharLinkedList of size 5 <<blond>>]");

}

/*
 * insert at  middle)
 * Name: mid_insertAt()
 * Purpose: Tests insertion into middle of a list.
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void mid_insertAt()
{
    char arr[4] = {'b', 'l', 'n', 'd'};
    CharLinkedList a_list(arr, 4);
    char blond = 'o';

    a_list.insertAt(blond, 2);
    //cerr << "list: " << a_list.toString() << endl;
    assert(a_list.toString() == "[CharLinkedList of size 5 <<blond>>]");
}

/*
 * insert at front full house
 * Name: front_insertAt()
 * Purpose: Tests correct insertAt for front of full-element list.
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void front_insertAt()
{
    char arr[4] = {'l', 'o', 'n', 'd'};
    CharLinkedList a_list(arr, 4);
    char blond = 'b';

    a_list.insertAt(blond, 0);
    //cerr << "list: " << a_list.toString() << endl;
    assert(a_list.toString() == "[CharLinkedList of size 5 <<blond>>]");
}

/*
 * insert at back
 * Name: back_insertAt()
 * Purpose: Tests correct insertAt for back of full-element list.
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void back_insertAt()
{
    char arr[4] = {'b', 'l', 'o', 'n'};
    CharLinkedList a_list(arr, 4);
    char blond = 'd';

    a_list.insertAt(blond, 4);
    //cerr << "list: " << a_list.toString() << endl;
    assert(a_list.toString() == "[CharLinkedList of size 5 <<blond>>]");
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
    char arr[4] = {'a', 'b', 'd', 'e'};
    CharLinkedList a_list(arr, 4);
    char abc = 'c';

    a_list.insertInOrder(abc);
    //cerr << "list: " << a_list.toString() << endl;
    assert(a_list.toString() == "[CharLinkedList of size 5 <<abcde>>]");

}

void elementAt_works()
{
    char arr[4] = {'h', 'e', 'r', 'e'};
    CharLinkedList a_list(arr, 4);
    
    //cerr << "elem: " << a_list.elementAt(1) << endl;
    assert(a_list.elementAt(0) == 'h');
    assert(a_list.elementAt(1) == 'e');
    assert(a_list.elementAt(2) == 'r');
    assert(a_list.elementAt(3) == 'e');
    
}

/*
 * remove from front 
 * Name: full_popFromFront_works
 * Purpose: Tests the popFromFront function
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void full_popFromFront_works()
{
    char arr[4] = {'h', 'e', 'r', 'e'};
    CharLinkedList a_list(arr, 4);

    a_list.popFromFront();
    assert(a_list.toString() == "[CharLinkedList of size 3 <<ere>>]");
    //cerr << a_list.toString() << endl;
    assert(a_list.first() == 'e');
    assert(a_list.last() == 'e');
}

/*
 * remove from back 
 * Name: full_popFromBack_works()
 * Purpose: Tests that the popFromBack function works
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void full_popFromBack_works()
{
    char arr[4] = {'h', 'e', 'r', 'e'};
    CharLinkedList a_list(arr, 4);

    a_list.popFromBack();
    assert(a_list.toString() == "[CharLinkedList of size 3 <<her>>]");
    //cerr << a_list.toString() << endl;
    assert(a_list.first() == 'h');
    assert(a_list.last() == 'r');
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
    char arr[4] = {'h', 'e', 'r', 'e'};
    CharLinkedList a_list(arr, 4);

    char b_arr[4] = {'a', 'b', 'd', 'e'};
    CharLinkedList b_list(b_arr, 4);

    a_list.concatenate(&b_list);
    //cerr << a_list.toString() << endl;
    assert(a_list.toString() == "[CharLinkedList of size 8 <<hereabde>>]");

}

/*
 * gemini but on the same line
 * Name: same_concatenate_works
 * Purpose: Tests the concatenate function works when the 
 *          LinkedList passed in is the same
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void same_concatenate_works()
{
    char arr[4] = {'h', 'e', 'r', 'e'};
    CharLinkedList a_list(arr, 4);


    a_list.concatenate(&a_list);
    //cerr << a_list.toString() << endl;
    assert(a_list.toString() == "[CharLinkedList of size 8 <<herehere>>]");

}

/*
 * are u here
 * Name: elemAt_works()
 * Purpose: Tests that the elementAt function is working
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void elemAt_works()
{
    char arr[4] = {'h', 'e', 'r', 'e'};
    CharLinkedList a_list(arr, 4);

    //cerr << "elem 1: " << a_list.elementAt(1) << endl;
    //cerr << "elem 2: " << a_list.elementAt(2) << endl;
    assert(a_list.elementAt(1) == 'e');
    assert(a_list.elementAt(2) == 'r');

}

//To do FC
void front_replaceAt_works()
{
    char arr[5] = {'t', 'h', 'e', 'r', 'e'};
    CharLinkedList a_list(arr, 5);

    a_list.replaceAt('g', 0);
    //cerr << "in RP: " << a_list.toString() << endl;
    assert(a_list.elementAt(0) == 'g');
}

//To do FC
void mid_replaceAt_works()
{
    char arr[4] = {'h', 'e', 'a', 'r'};
    CharLinkedList a_list(arr, 4);

    a_list.replaceAt('i', 2);
    //cerr << "in RP: " << a_list.toString() << endl;
    assert(a_list.elementAt(2) == 'i');
    assert(a_list.size() == 4);
    assert(a_list.toString() == "[CharLinkedList of size 4 <<heir>>]");
}

//To do FC
void back_replaceAt_works()
{
    char arr[4] = {'y', 'e', 'r', 't'};
    CharLinkedList a_list(arr, 4);

    a_list.replaceAt('n', 3);
    //cerr << "in RP: " << a_list.toString() << endl;
    assert(a_list.elementAt(3) == 'n');
    assert(a_list.toString() == "[CharLinkedList of size 4 <<yern>>]");
}

void copy_work()
{
    char arr[4] = {'y', 'e', 'r', 't'};
    CharLinkedList a_list(arr, 4);

    CharLinkedList b_list(a_list);

    //cerr << "cp werk: " << b_list.toString() << endl;

}


//TO DO
void clear_work()
{
    char arr[4] = {'y', 'e', 'r', 't'};
    CharLinkedList a_list(arr, 4);

    a_list.clear();
    assert(a_list.toString() == "[CharLinkedList of size 0 <<>>]");
    //cerr << "clear werk: " << a_list.toString() << endl;

}

//To do 
void op_works()
{
    char arr[4] = {'y', 'e', 'r', 't'};
    CharLinkedList a_list(arr, 4);
    CharLinkedList b_list;

    b_list = a_list;
    //cerr << "op_works:" << b_list.toString() << endl;
    assert(b_list.toString() == "[CharLinkedList of size 4 <<yert>>]");
    
    
}

void zero_first_works() 
{
    bool runtime_error_thrown = false;

    CharLinkedList b_testing;
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
    assert(error_message == "cannot get first of empty LinkedList");
   
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

    CharLinkedList b_testing(arr, 4);

    assert(b_testing.last() == 'r');

    char a_arr [5] = {'a','x', 'i', 'e', 'o'};

    CharLinkedList a_testing(a_arr, 5);

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

    CharLinkedList b_test;
    std::string error_message = "";

    try {
        assert(b_test.last() == 'c');
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    //asserting that 
    assert(runtime_error_thrown);
    assert(error_message == "cannot get last of empty LinkedList");
}


/*
 * multiple works 
 * Name: mult_pushAtFront_works
 * Purpose: Tests that push at front function is working for when
 *          there is one element in the LinkedList
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void mult_pushAtFront_works() 
{
    CharLinkedList testing('o');
    char test = 'y';
    testing.pushAtFront(test);

    assert(testing.first() == 'y');
    assert(testing.toString() == "[CharLinkedList of size 2 <<yo>>]");
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
    CharLinkedList testing(arr, 4);

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
    CharLinkedList testing(arr, 4);

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
    CharLinkedList testing;
    std::string error_message = "";

    try {
        testing.removeAt(0);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0]");
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
    CharLinkedList testing(arr, 4);
    std::string error_message = "";


    //cerr << testing.toString() << endl;
    testing.removeAt(2);
        
    //cerr << testing.toString() << endl;
    assert(testing.elementAt(2) == 'd');
    
}


/*
 * move to the back
 * Name: pushAtBack_works 
 * Purpose: Tests the pushAtBack function works 
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void single_pushAtBack_works() 
{
    CharLinkedList testing('y');
    testing.pushAtBack('t');

    //cerr << "last: " << testing.last() << endl;

    //cerr << "PAB: " << testing.toString() <<endl;
    assert(testing.last() == 't');

}

/*
 * move to the back
 * Name: pushAtBack_works 
 * Purpose: Tests the pushAtBack function works 
 * Parameters: N/A
 * Returns: Nothing
 *
 */
void empty_pushAtBack_works() 
{
    CharLinkedList testing;
    testing.pushAtBack('t');

    //cerr << "last: " << testing.last() << endl;

    //cerr << "PAB: " << testing.toString() <<endl;
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
    CharLinkedList testing(arr, 3);

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
    CharLinkedList testing(arr, 3);
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
    CharLinkedList testing;
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
        
    CharLinkedList test_list;
    test_list.insertAt('a', 0);
    //cerr << test_list.toString() << endl;
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

    CharLinkedList test_list;
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
    CharLinkedList test_list('a');

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
    CharLinkedList test_list('a');

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
    
    CharLinkedList test_list;

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
        CharLinkedList test_list(test_arr, 8);
        

        // insertAt middle
        test_list.insertAt('z', 3);

        assert(test_list.size() == 9);
        assert(test_list.elementAt(3) == 'z');
        //cerr << test_list.toString();

        assert(test_list.toString() ==
         "[CharLinkedList of size 9 <<abczdefgh>>]");

        // insertAt front
        test_list.insertAt('y', 0);

        assert(test_list.size() == 10);
        assert(test_list.elementAt(0) == 'y');
        assert(test_list.toString() ==
         "[CharLinkedList of size 10 <<yabczdefgh>>]");

        // insertAt back
        test_list.insertAt('x', 10);

        assert(test_list.size() == 11);
        assert(test_list.elementAt(10) == 'x');
        assert(test_list.toString() == 
        "[CharLinkedList of size 11 <<yabczdefghx>>]");
        
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
    CharLinkedList test_list(test_arr, 8);

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
    CharLinkedList f_testing(arr, 4);
    string f_test = f_testing.toReverseString();
    //cerr << f_test << endl;

    char b_arr[4] = {'d', 'c', 'b', 'a'};
    CharLinkedList b_testing(b_arr, 4);
    string b_test = b_testing.toString();
    //cerr << b_test << endl;


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
    CharLinkedList testing(arr, 3);
    
    testing.insertInOrder('b');
    for (int i = 0; i < 4; i++) {
        //cerr << testing.elementAt(i);
    }
    //cerr << "entering element at with char b" << endl;
    assert(testing.elementAt(2) == 'b'); 
    //cerr << testing.toString() << endl;

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
    CharLinkedList a_testing(a_arr, 2);

    char b_arr[2] = {'c', 'd'};
    CharLinkedList b_testing(b_arr, 2);

    a_testing.operator=(b_testing);
    assert(a_testing.toString() == b_testing.toString());

    //cerr << a_testing.toString() << endl;
    //cerr << b_testing.toString() << endl;
    //cerr << &a_testing << endl;
    //cerr << &b_testing << endl;


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
    CharLinkedList f_testing(arr, 4);

    f_testing.replaceAt('t', 2);
    assert(f_testing.toString() == "[CharLinkedList of size 4 <<abtd>>]");
    //cerr << f_testing.toString() << endl;
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
    CharLinkedList f_testing;

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
    CharLinkedList f_testing(arr, 4);

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


