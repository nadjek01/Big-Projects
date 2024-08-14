###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Nana Adjekum

MAKEFLAGS += -L 
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 


#rule for building CalcYouLater
CalcYouLater: main.o DatumStack.o Datum.o RPNCalc.o
	$(CXX) $(LDFLAGS) -o CalcYouLater main.o DatumStack.o Datum.o RPNCalc.o

#rule for building unit_test
unit_test: unit_test_driver.o DatumStack.o Datum.o RPNCalc.o
	$(CXX) $(CXXFLAGS) unit_test_driver.o DatumStack.o Datum.o RPNCalc.o

#rule for building RPNCalc
RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.cpp DatumStack.h Datum.h
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

#rule for buildind DatumStack
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp


provide:
	provide comp15 proj2_calcyoulater DatumStack.h \
	DatumStack.cpp parser.cpp \
	unit_tests.h main.cpp README Makefile \
	RPNCalc.h RPNCalc.cpp

#rule for clean
clean:
	rm CalcYouLater unit_test RPNCalc.o DatumStack.o


##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
