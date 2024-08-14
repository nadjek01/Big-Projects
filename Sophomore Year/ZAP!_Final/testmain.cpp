/*
 *  main.cpp- "the Client"
 *  Nana Adjekum
 *  8-Nov
 *
 *  CS 15 Proj3 ZAP!
 *
 *  main function for ZAP
 *  -i used this to test my phaseOne count_freqs
 *   function
 *
 */

#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include <iostream>
#include <sstream>
using namespace std;

void print_node (HuffmanTreeNode *root, std::ostream& out) {
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
    //out << endl;
}
int main () {
    //cout << "insert a string: ";
    std::stringstream temp("less   go");
    count_freqs(temp);

    cerr << "making a tree"; 

    HuffmanTreeNode *node1 = new HuffmanTreeNode('\0', 0);
    cerr << "the val of first node: " << node1->get_val() << endl;
    HuffmanTreeNode *node2 = new HuffmanTreeNode('b', 2);
    cerr << "the val of second node: " << node2->get_val() << endl;
    HuffmanTreeNode *node3 = new HuffmanTreeNode('c', 100);
    cerr << "the val of third node: " << node3->get_val() << endl;

    node1->set_left(node2);
    node1->set_right(node3);

    cerr << "making a string" << endl;
    string s_temp = serialize_tree(node1);
    cout << "this is what serialise made : " << s_temp << endl;

    cerr << "testing the string erase: " << endl;
    string lol = "lol";
    lol.erase(0,1);
    cerr << lol << endl;
    cerr << "testing the decereal: " << endl;
    string cereal = "IIILaLbILc";
    node1 = deserialize_tree(cereal);
    print_node(node1, cout);
    cout << endl;



}
