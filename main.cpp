/*
 * Collin Tran
 * ctt200001
 */
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>

#include "Driver.h"
#include "Node.h"
#include "LinkedList.h"

using namespace std;

//function prototypes
Node* makeNode(stringstream&, string);
double calculateArea(stringstream&);
bool driverValid(string n, string c);
bool commandValid(string c);

/* The function determines if a line from the driver file is valid
 * Valid lines contain valid names and coordinates
 * A name is valid if it only contains alphanumeric characters, spaces, -, and '
 * If a name is invalid, false is returned
 * Valid coordinates must contain commas, otherwise false is returned
 * False is also returned if a coordinate has more than one -, more than one ., and more than one comma
 * Valid coordinates can only contain numbers, commas, ., and -
 * For the coordinates to be valid, the first and last coordinate pairs must be the same, false is returned otherwise
 * If all conditions are true, true is returned
 */
bool driverValid(string n, string c) {
    string name = "";
    string coords = "";
    string first = "";
    string last = "";
    string term = "";
    int hasNum = 0;
    stringstream ss(n);
    stringstream cc(c);
    
    //checks if the coordinates are separated by one space
    int index = (int)c.size() - 1;
    while(isspace(c.at(index))){
        c.erase(index);
        index--;
    }
    for(int i = 0; i < (int)c.size() - 1; i++){
        if(isspace(c.at(i))) {
            if(isspace(c.at(i + 1))) {
                return false;
            }
        }
    }
    
    
    
    //check if the name only contains valid characters
    //valid characters are alphanumeric characters, spaces, -, and '
    while(ss >> name){
        for(int i = 0; i < (int)name.size(); i++){
            if(!isalpha(name.at(i)) && !isdigit(name.at(i)) && !isspace(name.at(i)) && name.at(i) != '-' && name.at(i) != '\'') {
                return false;
            }
        }
    }
    //checks to see if there are coordinate pairs, since every pair has a comma
    if(c.find(',') == string::npos){
        return false;
    }
    //loops until all coordinates have been checked
    while(cc >> coords) {
        //sets first to the first coordinate pair
        if(first == ""){
            first = coords;
        }
        //checks if coord has a comma
        if(coords.find(',') == string::npos){
            return false;
        }
        //checks if coord only has one comma
        if(coords.find(',') != coords.rfind(',')){
            return false;
        }
        //checks to see if coordinate pairs only contain valid characters
        for(int i = 0; i<(int)coords.size(); i++){
            if(!isdigit(coords.at(i)) && coords.at(i) != ',' && coords.at(i) != '-' && coords.at(i) != '.') {
                return false;
            }    
        }
        //gets the last coordinate pair
        last = coords;
        
        //checks if the x coordinate exists
        term = coords.substr(0, coords.find(','));
        for(int i = 0; i < (int)term.size(); i++){
            if(isdigit(term.at(i))){
                hasNum = 1;
            }
        }
        if(hasNum == 0){
            return false;
        }
        //checks to see if x and y terms of coordinate pair have a max of 1 . or -
        if((term.find('.') != term.rfind('.')) || (term.find('-') != term.rfind('-'))){
            return false;
        }
        
        //checks if there is a - that is in the middle of the number
        for(int i = 1; i < (int)term.size(); i++){
            if(!isdigit(term.at(i)) && term.at(i) != '.'){
                return false;
            }
        }
        
        coords.erase(0, coords.find(',') + 1);
        term = coords.substr(0, coords.size());
        hasNum = 0;
        
        //checks to see if the y coordinate exists
        for(int i = 0; i < (int)term.size(); i++){
            if(isdigit(term.at(i))){
                hasNum = 1;
            }
        }
        if(hasNum == 0){
            return false;
        }
        //checks to see if x and y terms of coordinate pair have a max of 1 . or -
        if((term.find('.') != term.rfind('.')) || (term.find('-') != term.rfind('-'))){
            return false;
        }
        
        //checks if there is a - that is in the middle of the number
        for(int i = 1; i < (int)term.size(); i++){
            if(!isdigit(term.at(i)) && term.at(i) != '.'){
                return false;
            }
        }
        
        hasNum = 0;
    }
    
    //checks if the first and last coordinate pair are the same 
    if(first != last){
        return false;
    }
    //return true if all conditions are true
    return true;
}

