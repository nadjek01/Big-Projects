/*
 *  HuffmanCoder.h- "the Interface"
 *  Nana Adjekum
 *  Nov 14
 *
 *  CS 15 Proj 3 HuffmanCoder
 *
 *  Declares data members (public and private) in HuffmanCoder class
 *  Names the data members to be defined for client use
 *
 */


#ifndef _HUFFMANCODER_H_
#define _HUFFMANCODER_H_

#include "HuffmanTreeNode.h"
#include "BinaryIO.h"
#include <iostream>
#include <map>

using namespace std;

class HuffmanCoder 
{
    public:
    //constructor
    HuffmanCoder();
    //destructor
    ~HuffmanCoder();
    
    //encodes the text file
    void encoder(string input_file, string output_file);
    //decodes an instance of a zapped file
    void decoder(string input_file, string output_file);
    

    private:
    //member functions:

    //counts the frequency of a char in a string and makes tree
    HuffmanTreeNode* make_tree(std::istream &text);
    //serialises an instance of a tree
    std::string serialise_tree(HuffmanTreeNode *root);
    
    //deserialises a given string
    HuffmanTreeNode *deserialise_tree(std::string serial_tree);
    //the helper for deserialising the tree
    HuffmanTreeNode *h_deserial_tree(std::string str, int &indx);
    
    //opens ta given file
    template<typename streamtype>
    void open_or_kaput(streamtype &stream, string filename);

    //store char codes
    void store_char(HuffmanTreeNode *root, string code);
    //acc encodes the text
    string encodetxt();

    //prints the node
    void print_node (HuffmanTreeNode *root, std::ostream& out);

    //decodes the given string
    string decode_me(HuffmanTreeNode *node, string bit_str);

    //deletes the given node
    void p_o_del(HuffmanTreeNode *node);
    


    //member variables:

    //the map for keeping the chars and it binary string
    std::map<char, string>charcodes;
    //the string that keeps the string to be encoded
    string contents;



};

#endif