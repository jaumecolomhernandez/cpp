#! /usr/bin/make

CXX=g++
CXXFLAGS=-Wall -pedantic --std=c++11 -O2

all: test_permutation.exe chrono_fixed_points.exe

test_permutation.exe: permutation.o test_permutation.o arithm.o
	$(CXX) -o $@ $^

gen_rnd_perm.exe: gen_rnd_perm.o permutation.o arithm.o
	$(CXX) -o $@ $^

chrono_fixed_points.exe: chrono_fixed_points.o permutation.o arithm.o
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: all clean distclean

clean:
	$(RM) *.o *.exe

