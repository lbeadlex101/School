//-----------------------------------------------------------------------------
// Main.cpp
// Paragraph ADT Main Driver 
// 
// Copyright (c) 2016 Donald Lee Beadle 
//
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "Paragraph.h"
using namespace std;

int main(int argc, char** argv) 
{
  Paragraph one;

  // Paragraph objectOne(testFile1), objectTwo(testFile2);

  // cout << objectOne << endl;

  // cout << objectTwo << endl;

  // objectOne = objectTwo; 

  // cout << objectTwo;

  one.dump();

  return 0;
}
