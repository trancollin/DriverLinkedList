/*
 * Collin Tran
 * ctt200001
 */
#include "LinkedList.h"
#include <iostream>
#include <string>
#include "Node.h"

/*LinkedList::~LinkedList(){
    while(head){
        Node* n = head->getNext();
        delete head;
        head = n;
    }
}*/


/* The function prints out the list
 * The list is traversed and every node is printed
 * An ostream containing all of the driver's is returned
 */
std::ostream& operator<<(std::ostream &out, const LinkedList &l){
    Node* currentNode;
    currentNode = l.getHead();
    //the list traverses from the head of the list 
    while(currentNode != nullptr){
        //the value of the node is added to the ostream
        out << *(currentNode);
        //current node is incremented
        currentNode = currentNode->getNext();
    }
    return out;
}

/* The function adds a node to the end of the list
 * The function adds a node whether or not the list is empty
 */
void LinkedList::append(Node* n) {
    //if the list is empty, the head and tail value of the list is set to the node
    if(head == nullptr) {
        head = n;
        tail = n;
    }
    //otherwise, the next value of the tail is set to the node
    //the previous value of the node is set to tail
    //the tail of the list is then set to the node
    else {
        tail->setNext(n);
        n->setPrev(tail);
        tail = n;
    }
}
/* The function searches for a specified value in the list
 * The value can be a driver name or a driver's area
 * If the value is found, the driver's information is printed
 * Otherwise, the function prints that the value wasn't found
 */
void LinkedList::search(std::string command) {
    bool match = false;
    Node* currentNode;
    currentNode = head;
    std::string c = command;
    
    //the list is traversed until the end is reached
    while(currentNode != nullptr) {
        //if a match in the list is found, the driver's info is printed
        match = currentNode->equal(command);
        if(match == true){
            std::cout << *(currentNode);
            break;
        }
        currentNode = currentNode->getNext();
    }
    //if the search reached the end of the list without finding a match
    //the function prints that the value wasn't found
    if(currentNode == nullptr) {
        std::cout << command << " not found " << '\n' << '\n';
    }
}

/* The function removes a specified node from the list
 * The function performs different actions depending on whether the node 
 * specified for removal is at the beginning, middle, or end of the list
 * The node that has been removed is returned
 */
Node* LinkedList::removeNode(Node* curr){
    Node* hold;
    Node* current = head;
    //if the list is empty, return a null pointer
    if(head == nullptr) {
        return nullptr;
    }
    /*
    //if there is only one node in the list, the node is removed and returned
    else if(head->getNext() == nullptr){
        head = nullptr;
        return head;
    }*/
    //if the node to be removed is at the beginning of the list
    else if(head == curr) {
        //the head node is set to the second node in the list, and the former head node
        //is disconnected from the list
        head = head->getNext();
        head->setPrev(nullptr);
        current->setNext(nullptr);
        return current;
    }
    //if the node to be removed is at the end of the list
    else if(tail == curr) {
        //the tail node is set to the second to last node in the list, and the former
        //tail node is disconnected from the list
        tail = tail->getPrev();
        tail->setNext(nullptr);
        current->setPrev(nullptr);
        return tail;
    }
    //if the node to be removed is in the middle of the list
    //the search stops at the node before the one that is supposed to be removed
    else {
        //the list is traversed until the end of the list is reached
        while(current->getNext() != nullptr){
            //if the node to be removed is found
            if(current->getNext() == curr) {
                //the node is held in a holder pointer
                hold = current->getNext();
                //the current node's next value is set to the node after the one to be removed
                current->setNext(current->getNext()->getNext());
                //the prev value of the node after the one to be removed is set to the current node
                current->getNext()->setPrev(current);
                //the node to be removed is disconnected from the list
                hold->setNext(nullptr);
                hold->setPrev(nullptr);
                return hold;
            }
            //increments current node so the list can be traversed
            current = current->getNext();
        }
    }
    //if the node to be removed isn't in the list, return null 
    return nullptr;
}
/* The function sorts the linkedlist depending on user specifications if the list isn't empty
 * The list can be sorted either in ascending or descending order
 * The list is sorted based on either area or driver name
 * If the list is sorted in asc order by area, the smallest area is first
 * If the list is sorted in des order by area, the largest area is first
 * If the list is sorted in asc order by name, the list is sorted in alphabetical order
 * If the list is sorted in des order by name, the list is sorted in reverse alphabetical order
 * An insertion sorting algorithm is used
 */
void LinkedList::sort(std::string order){
    //the list is sorted if the list isn't empty
    if(head != nullptr) {
        //if the list is to be sorted in ascending order
        if (order == "asc") {
            //current is set to the node after the head node
            Node* current = head->getNext();
            //loops while current hasn't reached the end of the list
            while (current != nullptr){
                Node* next = current->getNext();
                Node* search = current->getPrev();
                //search moves towards the beginning of the list until it finds a value less than current
                while (search != nullptr && (*search > *current)) {
                    search = search->getPrev();
                }
                //the current node is removed
                removeNode(current);
                //if the search pointer reached the beginning and found no value less than current, 
                //the current node is sent to the beginning
                if (search == nullptr) {
                    current->setPrev(nullptr);
                    current->setNext(head);
                    head->setPrev(current);
                    head = current;
                }
                //if the search pointer found a value less than current, the current node is placed after it.
                else {
                    //if the search node is at the end of the list
                    if(search == tail){
                        search->setNext(current);
                        current->setNext(nullptr);
                        current->setPrev(search);
                        tail = current;
                    }
                    //if the search node is in the middle of the list
                    else {
                        current->setNext(search->getNext());
                        search->setNext(current);
                        current->setPrev(current->getNext()->getPrev());
                        current->getNext()->setPrev(current);
                    }
                }
                //current is set to the node that was after it
                current = next;
            }
        }
        //if the list is to be sorted in descending order
        else if (order == "des") {
            //current is set to the node right before the tail node
            Node* current = tail->getPrev();
            //loops while current hasn't reached the beginning of the list
            while (current != nullptr){
                Node* prev = current->getPrev();
                Node* search = current->getNext();
                //search moves towards the end of the list until a value larger than current has been found
                while (search != nullptr && (*search > *current)) {
                    search = search->getNext();
                }
                //removes the current node
                removeNode(current);
                //if the search pointer reaches the end of the list and found no value less than current,
                //the current node is sent to the end
                if (search == nullptr) {
                    current->setNext(nullptr);
                    current->setPrev(tail);
                    tail->setNext(current);
                    tail = current;
                }
                //if the search pointer found a value less than current, the current node is placed before it.
                else {
                    //if the search node is at the beginning of the list
                    if(search == head) {
                        search->setPrev(current);
                        current->setPrev(nullptr);
                        current->setNext(search);
                        head = current;
                    }
                    //if the search node is in the middle of the list
                    else {
                        current->setPrev(search->getPrev());
                        search->setPrev(current);
                        current->setNext(current->getPrev()->getNext());
                        current->getPrev()->setNext(current);
                    }
                }
                //current is set to the node that was before it
                current = prev;
            }
        }
    }
}


