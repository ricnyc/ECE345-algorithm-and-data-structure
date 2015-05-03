
	
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
int parser();
 
//basic functions using peek to get the value
void get_value_after_current_space(stringstream &linestream);
 
//to store the value for each parts
void store_value_for_name_resistor(string &name_resistor, stringstream &linestream);
void store_value_for_resistance(double &resistance, stringstream &linestream);
void store_value_for_nodes(int &node1, int &node2, stringstream &linestream);
void store_value_for_node(int &node1, stringstream &linestream);
void store_value_for_max_node_number(int &max_node_number, stringstream &linestream);
void store_value_for_max_resistor(int &max_resistor, stringstream &linestream);
 
 
 
//command options
void maxVal_command(stringstream &linestream, string &line, int &max_node_number, int &max_resistor);
void insert_command(stringstream &linestream, string &line, int &rindex,  int max_node_number, int max_resistor);
void modify_command(stringstream &linestream, string &line, int max_node_number, int max_resistor);
void delete_command(stringstream &linestream, int max_node_number, int max_resistor, int& rindex);
void print_node_command(stringstream &linestream, string &line, int max_node_number);
void print_resistor_command(stringstream &linestream, int max_node_number, int max_resistor);
 
 
//error checking command
void error_invaild_argument(stringstream& copy_linestream, string& line);
 
#endif

