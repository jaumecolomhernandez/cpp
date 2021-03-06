
#ifndef CLASS_GRAPH
#define CLASS_GRAPH

#include <vector>
#include <utility>
#include <iostream>

class Graph;

std::ostream & operator<< (std::ostream &,const Graph &);



class Graph { // TABLEAUX DE VOISINS NON ORDONNES.
    public:
        // CONSTRUCTEURS
        Graph(int n); // ex ligne 12 //FAIT
        Graph();//ex ligne 15 //FAIT
        
        //Graph(const Graph &);//constructeur par copie
        // ici on n'en a pas besoin !
        
        // fonctions membres  // méthodes
        
        
        // ------- ACCESSEURS ------------
        int nb_of_edges() const { return edges.size();};// inline
        int size() const { return nb_vertices; };
        
        
        void read_from_file(const std::string &);//ligne 16 //FAIT
        
        
        
        int nb_of_neighbours(int) const; // FAIT
        bool test_connect_from_to(int,int) const; //FAIT
        
        void add_edge(int,int) ;// pas de const !!! 
        
        friend std::ostream & operator<<(std::ostream &, const Graph &);
        // friend donne accès aux champs privés à cette fonction.
    private:
        // champs  // attributs
        int nb_vertices;
        std::vector< std::pair<int,int> > edges;
        /* INVARIANT DE CLASSES:
         * chaque arete (i,j) doit satisfait 0<= i,j < nb_vertices
         * chaque arete apparaisse au plus une fois !
         * */
};

#endif


