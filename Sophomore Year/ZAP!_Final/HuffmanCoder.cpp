/*
 *  HuffmanCoder.cpp- "the Implementation"
 *  Nana Adjekum
 *  14-Nov
 *
 *  CS 15 Proj 3 ZAP!
 *
 *  Defines the functions to be utilised in the HuffmanCoder.h file
 *  which will allow for user input to be "zapped" or serialised
 *  to minimised the amount of space used and "unzap" or unserialised
 *  so the user can recieve the item with less space and have it decoded
 *
 */

#include "HuffmanCoder.h"
#include "BinaryIO.h"
#include <iostream>
#include <istream>
#include <fstream>
#include <queue>
#include <stdexcept>

/*
 * 
 * Name: HuffmanCoder()
 * Purpose: the Constructor for HuffmanCoder
 *          -the only thing initialised is the priv member var
 *           contents which holds the contents of the string passed
 *           into the encode function
 * Parameters: None
 * Returns: Nothing
 *
 */
HuffmanCoder::HuffmanCoder()
{
    contents = "";
}

/*
 * 
 * Name: HuffmanCoder()
 * Purpose: the destructor for HuffmanCoder
 *          -nothing to descruct here, the tree deletion
 *           is done when the encode/decode functions are 
 *           done
 * Parameters: None
 * Returns: Nothing
 *
 */
HuffmanCoder::~HuffmanCoder()
{
    //
}

/*
 * 
 * Name: encoder
 * Purpose: the encoding portion of the zap! program
 *          - encodes a given ASCII text file into compressed binary code
 * Parameters: two strings which are names for an input_file and an output_file
 * Returns: Nothing
 *
 */
void HuffmanCoder::encoder(string input_file, string output_file)
{
    //creates an ifstream for the input file
    ifstream i_file;
    string error_message;
    open_or_kaput(i_file, input_file);

    //makes the tree
    HuffmanTreeNode *temp;
    temp = make_tree(i_file);

    store_char(temp, "");
    string bit_string = encodetxt();
    string t_serialised = serialise_tree(temp);

    //writes the file with the binary string and serialised string
    BinaryIO done;
    done.writeFile(output_file, t_serialised, bit_string);
    cout << "Success! Encoded given text using " << bit_string.size()
         << " bits." << endl;
    
    //closes everything and deletes the tree
    i_file.close();
    p_o_del(temp);
    //return;
}

/*
 * 
 * Name: p_o_del
 * Purpose: deletes the tree in post-order
 * Parameters: the tree to be deleted
 * Returns: Nothing
 *
 */
void HuffmanCoder::p_o_del(HuffmanTreeNode *node)
{
    if (node != nullptr) {
        p_o_del(node->get_left());
        p_o_del(node->get_right());
        delete node;
    }
}

/*
 * 
 * Name: encodetxt
 * Purpose: creates a binary string from the finding the instance of the
 *          char at i in the charcodes map
 * Parameters: Nothing
 * Returns: the binary string
 *
 */
string HuffmanCoder::encodetxt()
{
    string bitstr;
    for (unsigned int i = 0; i < contents.size(); i++) {
        bitstr += charcodes.find(contents[i])->second;
    }
    return bitstr;

}

//use this to test
/*
 * 
 * Name: print_node
 * Purpose: prints a given node
 * Parameters: a node (to printed), an instance of a 
 *             ostream that the node prints to
 * Returns: Nothing
 *
 */
void HuffmanCoder::print_node (HuffmanTreeNode *root, std::ostream& out) 
{
    if (root == nullptr) {
        return;
    } else {
        if (root->get_left()) {
            print_node(root->get_left(), out);
        }

        out << root->get_val() << " ";
        if (root->get_right()) {
            print_node(root->get_right(), out);
        }
    }
}

/*
 * 
 * Name: decoder
 * Purpose: the decoding portion of the zap! program
 *          - takes the compressed binary code and turns it back into text
 * Parameters: two strings which are names for an input_file and an output_file
 * Returns: Nothing
 *
 */
void HuffmanCoder::decoder(string input_file, string output_file)
{
    //opens the input file
    ifstream i_file;
    string error_message;
    open_or_kaput(i_file, input_file);

    //opens the output file
    ofstream o_file;
    open_or_kaput(o_file, output_file);

    BinaryIO read;
    std::vector<std::string> ifile;
    ifile = read.readFile(input_file);
    string s_hufftree = ifile[0];
    string en_bin_str = ifile[1];

    HuffmanTreeNode *root = deserialise_tree(s_hufftree);

    string decoded;
    
    decoded = decode_me(root, en_bin_str);

    o_file << decoded;
    o_file.close();
    i_file.close();
    p_o_del(root);

}

/*
 * 
 * Name: make_tree
 * Purpose: makes the tree for encoding
 *          - counts the frequency
 *          - buids a tree where the internal nodes have frequency equal to
 *            the sum of its children and the val is \0
 *          - the leaf nodes frequency is just the frequency of the char
 *            in the string and the value is the char
 *            
 * Parameters: the finished tree
 *
 */
