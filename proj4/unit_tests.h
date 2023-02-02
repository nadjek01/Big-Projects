/*
 *  unit_tests.h- "the testing interface"
 *  Nana Adjekum and Max Samuels
 *  30-Nov
 *
 *  CS 15 Proj 4 GERP
 *
 *  TD FC
 *
 */
#include "stringProcessing.h"
#include <cassert>
#include <iostream>
#include "HashTable.h"
#include "FSTree.h"
using namespace std;

//TD FC
void all_stripNonAlphaNum_works()
{
    std::string temp = "&$&#";
    cerr << "prev: " << temp << endl;
    temp = stripNonAlphaNum(temp);
    cerr << "post: " << temp << endl;
    
    assert(temp.size() == 0);

}


//TD FC
void single_stripNonAlphaNum_works()
{
    std::string temp = "&$&#b";
    cerr << "prev: " << temp << endl;
    temp = stripNonAlphaNum(temp);
    cerr << "post: " << temp << endl;
    
    assert(temp.size() == 1);
    assert(temp == "b");

}

//TD FC
void front_stripNonAlphaNum_works()
{
    std::string temp = "b%^^&&";
    cerr << "prev: " << temp << endl;
    temp = stripNonAlphaNum(temp);
    cerr << "post: " << temp << endl;
    
    assert(temp.size() == 1);
    assert(temp == "b");

}

//TD FC
void mid_stripNonAlphaNum_works()
{
    std::string temp = "&$&#b&(!";
    cerr << "prev: " << temp << endl;
    temp = stripNonAlphaNum(temp);
    cerr << "post: " << temp << endl;
    
    assert(temp.size() == 1);
    assert(temp == "b");

}

//TD FC
// void test_hash_funct()
// {
//     string hash_test = "Nana + Max";
//     HashTable test;
//     int test_hash_funct = test.hash_function(hash_test);
//     cerr << "this is the hash key: " << test_hash_funct << endl;

// }


