//-----------------------------------------------------------------------------
// LinkedList.h
// Linked List Interface
// 
// Donald Lee Beadle 
//
//-----------------------------------------------------------------------------
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdexcept>
#include <iostream>

using namespace std;

template <class T>
class List 
{
public:
    List(int ignored = 0); // Compatitibility issue IGNORE!
    List(const List& other); // Copy Constructor
    List& operator=(const List& other); // Overloaded Assignment Operator
    ~List(); // Destructor

    void insert(const T& newDataItem); // Insert dataItem Function
    void remove(); // Remove dataItem
    void replace(const T& newDataItem); // Replace dataItem
    void clear(); // Clear linked list of items

    bool isEmpty() const; // Is List Empty Function
    bool isFull() const; // Is List Full Function

    void gotoBeginning() throw(logic_error); // Sets cursor to beginning of list
    void gotoEnd() throw(logic_error); // Sets cursor to end of list
    bool gotoNext(); // Moves cursor forward through the list
    bool gotoPrior(); // Moves cursor backwards through the list

    T getCursor() const; // Returns cursor's dataItem of type T  

    void showStructure() const; // Debugging Function 

private:
    class ListNode 
    {
    public:
        // Constructs the first node of a linked list
	   ListNode(const T& nodeData, ListNode* nextPtr);
        // Data of type T stored in a linked list
       T dataItem;
        // Pointer to next node in linked list
	   ListNode* next;
    };

    ListNode* head; // Head Node of linked list
    ListNode* cursor; // Cursor Node of linked list
};


#endif // LINKEDLIST_H
