/*
 *  gerp.cpp
 *  Daniel Jarka & Paul Wang
 *  12/10/24
 *
 *  CS 15 Project 4: Gerp
 *
 *  This file contains the driver that allows the user to create an instance
 *  of Gerp and run it. To use Gerp, the client must enter an input Directory
 *  and the name of an output file to send outputs to. Using this driver,
 *  gerp will index the inputted directory and ask the user queries to search
 *  for words inputted by the user. 
*/
#include "gerp.h"
#include <fstream>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./gerp inputDirectory outputFile" << '\n';
        exit(EXIT_FAILURE);
    }

    Gerp new_gerp(argv[1]);
    new_gerp.query(argv[2]);

}