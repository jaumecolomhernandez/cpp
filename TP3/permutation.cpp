#include "permutation.hpp"
#include "arithm.hpp"

#include <numeric>
#include <algorithm>
#include <iterator>

// -------------------- Class functions -------------------------
Permutation::Permutation(std::istream &f) {
    f >> n;
    images.resize(n);

    std::istream_iterator<unsigned> flux(f), eof;
    std::copy(flux, eof, images.begin());

    /* non STL
    for(unsigned i=0; i<n; ++i) {
        f >> images[i];
    }
    */
}

Permutation::Permutation(unsigned _n, std::mt19937 &g): n(_n), images(_n) {
    // Knuth shuffle algorithm
    std::iota(images.begin(), images.end(),0);

    for(unsigned i=0; i<n-1; i++){
        std::uniform_int_distribution<int> distribution(i,n-1);
        std::swap(images[i],images[distribution(g)]);
    }
}

Permutation Permutation::extend(int m) const {
    if (m<size()){
        std::cout << "The size is already bigger, no effect!";
        return *this;
    } else {
        Permutation t(m); // New permutation (bigger than original)
        for (int i=0; i<size(); i++){
            t[i]=images[i];
        }
        return t;
    }
}

std::vector<int> Permutation::fixedPoints() const {
    std::vector<int> fixed;
    for (int i=0; i<n;i++){
        if (i==images[i]) fixed.push_back(i);
    }

    /* Alternative with STL functions
    int index=0;
    copy_if(images.begin(), images.end(), back_inserter(fixed),
        [&index](int im) {return im==index++; } ); // Here i++ bc we first compare actual value and then add one to the result
    */

    return fixed;
}

bool Permutation::is_derangement() const {
    return fixedPoints().empty();
}

Permutation Permutation::inverse() const {
    // Returns a permutation with the indices of the og position
    Permutation t(size());
    for (int i=0; i<n; i++){
        t[images[i]] = i;
    }
    return t;
}

std::list<Cycle> Permutation::cycles() const {
    // Detects the cycles in a specific permutation
    std::list<Cycle> cycles;
    std::set<unsigned> s(images.begin(),images.end()); // This fills the set
    // Rotate each position of permutation until it comes back to og place
    while(!s.empty()){
        int depart = *(s.begin()); // The * is to get the value (if not it is the adress)
        std::list<int> c;
        int k=depart;
        do {
            s.erase(k);     
            c.push_back(k);
            k=images[k];
        } while (k != depart);
        if (c.size() > 1){  // we do not want the fixed points
            cycles.emplace_back(c);
        }
    }
    return cycles;
}

unsigned Permutation::order() const {
    // returns the mcm of the orders (mcm of all the orders in specific permutation)
    std::list<Cycle> l = cycles();
    std::list<unsigned>orders(l.size());
    std::transform(l.begin(), l.end(), orders.begin(),
        [](Cycle c) {return c.order();});
    return lcm_list(orders);
}

// -------------------- global functions ------------------------
Permutation operator*(const Permutation &  s, const Permutation & t) {
    if (s.size()!=t.size()) {
        unsigned m=std::max(s.size(), t.size());
        return s.extend(m)*t.extend(m);
    } else { // They are not the same, right?
        Permutation p(s.size());
        for(unsigned i=0; i<s.size(); i++){
            p[i] = s[t[i]];
        }
        return p;
    }
}

std::ostream & operator<<(std::ostream &o, const Permutation &s){
    // Just print the length n and the values of the permutation
    o << s.n << std::endl;
    for(unsigned i=0;i<s.n-1;i++){
        o << s.images[i] << " ";
    }
    o << s.images[s.n-1] << std::endl;
    return o;
}

bool operator<(const Cycle &c1, const Cycle &c2) {
    if (c1.order() != c2.order()){
        return c1.order() < c2.order();
    } else {
        return std::lexicographical_compare(c1.elem.begin(), c1.elem.end(),
            c2.elem.begin(), c2.elem.end());
    }
}

std::ostream & operator<<(std::ostream & out, const Cycle & c){
    std::ostream_iterator<int> out_it(out, " ");
    std::copy(c.elem.begin(), c.elem.end(), out_it);
    return out;
}

// This one is not working
std::ostream & operator<<(std::ostream & out, std::list<Cycle> & l){
    std::ostream_iterator<Cycle> out_it(out, " ");
    std::copy(l.begin(), l.end(), out_it);
    return out;
}