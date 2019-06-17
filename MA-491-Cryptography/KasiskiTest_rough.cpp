//-----------------------------------------------------------------------------
// Donald Lee Beadle
// CS 491
// Assignment #3
// Rough Version: Does not correctly generate key. Also, main driver needs to 
// be compartmentalized. 
//-----------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

//-----------------------------------------------------------------------------
char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
				  'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
//-----------------------------------------------------------------------------				  
double englishProbs[26]= {.082,.015,.028,.043,.127,.022,.02,.061,.07,.002,.008,
						.04,.024,.067,.075,.019,.001,.06,.063,.091,.028,.01,.023,
						.001,.02,.001};
//----------------------------------------------------------------------------
string fileInput();
int GCD(int a, int b);
//-----------------------------------------------------------------------------
int main()
{
//-----------------------------------------------------------------------------
// Counts trigrams and frequencies of trigrams.

	string cipherText = fileInput();
	string gram = "";
	
	int letterCount = cipherText.length();
	int n = 3; // Declare trigram size
	int totalGramCount = 0;
	int instanceGramCount = 0;
	int count = 0;
	int numberOfMatches = 0;
	
	bool isDuplicate = false;
	
	vector <string> allNGrams;
	vector <int> frequency;
	
	for(int i = 0; i < letterCount - 1; i++)
	{
		gram = cipherText.substr(i, n);
		
		if(gram.length() == n)
		{
			allNGrams.push_back(gram);
			totalGramCount++;
			frequency.push_back(0);
		}
	}
	
	for(int i = 0; i < letterCount - 1; i++)
	{
		gram = cipherText.substr(i, n);
		
		for(int j = 0; j < totalGramCount; j++)
		{
			if(allNGrams[j] == gram )
			{
				frequency[i]++;
				numberOfMatches++;
				isDuplicate = true;
			}
			
			else
			{
				isDuplicate == false;
			}
		}
	}
	
//--------------------------------------------------------------------
// Scans vector for highest frequency. 

	int max = 0;
	int index = 0;

	for(int i = 0; i < frequency.size(); i++)
	{
		if (max < frequency[i])
		{
			max = frequency[i];
			index = i;
		}	
	}	
	
	string mostUsed = allNGrams[index];
//--------------------------------------------------------------------
// Find the indices of high frequency and store in an array.

	vector <int> indices; 
	
	int j = 0;
	for(int i = 0; i < allNGrams.size(); i++)
	{
		if(max == frequency[i])
		{
			indices.push_back(i);
			j++;
		}
	}
//-----------------------------------------------------------------------------
// Builds vector list of distances occurences.

	vector <int> distances; 
	int temp = 0;
	
	for(int i = 0; i < indices.size()-1; i++)
	{
		temp = indices[i+1] - indices[i];
		distances.push_back(temp);	
	}
	
//-----------------------------------------------------------------------------
// Builds vector list of gcd's based on difference of distances. 

	vector <int> possibleKeys; 
	int temporary = 0;
	
	for(int i = 0; i < distances.size()-1; i++)
	{
		temporary = GCD(distances[i], distances[i+1]);
		possibleKeys.push_back(temporary);	
	}
	


//-----------------------------------------------------------------------------	
// Debugging Output functions: 	
	cout << "--------------------------------------------------------\n";
	cout << "Number of Ngrams: " << allNGrams.size() << endl;
	cout << "--------------------------------------------------------\n";
	
	cout << "--------------------------------------------------------\n";
	cout << "Cipher Text: \n" << cipherText << endl;
	cout << "--------------------------------------------------------\n";
	
	cout << "--------------------------------------------------------\n";
	cout << "String Length: " << letterCount << endl << endl;
	cout << "--------------------------------------------------------\n";
	
	cout << "--------------------------------------------------------\n";
	cout << "Display Trigrams \n";
	cout << "--------------------------------------------------------\n";

	for(int i = 0; i < totalGramCount; i++)
	{
		cout << " " << allNGrams[i] << " : " << frequency[i] << "  ";
	}
	
	cout << "\n--------------------------------------------------------\n";
	cout << "MAX Frequency: " << max << endl;
	cout << "--------------------------------------------------------\n";

	cout << "--------------------------------------------------------\n";
	cout << "First Index of Max: " << index << endl;
	cout << "--------------------------------------------------------\n";

	cout << "--------------------------------------------------------\n";
	cout << "Most Used Trigram: " << mostUsed << endl;
	cout << "--------------------------------------------------------\n";
	
	cout << "--------------------------------------------------------\n";
	cout << "Indices of : " << mostUsed << endl;
	for(int i = 0; i < indices.size(); i++)
	{
		cout << " " << indices[i] << " ";
	}
	cout << "\n--------------------------------------------------------\n";
	
	cout << "--------------------------------------------------------\n";

	cout << "Vector of Distances : ";
	for(int i = 0; i < distances.size(); i++)
	{
		cout << " " << distances[i] << " ";
	}
	
	cout << "\n--------------------------------------------------------\n";
	
	
	cout << "GCD's: \n";
	for(int i = 0; i < possibleKeys.size(); i++)
	{
		cout << i << ") "  << possibleKeys[i] << endl;
	}
	cout << "\n--------------------------------------------------------\n";
	
	int userKey = 0;
	cout << "\n--------------------------------------------------------\n";
	cout << "Enter possible key length selection: ";
	cin >> userKey;
	

//-----------------------------------------------------------------------------
// Builds substrings. 
	vector <string> substrings;
	string sub = "";
	int keyLength = possibleKeys[userKey];
	int numOfSubstrings = cipherText.length() / keyLength; 
	int dex = 0;
	
	
	for(int i = 0; i < numOfSubstrings; i++)
	{
		sub = cipherText.substr(i, keyLength);
		substrings.push_back(sub);
	}
	
	cout << "\n------------------------------------------------------\n";
	cout << "Substrings: " << endl;
	for(int i = 0; i < numOfSubstrings; i++)
	{
		cout << "'" << substrings[i] << "'";
	}

	return 0;
}
//----------------------------------------------------------------------------- 
// Reads ciphertext from a file.                        
string fileInput()
{
	ifstream inFile;
	string line, cipherText;
	
	
	inFile.open("cipher.txt");
	
	if(inFile.fail())
	{
		cerr << "File Open Failed";	
	}
	
	else
	{
		while(!inFile.eof())
		{
			getline(inFile, line);
			cipherText += line;
		}
	}
	
	inFile.close();
	
	return cipherText;
	
}
//-----------------------------------------------------------------------------
// Computes GCD of two integers. 
int GCD(int a, int b)
{

	int temp =  0;

	while(b != 0)
	{
		temp = b;
		b = a % b;
		a = temp;
	}
	
	return a;
}
//-----------------------------------------------------------------------------

