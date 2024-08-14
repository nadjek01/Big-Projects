//
//                       test_linked_list.cpp
//
//     A testing program that creates a CardLinkedList object and
//     tries the basic operations on it, using debug_print to report
//     on the internal state of all objects as it goes.
//
//                   Tufts University, Fall 2021 
//                        CS 11: Project 2
//
//    Modified by: Nana Adjekum
//

#include <iostream>
#include "Card.h"
#include "CardLinkedList.h"
using namespace std;

int main()
{
    cout << "Making card: value 33" << endl;
    cout << "Making card: value 44" << endl;
    cout << "Making card: value 69" << endl;
    Card c33(33);
    Card c44(44);
    Card c69(69);
    Card c48(48);
    Card c4(4);
    
    c33.debug_print();
    c44.debug_print();
    c69.debug_print();
    
    cout << endl;  // newline for viewing convenience

    cout << "Making linked list" << endl;
    CardLinkedList ll;
    ll.debug_print();

    cout << "Adding card 33 to list" << endl;
    ll.add_card_at(0, c33);

    cout << "Adding card 44 to list" << endl;
    ll.add_card_at(0, c44);
    cout << "Adding card 69 to list" << endl;

    ll.add_card_at(0, c69);
    ll.add_card_at(1, c48);
    ll.add_card_at(10, c4);
    ll.add_card_at(4, c4);
    
    ll.debug_print();
    cout << "Checking card at 2nd index" << endl;
    Card c5 = ll.get_card_at(2);
    c5.debug_print();
    
    cout << "here main" << endl;
    ll.remove_card_at(0);
    
    ll.debug_print();
    
    ll.remove_card_at(1);
    
    ll.debug_print();
    
    cout << "Checking add card at" << endl;
    ll.add_card_at(5, c5);
    
    

    return 0;
}

