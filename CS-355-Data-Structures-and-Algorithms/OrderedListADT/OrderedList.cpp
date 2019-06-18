//--------------------------------------------------------------------
//
//  CS 355 Fall 2016
//
//  Ordered List Implementation
//
//  Donald Lee Beadle
//--------------------------------------------------------------------
#ifndef ORDEREDLIST_CPP
#define ORDEREDLIST_CPP

#include "OrderedList.h"

template <class T, class KeyType >
OrderedList<T,KeyType>:: OrderedList ( int maxNumber ) : List<T>(maxNumber) 
{   }
//---------------------------------------------------------------------------
// Replaces the data item marked by the cursor with newData and
// moves the cursor to newData.
template <class T, class KeyType >
void OrderedList<T, KeyType>:: replace ( const T& newDataItem ) 
{

    if ( binarySearch(newDataItem.getKey(), this->cursor) ) 
    {
        this->dataItems[this->cursor] = newDataItem;                                  
        ++this->cursor;
  
    }
}
//---------------------------------------------------------------------------
// Searches a list for the data item with key searchKey. If the
// data item is found, then moves the cursor to the data item,
// copies the data item to searchDataItem, and returns true.
// Otherwise, returns false without moving the cursor and with
// searchDataItems undefined.
template <class T, class KeyType >
bool OrderedList<T, KeyType>:: retrieve ( const KeyType& searchKey, T&)
{



}
//-----------------------------------------------------------------------------
// Inserts newDataItem in its appropriate location within an ordered
// list. If a data item with the same key as newData already
// exists in the list, then updates that data item's data with
// newData's data. Moves the cursor to newData.
template <class T, class KeyType >
void OrderedList<T, KeyType>:: insert ( const T& newDataItem ) 
{
    //Exception Handling

    if ( binarySearch(newDataItem.getKey(), this->cursor) ) 
    {
        this->dataItems[this->cursor] = newDataItem;
	} 
    else 
    {       
        for ( int j = this->size-1 ; j > this->cursor ; --j )
        {
            this->dataItems[j+1] = this->dataItems[j];
        }
        ++this->cursor;
        this->dataItems[this->cursor] = newDataItem;
        ++this->size;
    }
}
//-----------------------------------------------------------------------------
// Output the list structure -- used in testing/debugging
template <typename T, typename KeyType>
void OrderedList<T,KeyType>:: showStructure () const 
{
    if ( this->size == 0 ) 
    {
    cout << "Empty list" << endl;
	} 
    else 
    {
        cout << "size = " << this->size <<  "   cursor = " 
             << this->cursor << endl;

       for ( int j = 0 ; j < this->maxSize ; ++j )
           cout << j << "\t";

       cout << endl;

       for ( int j = 0 ; j < this->size ; ++j ) 
        {
	        if( j == this->cursor ) 
            {
	           cout << "[" << this->dataItems[j].getKey() << "]\t";
		    } 
            else 
            {
	           cout << this->dataItems[j].getKey() << "\t";
		    }
       }
    
       cout << endl;
    }
}

//-----------------------------------------------------------------------------
// Binary search routine. Searches a list for the data item with
// key searchKey. If the data item is found, then returns true with
// index returning the array index of the entry containing searchKey.
// Otherwise, returns false with index returning the array index of the
// entry containing the largest key that is smaller than searchKey
// (or -1 if there is no such key).
template < typename T, typename KeyType >
bool OrderedList<T,KeyType>:: binarySearch ( KeyType searchKey, int &index )
{
    int low  = 0,           // Low index of current search range
        high = this->size - 1;    // High index of current search range
    bool result;            // Result returned

    while ( low <= high )
    {
        index = ( low + high ) / 2;               // Compute midpoint
        if ( searchKey < this->dataItems[index].getKey() )
           high = index - 1;                      // Search lower half
        else if ( searchKey > this->dataItems[index].getKey() )
           low = index + 1;                       // Search upper half
        else
           break;                                 // searchKey found
    }

    if ( low <= high )
       result = true;       // searchKey found
    else
    {
       index = high;        // searchKey not found, adjust index
       result = false;
    }

    return result;
}
//---------------------------------------------------------------------------

#endif
