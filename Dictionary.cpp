#include "Dictionary.h"
using namespace std;

// Constructor to construct the hash table with the information in the file passed in:
Dictionary::Dictionary(string fname, int tsize)
{
	// This sets the size of the primary hash table:
	primaryTableSize = tsize;

	// This assigns the vector a size of "primaryTableSize" and fills each slot with a "PrimarySlot":
	primaryTable.assign(primaryTableSize, PrimarySlot());

	// This creates an ifstream object:
	ifstream ifs;

	// This opens the file to be read:
	ifs.open(fname);

	// The file to be read was not open:
	if (!ifs)
	{
		cerr << "Error: file was not open" << endl;
		return;
	}

	string word;
	int indexPrimaryTable = 0;
	while (ifs.eof() == 0)
	{
		// This reads a line (word) from the file into the string "word":
		// If you attempt to read the file past the end of it, then "eof()" becomes returns a non-zero int.
		getline(ifs, word);

		// This is used to track the number of words read in from the file:
		wordsReadIn++;

		// This tells you at which index of the primary table the word read in will be stored:
		indexPrimaryTable = HashForPrimaryTable.hash(word) % primaryTableSize;

		// This stores the word read in at the specific index/slot you found of the primary table:
		// The word is pushed inside the "wordsInPrimarySlot" vector at the specific slot of the primary table. 
		primaryTable[indexPrimaryTable].wordsInPrimarySlot.push_back(word);
	}

	// This closes the file to be read:
	ifs.close();

	// Checking each slot of the primary table:
	for (int i = 0; i < primaryTable.size(); i++)
	{
		// Checking if a slot of the primary table contains at least more than one word:
		if (primaryTable[i].wordsInPrimarySlot.size() > 1)
		{
			// This creates a secondary table of size t^2 (t = words in a slot) for each primary table slot:
			// Each slot is initialized with an empty string:
			primaryTable[i].secondaryTable.assign(pow(primaryTable[i].wordsInPrimarySlot.size(), 2), "");

			// This sets the size of each secondary hash table:
			primaryTable[i].secondaryTableSize = primaryTable[i].secondaryTable.size();

			// Loop that keeps executing until all the words of the primary slot have been inserted in the secondary table:
			bool finishedInserting = false;
			while (!finishedInserting)
			{
				// This re-initialize the "HashForSecondaryTable" object for each slot of the primary table:
				Hash24 tempHash24;
				primaryTable[i].HashForSecondaryTable = tempHash24;

				// This increments the number of hash functions attempted:
				primaryTable[i].hashAttempts++;

				// Checking each word in a slot of the primary table:
				for (int j = 0; j < primaryTable[i].wordsInPrimarySlot.size(); j++)
				{
					// This tells you at which index of the secondary table the word read in will be stored:
					// Note: remember to take the value returned by "hash()" and mod it by the size of the secondary table.
					int indexSecondaryTable = (primaryTable[i].HashForSecondaryTable.hash(primaryTable[i].wordsInPrimarySlot[j])) % (primaryTable[i].secondaryTable.size());

					// Checking if a slot of the secondary table is empty:
					if (primaryTable[i].secondaryTable[indexSecondaryTable] == "")
					{
						primaryTable[i].secondaryTable[indexSecondaryTable] = primaryTable[i].wordsInPrimarySlot[j];
					}
					else
					{
						// This resets the secondary table with empty strings:
						for (int k = 0; k < primaryTable[i].secondaryTable.size(); k++)
							primaryTable[i].secondaryTable[k] = "";

						// Break out of the for loop if there is a collision:
						break;
					}
				}
				// Checking if the last word of the primary slot has been inserted in the secondary table:
				if (std::find(primaryTable[i].secondaryTable.begin(), primaryTable[i].secondaryTable.end(), primaryTable[i].wordsInPrimarySlot[primaryTable[i].wordsInPrimarySlot.size() - 1]) != primaryTable[i].secondaryTable.end())
				{
					finishedInserting = true;
				}
			}
		}
		else
		{
			// Checking if a slot of the primary table contains only one word:
			if (primaryTable[i].wordsInPrimarySlot.size() == 1)
			{
				// This creates a secondary table of size one for each primary table slot that contains only one word:
				primaryTable[i].secondaryTable.assign(1, primaryTable[i].wordsInPrimarySlot[0]);

				// This sets the size of the secondary hash table to one:
				primaryTable[i].secondaryTableSize = 1;
			}
			else

				// This sets the size of the secondary hash table to zero:
				primaryTable[i].secondaryTableSize = 0;
		}
	}

	// This is a dump of the hash function used by the primary hash table:
	HashForPrimaryTable.dump();

	// This prints the number of words read in from the file:
	cout << "Number of words = " << wordsReadIn << endl;

	// This prints the size of the primary hash table:
	cout << "Table size = " << primaryTableSize << endl;

	// This is used to get the primary hash table slot that has the most collisions:
	for (int i = 0; i < primaryTable.size(); i++)
	{
		if (primaryTable[i].wordsInPrimarySlot.size() > maxCollisions)
		{
			maxCollisions = primaryTable[i].wordsInPrimarySlot.size();
			slotMaxCollisions = primaryTable[i].wordsInPrimarySlot;
		}
	}
	cout << "Max collisions = " << maxCollisions << endl;

	// This stores and then prints the number of primary slots containing i words for each i between 0 and 20 (inclusive):
	for (int i = 0; i < primaryTable.size(); i++)
	{
		primarySlotsOfWords[primaryTable[i].wordsInPrimarySlot.size()]++;
	}
	for (int i = 0; i < 21; i++)
	{
		cout << "# of primary slots with " << i << " words = " << primarySlotsOfWords[i] << endl;
	}

	// This prints the words that are in the primary hash table slot with the most collisions:
	cout << "*** Words in the slot with most collisions ***" << endl;
	for (int i = 0; i < slotMaxCollisions.size(); i++)
	{
		cout << slotMaxCollisions[i] << endl;
	}

	// This stores and then prints the number of secondary tables attempting i hash functions for each i between 1 and 20 (inclusive):
	for (int i = 0; i < primaryTable.size(); i++)
	{
		attemptsHashForSecondaryTable[primaryTable[i].hashAttempts]++;
	}
	for (int i = 1; i < 21; i++)
	{
		cout << "# of secondary hash tables trying " << i << " hash functions = " << attemptsHashForSecondaryTable[i] << endl;
	}

	// This is used to get the average number of hash functions attempted per slot of the primary table that had at least two words:
	double slotsWithMoreThanOneWord = 0.0;
	double sumOfHashFunctionsAttempted = 0.0;
	for (int i = 0; i < primaryTable.size(); i++)
	{
		// Checking if a slot of the primary table has at least two words:
		if (primaryTable[i].wordsInPrimarySlot.size() > 1)
		{
			// This increments the number of primary table slots that have at lest two words:
			slotsWithMoreThanOneWord++;

			// This sums up all the hash function attempts made for the secondary tables:
			sumOfHashFunctionsAttempted = sumOfHashFunctionsAttempted + primaryTable[i].hashAttempts;
		}
	}
	double avgNumberOfHashPerSlot = (sumOfHashFunctionsAttempted) / (slotsWithMoreThanOneWord);
	cout << "Average # of hash functions tried = " << avgNumberOfHashPerSlot << endl;
}

