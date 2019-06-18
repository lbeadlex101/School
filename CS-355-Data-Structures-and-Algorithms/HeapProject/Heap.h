//---------------------------------------------------------------------------
// Donald Lee Beadle
// 
// CS 355
//
// Heap.h
//---------------------------------------------------------------------------
#ifndef HEAP_H
#define HEAP_H
#include <stdexcept>
#include <iostream>

using namespace std;

class Heap
{
  public:
  	
    const static int kDefaultHeapMax = 100;
  	
    Heap(int max = kDefaultHeapMax);
	Heap(const Heap& other);
	Heap& operator=(const Heap& other);
    
	virtual ~Heap();

    // Heap manipulation operations
    void insert ( int newDataItem ) throw ( logic_error );

    int remove () throw ( logic_error );  // Remove max priority element
    void clear ();                          // Clear heap

    // Heap status operations
    bool isEmpty () const;                  // Heap is empty
    bool isFull () const;                   // Heap is full

    // Output the heap structure -- used in testing/debugging
    void showStructure () const;

  private:
    // Sort
    void sort();
    
    // Restore heap property
    void restore();

    // Data members
    int maxSize;
    int size;
    int* dataItems;
    
  friend void heapsort(int data[], int size);
};

#endif	//#ifndef HEAP_H
