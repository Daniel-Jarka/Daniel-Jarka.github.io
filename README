/******************************************************************************
* Project 4: Gerp
* CS 15
* README
* Authors: Daniel Jarka (djarka01) and Paul Wang (pwang12)
******************************************************************************/

B. Program Purpose:

    The program is a search query. It will take in commands, and with a given
    directory output the location of the apperance of the given word into an 
    output file. It can consider case insensitive searches where capitalization
    doesn't matter and case sensitive search where the specific word is 
    searched. Additionally, the program can create a new output file if asked.

C. Acknowledgements: 

    Nadia the TA

    used the cctype reference:
    https://cplusplus.com/reference/cctype/
    

D. Files: 
     main.cpp:
          The main driver file that we used to create the instance of the
          gerp class to execute the program

     README:
          this file

     Makefile:
          the compiling program that compiles working c++ files to a runnable
          executable

     gerp.h:
          The interface for the main program class, gerp. Contains query 
          function and all search commands

     gerp.cpp:
          The implementation of the gerp class

     HashMap.h:
          The interface to the hashmap class, contains public functions to
          insert and retrieve hasmap values and locations

     HashMap.cpp:
          The implementation of hashmap class

     Sensitivehash.h:
          The interface of the sensitive hash map class. This class is used as 
          the hashmap for the specific case snesitive buckets of larger words.

     SensitiveHash.cpp:
          the implementation of the sensitive hashmap class.

     unit_test.h:
          A unit testing file for the processing functions, and for testing
          of inital hashmapping and gerp. Functions were made public for
          testing, so they are now all commented out.

     file1.in:
          A testing file used to test basic queries, punctuation, and non
          alphanumeric characters.
     
     file2.in:
          Testing file used to test sensitive, insenstive, and new file
          commands

     file3.in:
          Testing file used to test tricky text like equations and hyperlinks

E. Compile/run:

     import all relevant c++ files stated above and the make file.
     write "make" while in the directory with the files to compile.

     To run:
          The program takes three arguments:
          write "./gerp" and then the name of the directory to search, and then
          the name of the output file that will be intially written into.

F. Architectural Overview:

     To start, the entire program runs through the gerp class. In the gerp
     constructor, we build the hashmap and file directory. 
     
     The hashmap itself contains a pointer to another hashmap in each of its
     buckets. The top-level hashmap is built using the hashmap class, where the 
     buckets contain the sensitive hash class. Both hash map classes contain a 
     bucket struct with information that aids in both indexing and querying
     words.

     For the file directory data, we used the FStree to build an n-arry tree
     that will represent the working directories. The DirNode is the node of
     the FS tree with the data to traverse and builds the path through the 
     tree. The file information is stored in the gerp class as a private member
     variable in a vector that contains directory structs. Each struct has a
     directory id, a vector that contains all of the lines in the file, and
     a string that holds the filepath to the directory. 

     The query is located in the gerp class, and depending on the command, it
     will execute a case sensitive or insensitve search. For sensitive search,
     it will first hash through the hashmap class to find the general bucket of
     that key. In this bucket, the key is sent to the sensitive hash, which
     will hash the key again and send this key to a case-unique bucket if it
     exists. For insensitive search, the program will only hash to the general
     bucket and return a pointer to all of the potential buckets that underly
     this general bucket.
     
