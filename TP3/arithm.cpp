#include "arithm.hpp"
#include <numeric>

unsigned gcd(unsigned a, unsigned b) {
    unsigned temp;
    while ( b != 0) {
        temp = a;
        a = b;
        b = temp%b;
    }
    return a;
}

unsigned lcm(unsigned a, unsigned b) {
    return (a*b)/gcd(a,b);
}

unsigned gcd_list(const std::list<unsigned> &l) {
    return std::accumulate(l.begin(), l.end(), 0, gcd);
}

unsigned lcm_list(const std::list<unsigned> &l) {
    return std::accumulate(l.begin(), l.end(), 1, lcm);
}