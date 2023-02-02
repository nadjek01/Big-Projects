// Lawrence Chan
// COMP15 Hash Example
// 3/30/2019 
// Edits: 2019-03-31 Lawrence
//        2019-11-13 MAS some minor formatting/renaming
//
// example of hashing function to generate hashes; insertion
// compile: clang++ -std=c++11 -o hashEx hashExample.cpp
// run    : ./hashEx

#include <iostream>
#include <string>
#include <functional>

using namespace std;

const int ARRAYSIZE = 7;

int main() {
        //setup
        string input[ARRAYSIZE] = {"penguins", 
				   "harpseals", 
				   "polarbears", 
				   "seagulls", 
				   "walruses",
				   "articfoxes",
				   "narwhals"};

        string animal[ARRAYSIZE]; // initalized to all "-1"
        for (int i = 0; i < ARRAYSIZE; i++) {
            animal[i] = "-1";
        }

        // showing hash and compress
        cout << "string_tohash\thash\t\t\tcompressed" << endl;
        for (int i = 0; i < ARRAYSIZE; i++)
            cout << input[i] << "\t" //input
                 << hash<string>{}(input[i]) << "\t"     // hashing
                 << hash<string>{}(input[i]) % ARRAYSIZE // compression
                 << endl;

        cout << endl;

        //inserting if and only if no collision
        for (int i = 0; i < ARRAYSIZE; i++) {
            int index = hash<string>{}(input[i]) % ARRAYSIZE;

            if (animal[index] == "-1") {
                cout << "inserting " << input[i] 
                     << "\t at " << index << endl;
                animal[index] = input[i];
            } else {
                cout << "unable to insert " << input[i] << " at " << index
                     << " -- collision with " << animal[index] << endl;
	    }
        }

        cout << endl;

        //final array print
        cout << "Final array: ";
        for (int i = 0; i < ARRAYSIZE; ++i) {
            cout << animal[i];
            if (i < ARRAYSIZE - 1)
                cout << " | ";
            else
                cout << endl;
        }
        return 0;
}
