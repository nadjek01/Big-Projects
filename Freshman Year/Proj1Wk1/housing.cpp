//===============================================================
// housing.cpp
// By:  Nana Adjekum
// Credits: Proj1WK1
// Any Bugs/Issues:
// Date: 03/02/22
//
// IMPORTANT NOTE: Only write where the starter indicates "YOUR
// CODE GOES HERE." Do not change anything unless comments tell
// you to do so, OR YOU MAY GET NO CREDIT ON THIS ASSIGNMENT!
//
//===============================================================

#include <iostream>
#include <fstream>

using namespace std;

// DO NOT CHANGE THE FOLLOWING CONSTANTS. WHEN YOU SUBMIT,
// THEY MUST HAVE THESE VALUES AND THEY MUST BE USED
// AS THE DIMENSIONS FOR YOUR all_houses ARRAY.
const int ROWS = 50;
const int COLS = 20;

//===============================================================
//
//                             House
//
//     Each House struct records the information about one
//     house.  Three of the fields are declared for you and
//     you MUST use them as given.  You should declare below
//     them any additional members that you need.
//
//     Note that if the "no_house_here" member field is set
//     to true, then the other fields are not used.  Of course,
//     if no_house_here is false; then all the fields should
//     be set.
//
//===============================================================

struct House
{
    bool   no_house_here;  // true if there is NO house on this location
    int    id;             // id from the data file, converted to int
    string lot_code;       // lot_code string from the data file

    // DO NOT CHANGE ANYTHING ABOVE THIS LINE
    // ===================================================

    // YOUR CODE GOES HERE
    float price;
    int numrooms;
    string color;
    string is_available;

    // ===================================================
};


/*===============================================================
                   Required Function Prototypes

        DO NOT CHANGE ANYTHING IN THIS SECTION. YOUR CODE
        MUST ADHERE TO THESE FUNCTION DECLARATIONS OR YOU WILL
        RECEIVE NO CREDIT.
  ===============================================================*/

// - - - - - - - - - - - - - - - - - - - - - - - - - - -
//   Functions operating on a single house
// - - - - - - - - - - - - - - - - - - - - - - - - - - -
House read_one_house(ifstream &input_file);
void print_house(House h);

// - - - - - - - - - - - - - - - - - - - - - - - - - - -
//   Functions relating to the array of houses
// - - - - - - - - - - - - - - - - - - - - - - - - - - -
int col_from_lot(string lot);
int row_from_lot(string lot);
void fill_with_no_houses(int rows, int cols, House all_houses[ROWS][COLS]);
bool read_all_house_data(string filename, House all_houses[ROWS][COLS]);

// - - - - - - - - - - - - - - - - - - - - - - - - - - -
//   Functions for week 2 (ignore during week 1)
// - - - - - - - - - - - - - - - - - - - - - - - - - - -
// bool is_available(int house_id, House all_houses[ROWS][COLS]);
/* int matching_houses(float max_price, string desired_color,
                       int desired_bedrooms, House all_houses[ROWS][COLS],
                       House results[ROWS * COLS]); */
// int num_neighbors(int house_id, House all_houses[ROWS][COLS]);
// int rent_house(int house_id, House all_houses[ROWS][COLS]);


/*===============================================================
                   Additional Function Prototypes

        Write any additional function prototypes that you
        define here. You may not need any, or you may choose
        to write several
  ===============================================================*/

// YOUR FUNCTION PROTOTYPES HERE



//======================================================================
//                              main
//======================================================================

