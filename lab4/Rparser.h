

	
//
//  Rparser.h
//  check 111111
//
//  Created by Chuanrui Li on 2013-10-10.
//  Copyright (c) 2013 Chuanrui Li. All rights reserved.
//
 
#ifndef check_111111_Rparser_h
#define check_111111_Rparser_h
 
using namespace std;
#include <string>
#include <iostream>
#include <iomanip>
#include "Node.h"
#include "Resistor.h"
#include "ResistorList.h"
#include "NodeList.h"
int parser(NodeList *&Nodehead);
 
//basic functions using peek to get the value
void get_value_after_current_space(stringstream &linestream);
 
//to store the value for each parts
void store_value_for_name_resistor(string &name_resistor, stringstream &linestream);
void store_value_for_resistance(double &resistance, stringstream &linestream);
void store_value_for_nodes(int &node1, int &node2, stringstream &linestream);
void store_value_for_node(int &node1, stringstream &linestream);
void store_value_for_voltage(double &voltage, int &node, stringstream &linestream);
 
 
 
//command options
void insert_command(stringstream &linestream, string &line, NodeList *&Nodehead);
void modify_command(stringstream &linestream, string &line, NodeList *&Nodehead);
void delete_command(stringstream &linestream, NodeList *&Nodehead);
void print_node_command(stringstream &linestream, string &line, NodeList *&Nodehead);
void print_resistor_command(stringstream &linestream, NodeList *&Nodehead);
void setV_command(stringstream &linestream, NodeList *&Nodehead);
void unsetV_command(stringstream &linestream, NodeList *&Nodehead);
void solve_command(stringstream &linestream, NodeList *&Nodehead);

//error checking command
void error_invaild_argument(stringstream& copy_linestream, string& line);
 
#endif

