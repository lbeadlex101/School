//-----------------------------------------------------------------------------
// Donald Lee Beadle
// 
// CS 355
// 
// HashTable.cpp
//-----------------------------------------------------------------------------
#include <iostream>
#ifndef HASHTABLE_CPP
#define HASHTABLE_CPP
#include "HashTable.h"
//-----------------------------------------------------------------------------
// Constructor:
// Initializes an object of Class HashTable with a given size. 
template <class T, class K>
HashTable<T, K>::HashTable(int initTableSize): tableSize(initTableSize)
{

	dataTable = new BST<T, K>[tableSize];
	
}
//-----------------------------------------------------------------------------
// Copy Constructor:
// Copies an object of Class HashTable.
template <class T, class K>
HashTable<T, K>::HashTable(const HashTable& other)
{

	tableSize = other.tableSize;
	
	dataTable = new BST<T, K>*[tableSize];
	
	for(int i = 0; i < tableSize; i++)
	{
		dataTable[i] = other.dataTable[i];
	}

}
//-----------------------------------------------------------------------------
// Assignment Operator Overload:
// Assigns an object of Class HashTable to another HashTable object. 
template <class T, class K>
HashTable<T, K>& HashTable<T, K>::operator =(const HashTable& rightTable)
{

	if(tableSize != rightTable.tableSize)
	{
		delete [] dataTable;
		
		tableSize = rightTable.tableSize;
		
		dataTable = new BST<T, K>*[tableSize];
	}
	
	for(int i = 0; i < tableSize; i++)
	{
		dataTable[i] = rightTable[i];
	}

}
//-----------------------------------------------------------------------------
// Destructor: 
// Deallocates memory used by Class HashTable and each BST data structure
// associated with the table. 
template <class T, class K>
HashTable<T, K>::~HashTable()
{

	for(int i = 0; i < tableSize; i++)
	{
		dataTable[i].clear();
	}
	
	delete [] dataTable;

}
//-----------------------------------------------------------------------------
// Insertion Function: 
// Inserts a new item of Type T into the Class HashTable object and hashes
// the key to a location within the table. 
template <class T, class K>
void HashTable<T, K>::insert(T& item) 
{
	
	int index = T::hash(item.getKey()) % tableSize;
	
	dataTable[index].insert(item);
	
}
//-----------------------------------------------------------------------------
// Remove Function: 
// Removes an item, based on key value, from the HashTable. 
template <class T, class K>
bool HashTable<T, K>::remove(const K& key) 
{

	int index = T::hash(key) % tableSize;
	dataTable[index].remove(key);

}
//-----------------------------------------------------------------------------
// Retrieve Function: 
// Returns the value of an item, based on a key, to the console. 
template <class T, class K>
bool HashTable<T, K>::retrieve(const K& searchKey,
					    T& returnItem)  const
{
    int index = T::hash(searchKey) % tableSize;
    
    if(dataTable[index].isEmpty())
    {
    	cout << endl << "Hash location is Empty!" << endl;
    	return false; 
	}
	
	T* item = dataTable[index].search(searchKey);
	
	returnItem = *item;


	return true;
	
}
//-----------------------------------------------------------------------------
// Clear HashTable Function: 
// Clears the HashTable of elements. 
template <class T, class K>
void HashTable<T, K>::clear() 
{

	for(int i = 0; i < tableSize; i++)
	{
		dataTable[i].clear();
	}

}
//-----------------------------------------------------------------------------
// Conditional Check: 
// A boolean function that returns false if an item is found in the HashTable
// and associated BSTs. Returns true if there are no values in the HashTable. 
template <class T, class K>
bool HashTable<T, K>::isEmpty() const
{

	for(int i = 0; i < tableSize; i++)
	{
		if(dataTable[i].isEmpty() == false)
		{
			return false;
		}
	}

	return true;
    
}
//-----------------------------------------------------------------------------
// Output Function: 
// Outputs the values of the HashTable based on key locations. 
template <class T, class K>
void HashTable<T, K>::showStructure()  const
{
	for (int i = 0; i < tableSize; i++) 
	{
		cout << i << ": ";
		dataTable[i].showStructure();
		cout << endl;
	}
}
//-----------------------------------------------------------------------------
#endif
