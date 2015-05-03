

#include "Node.h"
#include "NodeList.h"
#include "ResistorList.h"
using namespace std;
#include <cmath>        // std::abs

 #define MIN_ITERATION_CHANGE 0.0001

NodeList::NodeList()
{
    head = NULL;
}

NodeList::~NodeList()
{}

 Node* NodeList::find_head_of_NodeList()
 {
     return head;
 }
 

Node* NodeList::find_node(int nodeID)
{
    Node *ptr = NULL;
    for(ptr = head; ptr != NULL ; ptr = ptr->get_next_node())
    {
        if(nodeID == ptr->get_NodeID())
        {
            return ptr;
        }
        if(nodeID < ptr->get_NodeID())
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
    //head = NULL;
    Node* prev = NULL;//insert the correct position in the node list
    Node* curr = head;

    while(curr != NULL && nodeID > curr->get_NodeID())//not the end of list and ID larger the current checking position
    {
//        cout << "inside the updating process" << endl;
        prev = curr;
        curr = curr-> get_next_node();//update the curr position
    }
    
    Node *newNode = new Node(nodeID, curr);//connect the position to next

    if(prev == NULL)
    {
//        cout << "NodeList_inside1"<< endl;
        head  = newNode;//empty list and NodeID smaller than first node
    }
    else
    {
//        cout << "NodeList_inside2" << endl;
        prev-> set_next_node(newNode); 
    }
    return newNode;
}


bool NodeList::check_resistor_in_nodelist(string name)
{
    Node *ptr = NULL;//head for NodeList(node type)

    for(ptr = head; ptr != NULL ; ptr = ptr->get_next_node())
    { 
//        cout << ptr->get_NodeID() << endl;
        Resistor *ptr1 = NULL;//pointer for ResistorList(resistor type)
        for(ptr1 =  ptr->get_resistorList().get_head_ResistorList(); ptr1 != NULL; ptr1 = ptr1 -> get_resistor_next())
        {
//            cout << "name_input: " << name << " name_exiting " << ptr1->getName() << endl;
            if(name == ptr1->getName())
            {
//                cout << "name_input: " << name << "name_exiting" << ptr1->getName()
                cout << "inside 2"<< endl;
                ptr1->print();
                cout << "inside here" << endl;
                return true;
            }                     
        }
    }
   return false;
}



 int NodeList::change_resistance(string name, double& resistance)
 {
    Node *ptr = NULL;//head for NodeList(node type)
    double resistance1 = resistance;
    int checking = 0;//check find the resistor or not
    int get_resistance = 0;
    for(ptr = head; ptr != NULL; ptr = ptr->get_next_node())
    {  
//        cout << ptr->get_NodeID() << endl;
        Resistor *ptr1 = NULL;//pointer for ResistorList(resistor type)
        for(ptr1 =  ptr ->get_resistorList().get_head_ResistorList(); ptr1 != NULL; ptr1 = ptr1 -> get_resistor_next())
        {
//            cout << ptr1->getName() << endl;
            if(name == ptr1->getName())
            {  
                if(get_resistance == 0)
                {
                        resistance = ptr1->getResistance();
                        get_resistance = 1; //make sure the value of resistance only get once
                }
                
                ptr1->setResistance(resistance1);
                checking++;
                break;
            }                     
        }
    }
    return checking;
 }
 
 
 int NodeList::delete_resistor(string name)
 {
    Node *ptr = NULL;//head for NodeList(node type)
    int checking = 0;
    if(head == NULL)
    {
        return checking;
    }
    else
    {
        for(ptr = head; ptr != NULL ; ptr = ptr->get_next_node())
        {
            Resistor* prev = NULL;
            Resistor* ptr1 = NULL;//pointer for ResistorList(resistor type)
                for(ptr1 =  ptr -> get_resistorList().get_head_ResistorList(); ptr1 != NULL; ptr1 = ptr1 -> get_resistor_next())
                {    
                    Resistor* copy_for_ptr1 = NULL;
                    copy_for_ptr1 = ptr1;
                  if(name == copy_for_ptr1->getName())
                  {
                      checking++;
                      if(prev != NULL)
                      {
                          prev -> set_next_resistor(copy_for_ptr1 -> get_resistor_next()); //not at the start of link list
                      }
                      else
                      {
                          ptr->get_resistorList().set_head_ResistorList(copy_for_ptr1 -> get_resistor_next());//start of link list
                      }
                      delete copy_for_ptr1;
                      break;
                   }
                  prev = ptr1;//update the prev pointer          
                }
        }       
        return checking;
    }
 }
 
 void NodeList::delete_all_resistor()
 {
    Node *ptr = NULL;//head for NodeList(node type)
   
    if(head == NULL)
    {
         return;
    }
    else
    {
        for(ptr = head; ptr != NULL; ptr = ptr->get_next_node())
        {

            Resistor *ptr1 = NULL;//pointer for ResistorList(resistor type)
            
//            cout << ptr->get_NodeID() << endl;
                ptr1 =  ptr -> get_resistorList().get_head_ResistorList(); 
                while(ptr1 != NULL) 
                {

                    //cout << "prev " << prev << " ptr1 " << ptr1->getName(); 
                   
                    Resistor* ptr2 =  ptr1;//ptr2 is used to copy ptr1 and delete the memory of ResistorList

                          //find the head of ResistorList first, then let the head point to the next
                    
//                    ptr -> get_resistorList().set_head_ResistorList(ptr->get_resistorList().get_head_ResistorList()->set_next_resistor_and_return(ptr2 -> get_resistor_next()));//start of link list
                    ptr -> get_resistorList().set_head_ResistorList(ptr2 -> get_resistor_next());//start of link list
                    //cout << " ptr2_in_the_head " << ptr2->getName() << endl; 
                      
                      delete ptr2;
                      ptr2 = NULL;
                      ptr1 = ptr->get_resistorList().get_head_ResistorList();
               }                   
         }
        
        return;  
     }       
 }
 
 



//calculate the current per term
double NodeList::find_voltage_for_one_term(int new_ID, double connected_resistance)
{
    Node* ptr1 = NULL;
    double current = 0;
    double connected_node_volt = 0;
    for(ptr1 = head; ptr1 != NULL; ptr1 = ptr1->get_next_node())
    {        
        if(new_ID == ptr1->get_NodeID())
        {                                                
             connected_node_volt = ptr1->get_voltage();//get the voltage for that new nodeID
             current = connected_node_volt/connected_resistance;//add the current each time                                          
        }
    }
    return current;

}
 

    
    
 void NodeList::solve()
 { 
     
     double iteration_change = 0;
     bool beginning = true;
     double sum_resistance = 0;
     double sum_current = 0;
     double new_voltage = 0;
     double difference = 0;
//     int counter = 0;
//     while(counter < 100)
     while(MIN_ITERATION_CHANGE < iteration_change || beginning == true)
     {
//         counter++;
         Node *node_without_volt_set;
         beginning = false; 
         double max_iteration_change = 0;
            for(node_without_volt_set = head; node_without_volt_set != NULL; node_without_volt_set = node_without_volt_set->get_next_node())            
            {            
                Resistor* resistorList_ptr = NULL;       

                if(!node_without_volt_set->get_set_bool())
                {
                        int nodeID = node_without_volt_set->get_NodeID();//get nodeID each time
//                        cout << nodeID << endl;
                        for(resistorList_ptr = node_without_volt_set->get_resistorList().get_head_ResistorList(); resistorList_ptr != NULL; resistorList_ptr =  resistorList_ptr->get_resistor_next())
                        {
                               sum_resistance = sum_resistance + 1/(resistorList_ptr->getResistance());
                               int new_ID = resistorList_ptr->get_NodeID(nodeID);//find another new NodeI  

                             
                               double  current_per_term = find_voltage_for_one_term(new_ID, resistorList_ptr->getResistance());
                               sum_current = sum_current + current_per_term;  
                               
//                               cout << "new NodeID " << new_ID << " NodeID " << nodeID <<  "sum_resistance " << sum_resistance << endl;
//                               cout << "sum_current " << sum_current << " current_per_term " << current_per_term << endl;
                        }
                        new_voltage = (1/sum_resistance)*sum_current;
//                        cout << "voltage " << new_voltage << endl;

                        difference = new_voltage - node_without_volt_set->get_voltage();
                        
                        if(abs(difference) > max_iteration_change)
                        {
                            max_iteration_change = abs(difference);
                        }
                        
                        node_without_volt_set->set_voltage_without_bool(new_voltage);
                        sum_resistance = 0;
                        sum_current = 0;
                }
                
             }
          iteration_change = max_iteration_change;
//          cout<<iteration_change<<endl;
          
     }
                  
 }
  

 

 
 void NodeList::print_voltage_for_each_node()
 {
     Node* ptr = NULL;
     cout << "solve" << endl;
     for(ptr = head; ptr != NULL; ptr = ptr->get_next_node())
     {
         cout << "  " <<"Node " <<  ptr->get_NodeID() << ": " << ptr->get_voltage() << " V"<<endl;
//         cout <<  "  " << ptr->get_set_bool() << endl;
     }  
 }
 
 
 

 
// Node* ptr = NULL;
//     for(ptr = head; ptr != NULL; ptr = ptr->get_next_node())//find the unsetV one by one
//    // {
////         cout << ptr-> get_set_bool() << endl;
//         if(!ptr->get_set_bool())//check UnsetV one
//         { 
//            double Volt_for_single_unsetV_prev = 0; 
//            double Volt_for_single_unsetV_current =0;
//            double difference = 0;
//            double max_difference = 0;
//            int counter = 0;
////            cout << ptr->get_minimum_change() << endl;
//            while(counter < 100)//check minimum change for single UnsetV
//            {
//                
//                
//                
//                
//                counter++;
//                Node* node_without_volt_set = NULL;//find all unsetV nodes
//               
//                double sum_resistance = 0;
//                double sum_current = 0;
//                
//                //for all nodes without a set voltage 
//                for(node_without_volt_set = head; node_without_volt_set != NULL; node_without_volt_set = node_without_volt_set->get_next_node())
//                {   
//                    
//                    cout<<"2"<<endl;
//                    
//                    
//                    if(!node_without_volt_set->get_set_bool())//check UnsetV one
//                    {
//                        int nodeID = node_without_volt_set->get_NodeID();//get nodeID each time
//                        cout << "NodeID " << nodeID << endl;
//                        Resistor* resistorList_ptr = NULL;
//                        
//                        
//                        //find connected nodeID
//                         //go through the resistorList
//                        for(resistorList_ptr = node_without_volt_set->get_resistorList().get_head_ResistorList(); resistorList_ptr != NULL; resistorList_ptr =  resistorList_ptr->get_resistor_next())
//                        {
//                            
//                            
//                            cout<<"3"<<endl;
//                            
//                            
//                                int new_ID = resistorList_ptr->get_NodeID(nodeID);//find another new NodeID
//                                double connected_resistance = resistorList_ptr->getResistance();//find the resistance between two nodes 
//                                
//                           
//                                //find the voltage for the new NodeID
//                                Node *ptr1 = NULL;
//                                double connected_node_volt = 0;
//                                
//                                for(ptr1 = head; ptr1 != NULL; ptr1 = ptr1->get_next_node())
//                                {
//                                    
//                                    
//                                    
//                                    cout<<"4"<<endl;
//                                    
//                                    
//                                        if(new_ID == ptr1->get_NodeID())
//                                        {      
//                                            cout << "new NodeID " << new_ID << endl;
//                                            cout << "connected_resistance " << connected_resistance << endl;
//                                            
//                                                connected_node_volt = ptr1->get_voltage();//get the voltage for that new nodeID
//                                                sum_resistance = sum_resistance + 1/connected_resistance;//add the resistance each time
//                                                sum_current = sum_current + connected_node_volt/connected_resistance;//add the current each time
//                                                cout << "new NodeID " << new_ID << " NodeID " << nodeID <<  " connected_node_volt " << connected_node_volt << endl;
//                                                cout << "sum_resistance " << sum_resistance << " sum_current " << sum_current << endl;
//                                               
//                                        }
//                                
//                                    }       
//                               
//                        }    
//                 
//                   
//                        Volt_for_single_unsetV_current = (1/sum_resistance)*sum_current;//final answer for the equation  
//                        cout << "Volt_for_single_unsetV_current " << Volt_for_single_unsetV_current << endl; 
//                        node_without_volt_set->set_voltage_without_bool(Volt_for_single_unsetV_current);
//                        
//                  //reset the sum
//                        sum_resistance = 0;
//                        sum_current = 0;
//                    
//                    
//                    }
//                    
//                   
//                     cout << endl;                        
//                }
//                
//                  Volt_for_single_unsetV_prev = Volt_for_single_unsetV_current;//updating the prev
//                //feedback for voltage difference
//                  difference = abs(Volt_for_single_unsetV_current - Volt_for_single_unsetV_prev);//updating the difference  
//                  ptr->set_minimum_change(difference);//reset the minimum change to each change
//
//            }
//            //set final voltage for that single unsolved node
//            ptr->set_voltage(Volt_for_single_unsetV_current);
//            
//         }