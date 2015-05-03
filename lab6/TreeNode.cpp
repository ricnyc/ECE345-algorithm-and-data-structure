#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "TreeNode.h"
TreeNode::TreeNode(DBentry* _entryPtr)
{
    entryPtr = _entryPtr;
    left = NULL;
    right = NULL;
}

TreeNode::~TreeNode()
{
    delete entryPtr;
}

void TreeNode::setLeft(TreeNode* newLeft)
{
    left = newLeft;
}

void TreeNode::setRight(TreeNode* newRight)
{
    right = newRight;
}

TreeNode* TreeNode::getLeft() const
{
    return left;
}

TreeNode* TreeNode::getRight() const
{
    return right;
}

DBentry* TreeNode::getEntry() const
{
    return entryPtr;
}


string TreeNode::maximum()
{
    if(right == NULL)
    {
        return entryPtr->getName();
    }
    else 
        return right->maximum();
}

void TreeNode::deleteNode(TreeNode*& Node, string name, bool &check)
{
        if(name < Node->getEntry()->getName())
        {
            if(left != NULL)
            {
                (left->deleteNode(left, name, check));
            }
            return;
        }
        
        if(name > Node->getEntry()->getName())
        {
            if(right != NULL)
            {
                right->deleteNode(right, name, check);
            }
            return;
        }
        
        if((left == NULL)&&(right == NULL))//no nodes connected
        {
            Node = NULL;
            delete this;
            cout << "Success" << endl;
            check = true;
        }
        else if((left == NULL)&&(right != NULL))//no right node connected
        {
            Node = right;
            right = NULL;
            delete this;
            cout << "Success" << endl;
            check = true;
        }
        else if((left != NULL)&&(right == NULL))//no left node connected
        {
            Node = left;
            left = NULL;
            delete this;
            cout << "Success" << endl;
            check = true;
        }
        else//both left and right nodes connected
        {
            string max = left ->maximum();
            left->deleteNode(left, max, check);
            Node->getEntry()->setName(max);
            cout << "Success" << endl;
            check = true;
        }
}

void TreeNode::print()
{
    if(left != NULL)
    {
        left->print();
    }
    cout << getEntry()->getName() << " : " << getEntry()->getIPaddress() << " : ";
    if(getEntry()->getActive() == true)
    {
        cout << "active" << endl;
    }
    else if(getEntry()->getActive() == false)
    {
        cout << "inactive" << endl;
    }
    if(right != NULL)
    {
        right->print();
    }
}