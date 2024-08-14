/*
 *  RPNCalc.h- "the Interface"
 *  Nana Adjekum
 *  Oct 26
 *
 *  CS 15 Proj 3 phaseOne
 *
 *  Declares data members (public and private) in phaseOne
 *  Names the data members to be defined for client use
 *
 */


#ifndef _PHASEONE_H_
#define _PHASEONE_H_

#include "HuffmanTreeNode.h"
#include <iostream>

void count_freqs(std::istream &text);
std::string serialize_tree(HuffmanTreeNode *root);
HuffmanTreeNode *deserialize_tree(std::string serial_tree);
HuffmanTreeNode *h_deserial_tree(std::string str, int &indx);


#endif
