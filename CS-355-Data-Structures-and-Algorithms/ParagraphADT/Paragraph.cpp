//-----------------------------------------------------------------------------
// Paragraph.cpp
// Paragraph ADT Implementation 
// 
// Copyright (c) 2016 Donald Lee Beadle 
//
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Paragraph.h"
using namespace std;
//-----------------------------------------------------------------------------
// Initialization constructor
Paragraph::Paragraph(const char* fileName)
{

  ifstream file;

  file.open("alpha.txt");

  lines = countLines(file);

	 sizes = new int[lines];

  buffer = new char*[lines];


}
//-----------------------------------------------------------------------------
// Copy Constructor
Paragraph::Paragraph(const Paragraph& other)
{


}
//-----------------------------------------------------------------------------
// Assignment Operator overload
Paragraph& Paragraph::operator =(const Paragraph& other)
{

}
//-----------------------------------------------------------------------------
// Destuctor
Paragraph::~Paragraph()
{
  delete [] buffer;
}
//-----------------------------------------------------------------------------
// Member function to count the lines within a file
int Paragraph::countLines(ifstream& fileName)
{
  int numLines = 0;
  string line;

  while(!fileName.eof())
  {
    getline(fileName, line);
    numLines++;
  }

  fileName.close();

  return numLines;

}
//-----------------------------------------------------------------------------
// Member function to count the characters per line of a file
void Paragraph::countChars()
{

}
//-----------------------------------------------------------------------------
// Accessor function to return private member lines
int Paragraph::getNumLines() const
{

  return lines;

}
//-----------------------------------------------------------------------------
// Accessor function to return the number of characters
int Paragraph::getNumChars() const
{

}
//-----------------------------------------------------------------------------
//
char Paragraph::operator[] (int n) const
{

}
//-----------------------------------------------------------------------------
// Debugging function
void Paragraph::dump() const
{

  cout << "Lines Read: " << getNumLines() << endl << endl;

  cout << sizes[0] << endl << endl;

  cout << buffer[0][0];

}
//-----------------------------------------------------------------------------
// Outputs an object of Class Paragraph to the console
ostream& operator << (ostream& output, const Paragraph& object)
{

  output << object.buffer;
  return output;

}
//-----------------------------------------------------------------------------


