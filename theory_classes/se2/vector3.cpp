#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

int main()
{
    using namespace std;// tout se fait ici dans la bibliothèque standard
    
	auto vec = std::vector<double>{1., -2.5, 4. };
    // la taille n'apparaît plus et on lit tout le contenu immédiatement.
    
    cout << "vec: ";
    copy(
        begin(vec), 
        end(vec),
        ostream_iterator<double>(cout," | ")
    );// plus de taille, on voit que c'est de l'affichage, séparateur OK.
    cout << "\n";
    
    
    auto b=-4.3;
    vec.push_back(b);
    vec.push_back(b);
 
 
    cout << "vec: ";
    for(auto x: vec) 
    {
        cout << x << " | "; 
    }// autre possibilité sans écrire la taille
    cout << "\n";
    
    
    cout << "Le dernier est: " << vec.back()  << "\n";
        // on écrit vraiment qu'on peut le dernier !
    
    vec.push_back(b+3.);
    
    auto w = vector<double>(vec.size());
    //pas de taille à retrouver !
    // parenthèses nécessaires pour distinguer du contenu.
    
    transform(
        begin(vec),end(vec),
        begin(w),
        [](double x){ return x*x+1.;}
    ); //pas de taille, on voit la fonction mathématique et la transformation !
    
    
    auto somme_w = accumulate( begin(w), end(w), 0.);
    cout << "Valeur de la somme: " << somme_w  << "\n"; 
    
    
	return 0;
}

