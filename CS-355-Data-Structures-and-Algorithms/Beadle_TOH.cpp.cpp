//-----------------------------------------------------------------------------
// TOH.cpp
// Tower of Hanoi Program and Analysis
// 
// 2016 Donald Lee Beadle 
//
//-----------------------------------------------------------------------------
#include <iostream>
using namespace std;

void move(int n, char from, char aux, char to);

int main()
{

    move(20, 'A', 'C', 'B'); // 253 seconds

 
    return 0;
}
//---------------------------------------------------------------------------
// Move Function:
// Models a recurrence relation to represent solving the Tower of Hanoi 
// Problem.
void move(int n, char from, char aux, char to)
{

    if( n == 0) // Case for no disks. 
    {
        cout << "No moves can be made!";
    }

   else if( n == 1 ) // Case for only 1 disk.
    {
        cout << "move " << n << " from " << from << " to " << to << endl;
    }

    else // Case for more than 1 disk. 
    {
        {       
            move((n-1), from, to, aux);
            cout << "move " << n << " from " << from << " to " << to << endl;
            move((n-1), aux, from, to);
        }   
    }
    
}
//---------------------------------------------------------------------------
// Analysis: 
// The algorithm for the Tower of Hanoi problem represents a minimum move 
// solution. The fewest moves possible are utilized to ensure that disks 
// moved to the destination as efficiently as possible. However, in complexity
// of this algorithm with relation to time, the algorithm has a worst case 
// run-time of O(2^n). This can be observed by recording the run-times while 
// n represents a number of disks between 1 and 64. As the number of disks (n)
// increases, the function of time T(n) increases exponentially. 
