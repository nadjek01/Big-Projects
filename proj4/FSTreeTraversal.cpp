/*
 *  FSTreeTraversal.cpp- ""
 *  Nana Adjekum and Max Samuels
 *  30-Nov
 *
 *  CS 15 Proj 4 GERP
 *
 *  TD FC
 *
 */

#include "FSTree.h"
#include <stack>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

template <typename streamtype>
void open_or_die(streamtype &stream, std::string file_name);
void preorder(DirNode* root, string dir_print);



int main (int argc, char *argv[]) 
{
    if (argc != 2) {
        exit(EXIT_FAILURE);
    } else {
        ifstream file;
        std::string directory = argv[1];
        open_or_die(file, directory);

        FSTree dir_tree(directory);
        preorder( dir_tree.getRoot(), directory);

    }

    return 0;
}

/*
 * 
 * Name: open_or_die
 * Purpose: opens the given the file
 *          -according to the spec, it opens the highest directory
 *           passed in on the command line
 * Parameters: a streamtype (can be ostream or ifstream), a string file name
 * Returns: Nothing
 *
 */
template <typename streamtype>
void open_or_die(streamtype &stream, std::string file_name) {
    stream.open(file_name);
    if (not stream.is_open()) {
        throw runtime_error("Unable to open file " + file_name);
        exit(EXIT_FAILURE);
    } 
}

/*
 * 
 * Name: preorder
 * Purpose: traverses the n-ary tree and prints out files
 *          -will only print when it reachs a file
 *          -will print the associated path to get to the file
 * Parameters: None
 * Returns: Nothing
 *
 */
void preorder(DirNode* root, string dir_print) {
    if (root->hasFiles()) {
        for (int i = 0; i < root->numFiles(); i++) {
            cout << dir_print + "/" + root->getFile(i) << endl;
        }
    }
    
    if (root->hasSubDir()) {
        for (int i = 0; i < root->numSubDirs(); i++) {
            DirNode* sub_root = root->getSubDir(i);
            string subdir_print = dir_print + "/" + sub_root->getName();
            preorder(sub_root, subdir_print);
        }
    }
}