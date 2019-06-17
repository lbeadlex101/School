//-----------------------------------------------------------------------------
//	Lee Beadle
//	Cryptography 
//	Program #1
// 
// 	NOTE: I didn't get my program to work fully with testing. I beleive I made 
// 	a mistake in my array initializations or in the logical comparisons for 
//  when to transform a plain text letter to a corresponding cipher key letter. 
//  This error was also found in decryption. 
//
//  Also, even entering the decimal and hex ASCII codes for the Section symbol,
//  Yen symbol, and Cent would not display correctly to the console. 
//-----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//-----------------------------------------------------------------------------
// Global Substitution Tables
	
	char plainText[90] = {'a','b','c','d','e','f','g','h','i','j','k','l','m'
	,'n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E',
	'F','G','H','I', 'J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X',
	'Y','Z',48,49,50,51,52,53,54,55,56,57,45,39,33,34,35,37,38,40,41,42,44,46,
	249,47,58,59,63,64,94,95,43,60,61,62,0xa2,156,0xf5,190};
	
	
	char cipherTextOne[90] = {'i','c','o','l','a','p','x','s','t','v','y',
	'b','j','e','r','u','k','n','f','h','q','g',59,'d','z','w',62,'F','A',
	'U','T','C','Y','O','L','V','J','D','Z','I','N','Q','K','S','E','H','G',
	60,46,49,'P','B',53,50,51,52,48,54,55,56,57,45,249,95,38,'m',64,58,34,42,
	40,35,'W','M',245,94,44,189,47,63,33,41,37,'X',39,'R',43,190,156,61};
	
	char cipherTextTwo[90] = {'t','o','r','b','i','u','d','f','h','g','z',
	'c','v','a','n','q','y','e','p','s','k','x',189,49,'w',59,'R','C',62,
	'G','H','A','P','N','D',60,'V','U','B','L','I','K','J','E','T','O','Y',
	'X','M',50,'Q','F',54,51,52,48,53,55,56,57,45,249,245,41,34,'j',63,44,'m',
	35,42,64,46,'Z',156,33,'W',43,94,47,38,40,58,49,95,'S',37,61,190,39};
	
	char cipherTextThree[90] = {'h','r','n','c','t','q','l','p','s','x','w'
	,'o','g','i','e','k','z','a','u','f','y','d',43,'b',59,189,'S','A','R',
	'Y','O',62,'Q','I','U','X',60,'G','F','D','L','J','V','T','H','N','P',49,
	'Z',51,'K','C',55,52,48,53,54,56,57,45,249,254,156,40,'m','v',47,'W','j',
	64,35,63,'M','B',190,38,46,37,33,94,34,42,44,50,41,'E',58,39,61,95};
	
	char cipherTextFour[90] = {'s','n','e','o','h','k','b','u','f','d',59,'r',
	'x','t','a','y','w','i','q','p','z','l',37,'c',189,43,'E',62,'S','P','N',
	'R','K','L','G',49,'X','Y','C','U','D','V',60,'H','O','I','Q',50,'B',52,'J',
	'A',56,48,53,54,55,57,45,245,156,190,42,'j','g',94,46,'v',63,64,47,'Z','F',
	61,34,'N',58,38,33,'m',35,'W',51,40,'T',44,95,39,41};

//-----------------------------------------------------------------------------
// Encipher/Decipher Declarations

void encipher(int code);
void decipher(int code);

//-----------------------------------------------------------------------------
// Main Driver

int main()
{
	
	int code;
	char choice;

	cout << "Would you like to encipher or decipher a message?" << endl;
	cout << "E) Encipher" << endl
		 << "D) Decipher" << endl;
		 
	cin >> choice;
	
	if (choice == 'e' || choice == 'E')
	{
		cout << endl;
		cout << "Please select a code" << endl;
		cout << "1) " << endl;
		cout << "2) " << endl;
		cout << "3) " << endl;
		cout << "4) " << endl;
		
		cin >> code;
		
		encipher(code);
	}
	
	else if(choice == 'd' || choice == 'D')
	{
		cout << endl;
		cout << "Please select a code" << endl;
		cout << "1) " << endl;
		cout << "2) " << endl;
		cout << "3) " << endl;
		cout << "4) " << endl;
		
		cin >> code;
		
		decipher(code);
	}
	
	else
	{
		cout << "Invalid choice! Program closing!";
	}

	return 0;
}
//-----------------------------------------------------------------------------
// Encipher Implementation 

