


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
#include "ResistorList.h"
#include "Resistor.h"
class Node{
private:




    //new stuff
    int NodeID;
    Node* next;
    ResistorList r1;//object inside the ResistorList
    
    double voltage;
    bool setV;
    double min_iteration_change;
    
public:
    Node();
    ~Node();
    Node(int nodeID, Node* position);

    void print(int nodeIndex, int node1);

    //new member function

    
    ResistorList& get_resistorList();
    Node* get_next_node() const;
    int get_NodeID() const;
    void add_NodeID(int nodeID);
    void set_next_node(Node* r);
    void set_voltage(double volt_);
    void set_voltage_without_bool(double volt_);
    void unset_voltage();
    bool get_set_bool() const;
    void set_minimum_change(double min_change);
    double get_minimum_change() const;
    double get_voltage() const;

};

#endif  /* NODE_H */