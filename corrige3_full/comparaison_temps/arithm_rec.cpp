#include "arithm.hpp"
//#include <numeric> // nécessaire pour accumulate

unsigned gcd(unsigned a, unsigned b) {
    if(b==0) {
        return a;
    } else {
        return gcd(b,a%b);
    }
}

unsigned lcm(unsigned a, unsigned b) {
    return (a*b)/gcd(a,b);
}


unsigned arithm_rec(std::list<unsigned> & l,unsigned (* f)(unsigned,unsigned)) {
    if (l.size()==0) {
        return 0;
    }
    if (l.size()==1) {
        return l.front();
    }
    unsigned a=l.front();
    l.pop_front();
    unsigned b=l.front();
    l.pop_front();
    l.push_front(f(a,b));
    return arithm_rec(l,f);
}

unsigned gcd_list(std::list<unsigned> & l) {
    return arithm_rec(l,gcd);
    // ou 
    //return std::accumulate(l.begin(), l.end(), 0, gcd);
}
unsigned lcm_list(std::list<unsigned> & l) {
    return arithm_rec(l,lcm);
    // ou
    // return std::accumulate(l.begin(), l.end(), 1, lcm);
}
