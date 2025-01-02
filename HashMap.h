/*
 *  HashMap.h
 *  Daniel Jarka & Paul Wang
 *  12/10/24
 *
 *  CS 15 Project 4: Gerp
 *
 *  HashMap is a class that represents a HashMap that contains buckets
 *  for only the lowercase version of a word. For example, all variations of 
 *  "keep," such as "KEEP" "Keep" or "KEep" will be converted to lowercase. 
 *  From there, the line_locs associated with those words are inserted in the
 *  same "lowercase" bucket. The table of HashMap is a pointer to "Bucket" 
 *  structs, which contain the key of the bucket, an isEmpty boolean, and a 
 *  pointer to the SensitiveHash cases of a particular word. This is where the
 *  different cases of a word is accounted for and mapped to. Addititonally,
 *  an assignment operator overload is defined for the Bucket struct to
 *  sufficiently free memory associated with these pointers to SensitiveHash.
*/
#ifndef REFERENCE_HASHMAP_H
#define REFERENCE_HASHMAP_H

#include "SensitiveHash.h"
#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>
#include <utility>
#include <cctype>


class HashMap {


public:

    HashMap();
    ~HashMap();


    void insert(std::string key, SensitiveHash::line_loc lines);
    bool containsI(std::string key);
    bool containsS(std::string key);
    std::vector<SensitiveHash::line_loc> getSensitive(std::string key);
    SensitiveHash* getCases(std::string key);

private:

    struct Bucket {
        std::string key;
        bool isEmpty = true;
        SensitiveHash* cases = new SensitiveHash;

        Bucket& operator=(const Bucket &other) {
            if (this == &other) {
                return *this;
            }

            delete cases;
            key = other.key;
            isEmpty = other.isEmpty;
            cases = other.cases;

            return *this;
        }
    };

    Bucket* table;

    int capacity;
    int numItems;
    const double load_factor = 0.7;

    void expand();

};
#endif