G. Data Structures/ADT & Algorithms:

    The primary ADTS used for the function of this program are Hash Map,
    Vector, and Unordered Set.

    Vectors:   
    
    The first is to store the file location data and the actual line as 
    strings. One use of vectos stores directory structs where each element is a 
    file with its respective data. Each file also has its own vector which 
    stores the line information of the file. To access we would go to the first
    vector and go to the file with its respective index and then go to the 
    specific line number by using the line number as the index for the second 
    vector.

    Both the Hashmap and Sensitive Hash use pointers to buckets to represent
    the table. This table is accessed like an array, so it functions like an
    array of buckets. These buckets in the Hashmap contain a pointer to a 
    sensitive hash.

    The sensitive hash is the crux of the hashmap and hash function. The 
    buckets contain another vector that is the location structs of the key that
    mapped to that specific bucket. This allows us to store all of the 
    occurrences of a particular word in a directory without taking up too much
    space. 

    The reason why we used a vector was because of itss ability to provide us
    with instant access to elements. Especially with the file location data
    vector, our time complexity remains constant. Additionally, to avoid 
    a time complexity of O(n), we inserted all elements at the back to avoid
    shifting other values.

    Hashmap:

    Our hashmap while a bit complex was the most optimal way of checking for
    instances of a queried word. Our first hashmap uses a hash function where
    the key is the lowercased version of the queried word. This will map to a 
    bucket that contains a hashmap with the general insensitive cases of the
    word. Each sensitive case has its own bucket it maps to. In a
    sensitive search, it would use the sensitive hash function and the
    oirginal queried word as the key to find the bucket. In an insensitive 
    search, it would just iterate through the vector, and print out all the 
    information in each bucket.

    Unordered Sets:

    Sets are a data structure that stores only one of a unique element. We used
    an unordered set data structure to make sure that time was not wasted by
    trying to sort the insertions. A set is useful for making sure a line is 
    not outputted twice. In a vector of sets, the vector index represents the 
    file number, and our program inserts the line number of the respective 
    file into that respective set. This allows for our program to check if the 
    line has already been outputted, even when accessing different buckets.


    Algorithms:

    InsensitiveSearch():

    This function was decievingly tricky. Using the hash function, we can
    easily access the right bucket with all the insensitive cases. However,
    printing out all the lines is not straightforward. Beyond iterating through
    the entire vector of buckets, we also have to make sure that a line is not
    printed out twice. In order to do so, we would have to account for
    different sensivity cases within the same general case. For example in 
    large gutenberg, we had to account for "keeps" when "Keeps" and "keeps" 
    were on the same line. In order to do so, we implemented a vector of sets 
    to track if a line had been printed out yet during the query. We would 
    insert the line location to show that it had been inserted. This would 
    ensure that even when we are iterating through seperate buckets, there 
    wouldn't be repeated lines. 


    ContainsS():
    
    This function tests if a bucket is contained in our hashmap. For a 
    sensitive case, this would require the program to check the insensitive 
    larger bucket and the sensitive hash buckets as well. The complexity here
    is interesting, since there are two "contains" passes that must run.
    First the program checks if a bucket exists for the lowercase queried word
    in the general hash map. If it does, then the program must then check
    if a bucket for the original case of the queried word exists in the
    sensitive hash map. This took some time to get right, and certainly is
    not the most time efficient, but it was necessary for our design.

    Pros and Cons:

    Our implementation and use of imbedded Hash Maps comes with a variety of
    pros and cons. Our design is generally memory efficient because we only
    store each line occurence one time. We also use one consistent hash map,
    so there is no problem of repeatedly storing multiple instances of the same
    element. By design, our querying is extremely fast because the program
    is always a few constant time operations away from directly accessing
    a key from a bucket and then printing out all of the lines associated with
    that key. Our design does come with some redundencies, however, such as
    how our "contains" function essentially performs the same operations that
    our search functions perform, only it returns a different value. We do
    believe there is room for further optimization with this design, but it is
    currently very functional and quite fast (especially for querying).



H. Testing:

     1. unit_test
     
     We used the unit testing framework to test the following:

     a. Directory Traversal
          Tested with directories of varying depth and structure, including:
          Empty directories.
          Directories with nested subdirectories.
          Mixed directories containing files and subdirectories.
          Verified that the directory paths and file names were correctly 
          extracted using the direct_traverse function.

     b. Hash Map Initialization
          Checked:
          Words were correctly hashed and inserted into the primary hash map.
          The sensitive hash map correctly stored multiple cases of the same 
          word.
          Collisions in hash map buckets were handled without overwriting 
          existing data.

     c. Struct Data Integrity
          directory struct: Ensured accurate storage of file paths, file 
          indices, and line data.
          line_loc struct: Checked proper linking of line numbers, file 
          indices, and word occurrences.

     d. Edge Cases
          Tested input strings with:
          Non-alphanumeric characters at the edges.
          Case variations (e.g., Word, WORD, word).
          Words appearing on the same line in different cases.
          Ensured proper functioning of stripNonAlphaNum and lowerWord 
          functions.

    2. diff output testing

     To confirm the overall functionality of our gerp implementation, we used
     a variety of testing methods that mainly compared our program's outputs
     against the reference. 

     a. tinyData Input
     Initially used tinyData directory to query both case-sensitive and 
     case-insensitive words to ensure functionality on a small sample size.
     also tested words: not present in the files, present in multiple files and
     lines, and repeated multiple times on the same line for both case
     sensitive and insensitive.
     
     b. largeGutenberg Input
     After confirming functionality on tinyData, we ran gerp on largeGutenberg
     to test our program's handling of hundreds of thousands of lines and
     Input files with repetitive content to test hash map efficiency.
     We also used gerp_perf to measure runtime and RAM usage.

     c. Collision and Linear Probing
     Because we used a linear probing model for our hashmap, we used cout
     statements to track the behavior of insertion and retreival when a key
     would hash to index that was filled with a different key. 

     d. Input files
     Finally, we constructed a few input files to test how our program handled
     file input for different queries. The specfic content and nature of these
     testing files is described further above.


H. Time Spent: 

     22 hours
