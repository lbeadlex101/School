//--------------------------------------------------------------------
//
//  CS 355 Fall 2016
//
//  Binary Search Tree Driver
//
//  Donald Lee Beadle
//--------------------------------------------------------------------
#include <iostream>
#include "BST.h"
#include "BST.cpp"
using namespace std;

void print_help();

int main()
{
 BST<int> testTree;   // Test binary search tree
    int inputKey;                    // User input key
    char cmd;                        // Input command
    int* key;

    print_help();

    do
    {
        testTree.showStructure();

        cout << endl << "Command: ";                  // Read command
        cin >> cmd;
        if ( cmd == '+'  ||  cmd == '?'  || cmd == '-')
           cin >> inputKey;

        switch ( cmd )
        {
          case 'P' : case 'p' :
               print_help();
               break; 

          case '+' :                                  // insert
				testTree.insert(inputKey);
               break;

          case '?' :                                  // retrieve
               key = testTree.search(inputKey);
                if (key == 0) {
                    cout << "Not found" << endl;
                } else {
                    cout << "Retrieved : key = "
                       << *key << endl;
                }
               break;

          case '-' :                                  // remove
               if ( testTree.remove(inputKey) )
                  cout << "Removed data item" << endl;
               else
                  cout << "Not found" << endl;
               break;

          case 'I' : case 'i' :                  
               cout << "inorder:" << endl;
				testTree.inorder();
				cout << endl;
               break;
               
          case 'R' : case 'r' :
          		cout << "preorder:" << endl;
          		testTree.preorder();
          		cout << endl;
          		break;
          		
          case 'O' : case 'o' :
          		cout << "postorder:" << endl;
          		testTree.postorder();
          		cout << endl;
          		break;

          case 'C' : case 'c' :                       // clear
               cout << "Clear the tree" << endl;
               testTree.clear();
               break;

          case 'E' : case 'e' :                       // empty
               if ( testTree.isEmpty() )
                  cout << "Tree is empty" << endl;
               else
                  cout << "Tree is NOT empty" << endl;
               break;

          case 'Q' : case 'q' :                   // Quit test program
               break;

          default :                               // Invalid command
               cout << "Invalid command. 'P' prints help." << endl;
        }
    }
    while ( cin && ( cmd != 'Q' ) && ( cmd != 'q' ) );
    
    if ( !cin ) {
	cerr << "Error in console input. Exiting." << endl;
    }

	return 0;
}

//--------------------------------------------------------------------

void print_help() {
    cout << endl << "Commands:" << endl;
    cout << "  P    : [P]rint Help (displays this message)" << endl;
    cout << "  +key : Insert (or update) data item (use integers)" << endl;
    cout << "  ?key : Retrieve data item" << endl;
    cout << "  -key : Remove data item" << endl;
    cout << "  I    : Write keys in ascending order" << endl;
    cout << "  R    : Write keys in pRe order" << endl;
    cout << "  O    : Write keys in pOst order" << endl;
    cout << "  C    : Clear the tree" << endl;
    cout << "  E    : Empty tree?" << endl;
    cout << "  Q    : Quit the test program" << endl;
    cout << endl;
}

