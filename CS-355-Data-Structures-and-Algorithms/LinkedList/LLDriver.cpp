//-----------------------------------------------------------------------------
// LLDriver.cpp
// Linked List Main Driver 
// 
// Donald Lee Beadle 
//
//-----------------------------------------------------------------------------
#include <iostream>
#include "LinkedList.cpp"

// Character Data Type Test Case
void mLoop(List<char>& testList, List<char>& assignList, List<char>& copiedList);

// Integer Data Type Test Case
void mLoop(List<int>& testList, List<int>& assignList, List<int>& copiedList);

// Help Display Function
void print_help();

int main(int argc, char** argv) 
{
    
    int selection = 0;
    
    cout << "Choose Data Type: " << endl;
    cout << "1) Characters" << endl;
    cout << "2) Integers" << endl;
    
	cout << "Selection: ";
    cin >> selection;
    
    switch (selection)
    {
    	case 1 :
    	{
    		List<char> testList;
    		List<char> copiedList(testList);
    		List<char> assignList;
    		print_help();
    		mLoop(testList, copiedList, assignList);
    		break;
    	}
    
    	case 2 :
    	{
			List<int> testList;
			List<int> copiedList(testList);
			List<int> assignList;
			print_help();
    		mLoop(testList, copiedList, assignList);
			break;
		}
			
		default :
			cout << "Invalid Data Type Selection!";
			break;
	}

    return 0;

}
//-----------------------------------------------------------------------------
// Main Loop Function:
// Function used to test the Linked List class character data type
//-----------------------------------------------------------------------------
void mLoop(List<char>& testList, List<char>& assignList, List<char>& copiedList)
{
	char cmd;
	char testData;

do
    {	
        testList.showStructure();                     // Output list

        cout << endl << "Command: ";                  // Read command
        cin >> cmd;
        if ( cmd == '+'  ||  cmd == '='  ||  cmd == '#' )
           cin >> testData;

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
               cout << "Element marked by the cursor is "
                    << testList.getCursor() << endl;
               break;

          case '<' :                                  // gotoBeginning
               testList.gotoBeginning();
               cout << "Go to the beginning of the list" << endl;
               break;

          case '>' :                                  // gotoEnd
               testList.gotoEnd();
               cout << "Go to the end of the list" << endl;
               break;

          case 'N' : case 'n' :                       // gotoNext
               testList.gotoNext(); 
               break;

          case 'P' : case 'p' :                       // gotoPrior
               testList.gotoPrior(); 
               break;

          case 'C' : case 'c' :                       // clear
               cout << "Clear the list" << endl;
               testList.clear();
               break;

          case 'E' : case 'e' :                       // empty
               if ( testList.isEmpty() )
                  cout << "List is empty" << endl;
               else
                  cout << "List is NOT empty" << endl;
               break;

          case 'F' : case 'f' :                       // full
               if ( testList.isFull() )
                  cout << "List is full" << endl;
               else
                  cout << "List is NOT full" << endl;
               break;	

		  case 'A' : case 'a' :                       // assign list
		  		assignList = testList;
			   	cout << "Assigned List: ";
			   	assignList.showStructure();
			   	cout << endl;
			   	break;
			   	
		  case 'K' : case 'k' :                       // copy list
		  		copiedList = List<char>(testList);
		  		cout << "Copy: ";
		  		copiedList.showStructure();
		  		cout << endl;
		  		break;
				 
          case 'Q' : case 'q' :                   // Quit test program
               break;

          default :                               // Invalid command
               cout << "Inactive or invalid command" << endl;
        }
    }
    while ( cin && cmd != 'Q'  &&  cmd != 'q' );

    if( ! cin  )
    {
		cout << "cin read errror" << endl;
    }

}
//-----------------------------------------------------------------------------
// Main Loop Function:
// Function used to test Linked List Class with integer data type
//-----------------------------------------------------------------------------
void mLoop(List<int>& testList, List<int>& assignList, List<int>& copiedList)
{
	char cmd;
	int testData;

do
    {	
        testList.showStructure();                     // Output list

        cout << endl << "Command: ";                  // Read command
        cin >> cmd;
        if ( cmd == '+'  ||  cmd == '='  ||  cmd == '#' )
           cin >> testData;

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
               cout << "Element marked by the cursor is "
                    << testList.getCursor() << endl;
               break;

          case '<' :                                  // gotoBeginning
               testList.gotoBeginning();
               cout << "Go to the beginning of the list" << endl;
               break;

          case '>' :                                  // gotoEnd
               testList.gotoEnd();
               cout << "Go to the end of the list" << endl;
               break;

          case 'N' : case 'n' :                       // gotoNext
               testList.gotoNext(); 
               break;

          case 'P' : case 'p' :                       // gotoPrior
          	   testList.gotoPrior(); 
               break;

          case 'C' : case 'c' :                       // clear
        	   cout << "Clear the list" << endl;
               testList.clear();
               break;

          case 'E' : case 'e' :                       // empty
               if ( testList.isEmpty() )
                  cout << "List is empty" << endl;
               else
                  cout << "List is NOT empty" << endl;
               break;

          case 'F' : case 'f' :                       // full
               if ( testList.isFull() )
                  cout << "List is full" << endl;
               else
                  cout << "List is NOT full" << endl;
               break;	

		  case 'A' : case 'a' :                       // assign list
		  		assignList = testList;                
			   	cout << "Assigned List: ";
			   	assignList.showStructure(); 
			   	cout << endl;
			   	break;
			   	
		  case 'K' : case 'k' :                       // copy list
		  		cout << "Copy: ";
		  		copiedList = List<int>(testList);
		  		copiedList.showStructure();
		  		cout << endl;
		  		break;
				 
          case 'Q' : case 'q' :                   // Quit test program
               break;

          default :                               // Invalid command
               cout << "Inactive or invalid command" << endl;
        }
    }
    while ( cin && cmd != 'Q'  &&  cmd != 'q' );

    if( ! cin )
    {
		cout << "cin read errror" << endl;
    }

}
//-----------------------------------------------------------------------------
// Print Help Function:
// Displays the commands and operations that can be performed on objects
// of Class Linked List
//-----------------------------------------------------------------------------
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
    cout << "  A   : Assigned List" << endl;
	cout << "  K   : Copy testList" << endl;
    cout << "  Q   : Quit the test program" << endl;
    cout << endl;
}
//-----------------------------------------------------------------------------

