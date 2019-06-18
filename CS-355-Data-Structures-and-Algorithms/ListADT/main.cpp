//--------------------------------------------------------------------
//
//  CS 355 Fall 2016
//
//  Test program for the operations in the List ADT
//
// 
//--------------------------------------------------------------------

#include <iostream>
#include "List.h"

using namespace std;

// prototypes
void print_help();
void showTwoLists(List list1, List list2); 	

// ----------------------------------------------------------------------------------- 
// Test program entry point
// ----------------------------------------------------------------------------------- 
int main()
{

    List testList(8);    // Test list to test with ints
    List copyList(testList);  // Used to test copy constructor
    //List assignList;     // Used to test assignment operator
    int testData;             // List data item 

    int n;                    // Position within list
    char cmd;                 // Input command

    print_help();

    do
    {
        testList.showStructure();                     // Output list

        cout << endl << "Command: ";                  // Read command
        cin >> cmd;
        if ( cmd == '+'  ||  cmd == '='  ||  cmd == '?' )
           cin >> testData;
        else if ( cmd == 'M'  ||  cmd == 'm' )
           cin >> n;

        switch ( cmd )
        {
          case 'H' : case 'h':
               print_help();
               break;

          case '+' :                                  // insert
               cout << "Insert " << testData << endl;
               testList.insert(testData);
               break;

          case '-' :                                  // remove
               cout << "Remove the data item marked by the cursor"
                    << endl;
                  testList.remove();
               break;

          case '=' :                                  // replace
               cout << "Replace the data item marked by the cursor "
                    << "with " << testData << endl;
                  testList.replace(testData);
               break;

          case '@' :                                  // getCursor
                  cout << "Data item marked by the cursor is "
                       << testList.getCursor() << endl;
               break;

          case '<' :                                  // gotoBeginning
               cout << "Go to the beginning of the list" << endl;
               testList.gotoBeginning();
               break;

          case '>' :                                  // gotoEnd
               cout << "Go to the end of the list" << endl;
               testList.gotoEnd();
               break;

          //case 'N' : case 'n' :                       // gotoNext
                  if ( testList.gotoNext() )
                     cout << "Go to the next data item" << endl;
                  else
                     cout << "Failed -- either at the end of the list "
                          << "or the list is empty" << endl;
               break;

          //case 'P' : case 'p' :                       // gotoPrior
                  if ( testList.gotoPrior() )
                     cout << "Go to the prior data item" << endl;
                  else
                     cout << "Failed -- either at the beginning of the "
                          << "list or the list is empty" << endl;
               break;

          case 'C' : case 'c' :                       // clear
               cout << "Clear the list" << endl;
               testList.clear();
               break;

          case 'E' : case 'e' :                       // isEmpty
               if ( testList.isEmpty() )
                  cout << "List is empty" << endl;
               else
                  cout << "List is NOT empty" << endl;
               break;

          case 'F' : case 'f' :                       // isFull
               if ( testList.isFull() )
                  cout << "List is full" << endl;
               else
                  cout << "List is NOT full" << endl;
               break;

          case '!' :
				showTwoLists(copyList, testList);
				break;
          case '#' :
				//assignList.insert('x');
				//assignList = testList;
				//showTwoLists(assignList, testList);
				break;

          case 'Q' : case 'q' :                   // Quit test program
               break;

          default :                               // Invalid command
               cout << "Inactive or invalid command" << endl;
        }
    }
    while ( cin && cmd != 'Q'  &&  cmd != 'q' );

    if( !cin ) {
		cout << "Input error" << endl;
    }

    return 0;
}

// ----------------------------------------------------------------------------------- 
//
// ----------------------------------------------------------------------------------- 
void showTwoLists(List list1, List list2) {
    // Variables should match, but dynamic memory buffer must be different
    cout << "Look at the two lists below and decide whether they are equivalent" << endl;
    cout << "List 1: ";
    list1.showStructure();
    cout << "List 2: ";
    list2.showStructure();
    cout << endl;
}


// ----------------------------------------------------------------------------------- 
// ----------------------------------------------------------------------------------- 
void print_help()
{
    cout << endl << "Commands:" << endl;
    cout << "  H   : Help (displays this message)" << endl;
    cout << "  +x  : Insert x after the cursor" << endl;
    cout << "  -   : Remove the data item marked by the cursor" << endl;
    cout << "  =x  : Replace the data item marked by the cursor with x"
         << endl;
    cout << "  @   : Display the data item marked by the cursor" << endl;
    cout << "  <   : Go to the beginning of the list" << endl;
    cout << "  >   : Go to the end of the list" << endl;
    cout << "  N   : Go to the next data item" << endl;
    cout << "  P   : Go to the prior data item" << endl;
    cout << "  C   : Clear the list" << endl;
    cout << "  E   : Empty list?" << endl;
    cout << "  F   : Full list?" << endl;
    cout << "  !   : Test copy constructor" << endl;
    cout << "  #   : Test assignment operator" << endl;
    cout << "  M n : Move data item marked by cursor to pos. n" << endl;
    cout << "  Q   : Quit the test program" << endl;
    cout << endl;
}

