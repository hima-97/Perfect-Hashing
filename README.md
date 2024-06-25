# Project Description

This project consists of implementing a perfect hashing scheme using universal hash functions.
This hashing scheme is constructed in a way that it can be applied to a file containing approximately 350,000 words with one word per line.

The project is divided in two programs:
1. The first program consists of reading the dictionary words from a text file, creating a hash table using perfect hashing, and storing (i.e. writing) the hash table in an output file.
   While creating the hash table, the program also prints out some statistics about the hash table.
2. The second program consists of reading the hash table from the output file of the first program and executing some queries on such hash table.

# Universal Hashing

The analysis and performance of hash tables depend on the hash function having two fundamental properties:
- The hash function must be computable in constant time (i.e. independent of number of items in hash table)
- The hash function must distribute its items uniformly among the slots

Universal hash functions allow to choose the hash function randomly so that the second property above is satisfied. <br />
If we choose a hash function randomly from a universal family of hash functions, then the probability of a collision between any two distinct items is at most 1/M where M is the size of the hash table. Therefore, when adding into a table with N items, the probability of a collision at the initial point is at most N/M or the load factor.

A universal hash function has the following format: H_a,b(X) = [(aX + b) mod p] mod m
- p = prime number that is larger than any key (i.e. item) that will be hashed
- a, b = two random integers such that 1 ≤ a ≤ (p - 1) and 0 ≤ b ≤ (p - 1)
- m = size of table

To hash strings, convert the string to a number and only then use the hash function above to guarantee universality:
- Each character of the string is interpreted as a number (i.e. ASCII), so a single string becomes just a sequence of numbers d[0]d[1]d[2]d[3]···d[t]
- Moreover, a random constant c is picked such that 1 ≤ c ≤ (p - 1)
- Now convert the string to a number with G_c(str) = (d[0]c^(t) + d[1]c^(t−1) + d[2]c^(t−2) + ... + d[t]) mod p
- Note: to make sure that the arithmetic does not result in any overflows, you mod out by p at every step

# Perfect Hashing

Perfect hashing is hashing without collisions.

If you hash N items in a table of size N^2 with a randomly chosen hash function, then the probability of not having any collisions is greater than 1/2.
If you get a collision, then you pick another hash function and try again. <br />
With independent trials, the expected number of attempts you have to make to achieve 0 collisions is less than 2.

Having a table of size N^2 is a big waste of memory, therefore in this perfect hashing scheme you do not hash directly to a table of size N^2.
Instead, you first hash into a primary hash table of size N and then, when there is a collision at a certain slot of this primary table, you create a secondary hash table for that slot.
If t items collide at a certain slot of the primary hash table, then you create a secondary hash table of size t^2 and use perfect hashing to store the t items.
This means that each secondary hash table will be constructed using a different hash function until it is collision free. <br />
Note: the expected number of slots used by all of the secondary hash tables is less than 2N. <br />
Note: each secondary hash table has (i.e. stores) its own hash function, since it might be necessary to try different hash function to find one that did not result in any collisions.

The perfect hashing scheme described above requires the ability to randomly pick a different hash function until no collisions occur.
Such task is accomplished through universal hashing (see related section above).

To search for an item with this perfect hashing scheme, you have to hash twice. First, you hash the item to find its slot in the primary hash table.
If that slot is not empty, then you find the item's slot in the secondary hash table.
If the slot in the secondary hash table is also not empty, then you compare your item with the item in the secondary hash table.
If there is a match then you have found the item you wanted, otherwise the item is not in the hash table.

This perfect hashing scheme only works if we know all N items in advance, otherwise you cannot know how many items hash into the same slot of the primary hash table.
There are different applications where you would know the items in advance and this perfect hashing scheme would be useful:
- One example is when we store and burn files onto a CD/DVD. Once the disc is finalized, no additional files can be added to the disc.
  You can therefore construct a perfect hash table of the filenames and burn the hash table along with the files onto the disc.
