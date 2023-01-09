/*
 * Collin Tran
 * ctt200001
 */
#include "Node.h"
#include "Driver.h"

#include <iostream>
#include <string>
#include <cmath>

//the information of the driver is returned
std::ostream& operator<<(std::ostream &out, const Node &n){
    out << n.driver;
    return out;
}

/* The function determines wheter two nodes are equal or not depending on area or name
 * If the static variable is 0, names are checked
 * If the static variable is 1, areas are checked
 * If two nodes are equal, true is returned
 * Otherwise, false is returned
 */
bool Node::equal(std::string command) {
    //compares nodes based on names
    if(driver.getStatic() == 0){
        std::string n = driver.getName();
        std::string c = command;
        //if the name in the node is the same as the specified name return true
        if(driver.getName() == command){
            return true;
        }
        //otherwise, return false
        else {
            return false;
        }
    }
    //compares nodes based on areas
    else {
        //if the area in the node is the same as the specified area return true
        if(fabs(driver.getArea() - std::stod(command)) < 0.01){
            return true;
        }
        //otherwise return false
        else{
            return false;
        }
    }
}

/* The function determines whether this node is less than the specified node
 * The function makes the comparison based on name or area
 * If the static variable is 0, names are checked
 * If the static variable is 1, areas area checked
 * If this node is less than the specified one, return true
 * Otherwise, return false
 */
bool Node::operator< (Node n) {
    //compares names
    if(driver.getStatic() == 0){
        //returns true if this name is comes before the specified name alphabetically 
        //otherwise, returns false
        //call to driver overloaded operator
        return driver.getName() < n.driver.getName();
    }
    //compares areas
    else if(driver.getStatic() == 1) {
        //returns true if this area is less than the specified area
        //otherwise, returns false
        //call to driver overloaded operator
        return driver.getArea() < n.driver.getArea();
    }
    //prevents warning
    return false;
}

/* The function determines whether this node is greater than the specified node
 * The function makes the comparison based on name or area
 * If the static variable is 0, names are checked
 * If the static variable is 1, areas area checked
 * If this node is greater than the specified one, return true
 * Otherwise, return false
 */
bool Node::operator> (Node n) {
    //compares names
    if(driver.getStatic() == 0){
        //returns true if this name comes after the specified name alphabetically
        //otherwise, returns false
        //call to driver overloaded operator
        return driver.getName() > n.driver.getName();
    }
    //compares areas
    else if(driver.getStatic() == 1) {
        //returns true if this area is greater than the specified area
        //otherwise, returns false
        //call to driver overloaded operator
        return driver.getArea() > n.driver.getArea();
    }
    //prevents warning
    return false;
}