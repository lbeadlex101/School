//-----------------------------------------------------------------------------
// Donald Lee Beadle
// CS 491
// Assignment #3
// FINAL DRAFT
// This program uses frequency analysis and the Kasiski Test to compute a key 
// based on a given set of ciphertext.
//-----------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

//-----------------------------------------------------------------------------
// Alphabet Character Array: 
const char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
				  'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
//-----------------------------------------------------------------------------
// English Probability Double Array:				  
const double englishProbs[26]= {.082,.015,.028,.043,.127,.022,.02,.061,.07,.002,
								.008,.04,.024,.067,.075,.019,.001,.06,.063,.091,
								.028,.01,.023,.001,.02,.001};
//-----------------------------------------------------------------------------
// Declare Trigram Constant: 
const int n = 3;
//-----------------------------------------------------------------------------
// Index of Coincidence:
const double IOC = 0.065;
//-----------------------------------------------------------------------------
// Function Declarations: 
string fileInput();
int gcd(int a, int b);
void buildNGrams(const int n, const string &cipherText, int &totalGramCount, 
					vector <string> &allNGrams, vector <int> &frequency);
int scan(vector <int> frequency, vector <string> allNGrams);
vector <int> computeDistances(int max, vector<int> frequency, 
							  vector <string> allNGrams);
vector <int> listgcds(vector <int> distances);
void divideCipherText(string substrings[], const string cipherText, 
		              const int keyLength);
vector <double> matching(string s);
char closestToEnglish(const vector <double> l, const string alphabet);
string computeKey(const string substrings[], const int keyLength, 
                  const char alphabet[]);
