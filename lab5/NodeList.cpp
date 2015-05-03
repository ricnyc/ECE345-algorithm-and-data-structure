


#include "Node.h"
#include "NodeList.h"
#include "ResistorList.h"
using namespace std;
#include <cmath>        // std::abs

#define MIN_ITERATION_CHANGE 0.0001

NodeList::NodeList() 
{
    head = NULL;
//    cout << "new_node_list" << endl;
}

NodeList::~NodeList() {
    delete head;
//    cout << "delete_node_list" << endl;
}

void NodeList::set_head(Node* head_) {
    head = head_;
}

Node* NodeList::find_head_of_NodeList() {
    return head;
}

//checking the node inside nodelist
Node* NodeList::find_node(int nodeID) {
    Node *ptr = NULL;
    for (ptr = head; ptr != NULL; ptr = ptr->get_next_node()) {
        if (nodeID == ptr->get_NodeID()) {
            return ptr;
        }
        if (nodeID < ptr->get_NodeID()) {
            return NULL;
        }
    }

    head = NULL;
    return NULL;
}


Node* NodeList::find_or_insert_node(int nodeID) {
    Node *ptr = NULL;

    for (ptr = head; ptr != NULL; ptr = ptr->get_next_node()) {
        if (nodeID == ptr->get_NodeID()) {
            return ptr;
        }
    }
    //head = NULL;
    Node* prev = NULL; //insert the correct position in the node list
    Node* curr = head;

    while (curr != NULL && nodeID > curr->get_NodeID())//not the end of list and ID larger the current checking position
    {
        //        cout << "inside the updating process" << endl;
        prev = curr;
        curr = curr-> get_next_node(); //update the curr position
    }

    Node *newNode = new Node(nodeID, curr); //connect the position to next

    if (prev == NULL) {
        //        cout << "NodeList_inside1"<< endl;
        head = newNode; //empty list and NodeID smaller than first node
    } else {
        //        cout << "NodeList_inside2" << endl;
        prev-> set_next_node(newNode);
    }
    return newNode;
}

bool NodeList::check_resistor_in_nodelist(string name) {
    Node *ptr = NULL; //head for NodeList(node type)

    for (ptr = head; ptr != NULL; ptr = ptr->get_next_node()) {
        //        cout << ptr->get_NodeID() << endl;
        Resistor *ptr1 = NULL; //pointer for ResistorList(resistor type)
        for (ptr1 = ptr->get_resistorList().get_head_ResistorList(); ptr1 != NULL; ptr1 = ptr1 -> get_resistor_next()) {
            //            cout << "name_input: " << name << " name_exiting " << ptr1->getName() << endl;
            if (name == ptr1->getName()) {
                //                cout << "name_input: " << name << "name_exiting" << ptr1->getName()
                cout << "Print: " << endl;
                ptr1->print();
                return true;
            }
        }
    }
    return false;
}


