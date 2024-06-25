# Perfect Hashing Project

## Project Description

This project implements a perfect hashing scheme using universal hash functions. The hashing scheme is designed to efficiently handle a file containing approximately 350,000 words, with one word per line.

The project is divided into two programs:
1. **Hash Table Construction**: Reads dictionary words from a text file, creates a hash table using perfect hashing, and writes the hash table to an output file. During the creation, the program prints out various statistics about the hash table.
2. **Hash Table Querying**: Reads the hash table from the output file of the first program and executes queries on it.

## Universal Hashing

The performance of hash tables depends on two key properties of the hash function:
- The hash function must be computable in constant time (i.e., independent of the number of items in the hash table).
- The hash function must distribute items uniformly among the slots.

Universal hash functions allow for random selection to ensure uniform distribution. The probability of a collision between any two distinct items is at most 1/M, where M is the size of the hash table. Thus, for N items, the probability of a collision is at most N/M, or the load factor.

A universal hash function has the following format: H<sub>a,b</sub>(X) = [(aX + b) mod p] mod m
- **p**: A prime number larger than any key to be hashed.
- **a, b**: Two random integers such that 1 ≤ a ≤ (p - 1) and 0 ≤ b ≤ (p - 1).
- **m**: The size of the table.

For string hashing, convert the string to a number before using the universal hash function:
- Convert each character to its ASCII value, forming a sequence of numbers.
- Use a random constant **c** (1 ≤ c ≤ (p - 1)).
- Convert the string to a number using: G<sub>c</sub>(str) = (d<sub>0</sub>c<sup>t</sup> + d<sub>1</sub>c<sup>t−1</sup> + ... + d<sub>t</sub>) mod p

## Perfect Hashing

Perfect hashing aims to eliminate collisions.

By hashing N items into a table of size N² with a randomly chosen hash function, the probability of no collisions is greater than 1/2. If a collision occurs, a new hash function is selected, and the process is repeated. The expected number of attempts to achieve zero collisions is less than 2.

To conserve memory, perfect hashing is implemented in two levels:
1. **Primary Hash Table**: Hashes items into a primary table of size N.
2. **Secondary Hash Tables**: For collisions in the primary table, create secondary tables of size t² for t colliding items. Each secondary table uses its own hash function until it is collision-free.

Searching involves two hashes:
1. Hash the item to find its primary slot.
2. If the primary slot is non-empty, hash again to find the secondary slot.

Applications include:
- **CD/DVD Storage**: Finalized discs can't have additional files, making perfect hashing ideal for filenames.
- **GPS Device Place Names**: Names of places don't change often, making perfect hashing useful for storing them.

## Dictionary Class

The `Dictionary` class implements a perfect hashing scheme to manage a large number of words efficiently. It includes methods for constructing, querying, and serializing the hash table.

### Methods

- **Constructor**:
  - `Dictionary(string fname, int tsize)`: Constructs the hash table from a file, printing statistics about the process.
    - **Statistics Printed**:
      - Hash function used
      - Number of words read
      - Primary hash table size
      - Maximum collisions in a primary slot
      - Distribution of collisions across primary slots
      - Words in the most-collided primary slot
      - Secondary hash table construction attempts
      - Average hash functions tried for secondary tables

- **find()**:
  - `bool find(string word)`: Checks if a word is present in the hash table.

- **writeToFile()**:
  - `void writeToFile(string fName)`: Writes the entire dictionary object to a file using C++'s `write()` function.

- **readFromFile()**:
  - `static Dictionary readFromFile(string fName)`: Reads a dictionary object from a file using C++'s `read()` function.

### Class Structure

- **PrimarySlot Class**:
  - Represents a slot in the primary hash table.
  - Attributes include the hash function for the secondary table, words in the primary slot, the secondary table, its size, and hash attempts.

- **Dictionary Class**:
  - Manages the primary and secondary hash tables.
  - Attributes include the number of words read, primary table size, hash function for the primary table, primary table vector, maximum collisions, words in the most-collided slot, and tracking arrays for primary and secondary slots.

