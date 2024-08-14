/*
 *  phaseOne.cpp- "the Implementation"
 *  Nana Adjekum
 *  8-Nov
 *
 *  CS 15 Proj 3 ZAP!
 *
 *  Defines the functions to be used in the rest of this project
 *  which will allow for user input to be "zapped" or serialised
 *  to minimised the amount of space used and "unzap" or unserialised
 *  so the user can recieve the item with less space and have it decoded
 *
 */

#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include <map>
using namespace std;

//TD FC
void count_freqs(std::istream &text)
{
    std::map<char, int>freqmap;
    std::map<char, int>::iterator itr;

    char a;
    while (text.get(a)) {
        freqmap[a]++;
    }
    
    for (itr = freqmap.begin(); itr!=freqmap.end(); itr++) {
        cout << itr->first << ": " << itr->second << endl;
    }
}

//TD FC
std::string serialize_tree(HuffmanTreeNode *root)
{
    string re = "";
    if (root == nullptr) {
        return re;
    } else {
        if (root->isLeaf()) {
            re = "L";
            re += (root->get_val());
        } else {
            re = "I";
        }
    }
    

    return (re + (serialize_tree(root->get_left()) + serialize_tree(root->get_right())));
    
}

HuffmanTreeNode *deserialize_tree(std::string serial_tree)
{
    int index = 0;
    return h_deserial_tree(serial_tree, index);
    
}

HuffmanTreeNode *h_deserial_tree(std::string str, int &indx)
{
    HuffmanTreeNode *temp = nullptr;
    int sze = str.size();
    if (indx == (sze - 1)) {
        return temp;
    } else if (str[indx] == 'I') {
        indx++;
        temp = new HuffmanTreeNode('\0', -1);
        temp->set_left(h_deserial_tree(str, indx));
        temp->set_right(h_deserial_tree(str, indx));

    } else if (str[indx] == 'L') {
        temp = new HuffmanTreeNode(str[indx + 1], -1);
        indx += 2;
    }

    return temp;
}
