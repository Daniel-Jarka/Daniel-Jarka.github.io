/*
 *  gerp.cpp
 *  Daniel Jarka & Paul Wang
 *  12/10/24
 *
 *  CS 15 Project 4: Gerp
 *
 *  This file contains the implementation of the
 *  Gerp class.
*/
#include "gerp.h"
#include <set>
#include <fstream>

 

using namespace std;

 
/*
 * name:      gerp
 * purpose:   builds the file directory, and hashmap
 * arguments: a string the represent the directory name
 * returns:   none
 * effects: creates a vector of directories to store the line information of the
 * ,and inserts each word into the hashmap
 */
Gerp::Gerp(std::string directory){

    direct_index = 0;
    FSTree helper(directory);
    direct_traverse(helper.getRoot(), "");
}

/*
 * name:      direct_traverse
 * purpose: traverses through the directory and files and builds the respective
 * file path to each file. Reads the file when reaches it.
 * arguments: a directory node pointer that represents the current directory the
 * the function is working with, and a string that builds an output for the
 * file path.
 * returns:   none
 * effects: traverses through the filepath and calls the read file function
 * when it reaches a file. 
 */
void Gerp::direct_traverse(DirNode *subdirectory, string output)
{
    // base case for empty directoy
    if (not subdirectory) {
        return;
    }
    //concatnating the output
    output += subdirectory->getName();
    output += '/';

    //base case for files.
    if (subdirectory->hasFiles()) {

        for (int i = 0; i < subdirectory->numFiles(); i++) {
            read_file(output + subdirectory->getFile(i));
        }

    }

    //recursive case for more directories.
    if (subdirectory->hasSubDir()) {
        for (int i = 0; i < subdirectory->numSubDirs(); i++) {
            direct_traverse(subdirectory->getSubDir(i), output);
        }
    }
}

/*
 * name: read_file
 * purpose: read the file by getting each line and storing each line onto
 * vector, nad pushes it onto a directory index.
 * arguments: a string representing the filepath it takes to reach the current
 * working file.
 * returns:   none
 * effects: traverses through the filepath and calls the read file function
 * stores the file information and data into a vector of directory structs 
 * stored as private member variable
 */
void Gerp::read_file(string filepath) {

    //open file, and build variables to iterate through the file, line by line
    std::ifstream infile(filepath);
    int line_num = 0;
    std::string line;

    if (not infile) {
        throw runtime_error("Unable to open file " + filepath);
    }

    //build directoy struct with line information
    directory new_direct = {filepath, {}, direct_index};

    //read through the file
    while (getline(infile, line)) {
        new_direct.lines.push_back(line);
        read_line(line, line_num);
        ++line_num;

    }

    infile.close();

    // push the data on the private directory vector
    file_data.push_back(new_direct);
 
    direct_index++;

}

/*
 * name: read_line
 * purpose: reads 
 * arguments: a string representing the filepath it takes to reach the current
 * working file.
 * returns:   none
 * effects: traverses through the filepath and calls the read file function
 * stores the file information and data into a vector of directory structs 
 * stored as private member variable
 */
void Gerp::read_line(std::string &line, int line_num) {
    std::istringstream iss(line);
    std::string word;
    std::unordered_set<std::string> words_set;


    while (iss >> word) {

        stripNonAlphaNum(word);
        SensitiveHash::line_loc new_value = {line_num, direct_index, word};
        if (words_set.find(word) == words_set.end()) {
            lowerWord(word);
            hashmap.insert(word, new_value);
        }

        words_set.insert(new_value.original_name);
    }
}

/*
 * name: stripNonAlpaNum
 * purpose: strips the nonalphanumeric numbers from string edges
 * arguments: the input string that is subjected to be stripped
 * returns: none
 * effects: none
 */
void Gerp::stripNonAlphaNum(std::string &input) {
    int index = 0;
    while (not isalnum(input[index]) and index < int(input.size())) {
        index++;
    }
    
    int endex = input.size() - 1;
    while (not isalnum(input[endex]) and endex > 0) {
        endex--;
    }
    //turns input into a substring of itself
    input = input.substr(index, endex - index + 1);
}



