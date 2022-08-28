#include "Hash24.h"
#include "Dictionary.h"
using namespace std;

int main(int argc, char* argv[])
{
	// This creates an ifstream object:
	ifstream ifs;

	// This opens the file to be read:
	ifs.open(argv[1]); //ifs.open("dataset_100.txt"); 

	// Checking if the file to be read was not open:
	if (!ifs)
	{
		cerr << "Error: file was not open!!" << endl;
	}

	string fileLine;
	int wordCount = 0;
	while (ifs.eof() == 0)
	{
		// This reads a line from the file into the string "fileLine":
		// If you attempt to read the file past the end of it, then "eof()" returns a non-zero int.
		getline(ifs, fileLine);

		wordCount++;
	}

	// This closes the file to be read:
	ifs.close();

	// This calls the "Dictionary" constructor to construct the hash table with the file passed in:
	Dictionary myDictionary(argv[1], wordCount); // Dictionary myDictionary("dataset_100.txt", wordCount);

	// This calls the function to write the entire "Dictionary" object to the file passed in:
	myDictionary.writeToFile(argv[2]); // myDictionary.writeToFile("dictionary.txt");

	return 0;
}