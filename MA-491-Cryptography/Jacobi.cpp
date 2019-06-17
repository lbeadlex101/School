//-----------------------------------------------------------------------------
//	Donald Lee Beadle
//  MA 491
//  Assignment #7
// 	Jacobi Program
//-----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
//-----------------------------------------------------------------------------
// Function Declarations: 
int jacobi(unsigned long int a, unsigned long int n);
bool isEven(unsigned long int num);
bool validA(unsigned long int a, unsigned long int n);
bool isCongruent(unsigned long int a, unsigned long int b, unsigned long int m);
void findOddNum(int& s, unsigned int& r, unsigned long int top);
unsigned long int calculateModulo(unsigned long int b, unsigned long int e, 
                                  unsigned long int m);
string ssAlg(unsigned long int a, unsigned long int n);
//-----------------------------------------------------------------------------
// Main Driver:
int main()
{

    unsigned int long n = 0;
    unsigned int iterations = 0;
    double primeCount = 0;
    double average = 0.0; 
	string message = "";  
	 
    cout << "Enter an n-value: ";
    cin >> n;
    cout << endl;

    for (unsigned int a = 1; a < n; a++)
	{
        message = ssAlg(a,n);
        
		if (message == "n is prime")
		{
            primeCount++;
        }
            
		cout << message << "| JSymbol: " << jacobi(a,n) << endl << endl;
		iterations++;
    }
            
    average = primeCount / (n - 1);

	cout.precision(5);
    cout << "Primes Percentage: " << average * 100 << " %" << endl; 
	cout << "Prime Count: " << primeCount << endl;
	cout << "Iterations: " << iterations << endl;  
	cout << "n: " << n << endl;  

    return 0;
        
}
//-----------------------------------------------------------------------------
// Jacobi Function:
// This function builds Jacobi symbols and returns the corresponding value as 
// an integer. 
int jacobi(unsigned long int a, unsigned long int n)
{

    int result = 0;
    int inside = 0;
    int s = 0;
    unsigned int r = 0;
    bool isNegative = false;
    bool aontop = true;
        
    if(validA(a, n) == false)
    {
        return 0;
    }
        
    if( a == 1 )
    {
        result = 1;
        return result;
    }
        
    while( (aontop == true && n > 8) || (aontop == false && a > 8) ) 
    {
        if ((aontop == true) && (a % n == 0))
		{
            return 1;
        }
        
        if ((aontop == false) && (n % a == 0))
		{
            return 1;
        }
        
        // QR #4
        if (isCongruent(a, 3, 4) && isCongruent(n, 3, 4))
		{
            swap(a,n);
            isNegative = !isNegative;
            aontop = !aontop;
        }       
		 
        else
		{
            swap(a,n);
            aontop = !aontop;
        }
        
        // QR #1 #3 #2
        if (aontop == true)
		{
			
            a = a % n;
            findOddNum(s,r,a);
            a = r;
            aontop = !aontop;
             
            if (isCongruent(n, 1, 8) || isCongruent(n, -1, 8))
			{
                inside = 1;
            }
        }
        
        else
		{
            n = n % a;
            findOddNum(s,r,n);
            n = r;
            
            if (isCongruent(n, 1, 8) || isCongruent(n, -1, 8))
			{
                inside = -1;
            }
        }
        
        if (!isEven(s) && inside == -1)
		{
            isNegative = !isNegative;
        }
    }
    
    if (aontop == true)
	{
        result = 8 - n;
        
        if (result == 1)
		{
            return 1;
        }
        
        else
		{
            return -1;
        }
    }
    
    else
	{
        result = 8 - a;
        if (result == 1)
		{
            return 1;
        }
        
        else
		{
            return -1;
        }
    }
        
    return 0;
    
}
//-----------------------------------------------------------------------------
// Even or Odd Function:
// If a number is even, this function returns true. Else, the number is odd
// and returns false. 
bool isEven(unsigned long int num)
{
	if (num % 2 == 0)
	{
		return true;
	}
	
	else
	{
		return false;
	}
        
}
//-----------------------------------------------------------------------------
// Valid A-Value Function:
// This function tests if an a-value is valid with respect to an n-value. 
bool validA(unsigned long int a, unsigned long int n)
{

    if(a < 1)
    {
    	return false; 
    }
        
    if(a > (n - 1) )
    {
    	return false;
    }
 
	return true; 
 
}
//-----------------------------------------------------------------------------
// Is Congruent Function: 
// This function tests for congruency between two integers and an m-value. 
bool isCongruent(unsigned long int a, unsigned long int b, unsigned long int m)
{

	if(a < 0)
	{
		a = m - a;
	}
	
	else
	{
		a = a % m;	
	}
	
	if(b < 0)
	{
		b = m - b;	
	}

	else
	{
		b = b % m;
	}
	
	return (a == b);
	        
}
//-----------------------------------------------------------------------------
// Find Odd Num Function: 
// Calculates a number s that is a power of two and r is odd. 
void findOddNum(int& s, unsigned int& r, unsigned long int top)
{

    s = 1;
        
    while (isEven(top))
	{
    	top = top / 2;
        s++;
    }
        
    r = top;
        
}
//-----------------------------------------------------------------------------
// Modular Exponentiation Function: 
// Calculates the modular exponentiation given a base a, exp, and mod n.
unsigned long int calculateModulo(unsigned long int a, unsigned long int exp, 
                                  unsigned long int n)
{

	unsigned long int tempOne = 1;
	unsigned long int tempTwo = a;
	
	while(exp > 0)
	{
		if(exp % 2 == 1)
		{
			tempOne = (tempOne * tempTwo) % n;
		}
		
		tempTwo = (tempTwo * tempTwo) % n;
		exp = exp / 2;
	}
	
	return tempOne % n;
	
}
//-----------------------------------------------------------------------------
// Solovay-Strassen Algorithm Function: 
// Implements a yes-biased Monte Carlo Solovay-Strassen Algorithm to return 
// a string if n is or is not prime. 
string ssAlg(unsigned long int a, unsigned long int n)
{

    int x = 0;
    unsigned long int y;
        
    if( (n > 2) && (isEven(n) == true) )
    {
        return "n is REALLY composite";        // n is even and thus composite
    } 
        
    x = jacobi(a, n);
        
    if(isCongruent(x, 0, n) == true)
    {
        return "n is REALLY composite";        // n is composite
    }
        
    y = calculateModulo(a, ((n-1) / 2), n); // 

    if(isCongruent(x, y, n) )
    {

        return "n is prime";        // n MAY be composite
    }
        
    else
    {
        return "n is composite"; // n is composite
    }

}
//-----------------------------------------------------------------------------
