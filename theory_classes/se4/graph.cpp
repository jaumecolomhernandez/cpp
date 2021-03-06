#include "graph.hpp"
#include <algorithm>
#include <iterator>
#include <fstream>


using namespace std;
// puisqu'ici ce morceau sera compilé indépendamment de tout autre.


//SURCHARGE DE l'opérateur <<
ostream & operator<<(ostream & output, const Graph & G) {
    // à utiliser sous la forme: output << G 
    output << G.nb_vertices << "\n";
    for( auto p : G.edges) {
        output << p.first << " " << p.second << "\n"; 
    }
    return output;
}
/* explication du type de retour:
 *         ((cout << a) << b) << c ;
 * une fois a affiché: cout << b << c;
 * une fois b affiché: cout << c
 * */


//CONSTRUCTEUR:
Graph::Graph(int n): nb_vertices(n),  edges() {
    for( int i=0 ; i <n ; i++) {
        for(int j=0; j <n; j++ ) {
            edges.push_back(make_pair(i,j));
        }
    }
}

Graph::Graph(): nb_vertices(0), edges() {}


// NE PAS LE METTRE DANS LE FICHIER .cpp:
//int Graph::nb_of_edges() const {
//    return edges.size();
//}

//FONCTIONS MEMBRES - METHODES
bool Graph::test_connect_from_to(int i,int j) const {
    return any_of(
            edges.begin(),edges.end(),
            [i,j](pair<int,int> p) {  
                return (p.first == i) && (p.second==j);
            });
}

int Graph::nb_of_neighbours(int i) const {
    return count_if(
        edges.begin(),edges.end(),
        [i](pair<int,int> p) {
            return (p.first == i) && (p.second != i);
        });
}

void Graph::add_edge(int i,int j) {
    if( ! test_connect_from_to(i,j) ) { // ! : négation
        edges.push_back( make_pair(i,j));
    }
}

//~ void Graph::reverse_all_edges();

//~ vector<int> Graph::edges_from(int i) const;
    
    
// LECTURE DANS UN FICHIER:
void Graph::read_from_file(const std::string &s) {
    // PURGE: pour enlever les anciennes informations;
    edges.clear();
    // ouverture et lecture du fichier
    ifstream inputfile(s);
    inputfile >> nb_vertices;
    int source, target;
    while( inputfile >> source >> target) {
        edges.push_back( make_pair(source,target));
    }
    // Vérifications éventuelles ???
}



