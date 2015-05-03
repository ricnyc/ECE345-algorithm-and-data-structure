
	
/*
 * File:   main.cpp
 * Author: chuanruili
 *
 * Created on October 10, 2013, 10:15 AM
 */
 
#include <cstdlib>
#include <iostream>
#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"
#include "NodeList.h"
#include "ResistorList.h"

#define MIN_ITERATION_CHANGE 0.0001

using namespace std;
 
int main()
{
   
  
    
    cout.precision(2);
    cout.setf(ios::fixed);
    NodeList *Nodehead = new NodeList();
    parser(Nodehead);
    Nodehead->delete_memory();
    delete Nodehead;

 
}