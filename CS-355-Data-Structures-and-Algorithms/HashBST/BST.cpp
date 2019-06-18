//-----------------------------------------------------------------------------
// Donald Lee Beadle
// 
// CS 355
// 
// BST.cpp
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
template <class T, class K>
BST<T, K>::BST()
{
	
	root = 0;

}
//---------------------------------------------------------------------------
// Destructor: Public
template <class T, class K>
BST<T, K>::~BST()
{

    clear();

}
//-----------------------------------------------------------------------------
// Clear Function: Public
// Calls the private clear function and sets the root data member to NULL.
template <class T, class K>
void BST<T, K>::clear()
{

    clear(root);

    root = 0;

}
//-----------------------------------------------------------------------------
// IsEmpty Function: Public
// Tests the tree to see if it has an items.
template <class T, class K>
bool BST<T, K>::isEmpty()
{

    return root == 0;
    
}
//-----------------------------------------------------------------------------
// Preorder Function: Public
// Calls the protected preorder function to output the tree in preorder
// form.
template <class T, class K>
void BST<T, K>::preorder()
{
	
	preorder(root);

}
//---------------------------------------------------------------------------
// Inorder Function: Public
// Calls the protected inorder function to output the tree in inorder form.
template <class T, class K>
void BST<T, K>::inorder()
{
	
	inorder(root);

}
//---------------------------------------------------------------------------
// Postorder Function: Public
// Calls the protected postorder function to output the tree in postorder 
// form.
template <class T, class K>
void BST<T, K>::postorder()
{
	
	postorder(root);

}
//---------------------------------------------------------------------------
// Search Function: Public
// Accepts a T data element as a parameter and calls the private search 
// member function to search the tree for the referenced element. 
template <class T, class K>
T* BST<T, K>::search(const K& key) const
{
    
    return search(root, key);

}
//---------------------------------------------------------------------------
// Insert Function: Public
// Inserts a new node in the tree with the data element el. 
// Analysis: The complexity of insertion is O(n) as a worst case and O(lg n)
// on average. 
template <class T, class K>
void BST<T, K>::insert(const T& el)
{
	if(root == 0)
    {
        root = new BSTNode<T>(el);
        return;
    }
    
    BSTNode<T>* p = root;
    BSTNode<T>* prev = 0;

    while(p != 0)
    {
        prev = p;
        
        if(el.getKey() < p->el.getKey())
        {
            p = p->left;
        }

        else if(el.getKey() > p->el.getKey())
        {
            p = p->right;
        }
        
        else
        {
        	cout << endl << "Cannot insert duplicate Key!" << endl;
        	return;  
		}
    }

	if(el.getKey() < prev->el.getKey())
    {
        prev->left = new BSTNode<T>(el);
    }

    else if (el.getKey() > prev->el.getKey())
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
template <class T, class K>
bool BST<T, K>::remove(const K& key)
{

    BSTNode<T>* node = root;
    BSTNode<T>* prev = 0;

    while(node != 0)
    {
        if (node->el.getKey() == key)
    		break;

        prev = node;

        if(key < node->el.getKey())
        {
            node = node->left;
        }

        else
            node = node->right;
    }

    if(node != 0 && node->el.getKey() == key)
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
template <class T, class K>
void BST<T, K>::showStructure()
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
//
// ASK ABOUT!
template <class T, class K>
void BST<T, K>::clear(BSTNode<T>* p)
{

	if(p == 0)
	{
		return;
	}
	
	else if(p != 0)
	{
		delete p;
		p = 0;
	}

}
//---------------------------------------------------------------------------
// Search Function: Protected
// Accepts a BSTNode and element of type T as a parameter. Searches the tree 
// until element T is located. 
// Analysis: The search is O(lg n) on average and O(n) for the worst case. 
template <class T, class K>
T* BST<T, K>::search(BSTNode<T>* p, const K& key) const
{

    while(p != 0)
    {
        if(key == p->el.getKey())
        {
            return &p->el;
        }
        
        else if(key < p->el.getKey())
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
template <class T, class K>
void BST<T, K>::merge(BSTNode<T>*& node)
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

		if(temp != root)
		{
			delete temp;	
		}
		
		else
		{
			delete temp;
			root = NULL;
		}
		
        
    }

}
//-----------------------------------------------------------------------------
// Preorder Function: Private
// Outputs the preorder form of the tree to the console using the visit 
// function.
template <class T, class K>
void BST<T, K>::preorder(BSTNode<T> *p)
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
template <class T, class K>
void BST<T, K>::inorder(BSTNode<T> *p)
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
template <class T, class K>
void BST<T, K>::postorder(BSTNode<T> *p)
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
template <class T, class K> 
void BST<T, K>::visit(BSTNode<T>* p)
{

    cout << p->el.getValue() << ' '; 

}
//-----------------------------------------------------------------------------
