

	
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
    NodeID = 0;
    next = NULL;
    setV = false;
    voltage =  0;
    

}

Node::~Node()
{

}


void Node::print (int nodeIndex, int counter)
{
    if(counter != 0)
    {
        cout << "Connections at node " << nodeIndex <<  ": " << counter << " resistor(s)" << endl;
    }
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
 
 ResistorList& Node::get_resistorList()
 {    
     return r1;
 }
 
 Node::Node(int nodeID, Node* position)//position should be the node after the insert node
 {
     NodeID = nodeID;
     next = position;
     min_iteration_change = 1;
     voltage = 0;
     setV = false;
//        cout << "new_node" << endl;
 }
 
 void Node::set_next_node(Node* r)
 {
     next = r;

 }

 void Node::set_voltage(double volt_)
 {
     voltage = volt_;
     setV = true;
 }
 
 void Node::set_voltage_without_bool(double volt_)
 {
     voltage = volt_;
 
 }
  void Node::unset_voltage()
 {
     voltage = 0;
     setV = false;
 }
 
  bool Node::get_set_bool() const
  {
      return setV;
  }
  
  void Node::set_minimum_change(double min_change)
  {
      min_iteration_change = min_change;
  }
  
  double Node::get_minimum_change() const
  {
      return min_iteration_change; 
  }

  double Node::get_voltage() const
  {
      return voltage;
  }