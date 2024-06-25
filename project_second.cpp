#include "Hash24.h"
#include "Dictionary.h"
using namespace std;

// Function to parse the input string:
vector<string> inputParsing(string myInput)
{
	// "myWords" vector to store the parsed input string: 
	vector<string> myWords;

	stringstream ss(myInput);

	// This is used to store a single word of the input string:
	string singleWord;

	// Loop to parse the input string:
	while (getline(ss, singleWord, ' '))
	{
		// This erases the "," in each word:
		singleWord.erase(remove(singleWord.begin(), singleWord.end(), ','), singleWord.end());

		// This puts each word in the "myWords" vector:
		myWords.push_back(singleWord);
	}
	return myWords;
}

int main(int argc, char* argv[])
{
	// Ensure there are enough command-line arguments
    if (argc < 3)
    {
        cerr << "Usage: " << argv[0] << " <dictionary file> <query string>" << endl;
        return 1;
    }

	// This calls the static function to read the entire "Dictionary" object from the file passed in:
	Dictionary myDictionary2 = Dictionary::readFromFile(argv[1]); // Dictionary myDictionary2 = Dictionary::readFromFile("dictionary.txt");

	// Input string:
	string input = argv[2];
	//string input = "amenities, aaron, hima, abilities, akul, sujan, thread, this, zebra, yugoslavia, zinc, marito, moglie, xml, void, italiano, ciao";

	// Vector to store the parsed input string:
	vector<string> myWords = inputParsing(input);

	// Checking if the input words are inside the hash table:
    for (int i = 0; i < myWords.size(); i++)
    {
        if (myDictionary2.find(myWords[i]) == true)
        {
            cout << myWords[i] << " found" << endl;
        }
        else
        {
            cout << myWords[i] << " not found" << endl;
        }
    }

    return 0;
}