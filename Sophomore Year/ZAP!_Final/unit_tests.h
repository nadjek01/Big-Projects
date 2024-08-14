/*
 *  unit_test.h
 *  Nana Adjekum
 *  8-Nov
 *
 *  CS 15 Proj3 ZAP
 *
 *  Tester for ZAP
 *
 */

//#include "phaseOne.h"
using namespace std;
#include "HuffmanCoder.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include <queue>


/*
 * 
 * Name: faildecode
 * Purpose: tests the exception in the decodeme function
 *          - makes a "faux tree" and a faux binary string that does
 *            not match the tree
 *          - note: to test this i made decode me and p_o_del public
 * Parameters: Nothing
 * Returns: Nothing
 *
 */
void faildecode()
{
    HuffmanTreeNode *node1 = new HuffmanTreeNode('a', 4);
    HuffmanTreeNode *node2 = new HuffmanTreeNode('b', 5);
    HuffmanTreeNode *node3 = new HuffmanTreeNode('c', 6);
    //HuffmanTreeNode *node4 = new HuffmanTreeNode('d', 7);

    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>,
                   NodeComparator> my_pq;
    
    my_pq.push(node1);
    my_pq.push(node2);
    my_pq.push(node3);
    //my_pq.push(node4);

    while (my_pq.size() > 1) {
        HuffmanTreeNode *a_node;
        HuffmanTreeNode *b_node;

        a_node = my_pq.top();
        my_pq.pop();
        b_node = my_pq.top();
        my_pq.pop();

        HuffmanTreeNode *root = new HuffmanTreeNode('\0', 
                                (a_node->get_freq() + b_node->get_freq()));

        root->set_left(a_node);
        root->set_right(b_node);
        my_pq.push(root);
    }

    HuffmanTreeNode *tree = my_pq.top();
    my_pq.pop();

    string bit_str = "001";

    HuffmanCoder test;
    
    string decoded;
    string error_message;
    bool was_error;

    try {
        decoded = test.decode_me(tree, bit_str);
    } catch (const std::runtime_error &e) {
        was_error = true;
        error_message = e.what();
        std::cerr << error_message;
    }

    assert(was_error == true);

    test.p_o_del(tree);

}