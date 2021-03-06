#! /usr/bin/make

CXX=g++
CXXFLAGS=-Wall -pedantic --std=c++11 -O2

all: test_permutation chrono_fixed_points

test_permutation: permutation.o test_permutation.o arithm.o
	$(CXX) -o $@ $^

chrono_fixed_points: chrono_fixed_points.o permutation.o arithm.o
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: all clean distclean

clean:
	$(RM) *.o

distclean: clean
	$(RM) test_permutation
