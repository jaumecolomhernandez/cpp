#include <iostream>
#include <cmath>

#include <string>

// commentaire

// TYPES ELEMENTAIRES (pas besoin de std::)
// int et ses variantes
// double
// char pour les caractères
// bool pour les booléens


// TYPES DE LA BIBLIOTHEQUE STANDARD:
// std::vector<T>
// std::string
// std::ifstream // lecture de fichier
// std::ofstream // ecriture de fichier


// NOUVEAUX TYPES PERSONNALISES

struct Enseignant {
    std::string firstname;
    std::string name;
    int office;
};



int main()
{
	// les entiers
    int n1 = 29; 
    int n2 = 13;
    
    n1++; //augmente de 1; identique à   n1= n1+1;
    n1 += 4; // identique à n1= n1+4;
    
    //unsigned int p= 0; //entiers positifs
    //long int r = 454454234542323;// grands entiers
    //unsigned long int s= 4554435353435;//grands entiers positifs
    
    int somme = n1 + n2 ;
    int difference = n1 - n2 ;
    int produit = n1 * n2 ;
    
    int quotient = n1/n2; // division euclidienne
    int reste = n1 % n2; // reste euclidienne
    
    std::cout << somme << " " 
            << difference << " " 
            << produit << "\n" 
            << quotient << " " 
            << reste << "\n";
            
    double division = double(n1) / double(n2);//division réel
    std::cout << division << "\n";
    
    // PUISSANCES:
    //  ce n'est pas ** 
    int carre = n1*n1;
    int puissance4 = carre*carre;
    
    int puissance_grande = std::pow(n1, 11);
        // JAMAIS: std::pow(n1,p) avec p qui vaut 2,3,4,5,6 .
    std::cout << puissance_grande << "\n";


    // les réels
    
    //float x= 4.5; // faible precision -> ne pas utiliser
    double x=3.1; //double precision -> precision classique aujourd'hui
    double y=6.2;
    double z= y - (2.*x);
    
    //addition: +
    //soustraction: -
    //produit *
    //division /
    //conversion entier -> réels
    int n_entier= 4;
    double n_reel = n_entier;
    
    double grand_nombre = 3.4e-3;
    std::cout << grand_nombre << "\n";
    

    // les chaînes de caractères
    // en langage C : char * : NE PAS UTILISER EN C++.
    
    std::string S1 = "Coucou"; //valeur entre " "
    std::string espace = "  ";
    std::string S2 = "vous !";
    
    std::string S = S1 + espace + S2;
    
    char c = S[4];//5ème caractère: numérotation à partir de 0
    char premier = S[0];
    
    std::cout << S << "\n";
    std::cout << premier << " " << c << "\n";
    
    
    // les structures
    
    Enseignant Moi;
    Moi.firstname = "Damien";
    Moi.name = "Simon";
    Moi.office = 207;
    
     
    
	return 0;
}

