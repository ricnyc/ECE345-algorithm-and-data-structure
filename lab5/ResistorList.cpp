using namespace std;

#include "ResistorList.h"

ResistorList::ResistorList()
{
    head = NULL;
}

ResistorList::~ResistorList()
{
    delete head;
}

Resistor* ResistorList::get_head_ResistorList() const
{
    return head;
}

//insert the resistor at the ens of ResistorList
void ResistorList::insert_resistor_at_end(double resistance, string name, int endpoints_[2], int &print_once)
{

    Resistor *ptr = NULL;
    Resistor *temp = new Resistor(name, resistance, endpoints_);
    if(head == NULL)//empty resistor list 
    {
        head = temp;
        temp -> set_next_resistor(NULL);
        if(print_once == 0)
        {
         temp->print3();
         print_once = 1;
        }
    }
    else
    {
        for(ptr = head; ptr->get_resistor_next() != NULL; ptr = ptr->get_resistor_next())
        {
        }
        ptr->set_next_resistor(temp);
        temp->set_next_resistor(NULL);
        if(print_once == 0)
        {
         temp->print3();
         print_once = 1;
        }

    }
}


Resistor* ResistorList::find_resistor(string name, Resistor*& previous)
{
    Resistor *ptr = NULL;
    previous = NULL;
    for(ptr = head; ptr != NULL; ptr = ptr->get_resistor_next())//go through the NodeList
    {
        if(name == ptr->getName())
        {
            return ptr;
        
        }
        previous = ptr;
    }
    return NULL;
}

void ResistorList::delete_resistor(Resistor* r, Resistor* previous)
{
    if (previous == NULL)
    {
        if(head != NULL)
        {
            head == r ->get_resistor_next();
            delete r;
        }
    }
    else
    {
        previous ->set_next_resistor(r->get_resistor_next());
        delete r;
        //update the pointer given in previous
    }
}

void ResistorList::set_head_ResistorList(Resistor*R1)
{
    head = R1;
}

//not used
void ResistorList::find_number_of_resistor_inserted(int& counter)
{
    Resistor* ptr = NULL;

    for(ptr = head; ptr != NULL; ptr = ptr->get_resistor_next())
    {
        counter++;
    }
}

//not used
void ResistorList::find_number_of_resistor_inserted_print_statement()
{
    Resistor* ptr = NULL;

    for(ptr = head; ptr != NULL; ptr = ptr->get_resistor_next())
    {
        ptr->print2();
    }
}
