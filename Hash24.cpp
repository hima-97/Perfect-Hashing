#include "Hash24.h"

static bool initialized = false;

// Constructor:
Hash24::Hash24()
{
	if (!initialized)
	{
		srand(time(0));
		initialized = true;
	}

	// This creates random values for the hash function:
	random_a = rand() % (int)(prime2 - 1) + 1; // 1 <= random_a < prime2
	random_b = rand() % (int)(prime2);         // 0 <= randomo_b < prime2
	random_c = rand() % (int)(prime1 - 1) + 1; // 1 <= random_c < prime1
}

// Universal hash function:
int Hash24::hash(unsigned long x)
{
	if (x >= prime2)
		throw std::runtime_error("Input is greater than prime number!!");

	// This creates a random hash function h(X) = ((aX + b) mod p) mod m:
	// Note: the "mod m" part is missing here because "m" is the size of the table
	return (int)((random_a * x + random_b) % prime2);
}

// Hash function for strings: 
int Hash24::hash(string str)
{
	unsigned long result = 0;

	// This converts the string to a number:
	for (int i = 0; i < str.length(); i++)
	{
		result *= random_c;
		result += str.at(i);
		result %= prime1;
	}

	// This calls and returns the universal hash function:
	return hash(result);
}

// Function to show the values used for the hash function:
void Hash24::dump()
{
	std::cout << "*** Hash24 dump ***" << std::endl;
	std::cout << "prime1 = " << prime1 << std::endl;
	std::cout << "prime2 = " << prime2 << std::endl;
	std::cout << "random_a = " << random_a << std::endl;
	std::cout << "random_b = " << random_b << std::endl;
	std::cout << "random_c = " << random_c << std::endl;
}