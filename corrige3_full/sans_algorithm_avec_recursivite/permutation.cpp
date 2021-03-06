#include "permutation.hpp"
#include "arithm.hpp"

#include <algorithm>
#include <set>

Permutation::Permutation(unsigned _n, std::mt19937 & g): n(_n), images(_n) {
    // Knuth shuffle algorithm
    for(unsigned i=0; i<n; ++i) {
        images[i]=i;
    }
    for(unsigned i=0; i<n-1; ++i) {
        std::uniform_int_distribution<int> distribution(i,n-1);
        std::swap(images[i], images[distribution(g)]);
    }
}

Permutation::Permutation(std::istream & flux) {
    flux >> n;
    images.resize(n);
    for(unsigned i=0; i<n; ++i) {
        flux >> images[i];
    }
}

std::list<unsigned> Permutation::fixed_points() const {
    std::list<unsigned> l;
    for(unsigned i=0; i<n; ++i) {
        if(i==images[i]) {
            l.push_back(i);
        }
    }
    return l;
}

std::vector<unsigned> Permutation::fixed_points_v() const {
    std::vector<unsigned> v;
    for(unsigned i=0; i<n; ++i) {
        if(i==images[i]) {
            v.push_back(i);
        }
    }
    return v;
}

bool Permutation::is_derangement() const {
    return fixed_points().empty();
}

Permutation Permutation::extend(unsigned m) const {
    if (m<size()) {
        std::cout << "W Permutation::extend: taille plus grande que le paramètre" << std::endl;
        return *this; // ou bien: 	return Permutation(images);
    } else {
        Permutation t(m);
        for(unsigned i=0; i<size(); ++i) {
            t[i]=images[i];
        }
        return t;
    }
}


unsigned Permutation::order() const {
    std::list<Cycle> l = cycles();
    std::list<unsigned> orders(l.size());
    std::transform(l.begin(), l.end(), orders.begin(), [](Cycle c) {return c.order();});
    // ou :
    // std::list<unsigned> orders;
    // for_each(l.begin(), l.end(), [orders &](Cycle c) {orders.push_back(c.order());});
    return lcm(orders);
}

Permutation operator*(const Permutation & s, const Permutation & t) {
    if (s.size()!=t.size()) {
        unsigned m=std::max(s.size(), t.size());
        return s.extend(m)*t.extend(m);
		/* cela n'est pas le plus efficace car cela crée beaucoup d'objets intermédiaires par copie
		 * mais le code est court.
		 * Exercice: optimiser !!!!
		 * */
    }
    Permutation p(s.size());
    for(unsigned i=0; i<s.size(); ++i) {
        p[i] = s[t[i]];
        //on note ici l'utilisation du mutateur privé pour p: on y a droit grâce à l'usage de friend pour operator*
    }
    return p;
}

Permutation Permutation::inverse() const {
    Permutation t(size());
    for(unsigned i =0; i< n; ++i) {
        t[images[i]]=i;
    }
    return t;
}

bool operator==(const Permutation & s, const Permutation & t) {
    return s.images==t.images;
}

std::list<Cycle> Permutation::cycles() const {
    std::list<Cycle> cycles;
    std::set<unsigned> remaining;
    for(unsigned i=0; i<n; ++i) {
        remaining.insert(i);
    }
    while(!remaining.empty()) {
        auto x = remaining.begin();
        unsigned depart = *x;
        remaining.erase(depart);
        std::list<unsigned> c = {depart};
        unsigned k=images[depart];
        while(k!=depart) {
            remaining.erase(k);
            c.push_back(k);
            k=images[k];
        }
        cycles.push_back(Cycle(c));
    }
    return cycles;
}

bool operator<(const Cycle & c1, const Cycle & c2) {
    if (c1.order() != c2.order()) {
        return c1.order() < c2.order();
    } else {
        return c1.elem.front() < c2.elem.front();
    }
}

std::ostream & operator<<(std::ostream & o, const Permutation & s) {
    o << s.n << std::endl;
    for(unsigned i=0;i<s.n -1 ;++i) {
        o << s.images[i] << " ";
    }
    o << s.images[s.n-1];
    return o;
}


std::ostream & operator<<(std::ostream & o, const Cycle & c) {
    for(auto x : c.elem) {
        o << x << " ";
    }
    o << std::endl;
    return o;
}