/*
 * name: lowerWord
 * purpose: turn all characters in given word to lowercase
 * arguments: input address to word to be lowered.
 * returns: none
 * effects: none
 */
void Gerp::lowerWord(string &word) {
    for (char &c : word) {
        c = std::tolower(c);
    }
}



/*
 * name: Query
 * purpose: main query function that reads in the user input.
 * arguments: a string that repersents the original outFile
 * returns: none
 * effects: builds a query for the user, and can change the output File if 
 * needed.
 */
void Gerp::query(std::string outputFile) {
    std::ofstream outFile(outputFile);
    std::string input;

    while (input != "@q" and input != "@quit") {
        std::cout << "Query? ";
        cin >> input;
        if (cin.eof()) {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            outFile.close();
            return;
        }if (input == "@i" or input == "@insensitive") {
            cin >> input; 

            stripNonAlphaNum(input);
            if (hashmap.containsI(input) and not input.empty()) {
                insensitiveSearch(outFile, input);
            }else {
                outFile << input << " Not Found." << endl;
            }
        } else if (input == "@f") {
            cin >> input;
            outFile.close();
            outFile.open(input);
            //closes old file and creates new one
        } else if (input != "@q" and input != "@quit") {
                stripNonAlphaNum(input);
                if (hashmap.containsS(input) and not input.empty()) {
                    sensitiveSearch(outFile, input);
                } else {
                    outFile << input << " Not Found. Try with";
                    outFile << " @insensitive or @i." << endl;
                }
        }
    }
    outFile.close();
    cout << "Goodbye! Thank you and have a nice day." << endl;
}


/*
 * name: sensitiveSearch
 * purpose: with a given input, searches their specifc bucket is hashes to
 * prints the filepath to the ooutput file
 * arguments: an ostream address to the output file, and a string that 
 * represents the lowered input.
 * returns: none
 * effects: none
 */
void Gerp::sensitiveSearch(std::ostream &output, std::string input) {
    std::vector<SensitiveHash::line_loc> info = hashmap.getSensitive(input);

    for (int i = 0; i < info.size(); ++i) {
        sendToFile(output, info.at(i));
    }
}


/*
 * name: insensitive Search
 * purpose: searches the general case of a specific word. Traverses through the
 * hash map, and prints out a unique line once to the output file
 * arguments: an ostream address to the output file, and a string that 
 * represents the lowered input.
 * returns: none
 * effects: none
 */
void Gerp::insensitiveSearch(std::ostream &output, std::string input) {
    SensitiveHash *info = hashmap.getCases(input);
    SensitiveHash::sensitiveBucket *temp_table = info->getTable();
    unordered_set<int> processed_lines[direct_index];
    // uses a set to check for repeat lines

    // iterates through all buckets in the input's hashmap
    for (int j = 0; j < info->getCapacity(); ++j) {
        if (not temp_table[j].isEmpty) {
            for (int i = 0; i < temp_table[j].value.size(); ++i) {
                //check ecach table if output has changed
                SensitiveHash::line_loc data = temp_table[j].value.at(i);
                if (processed_lines[data.file_num].find(data.line_num) == 
                                    processed_lines[data.file_num].end()) {
                    sendToFile(output, data); //prints to output File
                    processed_lines[data.file_num].insert(data.line_num);
                }
            }
        }
    }
}

/*
 * name: sendToFile
 * purpose: prints linelocation of word to the output file
 * arguments: an ostream address to the output file, and a line_location struct
 * that stores the data of the current working struct 
 * represents the lowered input.
 * returns: none
 * effects: outputFile recieves changes
 */
void Gerp::sendToFile(std::ostream &output, SensitiveHash::line_loc &info) {
    output << file_data.at(info.file_num).dir_name;
    output << ":" << info.line_num + 1 << ": ";
    output << file_data.at(info.file_num).lines.at(info.line_num) << std::endl;
}

/*
 * name: getDirs
 * purpose: returns  a vector of file_data 
 * arguments: an ostream address to the output file, and a line_location struct
 * that stores the data of the current working struct 
 * represents the lowered input.
 * returns: none
 * effects: none
 */
std::vector<Gerp::directory> Gerp::getDirs()
{
    return file_data;
}