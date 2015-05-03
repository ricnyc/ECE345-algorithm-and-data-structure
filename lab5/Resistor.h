
//
//  Resistor.h
//  check 111111
//
//  Created by Chuanrui Li on 2013-10-10.
//  Copyright (c) 2013 Chuanrui Li. All rights reserved.
//
 
//question
//1, rindex add to be private part
 
#ifndef RESISTOR_H
#define RESISTOR_H
 
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
//extern   Resistor resistor_array;
//extern   Node *node_array[];
//extern   Resistor * resistor_array[];
class Resistor
{
private:
    
    double resistance; // resistance (in Ohms)
    string name; // C++ string holding the label
    int endpointNodeIDs[2]; // IDs of nodes it attaches to
    //there are only two elements inside the array, one is endpointNodeIDs[0], endpointNodeIDs[1]
    
    Resistor *next; 
public:
     
    Resistor();
    Resistor(string name_,double resistance_,int endpoints_[2]);
    // rIndex_ is the index of this resistor in the resistor array
    // endpoints_ holds the node indices to which this resistor connects
    
    void addResistor(int rIndex_, string name_,double resistance_,int endpoints_[2]);
    ~Resistor();
     
    string getName() const; // returns the name
    double getResistance() const; // returns the resistance
     
    void setResistance (double resistance_);
    
    // you *may* create either of the below to print your resistor
    void print ();
    void print2();//having two space before
    void print3();//print  the insert resistor
    friend ostream& operator<<(ostream&,const Resistor&);
    
    //new stuff
    Resistor* get_resistor_next() const;
    void set_next_resistor(Resistor* r);
    Resistor* set_next_resistor_and_return(Resistor* r);
    int get_NodeID(int nodeID);
};
#endif  
