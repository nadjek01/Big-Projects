/*
 *  HashTable.cpp- ""
 *  Nana Adjekum and Max Samuels
 *  5-Dec
 *
 *  CS 15 Proj 4 GERP
 *
 *  TD FC
 *
 */

#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <string>
#include <functional>
#include <set>
#include <iostream>
#include <fstream>
#include <vector>
#include "FSTree.h"
using namespace std;

struct Word
{
    string new_word;
    unsigned int index_key;
    std::set<int> lines;
};

struct Visit
{
    string output;
    bool been;
};

class HashTable
{
    public:
    //default constructor
    HashTable();

    //the lowkey constructor, starts the program
    void run(char *argv[]);

    //destructor
    ~HashTable();


    private:

    
    std::vector<Visit> output_string;

    std::vector<Word> hashtable;
    std::vector<std::vector<Word>> main_table;

    unsigned int hash_function(string key);
    bool it_set(std::set<int> set);
    void rehash();
    void traverse_tree(DirNode *root, string to_read);
    void read_file(string filename, string path);
    
    template <typename streamtype>
    void open_or_die(streamtype &stream, std::string file_name);

    void preorder(DirNode* root, string to_read);
    void add_to_hash_table(Word to_add);
    std::string parse_word(std::string input);
    std::string to_lower(string lower_me);

    void cmd_loop();
    void case_sensitive_search(string input_word);
    void case_insensitive_search();
    void new_output_file();
    int output_lines();

    const float LOAD_FACTOR = .7;
    int size;
    int num_in_hash;
    
    

    string o_file;
    ofstream fin_file;
    int num_output_line;
};

#endif