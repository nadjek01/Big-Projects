/*
 *  HashTable.cpp- "the implementation"
 *  Nana Adjekum and Max Samuels
 *  5-Dec
 *
 *  CS 15 Proj 4 GERP
 *
 *  TD FC
 *
 */

#include "HashTable.h"
#include "FSTree.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
using namespace std;


/*
 * 
 * Name: HashTable()
 * Purpose: the default constructor
 *          -we don't really use this but it still here
 * Parameters: noting
 * Returns: Nothing
 *
 */
HashTable::HashTable()
{

}

/*
 * 
 * Name: run(char *argv[])
 * Purpose: starts the program
 *          -initialises the private member variables
 *          -resizes the main_table to ensure we are able to track 
 *           the load_factor
 *          -loads all the files and subdirectories into a tree
 *           to then be placed in the 2d array
 *          -open the output file
 *          -starts the command loop
 *          -burns the tree in the end
 * Parameters: a pointer to an array of chars (essentially the command line)
 * Returns: Nothing
 *
 */
void HashTable::run(char *argv[])
{
    num_in_hash = 0;
    size = 1000;
    main_table.resize(size);
    string directory = argv[1];
    try {
        FSTree tree(directory);
        preorder(tree.getRoot(), directory);
        o_file = argv[2];
        open_or_die(fin_file, o_file);
        cmd_loop();
    
        tree.burnTree();
    }
    catch (const std::runtime_error &e) {
        cout << "Could not build index, exiting." << endl;
    }
}

/*
 * 
 * Name: ~HashTable
 * Purpose: the destructor
 *          -doesn't really do anything tbh
 * Parameters: Nothing
 * Returns: Nothing
 *
 */
HashTable::~HashTable()
{

}

/*
 * 
 * Name: hash_function(string key)
 * Purpose: returns an unsigned integer to a hashed string
 *          -we use this integer to then index the instance of the word
 * Parameters: a string
 * Returns: unsigned int
 *
 */
unsigned int HashTable::hash_function(string key)
{
    return std::hash<string>{}(key) % size;
}


/*
 * 
 * Name: preorder(DirNode* root, string to_read)
 * Purpose: searches through a given tree to then send instances
 *          of files to the read_file function
 *          -we use this to search through the directory to
 *           then find each file and index the path to said files
 * Parameters: a DirNode (pointer to root), a string (concatenated string that
 *             is a path to the file)
 * Returns: Nothing
 *
 */
void HashTable::preorder(DirNode* root, string to_read) {
    if (root->hasFiles()) {
        for (int i = 0; i < root->numFiles(); i++) {
            read_file(root->getFile(i), to_read);
        }
    }
    
    if (root->hasSubDir()) {
        for (int i = 0; i < root->numSubDirs(); i++) {
            DirNode* sub_root = root->getSubDir(i);
            string subdir_read = to_read + "/" + sub_root->getName();
            preorder(sub_root, subdir_read);
        }
    }
}

/*
 * 
 * Name: read_file(string filename, string path)
 * Purpose: reads the contents of each file 
 *          -concatenates the path to the file and then for each 
 *           line concatenates that
 *          -reads in every word in the line and stores it
 *          -stores the words and the concatenated string into the
 *           struct of words
 * Parameters: two strings (one that is the filename and other that is the path)
 * Returns: Nothing
 *
 */
void HashTable::read_file(string filename, string path)
{
    ifstream dir_file;
    string read_line;
    open_or_die(dir_file, path + "/" + filename);
    int lineNum = 1;
    while (getline(dir_file, read_line)) {
        Visit here;
        here.been = false;
        here.output = path + "/" + filename + ":" + 
                                 to_string(lineNum) + ": " + read_line;
        output_string.push_back(here);                      
        string word;
        std::stringstream sentence(read_line);
        int temp = 0;
        while(sentence >> word) {
            Word a_word;
            a_word.new_word = word;
            a_word.lines.insert(output_string.size() - 1);
            add_to_hash_table(a_word);
            temp++;
        }
        lineNum++; 
    }
    dir_file.close();
}

/*
 * 
 * Name: open_or_die(streamtype &stream, std::string file_name)
 * Purpose: opens the files
 *          -if the file cannot be open throws an run_time error
 * Parameters: a streamtype and a string (for the filename)
 * Returns: Nothing
 *
 */
template <typename streamtype>
void HashTable::open_or_die(streamtype &stream, std::string file_name) {
    stream.open(file_name);
    if (not stream.is_open()) {
        throw std::runtime_error("Unable to open file " + file_name);
        exit(EXIT_FAILURE);
    } 
}

/*
 * 
 * Name: add_to_hash_table(Word to_add)
 * Purpose: adds Word structs to the hash table
 *          -in charge of calling rehash
 * Parameters: an instance of the Word to add
 * Returns: Nothing
 *
 */
void HashTable::add_to_hash_table(Word to_add)
{
    to_add.new_word = parse_word(to_add.new_word);
    string temp = to_lower(to_add.new_word);
    rehash();

    to_add.index_key = hash_function(temp);
    main_table.at(to_add.index_key).push_back(to_add);
    num_in_hash++;
}

/*
 * 
 * Name: rehash()
 * Purpose: rehashes the table when the number of things in the hash
 *          divided by the size of the main_table is greater than the
 *          LOAD_FACTOR variable (which is set to 0.7)
 * Parameters:
 * Returns: Nothing
 *
 */
