//--------------------------------------------------------------------
//
//  CS 355 Fall 2016
//
//  List Implementation
//
//  Donald Lee Beadle
//--------------------------------------------------------------------
#ifndef LIST_CPP
#define LIST_CPP

#include <iostream>
using namespace std;

#include "List.h"

//---------------------------------------------------------------------------
// Default Constructor
template <class T>
List<T>::List (int maxNumber ) 
{

    maxSize = maxNumber;
    size = 0;
    cursor = -1;   
    dataItems = new T[maxSize];
}
//---------------------------------------------------------------------------
// Copy Constructor
template <class T>
List<T>::List (const List& other)
{

    size = other.getSize();

    dataItems = new T[size];

    for(int i=0;i<maxSize;i++)
    {
        dataItems[i] = other.dataItems[i];
    }

}
//---------------------------------------------------------------------------
// Assignment Overload
//template <class T>
//List& List<T>::operator =(const List& rightSide)
//{
//
  //  if(size != maxSize)
    //{
      //  delete [] dataItems;
        //dataItems = new T[rightSide.size];
    //}

   // size = rightSide.size;

    //for(int i=0; i<maxSize; i++)
    //{
     //   dataItems[i] = rightSide.dataItems[i];
    //}

   // return *this;

//} 
//---------------------------------------------------------------------------
// Destructor
template <class T>
List<T>::~List()
{

    delete [] dataItems;

}
//---------------------------------------------------------------------------
// Insert Function 
template <class T>
void List<T>::insert (const T &newDataItem) 
{

    for (int i=size; i > cursor+1; i-- ) 
    {
        dataItems[i] = dataItems[i-1];
    }
    
    size++;
    dataItems[++cursor] = newDataItem;
}
//---------------------------------------------------------------------------
// Remove Function
template <class T>
void List<T>::remove()
{


} 
//---------------------------------------------------------------------------
// Virtual Replace Function
template <class T>
void List<T>::replace(const T& newDataItem)
{


}
//---------------------------------------------------------------------------
// Clear Function
template <class T>
void List<T>::clear()
{


}
//---------------------------------------------------------------------------
// Boolean Function to test if list is empty
template <class T>
bool List<T>::isEmpty()
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
//---------------------------------------------------------------------------
// Boolean Function to test if list is full
template <class T>
bool List<T>::isFull()
{

    if(size == maxSize)
    {
        return true;
    }

    else
        return false;

}
//---------------------------------------------------------------------------
// Move cursor to first data item
template <class T>
void List<T>::goToBeginning()
{

    if(size >= 1)
    {
        cursor = -1;
    }

}
//---------------------------------------------------------------------------
// Move cursor to last data item
template <class T>
void List<T>::goToEnd()
{

    if(size >= 1)
    {
        cursor =  (size - 1);
    }

}
//---------------------------------------------------------------------------
// Move cursor to next data item
template <class T>
bool List<T>::goToNext()
{

    if( (size >= 1) && (size < maxSize) )
    {

        if(cursor != maxSize)
        {
            cursor++;
            return true;
        }
    }

  return false;

}
//---------------------------------------------------------------------------
// Move cursor to prior data item
template <class T>
bool List<T>::goToPrior()
{

    if(isEmpty() == false)
    {

        if(cursor != -1)
        {
            --cursor;
            return true;
        }

    }

    return false;

}
//---------------------------------------------------------------------------
// Return data item marked by cursor position
template <class T>
T List<T>::getCursor()
{


    if(size > 0)
    {
        return dataItems[cursor];
    }

    return 0;

}
//---------------------------------------------------------------------------
//
template <class T>
int List<T>::getSize()
{

  return size;

}
//---------------------------------------------------------------------------
template <class T>
void List<T>::showStructure () const {

    if ( size == 0 ) 
    {
        cout << "empty list" << endl;
    } 
    
    else 
    {
        cout << "size = " << size <<  "   cursor = " << cursor << endl;

        for (int i = 0 ; i < maxSize ; i++ ) 
        {
            cout << i << "\t";
        }
       
        cout << endl;

      
        for (int i = 0 ; i < size ; i++ ) 
        {
            if( i == cursor ) 
            {
                cout << "[" << dataItems[i].getKey() << "]" << "\t"; 
            } 
            else 
            {
              cout << dataItems[i].getKey() << "\t"; 
            }
        }
       
        cout << endl;
    }
}
//-----------------------------------------------------------------------------


#endif // LIST_CPP