//-----------------------------------------------------------------------------
// Main Driver:
int main()
{

	string cipherText = "";
	string key = "";
	
	int letterCount = 0;
	int totalGramCount = 0;
	int max = 0;
	int keyLength = 0;
	
	char closest = '\0';
	
	vector <string> allNGrams;
	vector <int> frequency;
	vector <int> distances; 
	vector <int> possibleKeyLens;
	vector <double> indices;
	
	cipherText = fileInput();
	letterCount = cipherText.length();
	
	buildNGrams(n, cipherText, totalGramCount, allNGrams, frequency);
	
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
	
	max = scan(frequency, allNGrams);
	
	distances = computeDistances(max, frequency, allNGrams);
	
	cout << "---------------------------------------------------------\n";
	cout << "Vector of Distances : ";
	for(int i = 0; i < distances.size(); i++)
	{
		cout << " " << distances[i] << " ";
	}
	cout << "\n--------------------------------------------------------\n";
	
	possibleKeyLens = listgcds(distances);
	
	cout << "GCD's: \n";
	for(int i = 0; i < possibleKeyLens.size(); i++)
	{
		cout << i << ") "  << possibleKeyLens[i] << endl;
	}
	cout << "\n--------------------------------------------------------\n";
	
	int userKey = 0;
	cout << "\n--------------------------------------------------------\n";
	cout << "Enter possible key length selection: ";
	cin >> userKey;
	
	keyLength = possibleKeyLens[userKey];
	
	cout << endl << "Key Length: " << keyLength << endl;
	
	string substrings[keyLength];
	
	divideCipherText(substrings, cipherText, keyLength);
	
	
	cout << "\n------------------------------------------------------\n";
	cout << "Substrings: " << endl;
	
	for(int i = 0; i < keyLength; i++)
	{
		cout << "'" << substrings[i] << "'";
	}
	cout << "\n------------------------------------------------------\n";
	
	indices = matching(substrings[0]);
	closest = closestToEnglish(indices, alphabet);
	
	
	cout << "\n------------------------------------------------------\n";
	cout << "Closest Character: " << closest;
	cout << "\n------------------------------------------------------\n";
	
	
	key = computeKey(substrings, keyLength, alphabet);
	
	cout << "------------------------------------------------------\n";
	cout << "KEY: " << key;
	cout << "\n------------------------------------------------------\n";
	
	return 0;
	
}
//-----------------------------------------------------------------------------
// File Input Function:
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
// GCD Function:
// Computes GCD of two integers. 
int gcd(int a, int b)
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
// Build NGrams Funtion:
// This function constructs the ngrams of a given ciphertext string and 
// counts the frequencies of occurence. 
void buildNGrams(const int n, const string &cipherText, int &totalGramCount, 
					vector <string> &allNGrams, vector <int> &frequency)
{

	string gram = "";
	int letterCount = cipherText.length();
	bool isDuplicate = false;
	
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
				isDuplicate = true;
			}
			
			else
			{
				isDuplicate == false;
			}
		}
	}
	
}
//-----------------------------------------------------------------------------
// Scan Function:
// This function scans the trigrams list for the most used trigram's 
// frequency. 
int scan(vector <int> frequency, vector <string> allNGrams)
{

	int index = 0;
	int max = 0;
	string mostUsed ="";

	for(int i = 0; i < frequency.size(); i++)
	{
		if (max < frequency[i])
		{
			max = frequency[i];
			index = i;
		}	
	}	
	
	mostUsed = allNGrams[index];
	
	cout << "\n--------------------------------------------------------\n";
	cout << "Most Used Trigram: " << mostUsed << endl;
	cout << "--------------------------------------------------------\n";
		
	return max;
	
}
//-----------------------------------------------------------------------------
// Compute Distances Function:
// Computes the distances of highest occuring trigram and returns the results
// in a vector. 
vector <int> computeDistances(int max, vector<int> frequency, 
							  vector <string> allNGrams)
{

	vector <int> locations; 
	vector <int> distances; 
	int temp = 0;
	int j = 0;
	
	for(int i = 0; i < allNGrams.size(); i++)
	{
		if(max == frequency[i])
		{
			locations.push_back(i);
			j++;
		}
	}

	for(int i = 0; i < locations.size()-1; i++)
	{
		temp = locations[i+1] - locations[i];
		distances.push_back(temp);	
	}
	
	return distances;
	
}
//-----------------------------------------------------------------------------
// Calculate GCDs:
// List possible gcds of the distances of highest occuring trigram.
vector <int> listgcds(vector <int> distances)
{

	vector <int> possibleKeyLens; 
	int temporary = 0;
	
	for(int i = 0; i < (distances.size() - 1); i++)
	{
		temporary = gcd(distances[i], distances[i+1]);
		possibleKeyLens.push_back(temporary);	
	}
	
	return possibleKeyLens; 
	
}
//-----------------------------------------------------------------------------
// Divide Ciphertext Function:
// Breaks the ciphertext into substrings indexed by position mod key length.
void divideCipherText(string substrings[], const string cipherText, 
                      const int keyLength)
{
	
	int count = 0;
	int index = 0;
	string aString = "";
	
	for(int i = 0; i < cipherText.length() - 1; i++)
	{
		index = i % keyLength;
		substrings[index] += cipherText[i];
	}
	
}
//-----------------------------------------------------------------------------
// Return Matching Indices Funtion:
// Returns a vector of doubles of corresponding indices. 
vector <double> matching(string s)
{

	vector <double> indices;
	double sum = 0;
	int nprime = s.length();
	
	for(int g = 0; g < 26; g++)
	{
		sum = 0;
		
		for(int i = 0; i < 26; i++)
		{
			sum = (sum + (englishProbs[i] * count((s.begin()), 
			      (s.end()),alphabet[(i+g) % 26]) ) / nprime);
		}
		
		indices.push_back(sum);
	}
	
	return indices;
	
}
//-----------------------------------------------------------------------------
// Calculate Frequency Closest to English Function:
// This function calculates the character closest to the index of
// coincidence and returns the character. 
char closestToEnglish(const vector <double> l, const string alphabet)
{

	int closeIndex = 0;
	double diff = fabs(l[0] - IOC);
	
	for(int i = 0; i < l.size(); i++)
	{
		if(fabs(l[i] - IOC) < diff)
		{
			diff = fabs(l[i] - IOC);
			closeIndex = i;
		}
	}
	
	return alphabet[closeIndex];
	
}
//-----------------------------------------------------------------------------
// Compute Key Function: 
// This function computes and returns a string key for a given ciphertext. 
string computeKey(const string substrings[], const int keyLength, 
                  const char alphabet[])
{

	string key = "";
	
	for(int i = 0; i < keyLength; i++)
	{
		key = key + closestToEnglish(matching(substrings[i]), alphabet);
	}

	return key;

}
//-----------------------------------------------------------------------------



