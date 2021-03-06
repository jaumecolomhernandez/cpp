test_graph.exe: test_graph.o graph.o
	g++ graph.o test_graph.o -o test_graph.exe

graph.o: graph.cpp graph.hpp
	g++ -Wall -O2 -c graph.cpp -std=c++17
		
test_graph.o: test_graph.cpp graph.hpp graph2.hpp
	g++  -Wall -O2 -c test_graph.cpp -std=c++17
	
graph2.o: graph2.cpp graph2.hpp
	g++ -Wall -O2 -c graph2.cpp -std=c++17
	
	
test2.exe: test_graph.o graph2.o
	g++ graph2.o test_graph.o -o test2.exe
