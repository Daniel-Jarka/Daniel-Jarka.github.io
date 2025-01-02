###
### Makefile for Gerp Project
###
### Author:  Daniel Jarka & Paul Wang

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -O2
LDFLAGS  = -g3 

## This rule lets the program execute with ./gerp
gerp: main.o gerp.o SensitiveHash.o HashMap.o DirNode.o FSTree.o 
	$(CXX) $(LDFLAGS) -o $@ $^

# This rule builds processing.o
processing.o: processing.cpp processing.h DirNode.h FSTree.h
	$(CXX) $(CXXFLAGS) -c processing.cpp

# This rule builds HashMap.o
HashMap.o: HashMap.cpp HashMap.h SensitiveHash.h
	$(CXX) $(CXXFLAGS) -c HashMap.cpp

# This rule builds sensitiveHash.o
SensitiveHash.o: SensitiveHash.cpp SensitiveHash.h
	$(CXX) $(CXXFLAGS) -c SensitiveHash.cpp

# This rule builds gerp.o
gerp.o: gerp.cpp gerp.h SensitiveHash.h HashMap.h DirNode.h FSTree.h
	$(CXX) $(CXXFLAGS) -c gerp.cpp

# This rule builds main.o
main.o: main.cpp gerp.h SensitiveHash.h HashMap.h DirNode.h FSTree.h
	$(CXX) $(CXXFLAGS) -c main.cpp


# The below rule will be used by unit_test.
unit_test: unit_test_driver.o gerp.o SensitiveHash.o HashMap.o DirNode.o FSTree.o 
	$(CXX) $(CXXFLAGS) $^
##
## Here is a special rule that removes all .o files besides the provided ones 
## (DirNode.o and FSTree.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ a.out

