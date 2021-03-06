#include "permutation.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <random>
#include <vector>

int main() {
    // première partie

    std::vector<unsigned> v {2,4,5,3,1,0};
    Permutation a(v);
    Permutation b(6); // identité

    for(unsigned i=0; i<= 6; ++i) {
        std::cout << "a^" << i<< std::endl << b << std::endl;
        b = b*a;
    }

    std::list<unsigned> fp = a.fixed_points();
    auto affiche =[](unsigned x) {std::cout << x;};
    std::for_each(fp.begin(), fp.end(), affiche);

    // deuxième partie

    std::ifstream fichier_s("./file_s.dat");
    std::ifstream fichier_t("./file_t.dat");
    Permutation s(fichier_s);
    Permutation t(fichier_t);
    fichier_s.close();
    fichier_t.close();

    Permutation u=s*t.inverse();
    std::cout << "L'ordre de la permutation s*t^-1 est égal à "
        << u.order() << std::endl;
    std::list<Cycle> l = u.cycles();
    std::cout << "Cette permutation a " << l.size() <<
        "cycles, dont le plus grand a pour longueur : " <<
        (*std::max_element(l.begin(), l.end())).order() << std::endl;

    // troisième partie

    std::mt19937 G;
    unsigned n=100;
    unsigned nb_echant = 10000;
    unsigned nb_derang = 0;
    for(unsigned i=0; i<nb_echant; ++i) {
        nb_derang += Permutation(n,G).is_derangement();
    }
    std::cout << "La proportion de dérangements est environ " <<
        nb_derang/double(nb_echant) << std::endl;

    // question 21;
    
    std::vector<char> ch0 {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
    a.permute(ch0);
    std::cout << "permutation d'un vecteur :"<< std::endl;
    for(unsigned i=0; i< ch0.size(); ++i) {
        std::cout << ch0[i];
    }
    std::cout << std::endl;


    return 0;
}
