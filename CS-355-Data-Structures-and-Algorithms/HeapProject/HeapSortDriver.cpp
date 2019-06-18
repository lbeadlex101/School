//---------------------------------------------------------------------------
// Donald Lee Beadle
// 
// CS 355
//
// HeapSortDriver.cpp // sorting driver
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <cctype>
#include "Heap.h"
using namespace std;

// forward declaration
void heapsort(int data[], int n);

int main()
{
    int numbers[] = {2, 8, 6, 1, 10, 15, 3, 12, 11};
    
    heapsort(numbers, 9);
    
    cout << "------- sorted ---------------" << endl;
    for (int i = 0; i < 9; i++) {
    	cout << numbers[i] << " ";
    }
    cout << endl;
 
    return 0;
}

//--------------------------------------------------------------------
void heapsort(int data[], int n)
{
    Heap testHeap;
    
    for (int i = 0; i < n; i++) 
	{
    	testHeap.insert(data[i]);
    }
	
    testHeap.sort();
	
    for (int i = 0; i < n; i++) 
	{
    	data[i] = testHeap.dataItems[i];
    }
    
}
