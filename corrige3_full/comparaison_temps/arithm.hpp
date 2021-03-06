#ifndef ARITHMETIQUE
#define ARITHMETIQUE

#include <list>
unsigned gcd(unsigned a, unsigned b);
unsigned gcd_list(std::list<unsigned> & l);
unsigned lcm(unsigned a, unsigned b);
unsigned lcm_list(std::list<unsigned> & l);

/* Nous avons enlevé les const pour assurer la compatibilité
 * avec les codes récursifs et non-récursifs, tout en minimisant les copies
 * mais c'est une mauvaise idée en fait...
 * */
#endif