void encipher(int code)
{

	cout << "Encipher code #" << code << " chosen!" << endl;
	
	int counter = 0;
	char buffer[256];

    ifstream inFile;
	ofstream outFile;
    
	inFile.open("message.in");
    
	while (!inFile.eof())
	{
    		inFile >> buffer[counter];
        	counter++;

    }
    
    inFile.close();
	
	if(code == 1)
    {
    	for(int i = 0; i < counter; i++)
    	{
    		for(int j = 0; j < 90; j++)
    		{
    			if( cipherTextOne[j] == buffer[i])
    			{
    				buffer[i] = cipherTextOne[j];
				}
    		}
		}
    }
	
	if(code == 2)
    {
    	for(int i = 0; i < counter; i++)
    	{
    		for(int j = 0; j < 90; j++)
    		{
    			if( cipherTextTwo[j] == buffer[i])
    			{
    				buffer[i] = cipherTextTwo[j];
				}
    		}
		}
    }
    
    if(code == 3)
    {
    	for(int i = 0; i < counter; i++)
    	{
    		for(int j = 0; j < 90; j++)
    		{
    			if( cipherTextThree[j] == buffer[i])
    			{
    				buffer[i] = cipherTextThree[j];
				}
    		}
		}
    }
    
    if(code == 4)
    {
    	for(int i = 0; i < counter; i++)
    	{
    		for(int j = 0; j < 90; j++)
    		{
    			if( cipherTextFour[j] == buffer[i])
    			{
    				buffer[i] = cipherTextFour[j];
				}
    		}
		}
    }
    
    
	outFile.open("message.out");
    
    for(int i = 0; i < (counter-1); i++)
    {
    	outFile << buffer[i];
	}

    outFile.close();

}
//-----------------------------------------------------------------------------
// Decipher Implementation

void decipher(int code)
{

	cout << "Decipher code #" << code << " chosen" << endl;

	int counter = 0;
	char buffer[256];

    ifstream inFile;
	ofstream outFile;
    
	inFile.open("message.in");
    
	while (!inFile.eof())
	{
    		inFile >> buffer[counter];
        	counter++;

    }
    
    inFile.close();
	
	if(code == 1)
    {
    	for(int i = 0; i < counter; i++)
    	{
    		for(int j = 0; j < 90; j++)
    		{
    			if( buffer[i] == cipherTextOne[j])
    			{
    				buffer[i] = plainText[j];
				}
    		}
		}
    }
	
	if(code == 2)
    {
    	for(int i = 0; i < counter; i++)
    	{
    		for(int j = 0; j < 90; j++)
    		{
    			if( plainText[j] == buffer[i])
    			{
    				buffer[i] = plainText[j];
				}
    		}
		}
    }
    
    if(code == 3)
    {
    	for(int i = 0; i < counter; i++)
    	{
    		for(int j = 0; j < 90; j++)
    		{
    			if( plainText[j] == buffer[i])
    			{
    				buffer[i] = plainText[j];
				}
    		}
		}
    }
    
    if(code == 4)
    {
    	for(int i = 0; i < counter; i++)
    	{
    		for(int j = 0; j < 90; j++)
    		{
    			if( plainText[j] == buffer[i])
    			{
    				buffer[i] = plainText[j];
				}
    		}
		}
    }
    
    outFile.open("message.out");
    
    for(int i = 0; i < (counter-1); i++)
    {
    	outFile << buffer[i];
	}

    outFile.close();

}
//-----------------------------------------------------------------------------
