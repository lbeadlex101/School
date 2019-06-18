//-----------------------------------------------------------------------------
//
//  CS 355 Fall 2016
//
//  Binary Search Tree Interface
//
//  Donald Lee Beadle
//-----------------------------------------------------------------------------
#include <iostream>
using namespace std;

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE
//-----------------------------------------------------------------------------
// BST Node Interface
template<class T>
class BSTNode 
{
public:
    BSTNode(); // Default Constructor
    BSTNode(const T& e); // Copy Constructor 
	
    T el;   // Element
    BSTNode<T> *left, *right; // Left and right children
};
//-----------------------------------------------------------------------------
// BST Structure Interface 
template<class T>
class BST 
{
public:
    BST(); // BST constructor 
    ~BST(); // BST destructor 
    void clear(); // Clears the tree
    bool isEmpty(); // Returns true if tree is empty

    void preorder(); // Preorder traversal
    void inorder(); // Inorder traversal
    void postorder(); // Postorder traversal

    T* search(const T& el) const; // Searching function
    void insert(const T& el); // Insert Function
    bool remove(const T& el); // Returns true if element is found

    void showStructure(); // Generates tree structure as a list. 


private:
    BSTNode<T>* root; // Private Data Member 

    void clear(BSTNode<T>* p); // Clear Function
    T* search(BSTNode<T>* p, const T& el) const; // Searching Function
    void merge(BSTNode<T>*& node); // Deletion By Merging Function

    void preorder(BSTNode<T>*); // Preorder Traversal
    void inorder(BSTNode<T>*); // Inorder Traversal
    void postorder(BSTNode<T>*); // Postorder Traversal
    virtual void visit(BSTNode<T>* p); // Print Function
   
};
//-----------------------------------------------------------------------------

#endif // BST_H
