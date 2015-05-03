#include "Resistor.h"

//
//  Resistor.cpp
//  check 111111
//
//  Created by Chuanrui Li on 2013-10-10.
//  Copyright (c) 2013 Chuanrui Li. All rights reserved.
//
 
 
 

#include <iomanip>
 
using namespace std;
 
Resistor::Resistor()//default
{
    resistance = 0;
    name = "";
    endpointNodeIDs[0] = 0;
    endpointNodeIDs[1] = 0;
}
 
 
Resistor::Resistor(string name_,double resistance_,int endpoints_[2])//constructor
{
    resistance = resistance_;
    name = name_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
    next = NULL;
//    cout << "new_resistor" << endl;
}


void Resistor::addResistor(int rIndex_, string name_,double resistance_,int endpoints_[2])//member function for initialize the array
{
    resistance = resistance_;
    name = name_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];

}


Resistor::~Resistor()
{
}
 
string Resistor::getName() const
{
    return name;
     
}
 
double Resistor::getResistance() const
{
    return resistance;
     
}
 
void Resistor::setResistance (double resistance_)
{
    resistance = resistance_;
}
 
void Resistor::print ()//for printing the node
{
    cout << fixed;
    cout << setw(20) << left << name << " ";
    cout << setw(8) << setprecision(2) << right << resistance;
    cout << " Ohms " << endpointNodeIDs[0] << " -> "<< endpointNodeIDs[1]<< endl;

}
 
void Resistor::print2()//different type of printing the node
{
    cout << fixed;
    cout  << "  "<< setw(20) << left << name << " ";
    cout << setw(8) << setprecision(2) << right <<  resistance;
    cout << " Ohms " << endpointNodeIDs[0] << " -> "<< endpointNodeIDs[1]<< endl;
}

void Resistor::print3()//insertR printing
{
     cout << "Inserted: resistor " + name + " " << resistance << " Ohms " << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
}

Resistor* Resistor::get_resistor_next() const
{
    return next;
}

void Resistor::set_next_resistor(Resistor* r)
{
    next = r;
}

Resistor* Resistor::set_next_resistor_and_return(Resistor* r)
{
    next = r;
}

int Resistor::get_NodeID(int nodeID)
{
    
    if(endpointNodeIDs[0] == nodeID)
    {
        return endpointNodeIDs[1];
    }
    else 
    {
        return endpointNodeIDs[0];
    }

}


