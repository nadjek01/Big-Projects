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
zap: main.o HuffmanTreeNode.o BinaryIO.o HuffmanCoder.o
	$(CXX) $(LDFLAGS) -o zap main.o HuffmanTreeNode.o HuffmanCoder.o BinaryIO.o

#rule for building unit_test
unit_test: unit_test_driver.o HuffmanTreeNode.o HuffmanCoder.o BinaryIO.o
	$(CXX) $(CXXFLAGS) unit_test_driver.o HuffmanTreeNode.o HuffmanCoder.o BinaryIO.o

#rule for building phaseOne
phaseOne.o: phaseOne.cpp phaseOne.h HuffmanTreeNode.h
	$(CXX) $(CXXFLAGS) -c phaseOne.cpp

#rule for building HuffmanCoder
HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h BinaryIO.h HuffmanTreeNode.h
	$(CXX) $(CXXFLAGS) -c HuffmanCoder.cpp
provide:
	provide comp15 proj3_zap README \
	phaseOne.cpp phaseOne.h main.cpp \
	unit_tests.h main.cpp README Makefile \
	B.zap C.txt moutput.txt output.txt \
	testmain.cpp toutput.txt tzoutput.txt \
	zap zoutput.txt HuffmanCoder.h \
	HuffmanCoder.cpp HuffmanTreeNode.h \
	



#rule for clean
clean:
	rm zap unit_test phaseOne.o HuffmanCoder.o
