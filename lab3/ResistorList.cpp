using namespace std;
#include "Resistor.h"
#include "ResistorList.h"

ResistorList::ResistorList()
{
    head = NULL;
}

ResistorList::~ResistorList()
{}

Resistor* ResistorList::get_head_ResistorList() const
{
    return head;
}

void ResistorList::insert_resistor_at_end()
{
    Resistor *ptr = NULL;
    Resistor *temp;
    for(ptr = head; ptr !=NULL; ptr = ptr->get_resistor_next())
    {
    }
    ptr->set_next_resistor(temp);
    temp->set_next_resistor(NULL);
}

//Resistor* previous_r;
//Resistor* r = find_resistor("my_resitor", previous_r);

// Returns the resistor that has the given name.
// Puts the previous resistor in "previous". Puts NULL in "previous" if the
// given name is the first resistor in the list.
Resistor* ResistorList::find_resistor(string name, Resistor*& previous)
{
    Resistor *ptr = NULL;
    previous = NULL;
    for(ptr = head; ptr !=NULL; ptr = ptr->get_resistor_next())
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