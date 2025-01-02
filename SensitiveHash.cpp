/*
 *  SensitiveHash.cpp
 *  Daniel Jarka & Paul Wang
 *  12/10/24
 *
 *  CS 15 Project 4: Gerp
 *
 *  This file contains the implementation of the
 *  SensitiveHash class.
*/
#include "SensitiveHash.h"

using namespace std;

/*
 * name:      Constructor
 * purpose:   Initializes initial values of Sensitive Hash class
 * arguments: none
 * returns:   none
 * effects:   Builds initial state of Sensitive Hash class
 */
SensitiveHash::SensitiveHash() {
    capacity = 0;
    numItems = 0;
    table = nullptr;
}

/*
 * name:      Destructor
 * purpose:   Frees memory allocated on the heap for the table
 * arguments: none
 * returns:   none
 * effects:   Frees dynamically allocated memory
 */
SensitiveHash::~SensitiveHash() {
    delete[] table;
}

/*
 * name:      insert()
 * purpose:   Inserts a line_loc into the Sensitive Hash
 * arguments: A line_loc struct that contains the key, line number, and file
 *            number of the key.
 * returns:   none
 * effects:   Inserts line_loc into the Sensitive Hash
 */
void SensitiveHash::insert(line_loc line) {
    if (capacity == 0 or numItems > capacity * load_factor) {
        expand();
    }

    //sensitive hash indexing
    int index = std::hash<std::string>{}(line.original_name) % capacity;

    // linear probbing
    while(not table[index].isEmpty and table[index].key != line.original_name){
        index = (index + 1) % capacity;
    }

    if (table[index].isEmpty) {
        table[index].key = line.original_name;
        table[index].isEmpty = false;
        ++numItems;
    }
    
    //pushes to back to save time
    table[index].value.push_back(line);
}


/*
 * name:      findKey()
 * purpose:   Finds the key associated with a particular word
 * arguments: A string that represents the key to search for in the Hash,
 * returns:   A line_loc vector that represents all of the line and file
 *            occurences of the key.
 * effects:   none
 */
std::vector<SensitiveHash::line_loc> SensitiveHash::findKey(std::string key) {
    int index = std::hash<std::string>{}(key) % capacity;
    
    while (not table[index].isEmpty and table[index].key != key) {
        index = (index + 1) % capacity;
    }
    return table[index].value;
}

/*
 * name:      getTable()
 * purpose:   returns the table of the Sensitive Hash
 * arguments: none
 * returns:   returns a pointer to sensitive buckets that represents the table
 * effects:   none
 */
SensitiveHash::sensitiveBucket *SensitiveHash::getTable() {
    return table;
}

/*
 * name:      getCapacity()
 * purpose:   returns the capacity of the Sensitive Hash
 * arguments: none
 * returns:   an integer that represents the capacity of the Sensitive Hash
 * effects:   none
 */

int SensitiveHash::getCapacity()
{
    return capacity;
}

/*
 * name:      contains()
 * purpose:   Checks if a certain key is in the SensitiveHash.
 * arguments: A string key to search for
 * returns:   true if the key is in the map, false if not.
 * effects:   none
 */
bool SensitiveHash::contains(std::string key) {
    int index = std::hash<std::string>{}(key) % capacity;
    int starting_index = index;

    // go through the bucket and check if the bucket is contained
    while (table[index].key != key) {
        index = (index + 1) % capacity;


        if (index == starting_index) {
            return false;
        }
    }
    //edge case
    if (table[index].isEmpty) {
        return false;
    }
    return true;
}

/*
 * name:      expand()
 * purpose:   Increases the capacity of the table and rehashes each key.
 * arguments: none
 * returns:   none
 * effects:   Creates a new table on the heap with double original capacity and
 *            rehashes all keys with the new capacity
 */
void SensitiveHash::expand() {
    int old_cap = capacity;
    capacity = old_cap * 2 + 2;
    sensitiveBucket* old_table = table;
    table = new sensitiveBucket[capacity];

    // create new table and fill in the data
    for (int i = 0; i < old_cap; ++i) {
        int index = std::hash<std::string>{}(old_table[i].key) % capacity;

        // Resolve collisions in the new table
        while (not table[index].isEmpty) {
            index = (index + 1) % capacity;
        }

        table[index] = old_table[i];
    }

    delete[] old_table;
}