- Another example is place names for a GPS device. Names of cities, towns, roads, etc. will not change often.
  Therefore, you can construct a perfect hash table to store these place names. Whenever the GPS device is updated, a new hash table will have to be constructed.
  
# Dictionary Class

The `Dictionary` class implements a perfect hashing scheme to manage a hash table that stores a large number of words efficiently. This class includes methods for constructing the hash table from a file, querying the table, and writing/reading the table to/from a file.

### Methods

- **Constructor**:
  - `Dictionary(string fname, int tsize)`: 
    - This constructor takes the name of a file and the primary hash table size as parameters.
    - It reads the words from the file to construct the hash table using the perfect hashing scheme.
    - Construction involves two passes:
      1. The first pass reads each word from the file and determines its slot in the primary hash table.
      2. The second pass creates secondary hash tables for slots in the primary table where needed.
    - While constructing the hash table, the following statistics are printed:
      - A dump of the hash function used
      - Number of words read
      - Primary hash table size
      - Maximum number of collisions in a slot of the primary hash table
      - For each i between 0 and 20 (inclusive), the number of primary hash table slots with i collisions
      - All the words in the primary hash table slot with the largest number of collisions (if multiple, one is chosen arbitrarily)
      - For each j between 1 and 20 (inclusive), the number of secondary hash tables that tried j hash functions to avoid collisions (excluding slots with no collisions)
      - The average number of hash functions tried per slot of the primary hash table with at least 2 items (excluding slots with no collisions)

- **find()**:
  - `bool find(string word)`: 
    - Queries the hash table for the given word.
    - Returns `true` if the word is present in the hash table, `false` otherwise.

- **writeToFile()**:
  - `void writeToFile(string fName)`:
    - Writes the entire dictionary object to a file using C++'s `write()` function from the `fstream` library.
    - The `write()` method writes the entire hash table to the file in one step, including all referenced objects.
    - This method has O(1) time complexity.

- **readFromFile()**:
  - `static Dictionary readFromFile(string fName)`:
    - Reads an entire dictionary object from a file using C++'s `read()` function from the `fstream` library.
    - This is a static method invoked using the `Dictionary` class name (i.e., `Dictionary::readFromFile()`).

### Class Structure

- **PrimarySlot Class**:
  - Represents each slot of the primary hash table.
  - Attributes:
    - `Hash24 HashForSecondaryTable`: Hash function used for the secondary hash table.
    - `vector<string> wordsInPrimarySlot`: Words that collide in this primary slot.
    - `vector<string> secondaryTable`: Secondary hash table.
    - `int secondaryTableSize`: Size of the secondary hash table.
    - `int hashAttempts`: Number of hash functions attempted to create a collision-free secondary table.
  - Constructor initializes an empty `PrimarySlot`.

- **Dictionary Class**:
  - Manages the primary and secondary hash tables.
  - Attributes:
    - `int wordsReadIn`: Number of words read from the input file.
    - `int primaryTableSize`: Size of the primary hash table.
    - `Hash24 HashForPrimaryTable`: Hash function for the primary hash table.
    - `vector<PrimarySlot> primaryTable`: Primary hash table.
    - `int maxCollisions`: Maximum number of collisions in any primary slot.
    - `vector<string> slotMaxCollisions`: Words in the primary slot with the most collisions.
    - `int primarySlotsOfWords[21]`: Slots categorized by the number of words they contain.
    - `int attemptsHashForSecondaryTable[21]`: Tracks hash attempts for secondary tables.

### Implementation Details

- The `Dictionary` class uses a two-pass construction process to ensure a perfect hashing scheme.
- The `find()` method allows efficient querying of the hash table.
- The `writeToFile()` and `readFromFile()` methods handle serialization and deserialization of the entire dictionary object, ensuring quick and efficient storage and retrieval.

This detailed structure ensures that the `Dictionary` class manages hash tables efficiently, supports perfect hashing, and provides robust data handling capabilities for large datasets.

# Tools and Concepts
- Languages: C++
- VSCode
- Dictionary
- Hashing
- File handling
- Object-Oriented Programming (OOP)
- String manipulation
- Vectors

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
