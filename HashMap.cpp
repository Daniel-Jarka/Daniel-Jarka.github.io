/*
 *  HashMap.cpp
 *  Daniel Jarka & Paul Wang
 *  12/10/24
 *
 *  CS 15 Project 4: Gerp
 *
 *  This file contains the implementation of the
 *  HashMap class.
*/
#include "HashMap.h"

using namespace std;

/*
 * name:      Constructor
 * purpose:   Initializes initial values of HashMap class
 * arguments: none
 * returns:   none
 * effects:   Builds initial state of HashMap class
 */
HashMap::HashMap() {
    capacity = 0;
    numItems = 0;
    table = nullptr;
}

/*
 * name:      Destructor
 * purpose:   Frees memory allocated on the heap for the table and sensitive
 *            hash pointers
 * arguments: none
 * returns:   none
 * effects:   Frees dynamically allocated memory
 */
HashMap::~HashMap() {
    for (int i = 0; i < capacity; ++i) {
        delete table[i].cases;
        table[i].cases = nullptr;
    }
    delete[] table;

}

/*
 * name:      insert()
 * purpose:   Inserts a key and the corresponding line into the HashMap
 * arguments: A key string that represents the lowercase key to map and a 
 *            line_loc struct that contains the origina word, line number, 
 *            and file number of the key.
 * returns:   none
 * effects:   Inserts key and line into the HashMap
 */
void HashMap::insert(std::string key, SensitiveHash::line_loc line) {
    if (numItems >= capacity * load_factor) {
        expand();
    }
    //find the index
    int index = std::hash<std::string>{}(key) % capacity;
    //linear probbing
    while (not table[index].isEmpty and table[index].key != key) {
        index = (index + 1) % capacity;
    }

    if (table[index].isEmpty) {
        table[index].key = key;
        table[index].isEmpty = false;
        ++numItems;
    }
    
    
    table[index].cases->insert(line);

}

/*
 * name:      containsI()
 * purpose:   Checks if a key regardless of case is in the HashMap.
 * arguments: A string key to search for
 * returns:   true if the key is in the map, false if not.
 * effects:   none
 */
bool HashMap::containsI(std::string key) {
    for (char &c : key) {
        c = std::tolower(c);
    }


    int index = std::hash<std::string>{}(key) % capacity;
    int starting_index = index;
    // loop through bucket vector
    while (table[index].key != key) {
        index = (index + 1) % capacity;
        if (index == starting_index) {
            return false;
        }
    }
    //check if bucket is empty or if is nullptr
    if (table[index].isEmpty or table[index].cases == nullptr) {
        return false;
    }

    return true;
}

/*
 * name:      containsS()
 * purpose:   Checks if a key of a particular case is in the Sensitive Hash.
 * arguments: A string key to search for
 * returns:   true if the key is in the map, false if not.
 * effects:   none
 */
bool HashMap::containsS(std::string key) {
    std::string copy_key = key;
    for (char &c : copy_key) {
        c = std::tolower(c);
    }

    int index = std::hash<std::string>{}(copy_key) % capacity;
    int starting_index = index;

    // loops and checks if bucket exists
    while (table[index].key != copy_key) {
        index = (index + 1) % capacity;
        if (index == starting_index) {
            return false;
        }
    }
    //checks if bucket is empty
    if (table[index].isEmpty or table[index].cases == nullptr) {
        return false;
    }
    //calls sensitive hash contains if not empty and found index
    return table[index].cases->contains(key);
}

/*
 * name:      expand()
 * purpose:   Increases the capacity of the table and rehashes each key.
 * arguments: none
 * returns:   none
 * effects:   Creates a new table on the heap with double original capacity and
 *            rehashes all keys with the new capacity
 */
void HashMap::expand() {
    int old_cap = capacity;
    Bucket* old_table = table;
    capacity = old_cap * 2 + 5;
    table = new Bucket[capacity];

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

/*
 * name:      getSensitive()
 * purpose:   Returns the vector of values that correspond to a sensitive case
 *            key
 * arguments: a string key whose values to find
 * returns:   a line_loc vector that contains all the occurences of a case
 *            sensitive key
 * effects:   none
 */
std::vector<SensitiveHash::line_loc> HashMap::getSensitive(std::string key) {
    std::string copy_key = key;
    for (char &c : key) {
        c = std::tolower(c);
    }
    //lowercase the key and hash function the key
    int index = std::hash<std::string>{}(key) % capacity;
    //check for linear probign
    while (not table[index].isEmpty and table[index].key != key) {
        index = (index + 1) % capacity;
    }

    return table[index].cases->findKey(copy_key);
}

/*
 * name:      getCases()
 * purpose:   Returns a Sensitive Hash pointer to all of the different case
 *            occurences of a key
 * arguments: a string key to search for
 * returns:   A Sensitive Hash pointer that represents all of the different
 *            buckets that correspond with unique casings of a key.
 * effects:   none
 */
SensitiveHash *HashMap::getCases(std::string key) {
    
    for (char &c : key) {
        c = std::tolower(c);
    }
    //hash index
    int index = std::hash<std::string>{}(key) % capacity;
    // account for linear probbing
    while (not table[index].isEmpty and table[index].key != key) {
        index = (index + 1) % capacity;
    }
    return table[index].cases;
}
