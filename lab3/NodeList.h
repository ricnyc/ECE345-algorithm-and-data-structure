/* 
 * File:   newfile.h
 * Author: lichuanr
 *
 * Created on October 31, 2013, 9:55 PM
 */

#ifndef NEWFILE_H
#define	NEWFILE_H
#include "Node.h"
#include "Resistor.h"
#include <iostream>
using namespace std;
 
class NodeList
{
private:
    Node*head;
    
public:
    NodeList();
    ~NodeList();
    
    Node* find_node(int nodeID);
    Node* find_or_insert_node(int nodeID);
    bool check_resistor_in_nodelist(string name);
    bool change_resistance(string name, double resistance);
    bool delete_resistor(string name);
    void delete_all_resistor();
    
};
            
#endif	/* NEWFILE_H */

