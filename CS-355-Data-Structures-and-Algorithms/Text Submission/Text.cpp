// -----------------------------------------------------------------------------
//
// CS 355 Fall 2016
//
// .cpp File for Text ADT.
// An object instantiated from the Text class is a logical string of chars.
//
// Copyright (c) 2016 Donald Lee Beadle
//
// -----------------------------------------------------------------------------
#include "Text.h"
#include <cstring>
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
// Constuctor
Text::Text(const char* charSeq) 
{
  
  bufferSize = strlen(charSeq) + 1;
  buffer = new char[bufferSize];
  strcpy(buffer, charSeq);

}
//---------------------------------------------------------------------------
// Copy Constructor 
Text::Text(const Text & other)
{

  if(bufferSize > 0)
  {
    delete [] buffer;
  }

  bufferSize = other.bufferSize;
  buffer = new char[bufferSize];

  strcpy(buffer, other.buffer);

}
//---------------------------------------------------------------------------
// Overloaded Assignment 
void Text::operator =(const Text &other)
{

  delete [] buffer;
  bufferSize = (other.getLength() + 1); 
  buffer = new char[bufferSize];

  for (int i = 0; i < (bufferSize); i++)
  {
    buffer[i] = other[i];
  }

}
//---------------------------------------------------------------------------
// Calculate character length function
int Text::getLength() const 
{

  int length = 0;

  length = bufferSize - 1;

  return length;

}
//---------------------------------------------------------------------------
// Subscript Function
char Text::operator [] ( int n ) const
{
  
  if (n >= 0 && n < bufferSize)
  {
    return buffer[n];
  }
  
  else
  {
    return '\0';
  }

}
//---------------------------------------------------------------------------
// Clears the buffer of characters
void Text::clear ()
{

  delete [] buffer;
  
  buffer = new char[bufferSize];
  
  for(int i=0; i < bufferSize;i++)
  {
    buffer[i] = ' ';
  }

}
//---------------------------------------------------------------------------
// Prints the characters to the console, one per line
void Text::showStructure() const 
{

  for(int i = 0; i < (bufferSize-1); i++)
  {
    if(buffer[i] == '\0')
    {
      cout << i << " : NULL terminator";
    }

    else
    {
    cout << i << " : " << buffer[i];
    }

    cout << " \n";
  }

}
//---------------------------------------------------------------------------
// Destructor
Text::~Text() 
{

  bufferSize = 0;
  delete buffer;

}
//---------------------------------------------------------------------------

