/*
 * Collin Tran
 * ctt200001
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

class LinkedList {
    public:
        //default constructor
        LinkedList(){
            head = nullptr;
            tail = nullptr;
        }
        //constructor if a node is passed in
        LinkedList(Node n){
            head = &n;
            tail = &n;
        }
        //return pointer head
        Node* getHead() const {
            return head;
        }
        //set pointer head to h
        void setHead(Node* h) {
            head = h;
        }
        //return pointer tail
        Node* getTail() const {
            return tail;
        }
        //set pointer tail to t
        void setTail(Node* t) {
            tail = t;
        }
        //~LinkedList();
        void append(Node* n);
        void search(std::string command);
        void sort(std::string order);
        Node* removeNode(Node* curr);
        friend std::ostream& operator<<(std::ostream &out, const LinkedList &l);
        
    private:
        //the beginning of the list
        Node* head;
        //the end of the list
        Node* tail;
};
#endif