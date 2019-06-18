//-----------------------------------------------------------------------------
// Donald Lee Beadle
// 
// CS 355
// 
// HashTable.h 
//-----------------------------------------------------------------------------
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdexcept>
#include <iostream>
#include "BST.cpp"
using namespace std;

template <class T, class K>
class HashTable 
{
public:
	// Constructors and = overload
	HashTable(int initTableSize); 
    HashTable(const HashTable& other);
    HashTable& operator=(const HashTable& rightTable);

	// Destructor 
    ~HashTable();

	// HashTable Operation Functions
    void insert(T& newDataItem);  
    bool remove(const K& deleteKey);
    bool retrieve(const K& searchKey, T& returnItem) const;
    void clear();

	// HashTable Conditional Check
    bool isEmpty() const;

	// Output HashTable Function
    void showStructure() const;

private:
	int tableSize;
	BST<T, K>* dataTable;
};

#endif	// ifndef HASHTABLE_H
