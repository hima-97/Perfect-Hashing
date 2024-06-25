/*
 * Hash24.cpp
 * 
 * This file implements the Hash24 class, which is used to perform universal hashing.
 * The Hash24 class provides methods to generate hash values for integers and strings
 * using randomly chosen parameters. This is part of a perfect hashing scheme that 
 * aims to minimize collisions by using a set of universal hash functions.
 */

#include "Hash24.h"

static bool initialized = false;

// Constructor: Initializes random values for the hash function parameters.
Hash24::Hash24()
{
    if (!initialized)
    {
        // Seed the random number generator once to ensure different random values on each run.
        srand(time(0));
        initialized = true;
    }

    // Generate random values for the hash function parameters.
    random_a = rand() % (int)(prime2 - 1) + 1; // Ensure 1 <= random_a < prime2
    random_b = rand() % (int)(prime2);         // Ensure 0 <= random_b < prime2
    random_c = rand() % (int)(prime1 - 1) + 1; // Ensure 1 <= random_c < prime1
}

// Universal hash function for integers: Computes the hash value for a given input x.
int Hash24::hash(unsigned long x)
{
    if (x >= prime2)
        throw std::runtime_error("Input is greater than prime number!!");

    // Compute the hash value using the formula: h(X) = (aX + b) mod p
    // Note: the "mod m" part is handled outside this function as it depends on the table size.
    return (int)((random_a * x + random_b) % prime2);
}

// Hash function for strings: Converts a string to a number and then hashes it.
int Hash24::hash(string str)
{
    unsigned long result = 0;

    // Convert the string to a number using a rolling polynomial hash method.
    for (int i = 0; i < str.length(); i++)
    {
        result *= random_c;
        result += str.at(i);
        result %= prime1; // Apply modulus at each step to avoid overflow.
    }

    // Compute the hash value of the resulting number.
    return hash(result);
}

// Dump function: Prints the values used for the hash function parameters.
void Hash24::dump()
{
    std::cout << "*** Hash24 dump ***" << std::endl;
    std::cout << "prime1 = " << prime1 << std::endl;
    std::cout << "prime2 = " << prime2 << std::endl;
    std::cout << "random_a = " << random_a << std::endl;
    std::cout << "random_b = " << random_b << std::endl;
    std::cout << "random_c = " << random_c << std::endl;
}
