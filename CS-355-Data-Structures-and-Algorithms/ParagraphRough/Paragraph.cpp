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
  delete [] sizes;
  delete [] buffer;
}
//-----------------------------------------------------------------------------
// Member function to count the lines within a file
void Paragraph::countLines(ifstream& fileName)
{
int numLines = 0;
  string line;

  while(!fileName.eof())
  {
    getline(fileName, line);  
    numLines++;
  }

  fileName.close();

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

}
//-----------------------------------------------------------------------------
// Outputs an object of Class Paragraph to the console
ostream& operator << (ostream& output, const Paragraph& object)
{
  output << object.buffer;
  return output;
}
//-----------------------------------------------------------------------------


