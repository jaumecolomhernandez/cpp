
all: temps_rec.exe temps_norec.exe


comparaison: all
	./temps_norec.exe  && ./temps_rec.exe


temps_rec.exe: temps.o arithm_rec.o
	g++ temps.o arithm_rec.o -o temps_rec.exe

temps_norec.exe: temps.o arithm_norec.o
	g++ temps.o arithm_norec.o -o temps_norec.exe

temps.o: arithm.hpp temps.cpp
	g++  -c temps.cpp -std=c++11 -O2

arithm_rec.o: arithm_rec.cpp arithm.hpp
	g++  -c arithm_rec.cpp -std=c++11 -O2

arithm_norec.o: arithm_norec.cpp arithm.hpp
	g++  -c arithm_norec.cpp -std=c++11 -O2
