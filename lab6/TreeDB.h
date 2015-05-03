#ifndef _TREEDB_H
#define _TREEDB_H

#include "TreeNode.h"
#include "DBentry.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
class TreeDB {

private:
   TreeNode* root;
   int probesCount;
   
   // You will need to add additional private functions
   
   bool insert_help_function(TreeNode* ins, TreeNode* curr);
   void print_help_function(TreeNode* Node);
   DBentry* find_help_function(TreeNode* Node, string name);   
   void help_find_level(TreeNode* node, string name, int& level);
   void help_clear_function(TreeNode* Node);
   void help_checking_active(TreeNode* Node, int &count);
   DBentry* update_help_function(TreeNode* node, string name);
   
public:
   // the default constructor, creates an empty database.
   TreeDB();

   // the destructor, deletes all the entries in the database.
   ~TreeDB();

   // inserts the entry pointed to by newEntry into the database. 
   // If an entry with the same key as newEntry's exists 
   // in the database, it returns false. Otherwise, it returns true.
   bool insert(DBentry* newEntry); 

   // searches the database for an entry with a key equal to name.
   // If the entry is found, a pointer to it is returned.
   // If the entry is not found, the NULL pointer is returned.
   // Also sets probesCount
   DBentry* find(string name);

   // deletes the entry with the specified name (key)  from the database.
   // If the entry was indeed in the database, it returns true.
   // Returns false otherwise.
   // See section 6 of the lab handout for the *required* removal method.
   // If you do not use that removal method (replace deleted node by
   // maximum node in the left subtree when the deleted node has two children)
   // you will not match exercise's output.
   bool remove(string name);
	
   // deletes all the entries in the database.
   void clear();
    
   // prints the number of probes stored in probesCount
   void printProbes(string name);
   
   // computes and prints out the total number of active entries
   // in the database (i.e. entries with active==true).
   void countActive ();
   

   // Prints the entire tree, in ascending order of key/name
   
   void printall(); 
   
   DBentry* update_status(string name, bool active);
   
   friend ostream& operator<< (ostream& out, const TreeDB& rhs);
}; 

// You *may* choose to implement the function below to help print the 
// tree.  You do not have to implement this function if you do not wish to.
ostream& operator<< (ostream& out, TreeNode* rhs);   
   
#endif 

