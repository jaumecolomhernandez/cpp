#include "arithm.hpp"
#include <numeric>

unsigned gcd(unsigned a, unsigned b) {
	unsigned temp;
	while( b != 0) {
		temp = a;
		a=b;
		b=temp%b;
	}
	return a;
}
/* Présentée ainsi, cette fonction n'est pas récursive et toute la récurrence
 * mathématique de l'énoncé se réduit à la boucle while. Du moins de vue optimisation
 * numérique, le cas présent est beaucoup mieux: au lieu d'encombrer la mémoire avec des
 * copies d'arguments à chaque appel récursif et de prendre le temps de faire des appels de fonctions,
 * on se contente de seulement trois variables: les copies de a et b et temp !
 * 
 * */

unsigned lcm(unsigned a, unsigned b) {
    return (a*b)/gcd(a,b);
}

unsigned gcd_list(const std::list<unsigned> & l) {
    return std::accumulate(l.begin(), l.end(), 0, gcd);
}
unsigned lcm_list(const std::list<unsigned> & l) {
    return std::accumulate(l.begin(), l.end(), 1, lcm);
}
/* Idéalement, d'ici deux semaines, il vaudrait mieux écrire deux fonctions (attention: dans le .hpp !)

template<class Iterator>
unsigned gcd_template(const Iterator & first,const Iterator & last) {
    return std::accumulate(begin, last, 0, gcd);
}

afin de pouvoir calculer le PGCD de n'importe quelle partie de n'importe quel conteneur d'entiers
* */

