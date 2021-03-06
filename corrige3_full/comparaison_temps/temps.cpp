#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <list>
#include <algorithm>
#include "arithm.hpp"

using namespace std;

int main() {
	const uint NMIN=1000;
	const uint NMAX=1000000;

	mt19937 G(666);
	uniform_int_distribution<uint> U(NMIN,NMAX);
	
// Préparation des vecteurs de test
{
	const uint V_size=1000000;
	const uint Nb_repeat=10;
	vector< pair<uint,uint> > Input(V_size);
	vector< uint > Result(V_size);	
	generate(Input.begin(),Input.end(),[&](){ return make_pair(U(G),U(G)); });
// Calcul des pgcd:
	auto t1 = std::chrono::system_clock::now();
	for (uint i = 0; i < Nb_repeat; i++)
	{
		transform(
			Input.begin(),Input.end(),
			Result.begin(),
			[](pair<uint,uint> p) { return gcd(p.first,p.second);}
		);
	}
	auto t2 = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = t2-t1;
	std::cout << "Temps mis: " << diff.count() << "s." << std::endl;
}

// PGCD de listes
{
	const uint V_size=2000;
	const uint L_size = 100000;
	vector< list<uint> > Input(V_size);
	vector< uint > Result(V_size);	
	generate(
		Input.begin(),Input.end(),
		[&](){ 
			list<uint> L(L_size);
			generate(L.begin(),L.end(),[&](){ return U(G); });
			return L;
		}
	);
	// Calcul des pgcd:
	auto t1 = std::chrono::system_clock::now();
	transform(
			Input.begin(),Input.end(),
			Result.begin(),
			[](list <uint> & L) { return gcd_list(L);}
			);
	auto t2 = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = t2-t1;
	std::cout << "Temps mis: " << diff.count() << "s." << std::endl;
}

/* CONCLUSION:
 * sur un code aussi court que gcd, cela ne fait pas grande différence car le compilateur
 * est capable d'analyser le code en profondeur et de faire les simplifications nécessaires.
 * 
 * En revanche, ce n'est plus le cas pour les listes pour lesquelles le code est plus évolué.
 * 
 *
 * */
}
