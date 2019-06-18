//--------------------------------------------------------------------
//
//  CS 355 Fall 2016
//
//  Class List interface
//
// Copyright (c) 2016 Donald Lee Beadle
//--------------------------------------------------------------------
#include <iostream>
using namespace std;

class List
{
public:
  List(int MaxNumber); // Initialization Constructor
  List(const List& other); // Copy Constructor
  List& operator =(const List& source); // Overloaded Assignment op

  virtual ~List(); // Destructor

  virtual void insert(const int& newDataItem); // Insert Function
  void remove(); // Remove Funtion
  virtual void replace(const int& newDataItem); // Replace Function
  void clear(); // Clear Function

  bool isEmpty() const; // List size/amount test
  bool isFull() const;  // List size/amount test
  void gotoBeginning(); // Cursor Function
  void gotoEnd();  // Cursor Function
  bool gotoNext();  // Cursor Function
  bool gotoPrior();  // Cursor Function

  int getCursor() const; // Accessor Cursor Value Function

  virtual void showStructure() const; // Debugging Function

protected:

private:
  int maxSize; // Maximum List size
  int size; // Actual capacity of current list
  int cursor; // Value of cursor location
  int* dataItems; // List array
};
