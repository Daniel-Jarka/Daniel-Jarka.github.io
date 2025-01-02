/*
 *  gerp.h
 *  Daniel Jarka & Paul Wang
 *  12/10/24
 *
 *  CS 15 Project 4: Gerp
 * 
 *  Gerp is a class that indexes a file directory and queries the user for
 *  words to search for in this index. A "directory" struct is defined here
 *  to store the filepath of a directory, a directory id (which is an int that
 *  represents the order in which the directory was traversed), and a string
 *  vector that stores all of the lines in a file. These directories are then
 *  stores in a directory vector. Gerp functions by inserting every single word
 *  it reads into a hashmap which internally handles the different cases of a
 *  word. Queries and indexed words are stripped of non alphanumeric characters
 *  and we use unordered sets to prevent repetiton when the same word appears
 *  on a line multiple times. 
*/
#ifndef REFERENCE_GERP_H
#define REFERENCE_GERP_H

#include "HashMap.h"
#include "SensitiveHash.h"
#include "DirNode.h"
#include "FSTree.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <sstream>

class Gerp {

public: 

struct directory {
    std::string dir_name;
    std::vector<std::string> lines;
    int dir_id;
};

Gerp(std::string directory);
void query(std::string outputFile);
void sensitiveSearch(std::ostream &output, std::string word);
void sendToFile(std::ostream &output, SensitiveHash::line_loc &info);
void insensitiveSearch(std::ostream &output, std::string input);

// GETTER FUNCTIONS FOR TESTING

std::vector<directory> getDirs();

private:

void direct_traverse(DirNode *subdirectory, std::string output);
void read_file(std::string filepath);
void read_line(std::string &line, int line_num);
void stripNonAlphaNum(std::string &input);
void lowerWord(std::string &word);


int direct_index;

std::vector<directory> file_data;

HashMap hashmap;

};

#endif

