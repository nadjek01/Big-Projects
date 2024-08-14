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
bool is_available(int house_id, House all_houses[ROWS][COLS]);
int matching_houses(float max_price, string desired_color,
                       int desired_bedrooms, House all_houses[ROWS][COLS],
                       House results[ROWS * COLS]);
int num_neighbors(int house_id, House all_houses[ROWS][COLS]);
int rent_house(int house_id, House all_houses[ROWS][COLS]);


/*===============================================================
                   Additional Function Prototypes

        Write any additional function prototypes that you
        define here. You may not need any, or you may choose
        to write several
  ===============================================================*/
bool within_range(int i , int j);
void wloop_helper(House all_houses[ROWS][COLS]);
void a_helper(int house_id, House all_houses[ROWS][COLS]);
void m_helper(float price, string colour, int numrooms, 
              House all_houses[ROWS][COLS], House results[ROWS * COLS]);
void n_helper(int house_id, House all_houses[ROWS][COLS]);
int r_helper(int house_id, House all_houses[ROWS][COLS]);


//======================================================================
//                              main
//======================================================================

int main(int argc, char *argv[])
{
    House all_houses[ROWS][COLS];
    if(argc != 2) {
        cerr << "No enough arguments!" << endl;
        return 1;
    }
    string filename = argv[1];
    
    fill_with_no_houses(ROWS, COLS, all_houses);
    read_all_house_data(filename, all_houses);
    
    wloop_helper(all_houses);

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
    House house_one;
    input_file >> house_one.id;
    input_file >> house_one.lot_code;
    input_file >> house_one.price;
    input_file >> house_one.numrooms;
    input_file >> house_one.color;
    input_file >> house_one.is_available;
            
    house_one.no_house_here = false;
    
    return house_one;
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
    int num = lot[0] - 'A';
    return num;     
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
    int total = 0;
    for(size_t i = 0; i < lot.length(); i++) {
        if (lot[i] >= '0' and lot[i] <= '9') {
            int num = lot[i] - '0';
            total = total * 10 + num;
        } 
    }
    return total -1;
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
    for (rows = 0; rows <= ROWS - 1; rows++) {
        for (cols = 0; cols <= COLS - 1; cols++) {
            all_houses[rows][cols].no_house_here = true;
        }
    }    
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
    return true;
}



/*
 * is_available
 *
 * Parameters: An int (house_id) and an array (all_houses)
 * Returns:    True 
 * Purpose:    To find if a house is available based on the user input of id
 * Notes:      
 * 
 */
bool is_available(int house_id, House all_houses[ROWS][COLS])
{
    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < COLS; c++) {
            if(house_id == all_houses[r][c].id) {
                if(all_houses[r][c].is_available == "available") {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    return false;
}

/*
 * int matching_houses
 *
 * Parameters: A float (max_price), a string (desired_color), 
              an int (desired_bedrooms), and 2 arrays
 * Returns:    An int  
 * Purpose:    To find a house that matches the parameters the user inputs
 * Notes:      
 * 
 */
int matching_houses(float max_price, string desired_color,
                    int desired_bedrooms, House all_houses[ROWS][COLS],
                    House results[ROWS * COLS])
{
    int count_house = 0;
    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < COLS; c++) {
            if(max_price >= all_houses[r][c].price) {
                if(desired_color == all_houses[r][c].color) {
                    if(desired_bedrooms <= all_houses[r][c].numrooms) {
                        results[count_house] = all_houses[r][c];
                        count_house++;
                    }
                }
            }
            
        }
    }
    return count_house; 
}

/*
 * int num_neighbors
 *
 * Parameters: An int (house_id) and a struct of houses (all_houses)
 * Returns:    An int  
 * Purpose:    To find if there are any neighbours and return that number
 * Notes:      
 * 
 */
int num_neighbors(int house_id, House all_houses[ROWS][COLS])
{
    int num_neighbors = 0;
    
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(all_houses[i][j].id == house_id) {
                for(int k = i - 1; k <= i + 1; k++) {
                    for(int l = j - 1; l <= j + 1; l++) {
                        if(within_range(k, l) == true) {    
                            if(all_houses[k][l].is_available == "booked") {
                                   num_neighbors++;
                            }
                        }
                    }
                }
            }
        }
    }
    return num_neighbors;
}

/*
 * bool within_range
 *
 * Parameters: Two ints (i, j)
 * Returns:    True or false  
 * Purpose:    To find if i and j are within the range of houses looked at
               (checks for edge cases)
 * Notes:      
 * 
 */
