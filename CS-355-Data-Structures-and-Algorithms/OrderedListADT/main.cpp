//--------------------------------------------------------------------
//
//  CS 355 Fall 2016
//
//  List/OrderedList test drive
//
//  Donald Lee Beadle
//--------------------------------------------------------------------
#include <iostream>
#include "OrderedList.cpp"
using namespace std;

class Record
{
  public: 
    Record () { 
		key = char(0); 
	}
    Record (char c) { 
		key = char(c); 
	}
    void setKey(char newKey) { 
		key = newKey; 
	}
    char getKey() const { 
		return key; 
	}
  private:
    char key;
};

int main(int argc, char** argv) {
	List<int>* l1 = new List<int>(3);
	l1->insert(33);
	l1->insert(44);
	l1->showStructure();
	
	List<char> lc;
	lc.insert('a');
	lc.insert('b');
	
	lc.showStructure();
	
	OrderedList<Record, char> chars;
	
	chars.insert(Record('m'));
	chars.insert(Record('x'));
	chars.insert(Record('c'));
	chars.insert(Record('s'));
	chars.insert(Record('b'));
	chars.insert(Record('z'));
	chars.insert(Record('r'));
	chars.insert(Record('a'));
	
	chars.showStructure();

	return 0;
}
