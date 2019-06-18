//-----------------------------------------------------------------------------
// Paragraph.cpp
// Paragraph ADT Interface 
// 
// Copyright (c) 2016 Donald Lee Beadle 
//
//-----------------------------------------------------------------------------
#include <iostream>
using namespace std;

class Paragraph 
{
public:
  Paragraph(const char* fileName =""); // Initialization constructor
  Paragraph(const Paragraph& other); // Copy constructor
  Paragraph& operator =(const Paragraph& other); // Assignment overload
  
  ~Paragraph(); // Destructor

  int countLines(ifstream& fileName); // 
  void countChars(); //

  int getNumLines() const; // Accessor function to return lines
  int getNumChars() const; // Accessor function to return number of characters
  
  char operator[] (int n) const; // Subscript
  
  void dump() const; // Debugging function

  friend ostream& operator << (ostream& output, const Paragraph& object); 
  // Output friend function to display an object of type Paragraph

private:
  int lines;  
  int* sizes;
  char** buffer;
};

