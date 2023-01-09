/*
 * Collin Tran
 * ctt200001
 */
#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <iostream>

class Driver {
    public:
        //default constructor
        Driver(){}
        //constructor if a driver name is passed
        Driver(std::string name){
            driverName = name;
        }
        Driver(std::string name, double a){
            driverName = name;
            area = a;
        }
        //returns double area
        double getArea() const {
            return area;
        }
        //sets double area to a
        void setArea(double a) {
            area = a;
        }
        //returns string driverName
        std::string getName() const {
            return driverName;
        }
        //sets string driverName to d
        void setName(std::string d) {
            driverName = d;
        }
        //returns the value of the static variable
        int getStatic() const {
            return howCompare;
        }
        //changes the value of the static variable
        void setStatic(int s) {
            howCompare = s;
        }
        friend std::ostream& operator<<(std::ostream &out, const Driver &d);
        bool operator<(Driver d);
        bool operator>(Driver d);
        
    private:
        std::string driverName;
        double area;
        //determines how to sort the list; 0 if sorting by name, 1 if sorting by area
        static int howCompare;
};
#endif