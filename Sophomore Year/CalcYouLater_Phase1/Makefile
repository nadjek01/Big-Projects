###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Nana Adjekum

MAKEFLAGS += -L 
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 
##
##  --- Delete these comments and put appropriate comments in ---
##
DatumStack.o: DatumStack.cpp DatumStack.h Datum.o
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp

# main.o: main.cpp DatumStack.h Datum.o
# 	$(CXX) $(CXXFLAGS) -c main.cpp

CalcYouLater: main.o DatumStack.o Datum.o
	$(CXX) $(CXXFLAGS) -o CalcYouLater main.o DatumStack.o Datum.o

unit_test: unit_test_driver.o DatumStack.o Datum.o
	$(CXX) $(CXXFLAGS) unit_test_driver.o DatumStack.o Datum.o


provide:
	provide comp15 proj2_calcyoulater_phase1 DatumStack.h \
	DatumStack.cpp parser.cpp \
	unit_tests.h main.cpp README Makefile
##
## CAUTION:  DO NOT JUST USE THE OLD RULES FOR 'clean'!!!
##           You do NOT want to remove Datum.o!!
##
##  --- Delete these comments and put appropriate comments in ---


##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
