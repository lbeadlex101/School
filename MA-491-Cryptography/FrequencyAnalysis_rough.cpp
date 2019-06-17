//-----------------------------------------------------------------------------
// Donald Lee Beadle
// MA 491
// Program #2
// Frequency Analysis:
// ROUGH PROTOTYPE - This program has limited functionality and implements 
// a loose design structure. 
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>
using namespace std;
//-----------------------------------------------------------------------------
// Global Constants:
char alpha[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
				  'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
// CONST N = 2
//-----------------------------------------------------------------------------
// Function Declarations:
void decipher(int buffer[], int& size, int& shift);
//-----------------------------------------------------------------------------
// Main Driver:
int main()
{

	int letterBuffer[26] = {0};
	int key = 0;
	int numOfChars = 0;	
	char aChar;	
	string cipherText, line;
	ifstream inFile;
	ofstream outFile;
	

	inFile.open("testCText.txt");
	
	while(!inFile.eof())
	{
		getline(inFile, line);
		cipherText += line;
	}
	
	inFile.close();
	
	
	cout << endl << "CipherText: " << cipherText << endl;
	
	
	for(int i = 0; i < cipherText.length(); i++)
	{
		aChar = cipherText[i];
		
		if(isalpha(aChar))
		{
			letterBuffer[toupper(aChar) - 'A']++;
		}
	}
	
	numOfChars = cipherText.length();
	
	cout << endl;
	
	for(int i = 0; i < 26; i++)
	{
	//	outFile << (char)('A' + i) << " = " << letterBuffer[i] << endl;
		cout << i << ") " << (char)('A' + i) << " = " << letterBuffer[i] << endl;
	}
	
	cout << "Number of Chars: " << numOfChars << endl;
	
	
	key = abs((13 - 5) % 26); // 13 is letter n // 5 is shift
	
	
	cout << "Decrypted Text: " << endl;
	
	for(int i = 0; i < numOfChars; i++)
	{
		cout << alpha[ (cipherText[i] + key) % 26];	
	}
	
	/* THE FREQUENCY ANALYSIS APPROACH RESTS ON THE FACT THAT THERE IS A 
	CHARACTERISTIC DISTRIBUTION OF LETTERS IN PROSE FOR A GIVEN LANGUAGE
	ENGLISH IN THIS CASE */
	
//-----------------------------------------------------------------------------
// Bigrams Portion: 
	cout << endl;
	
	vector <char> letters;
	vector <string> bigrams;
	vector <string> comps;
	int numberOfGrams = 0;
	string str, test;
	
	
	for(int i = 0; i < numOfChars; i++)
	{
		letters.push_back(cipherText[i]);
		
		if(letters.capacity() % 2 == 0)
		{
			numberOfGrams++;
		}
	}
	
	cout << endl << "Number of Grams: " << numberOfGrams << endl;
	int frequency[numberOfGrams] = {0};
	
	for(int i = 0; i < numberOfGrams; i++)
	{
		str = (cipherText.substr(i, 2) );
		bigrams.push_back(str);
		comps.push_back(str);
	}
	
	for(int i = 0; i < numberOfGrams; i++)
	{
	
		test = bigrams[i];
		
		for(int j = 0; j < numberOfGrams; j++)
		{
			if( test.compare(comps[j]) == 0)
			{
				frequency[i]++;
			}
		}
	}
	
	cout << endl;
	
	for(int i = 0; i < numberOfGrams; i++)
	{
		cout << i << ") " << bigrams[i] << " = " << frequency[i] << endl;
	}

	return 0;
}
//-----------------------------------------------------------------------------

