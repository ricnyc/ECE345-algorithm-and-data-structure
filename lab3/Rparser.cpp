
	
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
#include "Node.h"
#include "Resistor.h"
 
#define MAX_NODE_NUMBER 5000
#define MIN_NODE_NUMBER 0
#define MAX_RESISTORS_PER_NODE 5
 
 
using namespace std;
 
//declaration  Node * node_array;
//declaration  Resistor * resistor_array;
// checking integer for max_Val command
Node * node_array;
Resistor * resistor_array;

int max_Val = 0;
int parser()
{
 
    string line, command;
    int max_node_number = 0;
    int max_resistor = 0;
    int rindex = 0;
    cout << "> ";
    // May have some setup code here
    getline(cin, line);// Get a line from standard input
     
    while(!cin.eof())
    {
        // Put the line in a stringstream for parsing
        // Making a new stringstream for each line so flags etc. are in a known state
        stringstream linestream (line);
        linestream >> command;
        
        
        if(command == "maxVal")
        { 
            maxVal_command(linestream, line, max_node_number, max_resistor);
        }
        else if(command == "insertR")
        {
            // parse an insertR command
            insert_command(linestream, line, rindex,  max_node_number, max_resistor);
        }
        else if(command == "modifyR")
        {
            modify_command(linestream, line,  max_node_number, max_resistor);
             
        }
        else if(command == "printR")
        {
            print_resistor_command(linestream, max_node_number, max_resistor);
        }
         
        else if(command == "printNode")
        {
            print_node_command(linestream, line, max_node_number);
        }
         
        else if(command == "deleteR")
        {
            delete_command(linestream, max_node_number, max_resistor, rindex);
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
         
        //check the range of node1
    else if(node1.empty() == 0)
    {
        int node1_check;
        stringstream (node1) >> node1_check;
        if((MIN_NODE_NUMBER > node1_check) || (node1_check > MAX_NODE_NUMBER))
        {
             
            cout << "Error: node " << node1 << " is out of permitted range 0-5000" << endl;
        }
        //check the range of node2
    }
         
    else if(node2.empty() == 0)
    {
        int node2_check;
        stringstream (node2) >> node2_check;
        if((MIN_NODE_NUMBER > node2_check) || (node2_check > MAX_NODE_NUMBER))
        {
            cout << "Error: node " << node2 << " is out of permitted range 0-5000" << endl;
        }
    }
         
    else if(name_resistor == "all")
    {
        cout << "Error: resistor name cannot be the keyword \"all\" " << endl;
    }
         
        //check the both terminal
         
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
 
//identify the invaild arguments, few arguments.
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

int search_resistor(Resistor *resistor_array, int rindex, string name_resistor,  int max_node_number, int max_resistor)
{   
    
    for(rindex = 0; rindex < max_resistor; rindex++)
    {
        if( resistor_array[rindex].getName() == name_resistor)
        { 
            return rindex;//return the rindex for the correct position
        }
    } 
    cout << "Error: resistor " << name_resistor << " not found" << endl;
    
    return -1;
}
 
void maxVal_command(stringstream &linestream, string &line, int &max_node_number, int &max_resistor)
{
    //storing the string line into another stringstream
    stringstream linestream_copy(line);
    string check_space;
    store_value_for_max_node_number(max_node_number, linestream);
    store_value_for_max_resistor(max_resistor, linestream);
    if(max_Val == 1)
    {
       delete []node_array;
       delete []resistor_array;
       node_array = NULL;
       resistor_array = NULL;
       
       resistor_array = new Resistor[max_resistor];
       node_array = new Node[max_node_number+1];
    }
    
    else 
    {
    resistor_array = new Resistor[max_resistor];

    node_array = new Node[max_node_number+1];
         
    max_Val = 1;//make sure next time maxVal go to first if statement
    }


     
    if(max_node_number <= 0 || max_resistor <= 0)
    {
        cout << "Error: maxVal arguments must be greater than 0" << endl;
    }
     
    else
    {
        cout << "New network: max node number is " << max_node_number << "; max resistors is " << max_resistor << endl;
    }
}
 
 
 
void insert_command(stringstream &linestream, string &line, int& rindex, int max_node_number, int max_resistor)
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
    bool flag = true;
    if(0 > node1 || node1 > max_node_number)
    {
        cout << "Error: node " << node1 << " is out of permitted range 0-" << max_node_number << endl;
        flag = false;
    }
    
    else if((0 > node2) || (node2 > max_node_number))
    {
        cout << "Error: node " << node2 << " is out of permitted range 0-" << max_node_number << endl;
        flag = false;
    }
    
    else if(rindex == max_resistor)
    {
        cout << "Error: resistor array is full" << endl;
        flag = false;
    }
    
    else if(flag)//checking the resArray 
    {
       
            if(node_array[node1].getnumRes() == MAX_RESISTORS_PER_NODE||node_array[node2].getnumRes() ==  MAX_RESISTORS_PER_NODE)
            {
                cout << "Error: node is full" << endl;
                flag = false;
            }
     
    }
    
    if(flag)
    {
    //using to update the node array
    //the specific resistor connected to the node by rindex
    node_array[node1].addResistor(rindex);
    node_array[node2].addResistor(rindex);
    
    //add the resistor to array and update two entries
    resistor_array[rindex].addResistor(rindex, name_resistor, resistance, endpoint_);
    resistor_array[rindex].print3();
    rindex++;
    }
}
 
void modify_command(stringstream &linestream, string &line, int max_node_number, int max_resistor)
{
    string name_resistor;
    double resistance = 0;
    //storing the string line into another stringstream
    stringstream linestream_copy(line);
     
    store_value_for_name_resistor(name_resistor, linestream);
    store_value_for_resistance(resistance, linestream);
    
    int rindex = 0;
    rindex = search_resistor(resistor_array, rindex, name_resistor,  max_node_number, max_resistor);
    
    if(rindex != -1)//check the return value
    {
        cout << "Modified: resistor " << name_resistor << " from " << resistor_array[rindex].getResistance() << " Ohms to " << resistance << " Ohms"<<  endl;
        resistor_array[rindex].setResistance(resistance);
    }
}
 
void delete_command(stringstream &linestream, int max_node_number, int max_resistor, int & rindex)
{
    string name_resistor, check_space;
    store_value_for_name_resistor(name_resistor, linestream);
     
    //special case for all
    if(name_resistor == "all")
    {

       delete []node_array;
       delete []resistor_array;//delete everything inside the two arrays 
       node_array = NULL;
       resistor_array = NULL;//reset to NULL
       rindex = 0;//reset the rindex
       resistor_array = new Resistor[max_resistor];
        node_array = new Node[max_node_number+1];//rebuild two arrays

        cout << "Deleted: all resistors" << endl;
    }

     
}
 
void print_node_command(stringstream &linestream, string &line, int max_node_number)
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
            //j is counter in node array
            //i is counter in resIDArray
            for(int j = 0; j <= max_node_number; j++)
            {           
                node_array[j].print(j);
                for(int i = 0; i < node_array[j].getnumRes(); i++)
                {
                        resistor_array[node_array[j].getresIDArray(i)].print2();
                }
            }
        }
     }
    }
    
    
    else 
    {
        cout << "Print:" << endl;
        //print the node1(nodeIdex)
        //numRes inside each node and numRes is already updated in the insert command
        node_array[node1].print(node1);
    
        //print the resistor connected to the node
        for(int i = 0; i < node_array[node1].getnumRes(); i++)//max is the numRes 
        {
                //resistor_array[rindex]
                //finding which node first, then get IDArray, the find the rindex inside Array
    
            resistor_array[node_array[node1].getresIDArray(i)].print2();
        }
    

    }
     
}
 
 
void print_resistor_command(stringstream &linestream, int max_node_number, int max_resistor)
{
    string name_resistor;
    store_value_for_name_resistor(name_resistor, linestream);//store the value
    if(name_resistor == "all")
    {
        cout << "Print:" << endl;
        for(int index  =  0; index < max_resistor; index++)
        {
                if(resistor_array[index].getResistance() != 0)//print the node entry which resistance is not zero
                {
                         resistor_array[index].print();
                }
        }
    }
    
    else
    {
        int rindex = 0;
        rindex = search_resistor(resistor_array, rindex, name_resistor,  max_node_number, max_resistor);
    
        if(rindex != -1)
        {
            cout << "Print:" << endl;
            resistor_array[rindex].print();
        }
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
 
void store_value_for_max_node_number(int &max_node_number, stringstream &linestream)//store the value
{
    get_value_after_current_space(linestream);
    linestream >> max_node_number;
}
 
 
void store_value_for_max_resistor(int &max_resistor, stringstream &linestream)
{
    get_value_after_current_space(linestream);
    linestream >> max_resistor;
}
