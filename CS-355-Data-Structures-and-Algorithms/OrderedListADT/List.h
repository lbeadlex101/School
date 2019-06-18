//--------------------------------------------------------------------
//
//  CS 355 Fall 2016
//
//  List Interface
//
//  Donald Lee Beadle
//--------------------------------------------------------------------
#ifndef LIST_H
#define LIST_H

template <class T>
class List
{
public:
    static const int MAX_LIST_SIZE = 10; 
    List ( int maxNumber = MAX_LIST_SIZE );
    List (const List&);
    List& operator =(const List& rightSide);
    virtual ~List();

    virtual void insert( const T& newDataItem );
    void remove();
    virtual void replace(const T&);
    void clear();

    bool isEmpty();
    bool isFull();
            
    void goToBeginning(); // Cursor Function
    void goToEnd();  // Cursor Function
    bool goToNext();  // Cursor Function
    bool goToPrior();  // Cursor Function
        
    T getCursor();
    int getSize();

    virtual void showStructure () const;
            
protected:
    int maxSize;
    int size;
    int cursor;
    T* dataItems;
};

#endif
