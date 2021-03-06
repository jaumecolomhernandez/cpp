#include <iostream>
#include <cmath>


double circle_area(double r) {
   return M_PI*r*r;
}

int main(void) {
   std::cout << "Entrez le rayon du cercle:\n";
   double x;
   std::cin  >> x;
   std::cout    << "L'aire du cercle est " 
                << circle_area(x) 
                << "\n";
	return 0; 
}
    
/*
un autre commentaire sur plusieurs lignes
et hop
et hop
bon on va s'arreter la... 
*/
