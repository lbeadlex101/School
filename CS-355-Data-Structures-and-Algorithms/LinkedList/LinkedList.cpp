//-----------------------------------------------------------------------------
// LinkedList.cpp
// Linked List Implementation 
// 
// Donald Lee Beadle 
//
//-----------------------------------------------------------------------------
#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP
#include <iostream>
#include "LinkedList.h"
using namespace std;

//-----------------------------------------------------------------------------
// ListNode Constructor:
// Creates a node of class list. 
//-----------------------------------------------------------------------------
template <class T>
List<T>::ListNode::ListNode(const T& nodeData, ListNode* nextPtr)
{
    
    dataItem = nodeData; 
    next = nextPtr;

}

//-----------------------------------------------------------------------------
// Default constructor:
// (Int value ignored)
// Creates an object of Class List as a linked list
//-----------------------------------------------------------------------------
template <class T>
List<T>::List(int ignored)
{
    
    head = 0;
    cursor = 0;

}
//-----------------------------------------------------------------------------
// Copy constructor:
// Creates a deep copy of an object of Class List
//-----------------------------------------------------------------------------
template <class T>
List<T>::List(const List& other)
{
	
	if(other.isEmpty())
	{
		head = 0;
	}
	
	else
	{
		head = new ListNode(*other.head);
	
		ListNode *front = head;
		ListNode *end = other.head->next;
	
		while(end != 0) 
		{
			front->next = new ListNode(*end);
			front = front->next;
			end = end->next;
		}
	
		cursor = new ListNode(*other.cursor);
	}
	
}
//-----------------------------------------------------------------------------
// Overloaded assignment operator:
// Reinitializes the list to be equivalent in content to the "other" list.
// Note: we include self-assignment protection by checking whether
// "this" object is identical to the "other" object.
//-----------------------------------------------------------------------------
template <class T>
List<T>& List<T>::operator =(const List<T>& other)
{
	
	if(other.isEmpty() )
	{
		return *this;
	}
	
	else
	{
		head = new ListNode(other.head->dataItem, 0);
	
		ListNode* front = head;
	
		ListNode* end = other.head->next;
	
		while(end != 0) 
		{	
			front->next = new ListNode(*end);
			front = front->next;
			end = end->next;
		}
	
		cursor = new ListNode(other.cursor->dataItem, other.cursor->next);
	
		return *this;
	}
	
}
//-----------------------------------------------------------------------------
// Destructor:
// Frees the memory used by a list.
//-----------------------------------------------------------------------------
template <class T>
List<T>::~List()
{

    clear();

}
//-----------------------------------------------------------------------------
// Insert Function:
// Inserts newDataItem after the cursor. If the list is empty, then
// newDataItem is inserted as the first (and only) item in the list.
// In either case, moves the cursor to newDataItem.
// 
// This function has worst-case performance of O(1) which is a constant
// This is the case because a data item is added to the end of list as 
// long as the list is full. 
//-----------------------------------------------------------------------------
template <class T>
void List<T>::insert(const T& newDataItem)
{
    if(isEmpty() )
    {
        head = new ListNode(newDataItem, 0);
        cursor = head;   
    }

    else
    {
    	cursor->next = new ListNode(newDataItem, cursor->next);
    	cursor = cursor->next;
    }

}
//-----------------------------------------------------------------------------
// Remove Function:
// Removes the item marked by the cursor from a list. Moves the
// cursor to the next item in the list. Assumes that the first list
// item "follows" the last list item.
//
// This function has a worst-case of O(n) where n represents the number of
// nodes the function must traverse through to find the next to last node. 
// Thus, n is affected by how many or how few nodes are in the list.
//-----------------------------------------------------------------------------
template <class T>
void List<T>::remove()
{

	if(isEmpty() == true)
    {
    	cout << "Cannot remove X item from EMPTY LIST!" << endl;
    }

	else if(cursor==head)
	{
		delete head;
		head = 0;
		cursor = 0;
	}

    else
    {
		ListNode* tmp;
		for(tmp=head; tmp->next !=cursor; tmp=tmp->next);
		delete cursor;
		cursor = tmp;
		cursor->next=0;
	}
  
}
//-----------------------------------------------------------------------------
// Replace Function:
// Replaces the item marked by the cursor with newDataItem and
// leaves the cursor at newDataItem.
//-----------------------------------------------------------------------------
template <class T>
void List<T>::replace(const T& newDataItem)
{

	cursor->dataItem = newDataItem;

}
//-----------------------------------------------------------------------------
// Clear Function:
// Removes all the items from a list. Sets head and cursor to 0.
// deletes all nodes
//-----------------------------------------------------------------------------
template <class T>
void List<T>::clear()
{

    if(isEmpty())
    {
        cout << "Cannot Clear an Empty List!" << endl;
    }

    else if(head == cursor)
    {
        delete head;
    }

    else
    {

        while(!isEmpty())
        {
            ListNode* current = head;
            head = head->next;
            delete current;
        }  
  
    }

    head = 0;
    cursor = 0; 

}
//-----------------------------------------------------------------------------
// isEmpty Function:
// Returns true if a list is empty. Otherwise, returns false.
//-----------------------------------------------------------------------------
template <class T>
bool List<T>::isEmpty() const
{

    return (head == 0);

}
//-----------------------------------------------------------------------------
// isFull Function:
// Returns true if a list is full. Otherwise, returns false.
//-----------------------------------------------------------------------------
template <class T>
bool List<T>::isFull() const
{

    return false;

}
//-----------------------------------------------------------------------------
// gotoBeginning Function:
// If a list is not empty, then moves the cursor to the beginning of
// the list. If list is empty, throws logic error.
//-----------------------------------------------------------------------------
template <class T>
void List<T>::gotoBeginning() throw(logic_error)
{

    if(isEmpty() == true)
    {
        throw "Logic_Error";
    }

    else
    {

	   if(cursor == head)
	   {
	   	   cout << "Top of List!";
	   }

	   else
	   {
		  cursor = head;
	   }
    }
}
//-----------------------------------------------------------------------------
// gotoEnd Function:
// If a list is not empty, then moves the cursor to the end of the
// list. Otherwise, throws logic_error.
//-----------------------------------------------------------------------------
template <class T>
void List<T>::gotoEnd() throw(logic_error)
{

    if(isEmpty() == true)
    {
        throw "Logic Error";
    }

    else
    {
       if(cursor->next == 0)
	   {
	       cout << "End of List!" << endl;
	   }	

	   else
	   {
	       while(cursor->next != 0)
		   {
		      cursor = cursor->next;
		   }
	   }
    }

}
//-----------------------------------------------------------------------------
// gotoNext Function:
// If the cursor is not at the end of a list, then moves the
// cursor to the next item in the list and returns true. Otherwise, 
// leaves cursor unmoved and returns false.
//
// This function has a worst case of O(1) which is a constant. 
// This is the case since the next item can be pointed to as long as 
// there is a next item. 
//-----------------------------------------------------------------------------
template <class T>
bool List<T>::gotoNext()
{

	if(cursor->next != 0)
	{
		cursor = cursor->next;
		return true;
	}

	else
	{
		cout << "END OF LIST!" << endl;
		return false;
	}

}
//-----------------------------------------------------------------------------
// gotoPrior Function: 
// If the cursor is not at the beginning of a list, then moves the
// cursor to the preceeding item in the list and returns true.
// Otherwise, returns false.
// 
// This function has a worst case of O(n) where n represents the number of 
// nodes in a list. 
// This is the case since the previous node to move to is found by traversing 
// the list until the previous node is != to the cursor node. Thus, this
// directly affects the time it will take as dependant on the size of the list. 
//-----------------------------------------------------------------------------
template <class T>
bool List<T>::gotoPrior()
{

	if(head == cursor)
	{
		cout << "TOP of List!" << endl;
		return true;
	}

	else
	{
		ListNode* pred;
		for(pred=head; pred->next !=cursor; pred=pred->next);
		cursor = pred;
		return false;
	}

}
//-----------------------------------------------------------------------------
// getCursor Function:
// Returns the item marked by the cursor. Requires that list is not empty.
//-----------------------------------------------------------------------------
template <class T>
T List<T>::getCursor() const
{

    return cursor->dataItem;

}
//-----------------------------------------------------------------------------
// Output Function: 
// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.
//-----------------------------------------------------------------------------
template <class T>
void List<T>::showStructure() const
{
   
	if( isEmpty() )
	{
        cout << "Empty List" << endl;
	}

    else
    {
        for(ListNode* temp = head; temp != 0; temp = temp->next)
        {
            if(temp == cursor)
            {
                cout << "[";
            }

            cout << temp->dataItem;

            if(temp == cursor)
            {
                cout << "]";
            }
        
            cout << " ";
        }
    }

}
//-----------------------------------------------------------------------------

#endif		// LINKEDLIST_CPP
