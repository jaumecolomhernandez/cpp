#ifndef PERMUTATIONS_AND_CYCLES
#define PERMUTATIONS_AND_CYCLES

#include <vector>
#include <list>
#include <random>
#include <iostream>
#include <algorithm>

// CONTENU:
class Permutation;
class Cycle;

/*
 * Permutations comme vecteur des images
 */
class Permutation {
    private:
		// Champs privés:
        unsigned n;
        std::vector<unsigned> images;
        // Méthodes privées:
        Permutation extend(unsigned m) const;
        unsigned & operator[](unsigned i) {return images[i];} 
			/* privé car cela n'a pas de sens de changer la valeur d'un élément unique
			 * cela risquerait de briser le fait qu'une permutation est une bijection:
			 * on préfère mettre en public seulement des méthodes qui ne sont pas dangereuses.
			 * */

    public:
    // construction de l'identité (code court donc dans la classe)
        Permutation(unsigned _n=0): n(_n), images(_n) {
            for(unsigned i=0; i<_n; ++i) {
                images[i] = i;
            }
        }	
        /* la construction des champs privées est faite par copie pour n et par le constructeur
         * std::vector<T>(unsigned) de std::vector qui crée un vecteur de taille fixée avec 
         * des valeurs par défaut. */
        
        
    // construction à partir d'un vecteur:
		Permutation(const std::vector<unsigned> & v): n(v.size()), images(v) {}
		/* La construction des champs privées est faite ici par le constructeur par copie des entiers
		 * pour n et celui par copie des std::vector pour v. */
        
	// construction d'une permutation aléatoire.
        Permutation(unsigned _n, std::mt19937 & g);
        
    // construction par lecture dans un fichier.
        Permutation(std::istream & flux);

	// Accesseur à n:
        unsigned size() const {return n;}
    // Accesseur à la case i de images:
        unsigned operator[](unsigned i) const {return images[i];}
       
        std::list<unsigned> fixed_points() const;
        std::vector<unsigned> fixed_points_v() const;
        bool is_derangement() const;
        unsigned order() const;

        friend bool operator==(const Permutation &, const Permutation &);

        friend Permutation operator*(const Permutation &, const Permutation & s);
        Permutation inverse() const;
        std::list<Cycle> cycles() const;

        friend std::ostream & operator<<(std::ostream &, const Permutation &);

        template <typename T>
        void permute(std::vector<T> &) const;
};

class Cycle {
    private:
        std::list<unsigned> elem;

    public:
        Cycle(std::list<unsigned> l): elem(l) {}
        unsigned order() const {return elem.size();}

        friend bool operator<(const Cycle &, const Cycle &);
        friend std::ostream & operator<<(std::ostream &, const Cycle &);

        template <typename T>
        void permute(std::vector<T> &v) const;
};


template <typename T>
void Permutation::permute(std::vector<T> & v) const {
    if (size() <= v.size()) {
        std::list<Cycle> list_cycles=cycles();
        std::for_each(list_cycles.begin(), list_cycles.end(), [&](Cycle c) {c.permute(v);});
    }
    return;
}

template <typename T>
void Cycle::permute(std::vector<T> & v) const {
    T tampon=v[elem.front()];
    std::list<unsigned>::const_iterator next;
    for(std::list<unsigned>::const_iterator it=elem.begin(); it != std::prev(elem.end()); ++it) {
        next=std::next(it);
        v[*it]=v[*next];
    }
    v[elem.back()]=tampon;
}
#endif