HuffmanTreeNode* HuffmanCoder::make_tree(std::istream &text)
{
    std::map<char, int>::iterator itr;
    std::map<char, int>charfreqs;

    char a;
    while (text.get(a)) {
        charfreqs[a]++;
        contents += a;
    }
    
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>,
                   NodeComparator> tree_pq;
    for (itr = charfreqs.begin(); itr!=charfreqs.end(); itr++) {
        HuffmanTreeNode *temp = new HuffmanTreeNode(itr->first, itr->second);
        tree_pq.push(temp);
    }

    while (tree_pq.size() > 1) {
        HuffmanTreeNode *a_node;
        HuffmanTreeNode *b_node;

        a_node = tree_pq.top();
        tree_pq.pop();
        b_node = tree_pq.top();
        tree_pq.pop();

        HuffmanTreeNode *root = new HuffmanTreeNode('\0', 
                                (a_node->get_freq() + b_node->get_freq()));

        root->set_left(a_node);
        root->set_right(b_node);
        tree_pq.push(root);
    }

    HuffmanTreeNode *tree = tree_pq.top();
    tree_pq.pop();
    return tree;
    
}

/*
 * 
 * Name: serialise_tree
 * Purpose: creates a string for reconstructing the tree later
 *          - internal nodes stores one char 'I'
 *          - leaf node stores two chars 'L' and the char stored in the node
 * Parameters: the root of the the tree
 * Returns: the serialised tree
 *
 */
std::string HuffmanCoder::serialise_tree(HuffmanTreeNode *root)
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

    return (re + (serialise_tree(root->get_left()) + 
            serialise_tree(root->get_right())));
}

/*
 * 
 * Name: deserialise_tree
 * Purpose: converts the serialised string to a tree
 * Parameters: a string that is the serialised string 
 * Returns: the root of the tree created from the serialise string
 *
 */
HuffmanTreeNode* HuffmanCoder::deserialise_tree(std::string serial_tree)
{
    int index = 0;
    return h_deserial_tree(serial_tree, index);
}

/*
 * 
 * Name: h_deserial_tree
 * Purpose: helper function for the deserialise_tree function
 *          - allows for recursion which implements the nodes and its
 *            children
 *          - the indx int is a counter for iterating through the string
 * Parameters: the string (serialised string) and a pointer to the index
 * Returns: Nothing
 *
 */
HuffmanTreeNode* HuffmanCoder::h_deserial_tree(std::string str, int &indx)
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

/*
 * 
 * Name: decoder_me
 * Purpose: decodes the given message
 *          - goes through the tree to find the char associated with the
 *            binary code
 * Parameters: a node (which is the pointer to the root of the tree), a string
 *             (which is string version of the binary code)
 * Returns: the decoded string (or an error if the string does not correlate
 *          with the tree)
 *
 */
string HuffmanCoder::decode_me(HuffmanTreeNode *node, string bit_str) 
{
    HuffmanTreeNode *temp = node;
    string d_str = "";
    unsigned int index = 0;

    while (index < bit_str.size()) {
        if (bit_str[index] == '0') {
            temp = temp->get_left();
        } else if (bit_str[index] == '1') {
            temp = temp->get_right();
        }
        if (index == (bit_str.size() - 1) and (not temp->isLeaf())) {
            throw std::runtime_error ("Encoding did not match Huffman tree.");
        }
        if (temp->isLeaf()) {
            d_str += temp->get_val();
            temp = node;
        }

        index++;
    }
    return d_str;
}

/*
 * opens or kaputs
 * Name: open_or_kaput
 * Purpose: Opens the file or returns to main
 * Parameters: a streamtype instance (&stream)
 *			   -the file to be opened
			   a string (file_name) --> the name of the file
 * Returns: Nothing
 *
 */
template<typename streamtype>
void HuffmanCoder::open_or_kaput(streamtype &stream, string filename)
{
    stream.open(filename);
    if (not stream.is_open()) {
        throw std::runtime_error("Unable to open file " + filename);
    }
}

/*
 * 
 * Name: store_char
 * Purpose: stores the char and the binary code associated with it in a map
 *          - allows for a string to be encoded as a binary string
 *          - if the node moves to the left the string appends a '0' char
 *            and if it moves to the right a '1' char
 * Parameters: a node (which the root of the tree), a string (the binary string
 *             associated with the char)
 * Returns: Nothing
 *
 */
void HuffmanCoder::store_char(HuffmanTreeNode *root, string code)
{
    if (root->isLeaf()) {
        char at = root->get_val();
        charcodes.insert({at, code});
    } else {
        if (root->get_left()) {
            store_char(root->get_left(), code + "0");
        }

        if (root->get_right()) {
            store_char(root->get_right(), code + "1");
        }
        
    }
}