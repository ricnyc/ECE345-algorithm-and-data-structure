/* 
 * File:   ResistorList.h
 * Author: lichuanr
 *
 * Created on October 31, 2013, 9:58 PM
 */

#ifndef RESISTORLIST_H
#define	RESISTORLIST_H
using namespace std;
#include <iostream>

class ResistorList
{
        private:
            Resistor *head;
        public:
            ResistorList();
            ~ResistorList();
            Resistor* get_head_ResistorList() const;
            void insert_resistor_at_end();
            Resistor* find_resistor(string name, Resistor*& previous);
            void delete_resistor(Resistor* r, Resistor* previous);//r is the return pointer for finding resistor
            void set_head_ResistorList(Resistor*);
};

#endif	/* RESISTORLIST_H */

