#ifndef ARITHMETIQUE
#define ARITHMETIQUE

#include <list>
unsigned gcd(unsigned a, unsigned b);
unsigned gcd(std::list<unsigned> l);
unsigned lcm(unsigned a, unsigned b);
unsigned lcm(std::list<unsigned> l);

unsigned arithm_rec(std::list<unsigned> l,unsigned (* f)(unsigned,unsigned));

#endif
