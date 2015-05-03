//
//  main.cpp
//  ECE244 lab2
//
//  Created by Chuanrui Li on 2013-09-26.
//  Copyright (c) 2013 Chuanrui Li. All rights reserved.
//


#include <iostream>
#include <sstream>
#include <string>
#define MAX_NODE_NUMBER 5000
#define MIN_NODE_NUMBER 0

using namespace std;

int parser();

//basic functions using peek to get the value
void get_value_after_current_space(stringstream &linestream);

//to store the value for each parts
void store_value_for_name_resistor(string &name_resistor, stringstream &linestream);
void store_value_for_resistance(double &resistance, stringstream &linestream);
void store_value_for_nodes(int &node1, int &node2, stringstream &linestream);
void store_value_for_node(int &node1, stringstream &linestream);

//command options
void insert_command(stringstream &linestream, string &line);
void modify_command(stringstream &linestream, string &line);
void delete_command(stringstream &linestream);
void print_node_command(stringstream &linestream, string &line);
void print_resistor_command(stringstream &linestream);

//error checking command
void error_invaild_argument(stringstream& copy_linestream, string& line);

int main()
{
    cout.precision(2);
    cout.setf(ios::fixed);
    parser();
}

int parser()
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
            insert_command(linestream, line);
		}
		else if(command == "modifyR")
		{
            modify_command(linestream, line);

		}
		else if(command == "printR")
		{
            print_resistor_command(linestream);
        }

		else if(command == "printNode")
		{
            print_node_command(linestream, line);
        }

		else if(command == "deleteR")
		{
            delete_command(linestream);
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



void insert_command(stringstream &linestream, string &line)
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

    //error checking list
    //check the fail cases first
    if(linestream.fail())
    {
        error_invaild_argument(linestream_copy, line);//checking the copy
    }

    else if(resistance < 0)
    {
        cout << "Error: negative resistance" << endl;
    }
    //check the range of node1
    else if((MIN_NODE_NUMBER > node1) || (node1 > MAX_NODE_NUMBER))
    {

        cout << "Error: node " << node1 << " is out of permitted range 0-5000" << endl;
    }
    //check the range of node2
    else if((MIN_NODE_NUMBER > node2) || (node2 > MAX_NODE_NUMBER))
    {
        cout << "Error: node " << node2 << " is out of permitted range 0-5000" << endl;
    }

    else if(name_resistor == "all")
    {
        cout << "Error: resistor name cannot be the keyword \"all\" " << endl;
    }
    //check the both terminal
    else if(node1 == node2)
    {
        cout << "Error: both terminals of resistor connect to node 1" << endl;
    }

    else if(linestream.eof() == false)
    {
        linestream >> check_space;
        if(!check_space.empty())//check the space
        {
            cout << "Error: too many arguments" << endl;
        }

        else
        {
            cout << "Inserted: resistor " + name_resistor + " " << resistance << " Ohms " << node1 << " -> " << node2 << endl;
        }
    }

    //right case
    else if((resistance >= 0) && (MIN_NODE_NUMBER <= node1 && node1<= MAX_NODE_NUMBER) && (MIN_NODE_NUMBER <= node1 && node1<= MAX_NODE_NUMBER)&&(name_resistor != "all")&&(node1 != node2))
    {
          cout << "Inserted: resistor " + name_resistor + " " << resistance << " Ohms " << node1 << " -> " << node2 << endl;
    }
}




