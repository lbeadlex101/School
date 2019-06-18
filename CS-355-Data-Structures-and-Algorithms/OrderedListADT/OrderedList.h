//--------------------------------------------------------------------
//
//  CS 355 Fall 2016
//
//  Ordered List Interface
//
//  Donald Lee Beadle
//--------------------------------------------------------------------
#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H

#include <iostream>
using namespace std;

#include "List.cpp"

template <class T, class KeyType>
class OrderedList : public List<T>
{
public:

    OrderedList ( int maxNumber = List<T>::MAX_LIST_SIZE );
    virtual void insert ( const T &newDataItem );
    
    void replace ( const T& newDataItem ); 
    bool retrieve (const KeyType& searchKey, T&);

    void showStructure () const;

private:

    bool binarySearch ( KeyType searchKey, int &index );

};

#endif // #ifndef ORDEREDLIST_H

