// -----------------------------------------------------------------------------
//
// CS 355 Fall 2016
//
// Header File for the Text ADT.
// An object instantiated from the Text class is a logical string of chars.
//
// Copyright (c) 2016 Donald Lee Beadle
//
// -----------------------------------------------------------------------------

#ifndef TEXT_H
#define TEXT_H

class Text
{
public:
  Text(const char* charSeq = ""); 
		Text(const Text & other); 
		void operator =(const Text &other);
		int getLength() const; 
		char operator[] (int n) const; 
		void clear();
		void showStructure() const;
		~Text();
protected:
private:
  int bufferSize;
		char *buffer;
};

#endif