void HashTable::rehash()
{
    if ((num_in_hash/size) > LOAD_FACTOR) {
        std::vector<std::vector<Word>> temp_main_table;
        size = size * 2 + 10;
        num_in_hash = 0;
        temp_main_table.resize(size);
        for (unsigned int i = 0; i < main_table.size(); i++) {
            for (unsigned int j = 0; j < main_table.at(i).size(); j++) {
                Word temp;
                string t_string = main_table.at(i).at(j).new_word;
                int index = hash_function(to_lower(main_table.at(i).at(j).new_word));
                std::set<int> t_lines = main_table.at(i).at(j).lines;
                temp.new_word = t_string;
                temp.index_key = index;
                temp.lines = t_lines;
                temp_main_table.at(temp.index_key).push_back(temp);
            }  
            num_in_hash++;
        }
        main_table = temp_main_table;
    }
}

/*
 * 
 * Name: parse_word(std::string input)
 * Purpose: parses through the word and removes
 *          any non-alpha-numeric characters
 * Parameters:
 * Returns: Nothing
 *
 */
std::string HashTable::parse_word(std::string input)
{
    while ((not input.empty()) and (not isalnum(input[0]))) {
        input.erase(0,1);
    }

    while ((not input.empty()) and (not isalnum(input[input.size() - 1]))) {
        input.pop_back();
    }
    return input;

}

/*
 * 
 * Name: to_lower()
 * Purpose: lowers every char in the string, used search and hash
 * Parameters: a string
 * Returns: the string (but with every char lowered)
 *
 */
std::string HashTable::to_lower(string lower_me)
{
    string temp = "";
    for (unsigned int i = 0; i < lower_me.size(); i++) {
        temp += tolower(lower_me[i]);
    }
    return temp;
}

/*
 * 
 * Name: cmd_loop()
 * Purpose: the command loop for the function
 *          -prompts the user to place in a query
 *          -takes in command from the command line
 *          -will continue the command loop until the
 *           user inputs @q or theres an EOF
 * Parameters:
 * Returns: Nothing
 *
 */
void HashTable::cmd_loop()
{
    string cmd;
    cout << "Query? ";
    
    while (cin >> cmd) {
        if ((cmd == "@q") or (cmd == "@quit")) {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            fin_file.close();
            break;
        } else if ((cmd == "@i") or (cmd == "@insensitive")) {
            case_insensitive_search();
        } else if (cmd == "@f") {
            new_output_file();
        } else {
            case_sensitive_search(cmd);
        }
        cout << "Query? ";
    }
    fin_file.close();
    
}

/*
 * 
 * Name: case_insensitive_search()
 * Purpose: searches through the 2D vector
 *          -this search takes in any instance of the word
 *           regardless of if it's uppercase or lowercase
 * Parameters: Nothing
 * Returns: Nothing
 *
 */
void HashTable::case_insensitive_search()
{
    string input_word;

    cin >> input_word;
    input_word = parse_word(input_word);
    input_word = to_lower(input_word);
    if (input_word.empty()) {
        fin_file << input_word << " Not Found." << endl;
    } else {
        int hash = hash_function(input_word);
        bool found = true;
        for (unsigned int i = 0; i < main_table.at(hash).size(); i++) {
            if (to_lower(main_table.at(hash).at(i).new_word) == input_word) {
                found = it_set((main_table.at(hash).at(i).lines));
            }
        }
        if (found == false) {
            fin_file << input_word << " Not Found." << endl;
        }
    }
}

/*
 * 
 * Name: case_sensitive_search(string input_word)
 * Purpose: searches through the 2D vector
 *          -this search takes in any instance of the word
 *           (cares about the case of the word)
 * Parameters: Nothing
 * Returns: Nothing
 *
 */
void HashTable::case_sensitive_search(string input_word)
{
    input_word = parse_word(input_word);
    string temp = to_lower(input_word);
    int hashed = hash_function(temp);

    if (input_word.empty()) {
        fin_file << input_word << " Not Found. Try with @insensitive or @i." 
        << endl;
    } else {
        bool found = true;
        for (unsigned int i = 0; i < main_table.at(hashed).size(); i++) {
            if (main_table.at(hashed).at(i).new_word == input_word) {
                found = it_set((main_table.at(hashed).at(i).lines));
            }
        }

        if ((main_table.at(hashed).empty() == true) or (found == false)) {
                    fin_file << input_word << " Not Found. Try with @insensitive or @i." 
                    << endl;
        }
    }  
}

/*
 * 
 * Name: it_set(std::set<int> set)
 * Purpose: iterates through the given set to the function
 *          -for every thing the set its pointing the
 *           an index of output_string vector that it is associated
 *           with
 *         -returns a bool so we know it was found
 * Parameters: a set
 * Returns: Nothing
 *
 */
bool HashTable::it_set(std::set<int> set) 
{
    if (set.empty()) {
        return false;
    } else {
        for (std::set<int>::iterator it = set.begin(); it != set.end(); ++it) {    
            if ((output_string.at(*it).been) == false) {
                fin_file << output_string.at(*it).output << endl;
                output_string.at(*it).been = true;
            }
        }
        return true;
    }
}


/*
 * 
 * Name: new_output_file()
 * Purpose: close the old output file, read in a new file name, pass that 
            file_name to open_or_die to open it.
 * Parameters: Nothing
 * Returns: Nothing
 *
 */
void HashTable::new_output_file()
{
    string new_file;
    cin >> new_file;
    fin_file.close();
    open_or_die(fin_file, new_file);
}

