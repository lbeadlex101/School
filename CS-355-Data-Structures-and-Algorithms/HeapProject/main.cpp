//---------------------------------------------------------------------------
// Donald Lee Beadle
// 
// CS 355
//
// main.cpp // Heap main driver
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <cctype>
#include "Heap.h"
using namespace std;

void printHelp();

int main()
{
    Heap testHeap;  // Test heap
    int  inputPty;  // User input priority
    char cmd;       // Input command

    printHelp();

    do
    {
        testHeap.showStructure();                     // Output heap

        cout << endl << "Command: ";                  // Read command
        cin >> cmd;
	cmd = toupper( cmd );			      // Upcase input
        if ( cmd == '+' )
           cin >> inputPty;

        switch ( cmd )
        {
          case 'H' :
               printHelp();
               break;

          case '+' :                                  // insert
               cout << "Insert : priority = " << inputPty
                    << endl;
               testHeap.insert(inputPty);
               break;

          case '-' :                                  // remove
               cout << "Removed data item : "
                    << " priority = " << testHeap.remove() << endl;
               break;

          case 'C' :                                  // clear
               cout << "Clear the heap" << endl;
               testHeap.clear();
               break;

          case 'E' :                                  // isEmpty
               if ( testHeap.isEmpty() )
                  cout << "Heap is empty" << endl;
               else
                  cout << "Heap is NOT empty" << endl;
               break;

          case 'F' :                                  // isFull
               if ( testHeap.isFull() )
                  cout << "Heap is full" << endl;
               else
                  cout << "Heap is NOT full" << endl;
               break;

          case 'Q' :                              // Quit test program
               break;

          default :                               // Invalid command
               cout << "Invalid command" << endl;
        }
    }
    while ( cmd != 'Q' );

    return 0;
}

//--------------------------------------------------------------------

void printHelp()
{
    cout << endl << "Commands:" << endl;
    cout << "  H    : Help (displays this message)" << endl;
    cout << "  +pty : Insert data item with priority pty" << endl;
    cout << "  -    : Remove highest priority data item" << endl;
    cout << "  C    : Clear the heap" << endl;
    cout << "  E    : Empty heap?" << endl;
    cout << "  F    : Full heap?" << endl;
    cout << "  Q    : Quit the test program" << endl;
    cout << endl;
}
