//-----------------------------------------------------------------------------
// Main.cpp
// Test cases for Paragraph ADT
// 
// Copyright (c) 2016 Donald Lee Beadle 
//
//-----------------------------------------------------------------------------
#include <iostream>
#include <cassert>
#include "Paragraph.h"
#include <fstream>
using namespace std;

//-----------------------------------------------------------------------------

int main(int argc, char** argv) 
{
  ifstream testFile1, testFile2;

  testFile1.open("randomOne.txt");
  testFile2.open("randomTwo.txt");

  // Paragraph objectOne(testFile1), objectTwo(testFile2);

  // cout << objectOne << endl;

  // cout << objectTwo << endl;

  // objectOne = objectTwo; 

  // cout << objectTwo;

  return 0;
}
