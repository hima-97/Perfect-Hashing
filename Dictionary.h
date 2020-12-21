#pragma once
#include "Hash24.h"

class Dictionary
{
public:

	// Class representing each slot of the primary hash table:
	class PrimarySlot
	{
	public:

		// Pointer to a "Hash24" object:
		// This is used to store the hash function used for each secondary hash table:
		Hash24 HashForSecondaryTable;

		// This is used to track all the words that are in a specific slot of the primary table:
		vector<string> wordsInPrimarySlot;

		// This used for the secondary table of each slot:
		vector<string> secondaryTable;

		// This is used for the size of each secondary hash table:
		int secondaryTableSize;

		// This is used to keep track of the number of hash functions attempted for each secondary hash table: 
		int hashAttempts = 0;

		// Constructor:
		PrimarySlot() {};
	};

	// This is used to track the number of words read in from the file:
	int wordsReadIn = 0;

	// This is used for the size of the primary hash table:
	int primaryTableSize = 0;

	// "Hash24" object to hash the words in the primary hash table:
	// Note: this object remembers the randomly chosen a, b and c used in the universal hash, so you can retrieve it later and use the same hash function.
	Hash24 HashForPrimaryTable;

	// This vector is used for the primary hash table:
	vector<PrimarySlot> primaryTable;

	// This is used to keep track of the maximum number of collisions in a slot of the primary hash table:
	int maxCollisions = 0;

	// This is used to store the words that are inside the primary hash table slot with the most collisions:
	vector<string> slotMaxCollisions;

	// This is used to keep track of how many slots have a specific number of words:
	int primarySlotsOfWords[21] = {};

	// This is used to keep track of how many secondary hash tables attempted a specific number of hash functions:
	int attemptsHashForSecondaryTable[21] = {};

	// Default constructor:
	Dictionary() {};

	// Constructor to construct the hash table with the information in the file passed in:
	Dictionary(string fname, int tsize);

	// Function to find a word in the hash table:
	bool find(string word);

	// Function to write the entire "Dictionary" class object to the file passed in:
	void writeToFile(string fName);

	// Static function to read the entire "Dictionary" class object from the file passed in:
	// Note: static functions are usually declared and defined in the same file.
	static Dictionary readFromFile(string fName)
	{
		// This creates a "Dictionary" object to store the entire dictionary to be read:
		Dictionary myDictionary2;

		// Input file object:
		ifstream inputFile;

		// This opens the input file in binary mode:
		inputFile.open(fName, ios::binary);

		// Checking if the input file was opened successfully:
		if (!(inputFile.is_open()))
		{
			cerr << "Error: file was not open!!" << endl;
		}
		else
		{
			// This reads "int wordsReadIn" from the input file and stores it inside the new dictionary object:
			int wordsReadIn;
			inputFile.read((char*)&wordsReadIn, sizeof(wordsReadIn));
			myDictionary2.wordsReadIn = wordsReadIn;

			// This reads "int maxCollisions" from the input file and stores it inside the new dictionary object:
			int maxCollisions;
			inputFile.read((char*)&maxCollisions, sizeof(maxCollisions));
			myDictionary2.maxCollisions = maxCollisions;

			// This reads "vector<string> slotMaxCollisions" from the input file and stores it inside the new dictionary object:
			int mySize;
			inputFile.read((char*)&mySize, sizeof(mySize)); // This reads the size of the vector
			size_t length;
			for (int i = 0; i < mySize; i++)
			{
				// This is used to store each charachter of the word (string) read in:
				char wordsColliding[100];

				// This reads the length of each word (string):
				inputFile.read((char*)&length, sizeof(length));

				// This is used to read each word:
				inputFile.read(wordsColliding, length);

				// This converts the "c_str" just read into a string:
				myDictionary2.slotMaxCollisions.push_back(string(wordsColliding));
			}

			// This reads the "Hash24 HashForPrimaryTable" object from the input file and stores it inside the new dictionary object:
			Hash24 HashForPrimaryTable;
			inputFile.read((char*)&HashForPrimaryTable, sizeof(HashForPrimaryTable));
			myDictionary2.HashForPrimaryTable = HashForPrimaryTable;

			// This reads "vector<PrimarySlot> primaryTable" from the input file and stores it inside the new dictionary object:
			inputFile.read((char*)&myDictionary2.primaryTableSize, sizeof(myDictionary2.primaryTableSize)); // This reads the size of the primary table
			for (int i = 0; i < myDictionary2.primaryTableSize; i++)
			{
				// This is used to store each "PrimarySlot" object read in:
				PrimarySlot myPrimarySlot;

				// This reads each "HashForSecondaryTable" object:
				inputFile.read((char*)&myPrimarySlot.HashForSecondaryTable, sizeof(myPrimarySlot.HashForSecondaryTable));

				// This is used to store the length of each "secondaryTable" vector:
				int secondaryTableSize;

				// This reads the length of each "secondaryTable" vector:
				inputFile.read((char*)&myPrimarySlot.secondaryTableSize, sizeof(myPrimarySlot.secondaryTableSize));

				// This is used to store the length of each word (string) in the "secondaryTable" vector:
				size_t str_len = 0;

				// This is used to store each word (string) in the "secondaryTable" vector:
				string myWord;

				// This loop reads each word (string) in the "secondaryTable" vector:
				for (int j = 0; j < myPrimarySlot.secondaryTableSize; j++)
				{
					// This reads the length of each word (string):
					inputFile.read((char*)&str_len, sizeof(str_len));

					// This sets the size of "myWord" equal to the length of each word (string):
					myWord.resize(str_len);

					// This reads each word (string):
					inputFile.read(&myWord[0], str_len);

					// This assigns each "myWord" to each slot of the secondary table:
					myPrimarySlot.secondaryTable.push_back(myWord);
				}
				// This assigns each "myPrimarySlot" to each slot of the primary table:
				myDictionary2.primaryTable.push_back(myPrimarySlot);
			}
			// This closes the input file:
			inputFile.close();
		}
		// Returning the new dictionary object with the information read in:
		return myDictionary2;
	}
};