/* The function checks to see if a command line out of the command file is valid
 * If the command begins with sort, "sort" must be followed by area/driver and then asc/des
 * If so, true is returned, otherwise false is returned
 * If the command is not sort, the function checks validity depending on if the command is a name or number
 * If the command contains a letter, it is assumed to be a name, otherwise, it is assumed to be a number
 * Valid names can contain alphanumeric characters, spaces, -, and '
 * Valid numbers can contain only numbers, less than one -, and less than one .
 * Invalid numbers result in a false return, otherwise the function returns true
 */
bool commandValid(string c) {
    string command = "";
    stringstream ss(c);
    ss >> command;
    //if the command is sort
    if(command == "sort"){
        ss >> command;
        //if sort isn't followed by area or driver, return false
        if(command != "area" && command != "driver"){
            return false;
        }
        else {
            //if area/driver isn't followed by asc or des, return false
            ss >> command;
            if(command != "asc" && command != "des"){
                return false;
            }
            else {
                //if asc/des isn't the final command, return false
                if(ss >> command) {
                    return false;
                }
                //if all are conditions are true, return true
                else {
                    return true;
                }
            }
        }
    }
    else {
        command = c;
        //loop checks for if there is a letter in the command
        //if so, it checks if it's a valid name
        for(int i = 0; i < (int)command.size(); i++){
            //if the command contains a letter, it's a name
            if(isalpha(command.at(i))){
                for(int k = 0; k < (int)command.size(); k++){
                    if(!isalpha(command.at(k)) && !isdigit(command.at(k)) && !isspace(command.at(k)) && command.at(k) != '-' && command.at(k) != '\''){
                        return false;
                    }
                }
                return true;
            }
        }
        
        //at this point, command is assumed to be a number
        //returns false if the number has more than one .
        if(command.find('.') != command.rfind('.')){
            return false;
        }
        //returns false if the number has more than one -
        if(command.find('-') != command.rfind('-')){
            return false;
        }
        //loop to check if the command is a valid number starts if the name loop finishes without returning anything
        for(int i = 0; i < (int)command.size(); i++){
            //if there is a space in the number, return false
            if(isspace(command.at(i))){
                return false;
            }
            else if(!isdigit(command.at(i)) && command.at(i) != '-' && command.at(i) != '.') {
                return false;
            }
        }
        return true;
    }
}

/* The function calculates the area of the driver's path using the formula 
 * 1/2 * |summation of all the coordinates|
 * The function returns the calculated area
 */
double calculateArea(stringstream& s){
    double inix, iniy, currentX, currentY, x1, y1;
    string coords = "";
    
    //puts the first set of coordinates into inix and iniy
    s >> coords;
    inix = stod(coords.substr(0, coords.find(',')));
    coords.erase(0, coords.find(',') + 1);
    iniy = stod(coords.substr(0, coords.size()));
    
    //puts the second pair of coordinates into currentX and currentY
    s >> coords;
    currentX = stod(coords.substr(0, coords.find(',')));
    coords.erase(0, coords.find(',') + 1);
    currentY = stod(coords.substr(0, coords.size()));

    //performs (xi+1 + xi) * (yi+1 + yi) and adds the product to double sum, repeats for every coordinate pair for a specific driver
    //stops when the loop reaches a coordinate pair that is the same as the first one, which every coordinate row ends with
    //after the loop is done, the absolute value of sum is halved and returned
    double sum = (currentX + inix) * (currentY - iniy);
    while ((fabs(currentX - inix) > 0.0001) || (fabs(currentY - iniy) > 0.0001)) {
        //puts next pair of coordinates into x1 and y1 while the current set of coordinates
        //doesn't equal the first set
        s >> coords;
        x1 = stod(coords.substr(0, coords.find(',')));
        coords.erase(0, coords.find(',') + 1);
        y1 = stod(coords.substr(0, coords.size()));
        
        //does equation then sets 'current' values to '1' values
        sum += (x1 + currentX) * (y1 - currentY);
        currentX = x1;
        currentY = y1;
    }
    return (.5 * fabs(sum));
}

