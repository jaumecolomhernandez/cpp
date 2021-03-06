#include <iostream>
#include <fstream>
#include <vector>

#include "graph.hpp"

using namespace std;

int main()
{
	const unsigned int N=4;
    Graph Full(N); // auto Full = Graph(N);
    cout << "Graphe complet: " << Full << "\n\n";
        
    Graph G; // auto G= Graph();
    G.read_from_file("example.dat");
    cout << "Graphe lu:\n" << G << "\n";
        //lecture à partir d'un fichier
        /* on pourrait préférer: 
         *  input >> G;
         * voir plus tard */

    int k2= G.nb_of_neighbours(2);// nombre de voisins du sommet 2
    cout << "Voisins du vertex 2: " << k2 << "\n";
    
    bool b = G.test_connect_from_to(4,5);// regarde si une arête connecte 4 vers 5
    cout << "4 est-il connecté à 5 ? ";
        if(b) cout << "Oui";
        else cout << "Non";
    cout << "\n";
    
    std::cout<<"Nb of edges: "<< G.nb_of_edges()<<"\n";//nombre d'arêtes
    
    {
        Graph H(G);//nouveau H copié à partir de G // auto H = Graph(G);
        //constructeur par copie
        
        for (int i=1; i<G.size() ; i++) { //ajoute tous les liens de 2 vers i.
            H.add_edge(2,i);
        }
        std::ofstream output("graph_modified.dat");
        output << H; //écriture de H dans le fichier
        output.close();
    }//effacement de H.
    
    //~ G.reverse_all_edges(); // renversement des direction de toutes les arêtes.

    //~ cout << "Contenu du graphe renversé:\n" << G << "\n";
    
    //~ std::vector<int> vec = G.edges_from(4);//tableau des arêtes qui partent de 4.
    //~ cout << "Vertex accessibles à partir de 4: " ;
    //~ for (auto v: vec)
    //~ {
        //~ cout << v << " ";
    //~ }
    //~ cout << "\n";
    


//~ // SECONDE PARTIE:

    //~ const int M=3;
    //~ double proba=0.4;
    //~ Graph G1(M); 
    //~ Graph G2(M);
    //~ cout << G1;
    //~ std::mt19937_64 random_generator(time(nullptr));
    //~ G1.random_edges(random_generator,proba);
    //~ G2.random_edges(random_generator,proba);
    //~ cout << "-----------\nGraphe aléatoire 1:\n" << G1 << "------------\n";
    //~ cout << "-----------\nGraphe aléatoire 2:\n" << G2 << "------------\n";
    //~ Graph Gtot;
    //~ Gtot = G1+ G2; //fusion des graphes.
    //~ cout << "-----------\nUnion des Graphes aléatoires :\n" << Gtot << "------------\n";
    
    
    
    
    
    return 0;
}
    