int main(int argc, char *argv[])
{
    // If you have function arguments that aren't used yet
    // the g++ compiler complains. The following lines are
    // harmless and they suppress the complaint. You can remove
    // the (void) lines and this comment once you start using
    // the arguments.
    //   =======================================================
    int rows(0), cols(0);
    House all_houses[ROWS][COLS];
    if(argc != 2) {
        cerr << "No enough arguments!" << endl;
        return 1;
    }
    string filename = argv[1];
    
    fill_with_no_houses(rows, cols, all_houses);
    read_all_house_data(filename, all_houses);
    
    int u_row, u_col;
    while(u_row > -1 and u_col > -1) {
        cout << "Enter row: ";
        cin >> u_row;
        if (u_row < 0) {
            return 0;
        }
        cout << "Enter col: ";
        cin >> u_col;
        if (u_col < 0) {
            return 0;
        }
        House u_house = all_houses[u_row][u_col];
        print_house(u_house);
    }
    //
    //   =======================================================

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - -
//   Functions operating on a single house
// - - - - - - - - - - - - - - - - - - - - - - - - - - -

// read one line of the input_file; return corresponding House
/*
 * read_one_house
 *
 * Parameters: A reference to an ifstream object
 * Returns:    A single House struct
 * Purpose:    Read one line of the input file and return that
 *             corresponding House
 * Notes:      
 * 
 */
House read_one_house(ifstream &input_file)
{
    // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
    // ===================================================

    House house_one;
    input_file >> house_one.id;
    input_file >> house_one.lot_code;
    input_file >> house_one.price;
    input_file >> house_one.numrooms;
    input_file >> house_one.color;
    input_file >> house_one.is_available;
            
    house_one.no_house_here = false;
    
    return house_one;
    

    // ===================================================

}

// print information about a single house
/*
 * print_house
 *
 * Parameters: A single House struct (House h) to print
 * Returns:    None
 * Purpose:    Prints what is in the House struct (attributes-wise)
 * Notes:      
 * 
 */
void print_house(House h)
{
    // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
    // ===================================================
    //
    if(h.no_house_here == false) {
        cout << "Id: " << h.id;
        cout << " Lot: " << h.lot_code;
        cout << " Color: " << h.color;
        cout << " Price: " << h.price;
        cout << " Bedrooms: " << h.numrooms;
        if(h.is_available == "booked") {
            cout << " Available: No";
        } else {
            cout << " Available: Yes";
        }

        cout << endl; 
    } else {
        cout << "No house";
        cout << endl;
        
    }
      
    //
    // ===================================================

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - -
//   Functions relating to the array of houses
// - - - - - - - - - - - - - - - - - - - - - - - - - - -

// given a lot code, return the column and row (respectively)
// in the all_houses array
/*
 * col_from_lot
 *
 * Parameters: A string (lot) to convert from string to int
 * Returns:    An int (num) to be used for the COL index
 * Purpose:    Convert the given string into an int
 * Notes:     
 * 
 */
int col_from_lot(string lot)
{
    // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
    // ===================================================
    //
    int num = lot[0] - 'A';
    return num; 
    // 
    // ===================================================
}
/*
 * row_from_lot
 *
 * Parameters: A string (lot) to convert from int to string
 * Returns:    An int (total) to be used for the ROW index
 * Purpose:    Convert the given string into an int
 * Notes:      
 * 
 */
int row_from_lot(string lot)
{
    // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
    // ===================================================
    //
    int total = 0;
    for(size_t i = 0; i < lot.length(); i++) {
        if (lot[i] >= '0' and lot[i] <= '9') {
            int num = lot[i] - '0';
            total = total * 10 + num;
        } 
    }
    return total -1;
    //
    // ===================================================
}

//  set the no_house_here marker for every position
//  in the array
/*
 * fill_with_no_houses
 *
 * Parameters: Two ints and a struct with said ints as their index
 * Returns:    Nothing  
 * Purpose:    To populate the given struct with empty houses
 * Notes:      
 * 
 */
void fill_with_no_houses(int rows, int cols, House all_houses[ROWS][COLS])
{
    // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
    // ===================================================
    //
    for (rows = 0; rows <= ROWS - 1; rows++) {
        for (cols = 0; cols <= COLS - 1; cols++) {
            all_houses[rows][cols].no_house_here = true;
        }
    }
    //
    // ===================================================
}

//  given a file with a count n at the top
//  read the count and then n lines of house data
//  into appropriate positions in the array
//
//   return true if file was successfully read
//          false if file could not be opened
/*
 * read_all_house_data
 *
 * Parameters: A string (filename) and a House struct (all_houses)
 * Returns:    True 
 * Purpose:    To populate the given struct with houses
 * Notes:      
 * 
 */
bool read_all_house_data(string filename, House all_houses[ROWS][COLS])
{
    // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
    // ===================================================
    //
    
    ifstream input_file;
    input_file.open(filename);
    
    if (not input_file.is_open()) {
        cerr << "fileread.cpp: could not open file: "
             << filename << endl;
        return 1;
    }
    int num_houses;
    input_file >> num_houses;
    
    for(int i = 0; i < num_houses; i++) {
        House a_house;
        a_house = read_one_house(input_file);
        all_houses[row_from_lot(a_house.lot_code)]
                  [col_from_lot(a_house.lot_code)] = a_house;
    }
    
    input_file.close();
    //
    // ===================================================

    return true;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - -
//   Functions for week 2 (ignore during week 1)
// - - - - - - - - - - - - - - - - - - - - - - - - - - -

/*
bool is_available(int house_id, House all_houses[ROWS][COLS])
{
    // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
    // ===================================================
    // 
    // YOUR CODE GOES HERE
    //
    // ===================================================

    (void)house_id;         // DELETE THIS LINE
    (void)all_houses;       // DELETE THIS LINE
    return false; // REPLACE THIS WITH WHAT YOU REALLY WANT TO RETURN!
}
*/


/*
int matching_houses(float max_price, string desired_color,
                    int desired_bedrooms, House all_houses[ROWS][COLS],
                    House results[ROWS * COLS])
{
    // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
    // ===================================================
    //
    // YOUR CODE GOES HERE
    //
    // ===================================================

    (void)max_price;        // DELETE THIS LINE
    (void)desired_color;    // DELETE THIS LINE
    (void)desired_bedrooms; // DELETE THIS LINE
    (void)all_houses;       // DELETE THIS LINE
    (void)results;          // DELETE THIS LINE
    return 0;  // REPLACE THIS WITH WHAT YOU REALLY WANT TO RETURN!
}
*/


/*
int num_neighbors(int house_id, House all_houses[ROWS][COLS])
{
    // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
    // ===================================================
    //
    // YOUR CODE GOES HERE
    //
    // ===================================================

    (void)house_id;         // DELETE THIS LINE
    (void)all_houses;       // DELETE THIS LINE
    return 0;  // REPLACE THIS WITH WHAT YOU REALLY WANT TO RETURN!
}
*/


/*
int rent_house(int house_id, House all_houses[ROWS][COLS])
{
    // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
    // ===================================================
    //
    // YOUR CODE GOES HERE
    //
    // ===================================================
    
    (void)house_id;         // DELETE THIS LINE
    (void)all_houses;       // DELETE THIS LINE
    return 0;  // REPLACE THIS WITH WHAT YOU REALLY WANT TO RETURN!
}
*/

// ============================================================
//     INCLUDE CS11 TESTING CODE
//
//   LEAVE THIS STATEMENT IN PLACE. IT MUST BE THE 
//   LAST LINE OF CODE IN YOUR housing.cpp FILE!
// ============================================================

#include "housing_hooks.hpp"
