#include "permutation.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

int main(){
    // First part
    std::cout << "1ST PART - Create Permutation and get iterations" << std::endl;
    std::vector<int> v {2,4,5,3,1,0};
    Permutation a(v);
    Permutation b(6);

    for(unsigned i=0; i<=6; i++){
        std::cout << "a^" << i << std::endl << b << std::endl;
        b = b*a;
    }

    std::vector<int> fp = a.fixedPoints();
    std::cout << "Fixed points = ";
    for (int x : fp){
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Second part
    std::cout << "\n2ND PART - Test the cycles() function" << std::endl;
    std::list<Cycle> cycles_a = a.cycles();
    std::cout << "Cycles = " << std::endl;
    for (const Cycle &c : cycles_a){
        std::cout << c << std::endl;
    }
    
    std::cout << "\n2ND PART - Read and compute inverse, cycles and mcm" << std::endl;
    std::ifstream fichier_s("./file_s.dat");
    std::ifstream fichier_t("./file_t.dat");
    Permutation s(fichier_s);
    Permutation t(fichier_t);
    fichier_s.close();
    fichier_t.close();

    Permutation u=s*t.inverse();
    std::cout << "The order of permutation s*t^-1 is " << u.order() << std::endl;
    std::list<Cycle> l = u.cycles();
    std::cout << "There are " << l.size() << " cycles! The longest is " <<
        (*std::max_element(l.begin(), l.end())).order() << " cycles long\n" << std::endl;
    
    // Third part
    std::mt19937 g;
    unsigned n=100;
    unsigned nb_echant = 10000;
    unsigned nb_derang = 0;
    for (unsigned i=0; i<nb_echant; i++){
        nb_derang += Permutation(n,g).is_derangement();
    }
    std::cout << "La proportion de derangements est environ "
        << nb_derang/double(nb_echant) << std::endl;
}