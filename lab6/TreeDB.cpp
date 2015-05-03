#include "TreeDB.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
TreeDB::TreeDB()
{
    root = NULL;
    probesCount = 0;
}

TreeDB::~TreeDB()
{}

bool TreeDB::insert(DBentry* newEntry)
{

    
    TreeNode *ins = new TreeNode(newEntry);

    if(root == NULL)//basic
    {
        root = ins;
        root->setLeft(NULL);
        root->setRight(NULL);
        return true;
    }
    
    //private helper function
    return(insert_help_function(ins, root));
}

DBentry* TreeDB::find(string name)
{
    if(root == NULL)
    {
        cout << "Error: entry does not exist" << endl;
        return NULL;
    }
    return(find_help_function(root, name));
}

void TreeDB::printall()//inorder printing
{
    if(root != NULL)
    root->print();
}


bool TreeDB::remove(string name)
{
    if(root == NULL)//empty tree
    {
        cout << "Error: entry does not exist" << endl;
        return false;
    }
    bool check = false;
   root->deleteNode(root, name, check);
   if(!check)
   {
        cout << "Error: entry does not exist" << endl;
        return false;
   }
   return true;
}

void TreeDB::clear()
{
    if(root == NULL)
    {
        return;
    }
    help_clear_function(root);
    root = NULL;
}


void TreeDB::printProbes(string name)
{
    if(root == NULL)
    {
        cout << "Error: entry does not exist" << endl;
        return;
    }
    int level = 1;//initialize the level
    help_find_level(root, name, level);
}

void TreeDB::countActive()
{
    if(root == NULL)
    {
        return;
    }
    int count = 0;
    help_checking_active(root, count);
    cout << count << endl;
}

void TreeDB::help_checking_active(TreeNode* Node, int &count)
{
    if(Node != NULL)
    {
        help_checking_active(Node->getLeft(), count);
        if(Node->getEntry()->getActive() == true)
        {
            count++;
        }
        help_checking_active(Node->getRight(), count);
    }
    
}

//insert inorder 
bool TreeDB::insert_help_function(TreeNode* ins, TreeNode* curr)
{
    if(ins->getEntry()->getName() == curr->getEntry()->getName())    
    {
        delete ins;
        return false;//no repeat insertions
    } 
    
    //Go left
    if(ins->getEntry()->getName() < curr->getEntry()->getName())
    {       
        if(curr->getLeft() == NULL)
        {
                curr->setLeft(ins);
                return true;
//                probesCount++;
        }
        else
         return(insert_help_function(ins, curr->getLeft()));
    }
    
    //Go right
    else
    {
        if(curr->getRight() == NULL)
        {
            curr->setRight(ins); 
            return true;
        }
        else
            return(insert_help_function(ins, curr->getRight()));
    }
}




 void TreeDB::print_help_function(TreeNode* node)
 {     

     
    if(node != NULL)
    {
        print_help_function(node->getLeft());//print the right result 
        cout << node->getEntry()->getName() << " : " << node->getEntry()->getIPaddress() << " : ";
        if(node->getEntry()->getActive() == true)
        {
            cout << "active" << endl;
        }
        else if(node->getEntry()->getActive() == false)
        {
            cout << "inactive" << endl;
        }
        print_help_function(node->getRight());
    }
 }
 
 
DBentry* TreeDB::find_help_function(TreeNode* node, string name)
{
        
    if(node == NULL)//does not find the name
    {
        cout << "Error: entry does not exist" << endl;
        return NULL;
    }
    if(node->getEntry()->getName() == name)//found
    {
        //printing the value
        cout << node->getEntry()->getName() << " : " << node->getEntry()->getIPaddress() << " : ";
        if(node->getEntry()->getActive() == true)
        {
            cout << "active" << endl;
        }
        else if(node->getEntry()->getActive() == false)
        {
            cout << "inactive" << endl;
        }
        return node->getEntry();
    }
    if(name < node ->getEntry()->getName())
    {
        return(find_help_function(node->getLeft(), name));
    }
    else 
        return(find_help_function(node->getRight(), name));

}

//using updating the status for active and inactive
 DBentry* TreeDB::update_status(string name, bool active)
 {
    DBentry* info = NULL;
    if(root == NULL)
    {
        cout << "Error: entry does not exist" << endl;
        return NULL;
    }
    info = update_help_function(root, name);
    
    //avoid return NULL and set value
    if(info != NULL)
    {
        info->setActive(active);
    }
    
    return info;
    
 }
 
DBentry* TreeDB::update_help_function(TreeNode* node, string name)
{
        
    if(node == NULL)//does not find the name
    {
        cout << "Error: entry does not exist" << endl;
        return NULL;
    }
    if(node->getEntry()->getName() == name)//found
    {
        cout << "Success" << endl;
        return node->getEntry();
    }
    if(name < node ->getEntry()->getName())
    {
        return(update_help_function(node->getLeft(), name));
    }
    else 
        return(update_help_function(node->getRight(), name));

}


void TreeDB::help_find_level(TreeNode* node, string name, int &level)
{   
    if(node == NULL)//does not find the name in the tree
    {        
        cout << "Error: entry does not exist" << endl;
        return;
    }
    if(node->getEntry()->getName() == name)//found
    {
        cout << level << endl;
        return;
    }
    if(name < node ->getEntry()->getName())
    {
        level++;
        help_find_level(node->getLeft(), name, level);
    }
    else 
    {
        level++;
        help_find_level(node->getRight(), name, level);
    }
}


void TreeDB::help_clear_function(TreeNode* Node)//delete the treenode
{
    if(Node == NULL)
    {
        return;
    }
    help_clear_function(Node->getLeft());
    help_clear_function(Node->getRight());
    
    delete Node;
}
