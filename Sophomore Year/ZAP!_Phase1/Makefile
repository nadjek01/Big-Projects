###
### Makefile for ZAP Project
### ZAP is a compressor and decompressor for a string
###
### Author:  Nana Adjekum

MAKEFLAGS += -L 
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 


#rule for building CalcYouLater
zap: main.o phaseOne.o HuffmanTreeNode.o
	$(CXX) $(LDFLAGS) -o zap main.o phaseOne.o HuffmanTreeNode.o

#rule for building unit_test
unit_test: unit_test_driver.o phaseOne.o
	$(CXX) $(CXXFLAGS) unit_test_driver.o phaseOne.o

# #rule for building phaseOne
phaseOne.o: phaseOne.cpp phaseOne.h HuffmanTreeNode.h
	$(CXX) $(CXXFLAGS) -c phaseOne.cpp


provide:
	provide comp15 proj3_zap_phase1 README \
	phaseOne.cpp phaseOne.h main.cpp \
	unit_tests.h main.cpp README Makefile \

#rule for clean
clean:
	rm CalcYouLater unit_test RPNCalc.o DatumStack.o


##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
