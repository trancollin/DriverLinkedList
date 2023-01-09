/*
 * Collin Tran
 * ctt200001
 */
#ifndef NODE_H
#define NODE_H

#include "Driver.h"

#include <iostream>

class Node {
    public:
        //default constructor
        Node(){}
        //constructor for if driver d is passed
        Node(Driver d) {
            driver = d;
        }
        //returns next pointer
        Node* getNext() const {
            return next;
        }
        //sets pointer next to n
        void setNext(Node* n) {
            next = n;
        }
        //returns pointer prev
        Node* getPrev() const{
            return prev;
        }
        //sets pointer prev to p
        void setPrev(Node* p) {
            prev = p;
        }
        bool equal(std::string command);
        friend std::ostream& operator<<(std::ostream &out, const Node &n);
        bool operator< (Node n);
        bool operator> (Node n);
        
    private:
        //next value is used to traverse to a node after the current node
        Node* next;
        //prev value is used to traverse to a node before the current node
        Node* prev;
        Driver driver;
};

#endif