// Function to find a word in the hash table: 
bool Dictionary::find(string word)
{
	// This tells you at which index of the primary table the word we want to find is stored:
	int indexPrimaryTable = HashForPrimaryTable.hash(word) % primaryTableSize;

	// Checking if the primary table slot at the given index is not empty:
	if (!(primaryTable[indexPrimaryTable].secondaryTable.empty()))
	{
		// Checking if the secondary hash table of a primary slot contains only one word:
		if (primaryTable[indexPrimaryTable].secondaryTable.size() == 1)
		{
			// Checking if the one word inside the secondary table is the word we want to find:
			if (primaryTable[indexPrimaryTable].secondaryTable[0] == word)
				return true;
			else
				return false;
		}
		else
		{
			// This tells you at which index of the secondary table the word we want to find is stored:
			int indexSecondaryTable = (primaryTable[indexPrimaryTable].HashForSecondaryTable.hash(word)) % (primaryTable[indexPrimaryTable].secondaryTable.size());

			// Checking if the word at the given index of the secondary table is the word we want to find:
			if (primaryTable[indexPrimaryTable].secondaryTable[indexSecondaryTable] == word)
				return true;
			else
				return false;
		}
	}
	else
		return false;
}

// Function to write the entire "Dictionary" class object to a file:
void Dictionary::writeToFile(string fName)
{
	// Output file object:
	ofstream outputFile;

	// This opens the output file in binary mode:
	// Note: "ios::out" means the file is opened for output operations.
	// Note: "ios::trunc" means that if the file already existed, its previous content is deleted.
	outputFile.open(fName, ios::out | ios::trunc | ios::binary);

	// Checking if the output file was opened successfully:
	if (!(outputFile.is_open()))
	{
		cerr << "Error: file was not open!!" << endl;
		return;
	}
	else
	{
		// This writes "int wordsReadIn":
		outputFile.write((char*)&this->wordsReadIn, sizeof(this->wordsReadIn));

		//This writes "int maxCollisions":
		outputFile.write((char*)&this->maxCollisions, sizeof(this->maxCollisions));

		// This writes "vector<string> slotMaxCollisions":
		int mySize = slotMaxCollisions.size();
		outputFile.write((char*)&mySize, sizeof(mySize)); // This writes the size of the vector
		size_t length;
		for (int i = 0; i < slotMaxCollisions.size(); i++)
		{
			// This is used to store the length of each word (string):
			length = sizeof(slotMaxCollisions[i]);

			// This writes the length of each word (string):
			outputFile.write((char*)&length, sizeof(length));

			// This writes each word (string):
			outputFile.write(slotMaxCollisions[i].c_str(), length);
		}

		// This writes the "Hash24 HashForPrimaryTable" object:
		outputFile.write((char*)&this->HashForPrimaryTable, sizeof(this->HashForPrimaryTable));

		// This writes "vector<PrimarySlot> primaryTable":
		outputFile.write((char*)&primaryTableSize, sizeof(primaryTableSize)); // This writes the size of the vector
		for (int i = 0; i < primaryTableSize; i++)
		{
			// This writes each "HashForSecondaryTable" object:
			outputFile.write((char*)&primaryTable[i].HashForSecondaryTable, sizeof(primaryTable[i].HashForSecondaryTable));

			// This writes the length of each "secondaryTable" vector:
			outputFile.write((char*)&primaryTable[i].secondaryTableSize, sizeof(primaryTable[i].secondaryTableSize));

			// This is used to store the length of each word (string) in the "secondaryTable" vector:
			size_t str_len;

			// This writes each word (string) in the "secondaryTable" vector:
			for (int j = 0; j < primaryTable[i].secondaryTableSize; j++)
			{
				// This stores the length of each word (string):
				str_len = primaryTable[i].secondaryTable[j].length();

				// This writes the length of each word (string):
				outputFile.write((char*)&str_len, sizeof(str_len));

				// This writes each word (string):
				outputFile.write(primaryTable[i].secondaryTable[j].c_str(), str_len);
			}
		}
		// This closes the output file:
		outputFile.close();
	}
}