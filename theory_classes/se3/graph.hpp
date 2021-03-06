

#include <vector>
#include <utility>
#include <iostream>

class Graph;
std::ostream & operator<< (std::ostream &,const Graph &);



class Graph { // TABLEAUX DE VOISINS NON ORDONNES.
    public:
        Graph(int n); // ex ligne 12
        Graph();//ex ligne 15
        
        void read_from_file(const std::string &);//ligne 16
        int nb_of_neighbours(int) const;
        bool test_connect_from_to(int,int) const;
        
        
    private:
        int nb_vertices;
        std::vector< std::pair<int,int> > edges;
};



