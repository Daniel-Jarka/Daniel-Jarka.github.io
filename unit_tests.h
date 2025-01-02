/*
 *  unit_tests.h
 *  Daniel Jarka & Paul Wang
 *  12/10/24
 *
 *  CS 15 Project 4 Gerp
 *
 *  Uses Matt Russell's unit_test framework to 
 *  test the functionality of functions used for building gerp.
 */
#include "processing.h"
#include "DirNode.h"
#include "FSTree.h"
#include "HashMap.h"
#include "SensitiveHash.h"
#include "gerp.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void dummy_test() {}

// void hash_constructor_test() {
//     HashMap newmap;
// }

// void insert_test() {
//     HashMap newmap;
//     HashMap::line_loc line;
//     line.file_num = 1;
//     line.line_num = 1;
//     std::vector<HashMap::line_loc> lines;
//     lines.push_back(line);
//     newmap.insert("hello", lines);
//     newmap.insert("wtf", lines);
//     newmap.insert("hello", lines);
// }

// void strip_basic_test() {
//     string test = "!!hello@!$!#$";
//     string result = stripNonAlphaNum(test);
//     assert(result == "hello");
// }

// void strip_end_test() {
//     string test = "hello@!$!#$";
//     string result = stripNonAlphaNum(test);
//     assert(result == "hello");
// }

// void strip_front_test() {
//     string test = "@#$@#@!hello";
//     string result = stripNonAlphaNum(test);
//     assert(result == "hello");
// }

// void strip_even_test() {
//     string test = "@!hello!@";
//     string result = stripNonAlphaNum(test);
//     assert(result == "hello");
// }

// void strip_nothing_test() {
//     string test = "hello";
//     string result = stripNonAlphaNum(test);
//     assert(result == "hello");
// }

// void strip_all_test() {
//     string test = "@!@##@$!@";
//     string result = stripNonAlphaNum(test);
//     assert(result == "");
// }

// void traverse_dir_test() {
//     traverseDirectory("/comp/15/files/proj_gerp");
// }

// void traverse_single_dir_test() {
//     traverseDirectory("/comp/15/files/proj-gerp-test-dirs");
// }

// void traverse_single_dir_test() {
//     traverseDirectory("/comp/15/files/proj-gerp-test-dirs/tinyData");
// }

// void traverse_single_dir_test() {
//     traverseDirectory("/comp/15/files/proj-gerp-test-dirs/smallGutenberg");
// }

// void gerp_constructor_test() {
//     Gerp newGerp("/comp/15/files/proj-gerp-test-dirs/tinyData");
// }

// void gerp_getDirs_test() {
//     Gerp newGerp("/comp/15/files/proj-gerp-test-dirs/tinyData");
//     for (int i = 0; i < int(newGerp.getDirs().size()); ++i) {
//         cout << "Directory id: " << newGerp.getDirs().at(i).dir_id << "\n"
//         << "Directory location: " << newGerp.getDirs().at(i).dir_name 
//         << endl;
//         for (int j = 0; j < newGerp.getDirs().at(i).lines.size(); ++j) {
//             cout << newGerp.getDirs().at(i).lines.at(j) << endl;
//         }
//     }
// }

// void gerp_constructor_test() {
//     Gerp newGerp("/comp/15/files/proj-gerp-test-dirs/tinyData");
//     newGerp.sensitiveSearch"gerp");
// }

//void gerp_smallGutenberg_constructor_test() {
    //Gerp newGerp("/comp/15/files/proj-gerp-test-dirs/smallGutenberg/");
    //newGerp.sensitiveSearch("Author:");
//}

// void hash_map_insert_test() {
//     HashMap newmap;

//     SensitiveHash::line_loc loc1 = {1, 1};
//     vector<SensitiveHash::line_loc> loc_vec1 = {loc1};
//     newmap.insert("hello", loc_vec1);

// }

// void hash_map_contain_test() {

//     HashMap newmap;

//     SensitiveHash::line_loc loc1 = {1, 1};
//     vector<SensitiveHash::line_loc> loc_vec1 = {loc1};
//     newmap.insert("hello", loc_vec1);
//     assert(newmap.contains("hello"));
//     assert(newmap.get("hello")[0].line_num == 1);
//     assert(newmap.get("hello")[0].file_num == 1);

// }

// void hash_map_same_insertion_test() {
//     HashMap newmap;

//     SensitiveHash::line_loc loc1 = {1, 1};
//     newmap.insert("hello", loc1);

//     SensitiveHash::line_loc loc2 = {1, 2};
//     newmap.insert("hello", loc2);
//     assert(newmap.numItems == 1);

// }