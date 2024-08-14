// yoda.cpp
// purpose: take a four-word sentence and print out the four words in reverse
//          order on one line
//  author: Nana Adjekum
//   date: 2/1/22
//
#include <iostream>

using namespace std;

int main ()
{
    //line 15 identifies the string variables used: word1, word2, word3, word4
    string word1, word2, word3, word4;
    
    //line 17 prompts user to type in 4 words, getting the words to be jumbled
    cout << "Type in four words: ";
    cin >> word1;
    cin >> word2;
    cin >> word3;
    cin >> word4;
    
    //line 24 prints the words in reverse order
    cout << word4 << " " << word3 << " " << word2 << " " << word1 << endl;
    
    return 0;
}