//------------------------------------------------------------------------------
// Donald Lee Beadle
// MA 491
// Assignment #6
// Las Vegas Algorithm
//------------------------------------------------------------------------------
#include <iostream>
#include <math.h>
using namespace std;

int gcd(unsigned int a, unsigned int b);
unsigned int factorFromDecExp(unsigned int n, unsigned int e,
                                   unsigned int d);

int main()
{
    unsigned int primeFactor = 0;
    
    unsigned int n = 36581;
    unsigned int e = 4679;
    unsigned int d = 14039;
    
    primeFactor = factorFromDecExp(n, e, d);
    
    cout << primeFactor;
    
    
    return 0;
    
}
//------------------------------------------------------------------------------
// Calculate gcd Function:
int gcd(unsigned int a, unsigned int b)
{
    unsigned int temp = 0;
    
    while (b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
    
}

//------------------------------------------------------------------------------
//
unsigned int factorFromDecExp(unsigned int n, unsigned int e,
                                   unsigned int d)
{
    unsigned int r = 1;
    unsigned int v;
    unsigned int v0 = 0;
    unsigned int edMinusOne = (e * d) - 1;
    unsigned int possibleR;
    unsigned int s = 2;
    unsigned int w = 9983;
    //unsigned int w2 = 13461;
    unsigned int x = 0;
    
    x = gcd(w, n);
    possibleR = edMinusOne / pow(2, s);
    
    while( (possibleR % 2) == 0 )
    {
        s++;
        possibleR = edMinusOne / pow(2, s);
    }
    
    r = possibleR;
    
    if( (x > 1) && (x < n) )
    {
        return x;
    }
    
    v = (unsigned int)pow(w,r) % n;
    
    if( (v % n) == 1 )
    {
        return 0;
    }
    
    while ( (v % n) != 1 )
    {
        v0 = v;
        v = (unsigned int)pow(v, 2) % n;
    }
    
    if( (v0 % n) == (n-1) )
    {
        return 0;
    }
    
    else
    {
        x = gcd(v0 + 1, n);
        return x;
    }
}
//------------------------------------------------------------------------------
