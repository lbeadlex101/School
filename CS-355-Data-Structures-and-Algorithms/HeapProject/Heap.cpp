//---------------------------------------------------------------------------
// Donald Lee Beadle
// 
// CS 355
//
// Heap.cpp
//---------------------------------------------------------------------------
#ifndef HEAP_CPP
#define HEAP_CPP
#include <algorithm>
#include "Heap.h"
using namespace std;
//---------------------------------------------------------------------------
// Default constructor. Initializes an object of Class Heap with a max size 
// as passed by the parameter int max.
Heap::Heap(int max)
{

    maxSize = max;
    size = 0;
	dataItems = new int[maxSize];
    
}
//---------------------------------------------------------------------------
// Copy Constructor:
Heap::Heap(const Heap& other)
{

	maxSize = other.maxSize;
	size = other.size;
	dataItems = new int[maxSize];
	
	for(int i =0; i < size; i++)
	{
		dataItems[i] = other.dataItems[i];
	}

}
//---------------------------------------------------------------------------
// Assignment Operator:
Heap& Heap::operator=(const Heap& other)
{

	if(this == &other)
	{
		return *this;	
	}
	
	if(other.maxSize > maxSize)
	{
		delete [] dataItems;
		dataItems = new int[other.maxSize];
	}
	
	maxSize = other.maxSize;
	size = other.size;
	
	for(int i = 0; i < size; i++)
	{
		dataItems[i] = other.dataItems[i];
	}
	
	return *this;

}
//---------------------------------------------------------------------------
// Destructor:
// Deallocates memory used by Class Heap.
Heap::~Heap()
{

	delete [] dataItems;

}
//---------------------------------------------------------------------------
// Insertion Fuction:
// Inserts a new element into the Class Heap object. If the Heap is full, 
// a logic error exception is thrown.
void Heap::insert(int newDataItem) throw (logic_error)
{
	
	if(size == maxSize || size > maxSize)
	{
		throw logic_error ("FULL!");
	}
	
	int i = size;
	dataItems[size++] = newDataItem;
    int parent = (i - 1) / 2;

	while(i != 0 && dataItems[i] > dataItems[parent])
    {
        int tmp = dataItems[parent];
        dataItems[parent] = dataItems[i];
        dataItems[i] = tmp; 

        i = parent;
        parent = (i - 1) / 2;	
    }
    
    restore();

}
//---------------------------------------------------------------------------
// Removal Function:
// Removes an object from the Heap. If the Heap is empty or the item is not 
// in the Heap, a logic error exception is thrown. 
int Heap::remove() throw (logic_error)
{

	if(size == 0)
	{
		throw logic_error ("Item not found!");
	}
	
    int root = dataItems[0];
    int leaf = dataItems[size-1];
    int index = 1;
    
    while(index < size)
    {
    	if( (index < (size - 1)) && (dataItems[index] < dataItems[index + 1]))
    	{
    		index++;
		}
		
		if(leaf >= dataItems[index])
		{
			break;
		}
		
		else
		{
			dataItems[(index - 1) / 2] = dataItems[index];
			index = (2 * (index + 1));
		}
	}
	
	dataItems[(index - 1) / 2] = leaf;
	size--;
	restore();
		
	return root;
	
}
//---------------------------------------------------------------------------
// Clear Function:
// Clears the Heap of values. This function only sets the size of the heap to 
// zero but does not alter the values within the heap. 
void Heap::clear() 
{

	if(size == 0)
	{
		cout << endl << "Heap is already clear!" << endl;
	}

	else
	{
    	size = 0;
	}

}
//---------------------------------------------------------------------------
// Boolean Function:
// Tests to see if the Heap Object is empty. Returns true if the Heap size is 
// equal to zero. 
bool Heap::isEmpty() const
{

    return (size == 0);

}
//---------------------------------------------------------------------------
// Boolean Function:
// Tests to see if the Heap Object is at capacity. Returns true if the size is
// equal to maxSize. 
bool Heap::isFull() const
{

    return (size == maxSize);

}
//---------------------------------------------------------------------------
// Output Function:
// Outputs the Heap Structure as an array. 
void Heap::showStructure() const
{

    for(int i =0; i <size; i++)
    {
        cout << dataItems[i] << " ";
    }

    cout << endl;

}
//---------------------------------------------------------------------------
// Sorts the heap.
void Heap::sort() 
{

	int index = 0;

	while(index < size)
	{
		for (int i= size - 1; i >= 0; i--)
    	{
    		int temp = dataItems[0];
    		dataItems[0] = dataItems[i];
    		dataItems[i] = temp;
    	}
    
    	index++;
		restore();
    }
    
}
//---------------------------------------------------------------------------
// Restores the Heap Property.
void Heap::restore()
{

	for(int i = (size-1); i >= 0; i--)
	{
		int parent = (i-1) / 2;
		
		if(dataItems[i] > dataItems[parent])
		{
			int temp = dataItems[parent];
			dataItems[parent] = dataItems[i];
			dataItems[i] = temp;
		}
	}	
	
}
//---------------------------------------------------------------------------

#endif	//#ifndef HEAP_CPP
