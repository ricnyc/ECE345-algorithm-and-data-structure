//
//  Rparser.cpp
//  check 111111
//
//  Created by Chuanrui Li on 2013-10-10.
//  Copyright (c) 2013 Chuanrui Li. All rights reserved.
//
 
#include <iostream>
#include <sstream>
#include <string>
#include "Rparser.h"



 
using namespace std;
 


int parser(NodeList *&Nodehead)
{
    
    string line, command;
 
    cout << "> ";
    // May have some setup code here
    getline(cin, line);// Get a line from standard input
     
    while(!cin.eof())
    {
        // Put the line in a stringstream for parsing
        // Making a new stringstream for each line so flags etc. are in a known state
        stringstream linestream (line);
        linestream >> command;
        
        
       
        if(command == "insertR")
        {
            // parse an insertR command
            insert_command(linestream, line, Nodehead);
        }
        else if(command == "modifyR")
        {
            modify_command(linestream, line, Nodehead);
             
        }
        else if(command == "printR")
        {
            print_resistor_command(linestream, Nodehead);
        }
         
        else if(command == "printNode")
        {
            print_node_command(linestream, line, Nodehead);
        }
         
        else if(command == "deleteR")
        {
            delete_command(linestream, Nodehead);
        }
        else if(command == "setV")
        {
            setV_command(linestream, Nodehead);
        }
        else if(command == "unsetV")
        {
            unsetV_command(linestream, Nodehead);
        }
        else if(command == "solve")
        {
            solve_command(linestream, Nodehead);
        }
        else
        {
            cout << "Error: invalid command" << endl;//other invaild command
        }
        cout << "> ";
        getline(cin, line);
    }// End input loop until EOF.
    return 0;
}
 
 
 
 



 
 
void insert_command(stringstream &linestream, string &line, NodeList *&Nodehead)
{
    //storing the string line into another stringstream
    stringstream linestream_copy(line);
    string check_space;
    double resistance;
    int node1, node2 = 0;
    string name_resistor;
    
   
    store_value_for_name_resistor(name_resistor, linestream);//store the value
    store_value_for_resistance(resistance, linestream);//store the value
    store_value_for_nodes(node1, node2, linestream);//store the value

   
    int endpoint_[2];
    endpoint_[0] = node1;
    endpoint_[1] = node2; 
    int print_once = 0;
    Nodehead -> find_or_insert_node(node1) -> get_resistorList().insert_resistor_at_end(resistance, name_resistor,  endpoint_, print_once);
    Nodehead -> find_or_insert_node(node2) -> get_resistorList().insert_resistor_at_end(resistance, name_resistor,  endpoint_, print_once);
}
 
void modify_command(stringstream &linestream, string &line, NodeList *&Nodehead)
{
    string name_resistor;
    double resistance = 0;
//    storing the string line into another stringstream
    stringstream linestream_copy(line);
     
    store_value_for_name_resistor(name_resistor, linestream);
    store_value_for_resistance(resistance, linestream);
    
    double changed_resistance = resistance;
    


    int checking = Nodehead->change_resistance(name_resistor, resistance);//change the resistance inside the Resistor
//    cout << checking << endl;
    if(checking != 0)
    {
        cout << "Modified: resistor " << name_resistor << " from " << resistance << " Ohms to " << changed_resistance << " Ohms"<<  endl;
    }
    else
    {
        cout << "Error: resistor " <<  name_resistor << " not found" << endl;
    }
}
 
void delete_command(stringstream &linestream, NodeList *&Nodehead)
{
    string name_resistor, check_space;
    store_value_for_name_resistor(name_resistor, linestream);
     
//    special case for all
    if(name_resistor == "all")
    {
        Nodehead->delete_all_resistor();
        cout << "Deleted: all resistors" << endl;
    }
    else
    {
        int checking = Nodehead->delete_resistor(name_resistor);
        if(checking != 0)
        {
            cout << "Deleted: resistor " << name_resistor << endl;
        }
        else 
        {
            cout << "Error: resistor " <<  name_resistor << " not found" << endl;
        }
        
    }     
}
 
void print_node_command(stringstream &linestream, string &line, NodeList *&Nodehead)
{
    int node1 = 0;
    store_value_for_node(node1, linestream);//store the value
    stringstream linestream_copy(line);
      
    if(linestream.fail())
    {
      string command;
      string node1;
      string check_space;
      linestream_copy >> command >> node1;
     if(node1.empty() == 0)
     {
        if(node1 == "all")
        { 
         
                cout << "Print:" << endl;
                Node *ptr = NULL;//head for NodeList(node type)
                for(ptr = Nodehead->find_head_of_NodeList(); ptr != NULL ; ptr = ptr->get_next_node())
                {   
                        int counter = 0;
                        Nodehead->find_node(ptr->get_NodeID())->get_resistorList().find_number_of_resistor_inserted(counter);
                        Nodehead->find_node(ptr->get_NodeID())->print(ptr->get_NodeID(), counter);
                        Nodehead->find_node(ptr->get_NodeID())->get_resistorList().find_number_of_resistor_inserted_print_statement();
                }
        }
     }
    }
    
    else
    {
        int counter1 = 0;
        //find how many resistors inside one nodeID 
        cout << "Print: " << endl;
        Nodehead->find_node(node1)->get_resistorList().find_number_of_resistor_inserted(counter1);
        Nodehead->find_node(node1)->print(node1, counter1);
        Nodehead->find_node(node1)->get_resistorList().find_number_of_resistor_inserted_print_statement();     
    }     
}
 
 
void print_resistor_command(stringstream &linestream, NodeList *&Nodehead)
{
    string name_resistor;

    bool flag1 = Nodehead->check_resistor_in_nodelist(name_resistor);//for printing the resistor
    cout << "23e234234" << endl;
    if(!flag1)
    {
        cout << "Error: resistor " <<  name_resistor << " not found" << endl;
    }
}
 

