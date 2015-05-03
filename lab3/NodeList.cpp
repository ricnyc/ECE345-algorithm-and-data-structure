

#include "Node.h"
#include "NodeList.h"
#include "ResistorList.h"
using namespace std;
 

NodeList::NodeList()
{
    head = NULL;
}

NodeList::~NodeList()
{}

Node* NodeList::find_node(int nodeID)
{
    Node *ptr = NULL;
    for(ptr = head; ptr != NULL ; ptr = ptr->get_next_node())
    {
        if(nodeID == ptr->get_NodeID())
        {
            return ptr;
        }
        if(nodeID < ptr->NodeID)
        {
            return NULL;
        }
    }
    
    head = NULL;
    return NULL;
}

Node* NodeList::find_or_insert_node(int nodeID)
{
    Node *ptr = NULL;
    for(ptr = head; ptr != NULL ; ptr = ptr->get_next_node())
    {
        if(nodeID == ptr->get_NodeID())
        {
            return ptr;    
        }
    }
    
    Node* prev = NULL;//insert the correct position in the node list
    Node* curr = head;
    while(curr != NULL && nodeID > curr->get_NodeID())//not the end of list and ID larger the current checking position
    {
        prev = curr;
        curr = curr-> get_next_node();//update the curr position
    }
    
    Node *newNode = new Node(nodeID, curr);//connect the position to next
    if(prev = NULL)
    {
        head  = newNode;//empty list
    }
    else
    {
        prev-> set_next_node(newNode); 
    }
    return newNode;
}

bool NodeList::check_resistor_in_nodelist(string name)
{
    Node *ptr = NULL;//head for NodeList(node type)
  
    for(ptr = head; ptr != NULL ; ptr = ptr->get_next_node())
    { 
        Resistor *ptr1 = NULL;//pointer for ResistorList(resistor type)
        for(ptr1 ==  head.get_resistorList().get_head_ResistorList(); ptr1 != NULL; ptr1 = ptr1 -> get_resistor_next())
        {
            if(name == ptr1->getName())
            {
                return true;
            }                     
        }
    }
   return false;
}
    int get_NodeID() const;
    void add_NodeID(int nodeID);
    void set_next_node(Resistor* r);

 bool NodeList::change_resistance(string name, double resistance)
 {
    Node *ptr = NULL;//head for NodeList(node type)
    for(ptr = head; ptr != NULL ; ptr = ptr->get_next_node())
    {  
        Resistor *ptr1 = NULL;//pointer for ResistorList(resistor type)
        for(ptr1 ==  head.get_resistorList().get_head_ResistorList(); ptr1 != NULL; ptr1 = ptr1 -> get_resistor_next())
        {
            if(name == ptr1->getName())
            {
                ptr1->getResistance() = resistance;
            }                     
        }
    }
    return false;
 }
 
 
 bool NodeList::delete_resistor(string name)
 {
    
    Node *ptr = NULL;//head for NodeList(node type)
   
    if(head == NULL)
    {
        return false;
    }
    else
    {
        for(ptr = head; ptr != NULL ; ptr = ptr->get_next_node())
        {
            Resistor* prev = NULL;
            Resistor *ptr1 = NULL;//pointer for ResistorList(resistor type)
                for(ptr1 ==  head.get_resistorList().get_head_ResistorList(); ptr1 != NULL; ptr1 = ptr1 -> get_resistor_next())
                {
                  if(name == ptr1->getName())
                  {
                      if(prev != NULL)
                      {
                          prev -> set_next_resistor(ptr1 -> get_resistor_next()); //not at the start of link list
                      }
                      else
                      {
                          head.get_resistorList().get_head_ResistorList() = ptr1 -> get_resistor_next();//start of link list
                      }
                      
                      delete ptr1;
                      return true;
                  }
                  prev = ptr1;//update the prev pointer          
                }
        }       
        return false;
    }
 }
 
 void NodeList::delete_all_resistor()
 {
    Node *ptr = NULL;//head for NodeList(node type)
    for(ptr = head; ptr != NULL ; ptr = ptr->get_next_node())
    {  
        Resistor *ptr1 = NULL;//pointer for ResistorList(resistor type)
        for(ptr1 ==  head.get_resistorList().get_head_ResistorList(); ptr1 != NULL; ptr1 = ptr1 -> get_resistor_next())
        {
          delete ptr1;                 
        }
    }
    return false;
 
 }

 
 