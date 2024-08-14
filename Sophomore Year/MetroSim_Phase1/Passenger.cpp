/*
 *
 */

#include <iostream>
#include <string>
#include "Passenger.h"

/*
 * Remember to write a complete function contract here!
 */
void Passenger::print(std::ostream &output)
{
        output << "[" << id << ", " << from << "->" << to << "]";
}
