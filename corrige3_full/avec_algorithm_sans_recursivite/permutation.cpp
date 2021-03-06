#include "permutation.hpp"
#include "arithm.hpp"

#include <algorithm>
#include <set>
#include <numeric>
#include <iterator>

using namespace std;

Permutation::Permutation(unsigned _n, std::mt19937 & g): n(_n), images(_n) {
    // Knuth shuffle algorithm
    /*for(unsigned i=0; i<n; ++i) {
        images[i]=i;
    } remplacé par:*/
    iota(images.begin(),images.end(),0);
    
    for(unsigned i=0; i<n-1; ++i) {
        uniform_int_distribution<int> distribution(i,n-1);
        swap(images[i], images[distribution(g)]);
    }//inchangé car ce n'est pas une boucle sur un conteneur
}

Permutation::Permutation(std::istream & flux) {
    flux >> n;
    images.resize(n);
    
    istream_iterator<unsigned> fluxit(flux), eof;
    copy(fluxit,eof,images.begin());
    /* au lieu de:
    for(unsigned i=0; i<n; ++i) {
        flux >> images[i];
    }
    * */
}

list<unsigned> Permutation::fixed_points() const {
    list<unsigned> l;
    unsigned index=0;
    copy_if(images.begin(),images.end(),back_inserter(l),
		[&index](unsigned im) { return im==index++; } );
		/* pour les experts: on utilise ici la distinction subtile 
		 * entre ++index et index++ */
    return l;
}

vector<unsigned> Permutation::fixed_points_v() const {
	vector<unsigned> v;
    unsigned index=0;
    copy_if(images.begin(),images.end(),back_inserter(v),
		[&index](unsigned im) { return im==index++; } );
		/* pour les experts: on utilise ici la distinction subtile 
		 * entre ++index et index++ */
    return v;
}

bool Permutation::is_derangement() const {
    return fixed_points().empty();
}

Permutation Permutation::extend(unsigned m) const {
    if (m<size()) {
        cout << "W Permutation::extend: taille plus grande que le paramètre" << std::endl;
        return *this; 
    } else {
        Permutation t(m);
        copy(images.begin(),images.end(),t.images.begin());
        /* au lieu de 
        for(unsigned i=0; i<size(); ++i) {
            t[i]=images[i];
        } */
        return t;
    }
}


unsigned Permutation::order() const {
    list<Cycle> l = cycles();
    list<unsigned> orders(l.size());
    transform(l.begin(), l.end(), orders.begin(), [](Cycle c) {return c.order();});
    //on transforme une liste de cycles en liste d'entiers
    return lcm_list(orders);
}

Permutation operator*(const Permutation & s, const Permutation & t) {
    if (s.size() < t.size()) { 
        return s.extend(t.size())*t;
	} else if ( s.size() > t.size() ) {
		return s*t.extend(s.size());
    } else {
		Permutation p(s.size());
		transform(t.images.begin(),t.images.end(),p.images.begin(),
			[&s](unsigned k) { return s[k]; }
		);
		// La lambda-fonction avec s en capture correspond à prendre l'image par s
		return p;
	}
}

Permutation Permutation::inverse() const {
    Permutation t(size());
    for(unsigned i =0; i< n; ++i) {
        t[images[i]]=i;
    } /* je n'ai pas trouvé dans <algorithm> ! La composition de t et images
    * n'est pas naturelle du point de vue des itérateurs... */  
    return t;
}

bool operator==(const Permutation & s, const Permutation & t) {
    return s.images==t.images;
}

list<Cycle> Permutation::cycles() const {
    list<Cycle> cycles;
    set<unsigned> s(images.begin(),images.end());
    /* ce constructeur plus évolué présent dans set permet d'éliminer
     * la boucle:
    for(unsigned i=0; i<n; ++i) {
        remaining.insert(i);
    }
    * */
    while(!s.empty()) {
        unsigned depart = *(s.begin());//première valeur de l'ensemble 
        list<unsigned> c;
		unsigned k=depart;
        do {
			s.erase(k);
            c.push_back(k);
            k=images[k];
		} while (k != depart);
        if( c.size() > 1) {	//on enlève les points fixes, i.e. les cycles de longueurs 1
			cycles.emplace_back(c); // bonne alternative à cycles.push_back(Cycle(c)); pour concentrer "construction puis copie puis destruction"
		}
    }
    return cycles;
}

bool operator<(const Cycle & c1, const Cycle & c2) {
    if (c1.order() != c2.order()) {
        return c1.order() < c2.order();
    } else {
		auto p = mismatch(c1.elem.begin(),c1.elem.end(),c2.elem.begin());
		/* p est une paire d'itérateurs sur c1.elem et c2.elem vers la première
		 * case où c1.elem et c2.elem diffèrent
		 * */
		if( p.first == c1.elem.end() ){ // cas où les deux sont identiques
			return false;
		} else {
			return *p.first < *p.second; //on compare les contenus des deux cases
		}
    }
}

ostream & operator<<(ostream & out, const Permutation & s) {
    out << s.n << "\n";
    ostream_iterator<unsigned> out_it(out," ");
    copy(s.images.begin(),s.images.end()-1,out_it);
    out << s.images.back(); 
    /* on utilise le -1 dans le copy et on ajoute la ligne précédente
     * pour éliminer l'espace après le dernier élément;
     * */
    return out;
}

ostream & operator<<(ostream & out, const Cycle & c) {
	ostream_iterator<unsigned> out_it(out," ");
	copy(c.elem.begin(),c.elem.end(),out_it);
    return out;
}
