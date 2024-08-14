/*
 * most_common_int.cpp
 * 
 * Purpose: find the number that occurred the most in an array
 * 
 * Name: Nana Adjekum
 * Credits: HW03 Guidelines
 * Any Bugs/Issues:
 * Date: 02/10/2022
 */

#include <iostream>

using namespace std;

int most_common_int(int numbers[], int length);
void result (int numbers[], int length);

int main()
{

    int array_len = 10;
    int fiarray[array_len] = {1, 4, 5, 2, 1, 9, 8, 1, 7, 6};
    int sarray[array_len] = {2, 3, 7, 8, 1, 9, 2, 2, 1, 8};
    int tarray[array_len] = {4, 5, 3, 5, 1, 5, 2, 4, 1, 4};
    int foarray[array_len] = {2, 5, 6, 6, 2, 1, 6, 7, 2, 6};
    
    result(fiarray, array_len);
    result(sarray, array_len);
    result(tarray, array_len);
    result(foarray, array_len);
    
    return 0;
}
/*funct for finding the most_common_int
 *has two loops one that checks the first number
 *and the other that compares the number following 
 *to see if they are equal*/
int most_common_int(int numbers[], int length) {
    int i, j;
    //overarching count
    int maxcount = 0;
    int mci;
    
    for (i = 0; i < length; i++) {
        //inner loop count
        int count = 1;
        for (j = i+1; j < length; j++) {
            if (numbers[i] == numbers[j]) {
                count++;
            }
        }
        //at end of loop compares max count to count
        if (maxcount < count) {
            maxcount = count;
            mci = numbers[i];
        } else if (maxcount == count and numbers[i] < mci) {
            mci = numbers[i];
        }
    } 
    return mci;
}
//testing function
void result (int numbers[], int length) {
    int i;
    cout << "TESTING: ";
    for (i = 0; i < length; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl; 
    if (most_common_int(numbers, length) >= 0) {
        cout << "SUCCESS: ";
        cout << most_common_int(numbers, length) << endl;
        return;
    } else {
        cout << "FAILURE";
    }
    
}
