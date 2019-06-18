// -----------------------------------------------------------------------------
//
// CS 355 Fall 2016
//
// Main driver for testing Text ADT
//
// Copyright (c) 2016 Donald Lee Beadle
//
// -----------------------------------------------------------------------------
#include "Text.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) 
{

  Text text1("foo"), text2("baaar");

  cout << "length is " << text1.getLength() << endl;
  text1.showStructure();
  cout << endl;

  text1.clear();
  text1.showStructure();
  cout << endl;

  cout << "length is " << text2.getLength() << endl;
  text2.showStructure();
  cout << endl;

  text1 = text2;

  cout << "length is " << text1.getLength() << endl;
  text1.showStructure();
  cout << endl;

  return 0;

}
