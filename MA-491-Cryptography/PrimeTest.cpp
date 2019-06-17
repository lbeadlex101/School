// ---------------------------------------------------------------------
// Lee Beadle
// MA 491
// Assignment #5
// This program tests prime numbers, generates a list of primes for 
// time limit, and tests for p and q.
// ---------------------------------------------------------------------
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <ctime>
using namespace std;
//-------------------------------------------------------------------
// Function Declarations: 
bool isPrime(unsigned int n);
void runPrimes(unsigned int seconds, double& density);
void calculatePQ(unsigned int publicMod, unsigned int& p, unsigned int& q);
unsigned int calculatePhi(unsigned int p, unsigned int q);
int gcd(unsigned int a, unsigned int b);
//-------------------------------------------------------------------
// Main: 
int main(){
    unsigned int inputNum;
    unsigned int p, q, phi, GCD, publicMod, bobsPub;
    int inputTime = 0;
    double density = 0;  

    cout << "Please enter a number > 1: ";
    cin >> inputNum;
    
  	if(isPrime(inputNum) == true)
	{
    	cout << "The number is prime" << endl;
    }
        
	else
	{
    	cout << "The number is composite" << endl;
    }

    cout << "Let's generate a list of primes." << 
            "How long should we do this (in seconds)? ";
            
    cin >> inputTime;
    
    while (inputTime < 0)
	{
        cout << "n MUST BE >= to 0!" << endl;
        cin >> inputTime;
    }
    
    runPrimes(inputTime, density);

    cout << "Density = " << density << "%" << endl;   
	cout << "What should I factor (what is n)? (num > 2): ";
    cin >>  publicMod;
    
	calculatePQ(publicMod, p, q);

    cout << "What is Bob's Public Encrypt Key?";
    cin >> bobsPub;
    
   
    phi = calculatePhi(p,q);
    cout << endl << "Phi:" << phi << endl;
    
	GCD = gcd(bobsPub, phi);
    cout << "GCD: " << GCD << endl;


	return 0;
	
}
//-------------------------------------------------------------------
// Test if a number is prime.
bool isPrime(unsigned int n)
{

    if (n <= 1)
	{
        cout << "Number <= 1!";
    }
    
    else
	{
        for (unsigned int i = 2; i <= sqrt(n); i++)
		{
            if (n % i == 0)
			{
                return false;
            }
        }
    }
    
    return true;

}
// ----------------------------------------------------------------------
// Generates a list of a primes for a user-input number of seconds.
void runPrimes(unsigned int seconds, double& density)
{

    time_t start = time(0);
    double secondsSinceStart = difftime( time(0), start);
    double timeToRun = (double)seconds;
    unsigned int i = 2;
    int numPrime = 0;
    
    while (secondsSinceStart < timeToRun)
	{
        if (isPrime(i) == true)
		{
            cout << i << " is prime." << endl;
            numPrime++;
        }        
        
        i++;
        secondsSinceStart = difftime( time(0), start);
    }
    
    density = (100) * ((double)numPrime / (double)(i));
    
}
// ----------------------------------------------------------------------
// Returns a value for p and q which are two prime factors. 
void calculatePQ(unsigned int publicMod, unsigned int& p, unsigned int& q)
{
    
	unsigned int primeToCheck = 0;   

    for (unsigned int i = 2; i < publicMod; i++)
	{
        if ((publicMod % i) == 0)
		{
            primeToCheck = publicMod / i;
            
			if (isPrime(primeToCheck))
			{
                cout << "p and q are = " << i << "  " << primeToCheck 
                      << endl;
                p = i;
                q = primeToCheck;
                
                return;
            }
        }
    }

}
//-------------------------------------------------------------------
// Calculate Phi of n.
unsigned int calculatePhi(unsigned int p, unsigned int q)
{

    return ((p-1) * (q-1));
    
}
//-------------------------------------------------------------------
// Calculate gcd.
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
//-------------------------------------------------------------------