int NodeList::change_resistance(string name, double& resistance) {
    Node *ptr = NULL; //head for NodeList(node type)
    double resistance1 = resistance;
    int checking = 0; //check find the resistor or not
    int get_resistance = 0;
    for (ptr = head; ptr != NULL; ptr = ptr->get_next_node()) {
        //        cout << ptr->get_NodeID() << endl;
        Resistor *ptr1 = NULL; //pointer for ResistorList(resistor type)
        for (ptr1 = ptr ->get_resistorList().get_head_ResistorList(); ptr1 != NULL; ptr1 = ptr1 -> get_resistor_next()) {
            //            cout << ptr1->getName() << endl;
            if (name == ptr1->getName()) {
                if (get_resistance == 0) {
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


int NodeList::delete_resistor(string name) {
    Node *ptr = NULL; //head for NodeList(node type)
    int checking = 0;
    if (head == NULL) {
        return checking;
    } else {
        for (ptr = head; ptr != NULL; ptr = ptr->get_next_node()) {
            Resistor* prev = NULL;
            Resistor* ptr1 = NULL; //pointer for ResistorList(resistor type)
            for (ptr1 = ptr -> get_resistorList().get_head_ResistorList(); ptr1 != NULL; ptr1 = ptr1 -> get_resistor_next()) {
                Resistor* copy_for_ptr1 = NULL;
                copy_for_ptr1 = ptr1;
                if (name == copy_for_ptr1->getName()) {
                    checking++;
                    if (prev != NULL) {
                        prev -> set_next_resistor(copy_for_ptr1 -> get_resistor_next()); //not at the start of link list
                    } else {
                        ptr->get_resistorList().set_head_ResistorList(copy_for_ptr1 -> get_resistor_next()); //start of link list
                    }
                    delete copy_for_ptr1;
                    break;
                }
                prev = ptr1; //update the prev pointer          
            }
        }
        return checking;
    }
}


void NodeList::delete_all_resistor() {
    Node *ptr = NULL; //head for NodeList(node type)

    if (head == NULL) {
        return;
    } else {
        for (ptr = head; ptr != NULL; ptr = ptr->get_next_node()) {

            Resistor *ptr1 = NULL; //pointer for ResistorList(resistor type)

            //            cout << ptr->get_NodeID() << endl;
            ptr1 = ptr -> get_resistorList().get_head_ResistorList();
            while (ptr1 != NULL) {

                //cout << "prev " << prev << " ptr1 " << ptr1->getName(); 

                Resistor* ptr2 = ptr1; //ptr2 is used to copy ptr1 and delete the memory of ResistorList

                //find the head of ResistorList first, then let the head point to the next

                //                    ptr -> get_resistorList().set_head_ResistorList(ptr->get_resistorList().get_head_ResistorList()->set_next_resistor_and_return(ptr2 -> get_resistor_next()));//start of link list
                ptr -> get_resistorList().set_head_ResistorList(ptr2 -> get_resistor_next()); //start of link list
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
double NodeList::find_voltage_for_one_term(int new_ID, double connected_resistance) {
    Node* ptr1 = NULL;
    double current = 0;
    double connected_node_volt = 0;
    for (ptr1 = head; ptr1 != NULL; ptr1 = ptr1->get_next_node()) {
        if (new_ID == ptr1->get_NodeID()) {
            connected_node_volt = ptr1->get_voltage(); //get the voltage for that new nodeID
            current = connected_node_volt / connected_resistance; //add the current each time                                          
        }
    }
    return current;

}



void NodeList::solve() {

    double iteration_change = 0;
    int beginning = 1;//first time go inside the while loop
    double sum_resistance = 0;
    double sum_current = 0;
    double new_voltage = 0;
    double difference = 0;

    while (MIN_ITERATION_CHANGE < iteration_change || beginning == 1) {
        //         counter++;
        Node *node_without_volt_set;
        beginning = 0;
        double max_iteration_change = 0;
        for (node_without_volt_set = head; node_without_volt_set != NULL; node_without_volt_set = node_without_volt_set->get_next_node()) {
            Resistor* resistorList_ptr = NULL;

            if (!node_without_volt_set->get_set_bool()) {
                int nodeID = node_without_volt_set->get_NodeID(); //get nodeID each time
                //                        cout << nodeID << endl;
                for (resistorList_ptr = node_without_volt_set->get_resistorList().get_head_ResistorList(); resistorList_ptr != NULL; resistorList_ptr = resistorList_ptr->get_resistor_next()) {
                    sum_resistance = sum_resistance + 1 / (resistorList_ptr->getResistance());
                    int new_ID = resistorList_ptr->get_NodeID(nodeID); //find another new NodeI  


                    double current_per_term = find_voltage_for_one_term(new_ID, resistorList_ptr->getResistance());
                    sum_current = sum_current + current_per_term;

                    //                               cout << "new NodeID " << new_ID << " NodeID " << nodeID <<  "sum_resistance " << sum_resistance << endl;
                    //                               cout << "sum_current " << sum_current << " current_per_term " << current_per_term << endl;
                }
                new_voltage = (1 / sum_resistance) * sum_current;
                //                        cout << "voltage " << new_voltage << endl;

                difference = new_voltage - node_without_volt_set->get_voltage();
                updating_max_iteration_change(difference, max_iteration_change);
                

                node_without_volt_set->set_voltage_without_bool(new_voltage);
                sum_resistance = 0;
                sum_current = 0;
            }

        }
        iteration_change = max_iteration_change; //if the maximum change inside the NodeList is smaller than min_iteration_change, then works 

    }

}

//prii
void NodeList::print_voltage_for_each_node() {
    Node* ptr = NULL;
    cout << "Solve:" << endl;
    for (ptr = head; ptr != NULL; ptr = ptr->get_next_node()) {
        cout << "  " << "Node " << ptr->get_NodeID() << ": " << ptr->get_voltage() << " V" << endl;
        //         cout <<  "  " << ptr->get_set_bool() << endl;
    }
}

void NodeList::delete_memory() {
    Node *ptr = NULL; //head for NodeList(node type)

    if (head == NULL) 
    {

    } 
    else {
        for (ptr = head; ptr != NULL; ptr = ptr->get_next_node()) {

            Resistor *ptr1 = NULL; //pointer for ResistorList(resistor type)

            //            cout << ptr->get_NodeID() << endl;
            ptr1 = ptr -> get_resistorList().get_head_ResistorList();
            while (ptr1 != NULL) {

                //cout << "prev " << prev << " ptr1 " << ptr1->getName(); 

                Resistor* ptr2 = ptr1; //ptr2 is used to copy ptr1 and delete the memory
                ptr -> get_resistorList().set_head_ResistorList(ptr2 -> get_resistor_next()); //start of link list


                delete ptr2;
//////                 cout << "delete_resistor" << endl;
                ptr2 = NULL;
                ptr1 = ptr->get_resistorList().get_head_ResistorList();
            }
        }


    }

    //delete the NodeList
    Node *ptr3 = NULL; //head for NodeList(node type)
    ptr3 = head;
    while (ptr3 != NULL) {
        Node *ptr3_copy = ptr3;
        set_head(ptr3_copy->get_next_node());

        delete ptr3_copy;

        ptr3_copy = NULL;
        ptr3 = head;
    }


}

//updating the max iteration change
double NodeList::updating_max_iteration_change(double difference, double &max_iteration_change) const
{

     if (abs(difference) > max_iteration_change) 
     {
         max_iteration_change = abs(difference); //find the maximum_change 
     }
}

