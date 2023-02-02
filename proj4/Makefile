###
### Makefile for gerp Project
### gerp is a compressor and decompressor for a string
###
### Author:  Max Samuels and Nana Adjekum

MAKEFLAGS += -L 
CXX = clang++
CXXFLAGS = -O2 -g -Wall -Wextra -Wpedantic -Wshadow

gerp: main.o HashTable.o stringProcessing.o DirNode.o FSTree.o
	$(CXX) $(LDFLAGS) -o gerp main.o HashTable.o stringProcessing.o DirNode.o FSTree.o

main.o: main.cpp HashTable.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

treeTraversal: FSTreeTraversal.o DirNode.o FSTree.o
	$(CXX) $(LDFLAGS) -o treeTraversal FSTreeTraversal.o DirNode.o FSTree.o

HashTable.o: HashTable.cpp HashTable.h FSTree.h
	$(CXX) $(CXXFLAGS) -c HashTable.cpp

FSTreeTraversal.o: FSTreeTraversal.cpp FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp

stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp

unit_test: unit_test_driver.o stringProcessing.o HashTable.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) $^

make: stringProcessing.o
	$(CXX) $(CXXFLAGS) $^

provide:
	provide comp15 proj4_gerp_leaderboard Makefile HashTable.cpp \
			main.cpp README HashTable.h stringProcessing.h \
			stringProcessing.cpp FSTreeTraversal.cpp \
			FSTree.h DirNode.h unit_tests.h mout.txt tout.txt \
			xout.txt

##