
	
//
//  Node.cpp
//  check 111111
//
//  Created by Chuanrui Li on 2013-10-10.
//  Copyright (c) 2013 Chuanrui Li. All rights reserved.
//
 
 
#include "Node.h"
#include "Resistor.h"
using namespace std;
 

Node::Node()
{
    numRes = 0;
    for (int i = 0; i < MAX_RESISTORS_PER_NODE; i++)
    {
        resIDArray[i] = 0;
    }
}

Node::~Node()
{

}

 
int Node::getnumRes() const//get the number of resistors inside each node
{
    return numRes;
}

void Node::clear_node_array()
{
        numRes = 0;
    for (int i = 0; i < MAX_RESISTORS_PER_NODE; i++)
    {
        resIDArray[i] = 0;
    }
}

int Node::getresIDArray(int res_index) const//return the resistor index
{
    return resIDArray[res_index];
}


bool Node::addResistor (int rIndex)
{
    resIDArray[numRes] = rIndex;
    numRes++;//increment the node number inside 
    return true;
}
 
void Node::print (int nodeIndex)
{
    cout << "Connections at node " <<  nodeIndex << ": " << numRes <<  " resistor(s)" << endl;
}


 Node* Node::get_next_node() const
 {
     return next;
 }
 
 int Node::get_NodeID() const
 {
     return NodeID;
 }
 
 void Node::add_NodeID(int nodeID)
 {
     NodeID = nodeID;
 }
 
 ResistorList Node::get_resistorList() const
 {
     return r1;//
 }
 
 Node::Node(int nodeID, Node position)//position should be the node after the insert node
 {
     NodeID = nodeID;
     next = position;
 }
 
 void Node::set_next_node(Resistor* r)
 {
     next = r;
 }