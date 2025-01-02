/*
 *  SensitiveHash.h
 *  Daniel Jarka & Paul Wang
 *  12/10/24
 *
 *  CS 15 Project 4: Gerp
 * 
 *  SensitiveHash is a class that represents a HashMap that contains buckets
 *  for the different cases of a particular word. For example, the word all 
 *  variations of "keep," such as "KEEP" "Keep" or "KEep" will be sent to this
 *  SensitiveHash class. From there, each case variation is mapped to a unique
 *  bucket. SensitiveHash also defines a "line_loc" struct which is used to
 *  store the original word of a key (since all of our keys are first converted
 *  to lowercase), the line number a key appears on, and the file number a key
 *  appears in. This struct is used for mapping and accessing. The table of
 *  SensitiveHash is a pointer to "sensitive Bucket" structs, which contain
 *  the key of the bucket, an isEmpty boolean, and a line_loc vector that
 *  represents the "value" of a key. This value is all the line locations
 *  that the word appears on. 
*/

#ifndef REFERENCE_SENSITIVEHASH_H
#define REFERENCE_SENSITIVEHASH_H

#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <utility>
#include <cctype>

class SensitiveHash {


public:

    struct line_loc {
        int line_num;
        int file_num;
        std::string original_name;
    };

    struct sensitiveBucket {
        std::string key;
        bool isEmpty = true;
        std::vector<line_loc> value;
    };

    SensitiveHash();
    ~SensitiveHash();
    

    void insert(line_loc lines);
    std::vector<SensitiveHash::line_loc> findKey(std::string key);
    SensitiveHash::sensitiveBucket* getTable();
    int getCapacity();
    bool contains(std::string key);

private:

    sensitiveBucket* table;

    int capacity;
    int numItems;
    const double load_factor = 0.7;

    void expand();

};
#endif