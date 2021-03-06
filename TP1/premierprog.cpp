#include <iostream>
#include <cmath>

double aire_du_cercle(double x) {return M_PI*x*x;}
double aire_du_carre(double x) {return x*x;}

int main () {
    double r;
    std::cout << "Entrez le cote du carre: " << std::endl;
    std::cin >> r;
    std::cout << "Son aire est " << aire_du_carre(r) << std::endl;
    return 0;
}
