/******************************
*  Cryptography Final Project
*
*  Lee Beadle
*  Dillon Borden
*  Chad Etheredge
*  Katelyn Page
*
******************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;
const int keySize = 5;
void ImportMessage(string &text, const char* fileName);
void OutputMessage(const string &text, const char* fileName);
void ConvertUpper(string &text);
string EncryptMessage(string plaintext, string key);
string DecryptMessage(string ciphertext, string key);


char alpha[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M',
				   'N','O','P','Q','R','S','T','U','V','W','X','Y','Z', };

int main()
{
	string key, text, ciphertext, plaintext;
	char choice = 'N';
	
	//==============================
	// Get choice from user
	while (choice != 'E' && choice != 'D'){
		cout << "Would you like to encrypt or decrypt? (E or D, P to exit): ";
		cin >> choice;
		if (choice == 'P'){
			return 0;
		}
	}
	
	//==============================
	// Get Key from File
	cout << "Acquiring Key... " << endl;
	ImportMessage(key, "key.txt");
	ConvertUpper(key);

	//==============================
	// Encrypt message or Decrypt
	if (choice == 'E'){
		//==============================
		//  Import and display message
		ImportMessage(text, "plain.txt");
		ConvertUpper(text);
		cout << endl << text << endl << endl;
		ciphertext = EncryptMessage(text, key);
		cout << endl << endl;
		cout << ciphertext << endl << endl;
		system("pause");
		OutputMessage(ciphertext, "cipher.txt");
	}
	else{
		//==============================
		//  Import and display message
		ImportMessage(text, "cipher.txt");
		ConvertUpper(text);
		cout << endl << text << endl << endl;
		plaintext = DecryptMessage(text, key);
		cout << endl << endl;
		cout << plaintext << endl << endl;
		system("pause");
		OutputMessage(plaintext, "plain.txt");
	}
	

	return 0;
}

void ImportMessage(string &text, const char* fileName)
{
	string line;
	cout << "Importing file... " << endl << endl;

	ifstream message;
	message.open(fileName);
	if (message.is_open())
	{
		while (!message.eof())
		{
			getline(message, line);
			text += line;
		}
	}
	message.close();
	cout << "Imported successful." << endl;
}

void OutputMessage(const string &text, const char* fileName)
{
	string line;
	cout << "Outputting file... " << endl << endl;

	ofstream message;
	message.open(fileName);
	message << text;
	message.close();
	cout << "Output successful." << endl;
}

void ConvertUpper(string &text){
	for (int i = 0; i < text.length(); i++){
		text[i] = toupper(text[i]);
	}
}

string EncryptMessage(string text, string key)
{
	int keyVal[keySize];
	for (int i = 0; i < keySize; i++)
		for (int j = 0; j < 26; j++)
			if (key[i] == alpha[j])
				keyVal[i] = j;

	cout << "Key Array created..." << endl;
	system("pause");
	int k = 0;
	int j_2 = 0;
	int index = 0;
	bool stop = false;
	for (int i = 0; i < text.length(); i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (text[i] == alpha[j])
			{
				j_2 = j;
				j = 26;
			}
		}
		if ((k % 2) == 0)
		{
			index = (j_2 + keyVal[k]);
			if (index < 0)
				index = (26 + index);
			index = index % 26;
			text[i] = alpha[index];
			k = (k + 1) % keySize;
			
		}
		else //((j_2 % 2) != 0)
		{

			index = (j_2 - keyVal[k]);
			if(index < 0)
				index = (26 + index);
			index = index % 26;
			text[i] = alpha[index];
			k = (k + 1) % keySize;
			
		}
	}
	return text;
}

string DecryptMessage(string ciphertext, string key){
	int keyVal[keySize];
	for (int i = 0; i < keySize; i++)
		for (int j = 0; j < 26; j++)
			if (key[i] == alpha[j])
				keyVal[i] = j;
				
	cout << "Key Array created..." << endl;
	system("pause");
	int k = 0;
	int j_2 = 0;
	int index = 0;
	bool stop = false;
	for (int i = 0; i < ciphertext.length(); i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (ciphertext[i] == alpha[j])
			{
				j_2 = j;
				j = 26;
			}
		}
		if ((k % 2) == 0)
		{
			index = (j_2 - keyVal[k]);
			if (index < 0)
				index = (26 + index);
			index = index % 26;
			ciphertext[i] = alpha[index];
			k = (k + 1) % keySize;
			
		}
		else //((j_2 % 2) != 0)
		{

			index = (j_2 + keyVal[k]);
			if(index < 0)
				index = (26 + index);
			index = index % 26;
			ciphertext[i] = alpha[index];
			k = (k + 1) % keySize;
			
		}
	}
	return ciphertext;
}