void setV_command(stringstream &linestream, NodeList *&Nodehead)
{
    double voltage = 0;        
    int nodeID = 0;
    store_value_for_voltage(voltage, nodeID, linestream);
    if(!Nodehead->find_node(nodeID))
    {       
    }
    else
    {
        Nodehead->find_node(nodeID)->set_voltage(voltage);
    }
    cout << "Set: node " << nodeID << " to " << voltage << " Volts" << endl;

//    Nodehead->print_voltage_for_each_node();
}

void unsetV_command(stringstream &linestream, NodeList *&Nodehead)
{        
    int nodeID;
    store_value_for_node(nodeID, linestream);//store the value for node1
    if(!Nodehead->find_node(nodeID))
    {       
    }
    else
    {
       Nodehead->find_node(nodeID)->unset_voltage();
    }
     cout << "Unset: the solver will determine the voltage of node " << nodeID << endl;
}

void solve_command(stringstream &linestream, NodeList *&Nodehead)
{
     Node* ptr = NULL;
     bool flag = true;

     for(ptr = Nodehead->find_head_of_NodeList(); ptr != NULL; ptr = ptr->get_next_node())
     {
         cout << ptr->get_set_bool() << endl;
         if(ptr->get_set_bool() == true)
         {
              Nodehead->solve();
              Nodehead->print_voltage_for_each_node();
              flag = false;
         }
     }
     if(flag)
     {
        cout << "Error: no nodes have their voltage set" << endl;
     }
}

 
void store_value_for_name_resistor(string &name_resistor, stringstream &linestream)//store the value for name_resistor
{
    get_value_after_current_space(linestream);//get value
    linestream >> name_resistor;//output the value    
}
 
void store_value_for_resistance(double &resistance, stringstream &linestream)//store the value for resistance
{
    get_value_after_current_space(linestream);
    linestream >> resistance;
}
 
void store_value_for_nodes(int &node1, int &node2, stringstream &linestream)//store the value for node1 and node2
{
    get_value_after_current_space(linestream);
    linestream >> node1;
    linestream >> node2;
}
 
 
void store_value_for_node(int &node1, stringstream &linestream)//store the value for node1
{
    get_value_after_current_space(linestream);
    linestream >> node1;
}
 
void store_value_for_voltage(double &voltage, int &node, stringstream &linestream)
{
    get_value_after_current_space(linestream);
    linestream >> node >> voltage;
    
}


void get_value_after_current_space(stringstream &linestream)//basic function to get value after each spaces
{
    if(linestream.peek() == ' ')
    {
        linestream.get();
    }
}
    
//identify the invaild arguments, few arguments.
void error_invaild_argument(stringstream& linestream_copy, string &line)
{
    stringstream convert;
    string name_resistor, command;
    string resistance;
    string node1, node2;
    string s1;
    linestream_copy >> command >> name_resistor >> resistance >> node1 >> node2;
    if(name_resistor.empty() == 0 && resistance.empty() == 0 && node1.empty() == 0 && node2.empty() == 0)//check the all strings are empty or not
    {
        cout << "Error: invalid argument" << endl;
    }
    else//in order to check the priority
    {   if(resistance.empty() == 0)
    {
        double resistance_check;
        stringstream (resistance) >> resistance_check;
        if( resistance_check < 0)
        {
            cout << "Error: negative resistance" << endl;
        }
    }
         
//        check the range of node1
    else if(node1.empty() == 0)
    {
        int node1_check;
        stringstream (node1) >> node1_check;
    }
         
    else if(node2.empty() == 0)
    {
        int node2_check;
        stringstream (node2) >> node2_check;
  
    }
         
    else if(name_resistor == "all")
    {
        cout << "Error: resistor name cannot be the keyword \"all\" " << endl;
    }
         
//        check the both terminal
         
    else if(node1 == node2 && node1.empty() == 0 && node2.empty() == 0)
    {
        cout << "Error: both terminals of resistor connect to node 1" << endl;
    }
    else
    {
        cout << "Error: too few arguments" << endl;
    }
    }
}
 
///identify the invaild arguments, few arguments.
void error_invaild_argument_modify(stringstream& linestream_copy, string &line)
{
    string name_resistor, command;
    string resistance;
    linestream_copy >> command >> name_resistor >> resistance;
    if(name_resistor.empty() == 0 && resistance.empty() == 0 && resistance.empty() == 0)
    {
        cout << "Error: invalid argument" << endl;
    }
     
    else//check the priority
    {
        if(resistance.empty() == 0)
        {
            double resistance_check;
            stringstream (resistance) >> resistance_check;
            if( resistance_check < 0)
            {
                cout << "Error: negative resistance" << endl;
            }
        }
         
        else if(name_resistor == "all")
        {
            cout << "Error: resistor name cannot be the keyword \"all\" " << endl;
        }
         
        else
        {
            cout << "Error: too few arguments" << endl;
        }
    }
}
