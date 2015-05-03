


//
//  Node.h
//  check 111111
//
//  Created by Chuanrui Li on 2013-10-10.
//  Copyright (c) 2013 Chuanrui Li. All rights reserved.

//


#ifndef NODE_H
#define NODE_H

#define MAX_RESISTORS_PER_NODE 5
#include <iostream>


using namespace std;

class Node {
private:

    int numRes; // number of resistors currently connected
    int resIDArray[MAX_RESISTORS_PER_NODE]; // stores the index of each resistor connected


    //new stuff
    int NodeID;
    Node* next;
    ResistorList r1;//object inside the ResistorList

public:
    Node();
    ~Node();

    int getnumRes() const;
    // Updates resIDArray to show the resistor in position rIndex in
    // the resistor array is now connected to this node.
    // Returns true if successful

    void clear_node_array();
    bool addResistor(int rIndex);

    int getresIDArray(int res_index) const;
    // prints the whole node
    // nodeIndex is the position of this node in the node array.
    void print(int nodeIndex);

    //new member function

    ResistorList get_resistorList() const;
    Node* get_next_node() const;
    int get_NodeID() const;
    void add_NodeID(int nodeID);
    void set_next_node(Resistor* r);

};

#endif  /* NODE_H */