void modify_command(stringstream &linestream, string &line)
{
    string name_resistor, check_space;
    double resistance = 0;
    //storing the string line into another stringstream
    stringstream linestream_copy(line);

    store_value_for_name_resistor(name_resistor, linestream);
    store_value_for_resistance(resistance, linestream);

    //error checking list
    //check the fail cases first
    if(linestream.fail())
    {
        error_invaild_argument_modify(linestream_copy, line);
    }
    else if(resistance < 0)
    {
        cout << "Error: negative resistance" << endl;
    }

    else if(name_resistor == "all")
    {
        cout << "Error: resistor name cannot be the keyword \"all\" " << endl;
    }

    else if(linestream.eof() == false)
    {
        linestream >> check_space;
        if(!check_space.empty())//check the space
        {
            cout << "Error: too many arguments" << endl;
        }

        else
        {
             cout << "Modified: resistor " << name_resistor << " to " << resistance << " Ohms" << endl;
        }
    }

    //right case
    else if((resistance >= 0)&&(name_resistor != "all"))
    {
       cout << "Modified: resistor " << name_resistor << " to " << resistance << " Ohms" << endl;
    }
}


void delete_command(stringstream &linestream)
{
    string name_resistor, check_space;
    store_value_for_name_resistor(name_resistor, linestream);

    //error checking list
    //check the fail cases first
    if(linestream.fail())
    {
        if((name_resistor.empty() == 0))
        {
            cout << "Error: invalid argument" << endl;
        }
        else
        {
            cout << "Error: too few arguments" << endl;
        }
    }

    else if(linestream.eof() == false)
    {
        linestream >> check_space;
        if(!check_space.empty())//check the space
        {
            cout << "Error: too many arguments" << endl;
        }
        else if(name_resistor == "all")
        {
            cout << "Deleted: all resistors" << endl;
        }

        //right case
        else
        {
            cout << "Deleted: resistor " << name_resistor << endl;
        }
    }

    //special case for all
    else if(name_resistor == "all")
    {
        cout << "Deleted: all resistors" << endl;
    }

    //right case
    else
    {
        cout << "Deleted: resistor " << name_resistor << endl;
    }
}

void print_node_command(stringstream &linestream, string &line)
{
    int node1 = 0;
    store_value_for_node(node1, linestream);//store the value
    stringstream linestream_copy(line);
    string check_space;
    //error checking list
    //check the fail cases first
        if(linestream.fail())
        {
            string command;
            string node1;
            string check_space;
            linestream_copy >> command >> node1;
            if(node1.empty() == 0)
            {
                //special case, when node1 is "all"
                if(node1 == "all")
                {
                    cout << "Print: all nodes" << endl;

                }
                else
                {
                    cout << "Error: invalid argument" << endl;
                }

            }
            else
            {
                cout << "Error: too few arguments" << endl;
            }
        }
        //check the range for node1
        else if(MIN_NODE_NUMBER > node1 || node1 > MAX_NODE_NUMBER)
        {
            cout << "Error: node " << node1 << " is out of permitted range 0-5000" << endl;
        }


        else if(linestream.eof() == false)
        {
            linestream >> check_space;
            if(!check_space.empty())//check the space
            {
                cout << "Error: too many arguments" << endl;
            }
            else
            {
                cout << "Print: node " << node1 << endl;
            }
        }

        //right case
        else
        {
            cout << "Print: node " << node1 << endl;
        }

}


void print_resistor_command(stringstream &linestream)
{

    string name_resistor, check_space;
    store_value_for_name_resistor(name_resistor, linestream);//store the value

    //error checking list
    //check the fail cases first
    if(linestream.fail())
    {
        if((name_resistor.empty() == 0))
        {
            cout << "Error: invalid argument" << endl;
        }
        else
        {
            cout << "Error: too few arguments" << endl;
        }
    }

    else if(linestream.eof() == false)
    {
        linestream >> check_space;
        if(!check_space.empty())//check the space
        {
            cout << "Error: too many arguments" << endl;
        }
        else if(name_resistor == "all")
        {
            cout << "Print: all resistors"  << endl;
        }

        //right case
        else
        {
            cout << "Print: resistor " << name_resistor << endl;
        }
    }

    else if(name_resistor == "all")
    {
        cout << "Print: all resistors" << endl;
    }
    //right case
    else
    {
        cout << "Print: resistor " + name_resistor << endl;
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

