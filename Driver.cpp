/*
 * Collin Tran
 * ctt200001
 */
#include "Driver.h"

#include <iostream>
#include <iomanip>
#include <cmath>


//Prints out the driver's name, tab, area, newline
//The area is printed up to two decimals
//A tab separates the driver name and area
//Ostream containing the driver's information is returned
std::ostream& operator<<(std::ostream &out, const Driver &d){
    out << std::fixed << std::setprecision(2) << d.driverName << '\t' << d.area << std::endl;
    return out;
}

//declares the static variable
int Driver::howCompare = 0;

/* The function determines whether this driver's is less than a specified driver
 * The decision is made based on area or name, which can be specified using the static variable
 * If static variable is 0, compare names
 * If static varialbe is 1, compare areas
 * If comparing area, returns true if this driver's area is less than d's area, false otherwise
 * If comparing name, returns true if this driver's name comes before d's name, false otherwise
 */
bool Driver::operator<(Driver d){
    //compares names
    if (howCompare == 0){
        //returns true if this name is comes before the specified name alphabetically 
        //otherwise, returns false
        if(driverName < d.driverName){
            return true;
        }
        else {
            return false;
        }
    }
    //compares areas
    else if (howCompare == 1){
        //if two areas are the same, return false
        if(fabs(area - d.area) < 0.001){
            return false;
        }
        //returns true if this area is less than the specified area
        //otherwise, returns false
        else if(area < d.area) {
            return true;
        }
        else {
            return false;
        }
    }
    //prevents warning
    return false;
}
/* The function determines whether this driver's is greater than a specified driver
 * The decision is made based on area or name, which can be specified using the static variable
 * If static variable is 0, compare names
 * If static varialbe is 1, compare areas
 * If comparing area, returns true if this driver's area is greater than d's area, false otherwise
 * If comparing name, returns true if this driver's name comes after d's name, false otherwise
 */
bool Driver::operator>(Driver d){
    if (howCompare == 0){
        //returns true if this name comes after the specified name alphabetically
        //otherwise, returns false
        if(driverName > d.driverName){
            return true;
        }
        else {
            return false;
        }
    }
    else if (howCompare == 1){
        //if two areas are the same, return false
        if(fabs(area - d.area) < 0.001){
            return false;
        }
        //returns true if this area is greater than the specified area
        //otherwise, returns false
        else if(area > d.area) {
            return true;
        }
        else {
            return false;
        }
    }
    //prevents warning
    return false;
}