/*
 * Creates a new Node pointer
 * Calls calculate area in order to get the driver's area
 * Creates new driver using the driver's name and the area calculated
 * Passes the driver to the node pointer and returns the pointer
 */
Node* makeNode(stringstream& s, string name){
    double area = calculateArea(s);
    Driver d(name, area);
    Node* n = new Node(d);

    return n;
}

/* If the driver file opens, a Node is created for every driver in the file
 * Every node contains the driver's name and the area of their path
 * The first node created is passed into the linked list as the head and tail
 * Every subsequent node is appended to the list, the last one being the new tail
 * Once complete, the driver file closes and the command file is opened
 * If the command file is opened, a command is read from the file until there are no commands
 * If the command is to sort, the file is sorted ascending/descending based on name or area
 * Once the list is sorted, the list is printed
 * Otherwise, the list is searched for a name or area
 * If the value is found, the driver's name and area are printed
 * Otherwise, the function prints that the value wasn't found
 */
int main()
{
    LinkedList list;
    Driver d;
    string routeInfo = "";
    string drivername = "";
    string c = "";
    string command = "";
    string driverfile = "";
    string commandfile = "";
    //open the driver file
    ifstream inFS;
    cin >> driverfile;
    inFS.open(driverfile);
    //inFS.open("pilot_routes1.txt");
    if(inFS.is_open()) {
        //while a line can still be obtained from the file, and that line isn't whitespace
        while (getline(inFS, routeInfo) && !(isspace(routeInfo.at(0)))) {
            //passes the name of the driver into drivername, works only if the first coordinate has a comma
            drivername = routeInfo.substr(0, routeInfo.find(','));
            drivername = drivername.substr(0, drivername.rfind(' '));
            routeInfo.erase(0, (int)drivername.size() + 1);
            //check for line validity, continue if valid, otherwise line is ignored
            if(driverValid(drivername, routeInfo)){
                //check for validity right here
                stringstream ss(routeInfo);
                //passes drivername and stringstream to madeNode function, which creates the node
                Node* n = makeNode(ss, drivername);
                //appends the created node to the linkedlist
                list.append(n);
            }
        }
    }
    //close the driver file and print the list
    inFS.close();
    cout << list << endl;
    
    //open the command file
    cin >> commandfile;
    inFS.open(commandfile);
    if(inFS.is_open()) {
        //while a line can still be obtained from the file, and the line isn't whitespace
        while (getline(inFS, c) && !(isspace(c.at(0)))){
            //check for command line validity, continue if command line is valid, otherwise line is ignored
            if(commandValid(c)){
                stringstream ss(c);
                ss >> command;
                //if the command is sort
                if(command == "sort"){
                    ss >> command;
                    //if the list is to be sorted by driver
                    if(command == "driver") {
                        //change the static variable to 0
                        d.setStatic(0);
                        //sort the list then print
                        ss >> command;
                        list.sort(command);
                        cout << list << endl;
                    }
                    //if the list is to be sorted by area
                    else if(command == "area") {
                        //change the static variable to 1
                        d.setStatic(1);
                        //sort the list then print
                        ss >> command;
                        list.sort(command);
                        cout << list << endl;
                    }
                }
                else{
                    command = c;
                    for(int i = 0; i < (int)command.size(); i++){
                        //if the command is a name, set the static variable to 0 and search the list for the name
                        if(isalpha(command.at(i))) {
                            d.setStatic(0);
                            list.search(command);
                            break;
                        }
                        //if the command is a number, set the static variable to 1 and search the list for the num
                        //make sure to change if statement, part of line validation
                        //check for if the command is specifically a number, else return?
                        else if(i == (int)command.size() - 1) {
                            d.setStatic(1);
                            list.search(command);
                        }
                    }    
                }
            }
        }
    }
    //close the command file
    inFS.close();
    //delete list;
    return 0;
}