## Tools and Concepts
- Languages: C++
- IDE: VSCode
- Concepts: Dictionary, Hashing, File Handling, Object-Oriented Programming (OOP), String Manipulation, Vectors

## Running and Testing the Project

### First Program: Hash Table Construction

Compile and run:
```sh
g++ Dictionary.cpp project_first.cpp Hash24.cpp -o project_first
./project_first [words dataset text file] dictionary.txt
```

# Running and Testing the Project

You can run and test the first program of the project by running the following command:

- `if ($?) { g++ Dictionary.cpp project_first.cpp Hash24.cpp -o project_first } ; if ($?) { .\project_first [words dataset text file] dictionary.txt }`

- Note: replace `[words text file]` with one of the provided words dataset text files (i.e. dataset_11.txt or dataset_11.txt or dataset_11.txt)
        or you can also test your own words dataset text file following the same format

- Note: the `{ g++ Dictionary.cpp project_first.cpp Hash24.cpp -o project_first }` command compiles the Dictionary.cpp, project_first.cpp, and Hash24.cpp files,
        producing a project_first executable file

- Note: the `dictionary.txt` filename passed via argv[2] generates a text file that stores the entire dictionary

Example: <br />
The command `if ($?) { g++ Dictionary.cpp project_first.cpp Hash24.cpp -o project_first } ; if ($?) { .\project_first dataset_1000 dictionary.txt }` will output: <br />

`*** Hash24 dump ***` <br />
`prime1 = 16890581` <br />
`prime2 = 17027399` <br />
`random_a = 12275` <br />
`random_b = 32170` <br />
`random_c = 31357` <br />
`Number of words = 10000` <br />
`Table size = 10000` <br />
`Max collisions = 6` <br />
`# of primary slots with 0 words = 3694` <br />
`# of primary slots with 1 words = 3639` <br />
`# of primary slots with 2 words = 1863` <br />
`# of primary slots with 3 words = 626` <br />
`# of primary slots with 4 words = 140` <br />
`# of primary slots with 5 words = 31` <br />
`# of primary slots with 6 words = 7` <br />
`# of secondary hash tables trying 7 hash functions = 0` <br />
`# of secondary hash tables trying 8 hash functions = 0` <br />
`# of secondary hash tables trying 9 hash functions = 0` <br />
`# of secondary hash tables trying 10 hash functions = 0` <br />
`# of secondary hash tables trying 11 hash functions = 0` <br />
`# of secondary hash tables trying 12 hash functions = 0` <br />
`# of secondary hash tables trying 13 hash functions = 0` <br />
`# of secondary hash tables trying 14 hash functions = 0` <br />
`# of secondary hash tables trying 15 hash functions = 0` <br />
`# of secondary hash tables trying 16 hash functions = 0` <br />
`# of secondary hash tables trying 17 hash functions = 0` <br />
`# of secondary hash tables trying 18 hash functions = 0` <br />
`# of secondary hash tables trying 19 hash functions = 0` <br />
`# of secondary hash tables trying 20 hash functions = 0` <br />
`Average # of hash functions tried = 1.36895` <br />

You can run and test the second program of the project by running the following command:

- `if ($?) { g++ Dictionary.cpp project_second.cpp Hash24.cpp -o project_second } ; if ($?) { .\project_second dictionary.txt "query1, query2, query3, query4" }`

- Note: replace `"query1, query2, query3, query4"` with a series of comma-separated words to check if they are in the dictionary stored in the `dictionary.txt` file

- Note: the `dictionary.txt` file created from the first program is passed here via argv[1]

Example: <br />
The command `if ($?) { g++ Dictionary.cpp project_second.cpp Hash24.cpp -o project_second } ; if ($?) { .\project_second dictionary.txt  "hello, welcome, to, hanji" }` will output: <br />

`hello found` <br />
`welcome found` <br />
`to found` <br />
`hanji not found` <br />
