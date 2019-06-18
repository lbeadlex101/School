//-----------------------------------------------------------------------------
//
//  CS 355 Fall 2016
//
//  Binary Search Tree Implementation
//
//  Donald Lee Beadle
//-----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include "BST.h"
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Class BSTNode Members:
//-----------------------------------------------------------------------------
// Default Node Constructor: Public
template <class T>
BSTNode<T>::BSTNode()
{

	left = right = 0;

}
//-----------------------------------------------------------------------------
// Node Constructor: Public
template <class T>
BSTNode<T>::BSTNode(const T& e)
{

	BSTNode<T>* l = 0;
	BSTNode<T>* r = 0;

	el = e; 
	left = l; 
	right = r; 

}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Class BST Members:
//-----------------------------------------------------------------------------
// Default Constructor: Public
template <class T>
BST<T>::BST()
{
	
	root = 0;

}
//---------------------------------------------------------------------------
// Destructor: Public
template <class T>
BST<T>::~BST()
{

    clear();

}
//-----------------------------------------------------------------------------
// Clear Function: Public
// Calls the private clear function and sets the root data member to NULL.
template <class T>
void BST<T>::clear()
{

    clear(root);

    root = 0;

}
//-----------------------------------------------------------------------------
// IsEmpty Function: Public
// Tests the tree to see if it has an items.
template <class T>
bool BST<T>::isEmpty()
{

    return root == 0;
    
}
//-----------------------------------------------------------------------------
// Preorder Function: Public
// Calls the protected preorder function to output the tree in preorder
// form.
template <class T>
void BST<T>::preorder()
{
	
	preorder(root);

}
//---------------------------------------------------------------------------
// Inorder Function: Public
// Calls the protected inorder function to output the tree in inorder form.
template <class T>
void BST<T>::inorder()
{
	
	inorder(root);

}
//---------------------------------------------------------------------------
// Postorder Function: Public
// Calls the protected postorder function to output the tree in postorder 
// form.
template <class T>
void BST<T>::postorder()
{
	
	postorder(root);

}
//---------------------------------------------------------------------------
// Search Function: Public
// Accepts a T data element as a parameter and calls the private search 
// member function to search the tree for the referenced element. 
template <class T>
T* BST<T>::search(const T& el) const
{
    
    return search(root, el);

}
//---------------------------------------------------------------------------
// Insert Function: Public
// Inserts a new node in the tree with the data element el. 
// Analysis: The complexity of insertion is O(n) as a worst case and O(lg n)
// on average. 
template <class T>
void BST<T>::insert(const T& el)
{

    BSTNode<T>* p = root;
    BSTNode<T>* prev = 0;

    while(p != 0)
    {
        prev = p;
        
        if(el < p->el)
        {
            p = p->left;
        }

        else
        {
            p = p->right;
        }
    }

    if(root == 0)
    {
        root = new BSTNode<T>(el);
    }

    else if(el < prev->el)
    {
        prev->left = new BSTNode<T>(el);
    }

    else
    {
        prev->right = new BSTNode<T>(el);
    }
}
//-----------------------------------------------------------------------------
// Remove Function: Public
// Removes an element, passed as a parameter, from the tree using the method
// deletion by merging. 
// Analysis: The remove function is complexity O(n) and is more complex than 
// insertion. 
template <class T>
bool BST<T>::remove(const T& el)
{

    BSTNode<T>* node = root;
    BSTNode<T>* prev = 0;

    while(node != 0)
    {
        if (node->el == el)
    		break;

        prev = node;

        if(el < node->el)
        {
            node = node->left;
        }

        else
            node = node->right;
    }

    if(node != 0 && node->el == el)
    {
        if(node == root)
            merge(root);

        else if(prev->left == node)
        	merge(prev->left);

        else
            merge(prev->right);
            
        return true;
    }

	else 
	{
		return false;
	}
	
}
//-----------------------------------------------------------------------------
// Show Structure Function: Public
// Outputs the tree's structure to the console. For debugging purposes. 
// DOES NOT output tree in tree-like structure. Outputs as a pre-ordered list. 
template <class T>
void BST<T>::showStructure()
{

	BSTNode<T>* node = root;
//	int middle = 60; // Was using for setw function in tree-like display

	if(root == 0)
	{
		cout << "EMPTY Tree! \n";
	}
	
	else
	{
		preorder(node);	
		cout << endl;
	}
	
}
//---------------------------------------------------------------------------
// Clear Function: Protected
// Accepts a Binary Search Tree Node as a parameter and deletes the tree. The
// Node pointer is then set to NULL.
template <class T>
void BST<T>::clear(BSTNode<T>* p)
{

	while (p == 0)
	{
		clear(p->left);
		clear(p->right);
		delete p;
	}
	
}
//---------------------------------------------------------------------------
// Search Function: Protected
// Accepts a BSTNode and element of type T as a parameter. Searches the tree 
// until element T is located. 
// Analysis: The search is O(lg n) on average and O(n) for the worst case. 
template <class T>
T* BST<T>::search(BSTNode<T>* p, const T& el) const
{

    while(p != 0)
    {
        if(el == p->el)
        {
            return &p->el;
        }
        
        else if(el < p->el)
        {
            p = p->left;
        }

        else 
        {
            p = p->right;
        }
    }

    return 0;
    
}
//---------------------------------------------------------------------------
// Deletion by Merging Function: Private
// Uses the method Deletion by Merging to remove an element from the tree. 
template <class T>
void BST<T>::merge(BSTNode<T>*& node)
{

    BSTNode<T>* temp = node;

    if(node != 0)
    {
        if(!node->right)
            node = node->left;

        else if(node->left == 0)
            node = node->right;

        else
        {
            temp = node->left;

            while(temp->right != 0)
            {
                temp = temp->right;
            }

            temp->right = node->right;
            node = node->left;
        }

        delete temp;
    }

}
//-----------------------------------------------------------------------------
// Preorder Function: Private
// Outputs the preorder form of the tree to the console using the visit 
// function.
template <class T>
void BST<T>::preorder(BSTNode<T> *p)
{

    if(p != 0)
    {
        visit(p);
        preorder(p->left);
        preorder(p->right);
    }

}
//---------------------------------------------------------------------------
// Inorder Function: Private
// Outputs the inorder form of the tree to the console using the visit 
// function. 
template <class T>
void BST<T>::inorder(BSTNode<T> *p)
{
    if(p != 0)
    {
        inorder(p->left);
        visit(p);
        inorder(p->right);
    }
}

//---------------------------------------------------------------------------
// Postorder Function: Private
// Outputs the postorder form of the tree to the console using the visit 
// function. 
template <class T>
void BST<T>::postorder(BSTNode<T> *p)
{

    if(p != 0)
    {
        postorder(p->left);
        postorder(p->right);
        visit(p);
    }

}
//---------------------------------------------------------------------------
// Visit Function:
// Outputs the element of a tree node to the console.
template <class T> 
void BST<T>::visit(BSTNode<T>* p)
{

    cout << p->el << ' '; 

}
//-----------------------------------------------------------------------------