bool within_range(int i , int j) {
    
    if(i < 0 or j < 0 or i > 50 or j > 20) {
        return false;
    }
    return true; 
} 

/*
 * int rent_house
 *
 * Parameters: An int (house_id) and a struct (all_houses)
 * Returns:    An int  
 * Purpose:    To find if a house is available to rent and return 0,1,2
               if it can be rented, cant be rented or the house DNE
 * Notes:      
 * 
 */
int rent_house(int house_id, House all_houses[ROWS][COLS])
{
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(house_id == all_houses[i][j].id) {
                if(all_houses[i][j].is_available == "available") {
                    all_houses[i][j].is_available = "booked";
                    return 1;
                } else if (all_houses[i][j].is_available == "booked") {
                    return 2;
                }
            }
        }
    }
    return 0;
}

/*
 * void wloop_helper
 *
 * Parameters: Two ints (id, numroom), two strings (funct, colour), 
               a float (price), a house struct (results)
 * Returns:    N/A 
 * Purpose:    To execute a while loop
 * Notes:      
 * 
 */
void wloop_helper(House all_houses[ROWS][COLS]) {
    
    int id, numrooms;
    string funct, colour;
    float price;
    House results[ROWS * COLS];
    while (funct != "q") {
        cout << "query-> ";
        cin >> funct;
        if(funct == "a") {
            cin >> id;
            a_helper(id, all_houses);
        } else if(funct == "m") {
            cin >> price >> colour >> numrooms;
            m_helper(price, colour, numrooms, 
                     all_houses, results);
        } else if(funct == "n") {
            cin >> id;
            n_helper(id, all_houses);
        } else if(funct == "r") {
            cin >> id;
            int r_rent = r_helper(id, all_houses);
            if(r_rent == 1) {
                return;
            }
        } else if(funct == "q") {
            return;
        } else {
            cout << "Unknown command " << funct << endl; 
        }
    }
}

/*
 * void a_helper
 *
 * Parameters: An int (house_id)
 * Returns:    N/A 
 * Purpose:    To execute the is_available function from user input
 * Notes:      
 * 
 */
void a_helper(int house_id, House all_houses[ROWS][COLS]) {
    
    bool r_val = is_available(house_id, all_houses);
    if(r_val == true) {
        cout << "House " << house_id << " is " << 
        "available" << endl;
    } else if (r_val == false) {
        cout << "Sorry, House " << house_id << " is " << 
        "not available" << endl;
    }
}

/*
 * void m_helper
 *
 * Parameters: A float (price), a string (colour), and an int (numrooms)
 * Returns:    N/A
 * Purpose:    To execute the matching_houses function from user input
 * Notes:      
 * 
 */
void m_helper(float price, string colour, int numrooms, 
              House all_houses[ROWS][COLS], House results[ROWS * COLS]) {
    
    int rcount = matching_houses(price, colour, numrooms, 
                                 all_houses, results);
    cout << "Matching Houses: " << endl;
    for(int i = 0; i < rcount; i++) {
        print_house(results[i]);
    }
}

/*
 * void n_helper
 *
 * Parameters: An int (house_id)
 * Returns:    N/A
 * Purpose:    To execute the num_neighbors function from user input
 * Notes:      
 * 
 */
void n_helper(int house_id, House all_houses[ROWS][COLS]) {
    
    int r_neighbors = num_neighbors(house_id, all_houses);
    if(r_neighbors == 0) {
        cout << "You have no neighbors, practice your drums!" << endl;
    } else {
        cout << "You have " << r_neighbors << " neighbors!" << endl;
    }
    
}

/*
 * void r_helper
 *
 * Parameters: An int (house_id)
 * Returns:    N/A
 * Purpose:    To execute the rent_house function from user input
 * Notes:      
 * 
 */
int r_helper(int house_id, House all_houses[ROWS][COLS]) {
    
    int r_rent = rent_house(house_id, all_houses);
    if(r_rent == 0) {
        cout << "You can't rent a house that ";
        cout << "doesn't exist, but good try" << endl;
        return r_rent;
    } else if(r_rent == 1) {
        cout << "Congrats, you rented a house! ";
        cout << "Hope your door knobs don't fall off" << endl;
        return r_rent;
    } else if(r_rent == 2) {
        cout << "Too late...I hear the dumpster ";
        cout << "behind hill has some spaces open" << endl;
        return r_rent;
    }
    return 0;
} 


#include "housing_hooks.hpp"
