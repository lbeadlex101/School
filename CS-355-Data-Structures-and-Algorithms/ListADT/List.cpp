//--------------------------------------------------------------------
//
//  CS 355 Fall 2016
//
//  Class List Implementation
//
// Copyright (c) 2016 Donald Lee Beadle
//--------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include "List.h"
using namespace std;
//-----------------------------------------------------------------------------
// Default Constructor
// Creates new empty list and allocates enough memory for maximum number of
// data items. 
List::List(int maxNumber)
{

  maxSize = maxNumber;
  dataItems = new int[maxSize];

  for(int i =0; i<maxSize;i++)
  {
    dataItems[i] = '\0';
  }

  cursor = 0;

}
//-----------------------------------------------------------------------------
// Copy Constructor
List::List(const List& other)
{

}
//-----------------------------------------------------------------------------
// Assignment Operator Overload
//List& List::operator =(const List& source)
//{

//}
//-----------------------------------------------------------------------------
// Class List Destructor
// Deallocates the memory created for a list.
List::~List()
{

  delete [] dataItems;

}
//-----------------------------------------------------------------------------
// Insert Function 
// Inserts a new data item into the list based on the cursor position. 
void List::insert(const int& newDataItem)
{
  
  if(isFull() == false)
  {
    size++;
    dataItems[cursor] = newDataItem;
    cursor++;
  }

  else 
  {
    cout << "List Full";
  }  
  
}
//-----------------------------------------------------------------------------
// Remove Data Function:
// Removes the list item based on the cursor position. 
void List::remove()
{

}
//-----------------------------------------------------------------------------
// Replace Function:
// Replaces
void List::replace(const int& newDataItem)
{


}
//-----------------------------------------------------------------------------
// Clear function:
// Clears the list and resets cursor to starting postion. 
void List::clear()
{

  

  for(int i=0;i<size;i++)
  {
    dataItems[i] = 0;
  }

  size = 0;
  cursor = dataItems[0];

}
//-----------------------------------------------------------------------------
// Boolean Test: 
// Tests the first value of a list to see if the list is empty. 
bool List::isEmpty() const
{

  if(size == 0)
  {
    return true;
  }

  else
  {
    return false;
  }

}
//-----------------------------------------------------------------------------
// Boolean Test: 
// Tests the first value of a list to see if the list is full.
bool List::isFull() const
{

  if(size == maxSize)
  {
    return true;
  }

  else
    return false;

}
//-----------------------------------------------------------------------------
// Go To Beggining Function:
// Moves cursor to beginning of list.
void List::gotoBeginning()
{

  if(!isEmpty())
  {
    cursor = 1;
  }

}
//-----------------------------------------------------------------------------
// Go To End Function:
// Moves cursor to last item in list position. 
void List::gotoEnd()
{

  if(!isEmpty())
  {
    cursor =  (size - 1);
  }

}
//-----------------------------------------------------------------------------
// Go To Next Function:
// Moves the cursor from one data item to the next.
//bool List::gotoNext()
//{

//}
//-----------------------------------------------------------------------------
// Go To Prior Function:
// Moves the cursor from one data item to the previous item. 
//bool List::gotoPrior()
//{

//}
//-----------------------------------------------------------------------------
// Accessor Cursor Function:
// Returns the value of the list item at the current cursor position. 
int List::getCursor() const
{

  if(!isEmpty())
  {
    return cursor;
  }

  else
    return 0;

}
//-----------------------------------------------------------------------------
// Debugging Function:
// Shows the structure of the list and current position of the cursor
// with respect to the array. 
void List::showStructure() const
{

  cout << endl << "CURSOR: " << cursor << endl;

  if(size == 0)
  {
    cout << "Empty List!";
  }

  else
  {

    for(int i=0; i<maxSize; i++)
    {
      if(dataItems[i] == 0)
      {
        cout << " ";
      }

      else
      {
        cout << dataItems[i] << " ";
      }
    }

  }

}
//-----------------------------------------------------------------------------
