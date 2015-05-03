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
#include "Resistor.h"
class ResistorList
{
        private:
            Resistor *head;
        public:
            ResistorList();
            ~ResistorList();
            Resistor* get_head_ResistorList() const;
            void insert_resistor_at_end(double resistance, string name, int endpoints_[2], int &print_once);
            Resistor* find_resistor(string name, Resistor*& previous);
            void delete_resistor(Resistor* r, Resistor* previous);//r is the return pointer for finding resistor
            void set_head_ResistorList(Resistor* R1);
            void find_number_of_resistor_inserted(int& counter);
            void find_number_of_resistor_inserted_print_statement();
            


};

#endif	/* RESISTORLIST_H */
