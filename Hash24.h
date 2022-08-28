#ifndef HASH24_H
#define HASH24_H
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <algorithm> // Needed to remove characters from strings
#include <sstream> // Needed for the parsing function
using namespace std;

/*
The 24 in Hash24 indicates that the methods in the class work with values as large as 224 which is approximately 16 million.
This is more than large enough for the purposes of this project. To use the Hash24 class, simply create a Hash24 object
and then use it to invoke the universal hash function. The Hash24 object “remembers” the randomly chosen a, b and c used in the universal hash
function. Therefore, you can store the hash object, retrieve it later, and use it to compute the same hash function.
*/

// Class used to perform the universal hash function:
class Hash24
{
private:

	// Prime numbers of suitable size used for the hash function:
	static long const prime1 = 16890581L;   // Prime number ~ 2^24 = 16777216
	static long const prime2 = 17027399L;   // Larger prime ~ 2^24 = 16777216

public:

	// Random numbers used for the hash function:
	long random_a;
	long random_b;
	long random_c;

	// Constructor:
	Hash24();

	// Universal hash function:
	int hash(unsigned long x);

	// Hash function for strings: 
	int hash(string str);

	// Function to show the values used for the hash function:
	void dump();
};

#endif