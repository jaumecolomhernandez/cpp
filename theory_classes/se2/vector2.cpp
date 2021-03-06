#include <iostream>
#include <vector>

int main()
{
    int N = 3;
	std::vector<double> vec(N);
    vec[0]= 1.;
    vec[1]= -2.5;
    vec[2]= 4.;
    // en a-t-on oublié ?
    
    std::cout << "vec: ";
    for (int i = 0; i < N; i++) 
        // quelle numérotation des cases ?
        // quel lien entre vec et N ?
    {
        std::cout << vec[i] << " | "; 
    }
    std::cout << "\n";
    
    
    double b=-4.3;
    vec.push_back(b);
    vec.push_back(b);
    
    std::cout << "vec: ";
    for (int i = 0; i < N+2; i++)
        // quel lien entre vec et N ?
    {
        std::cout << vec[i] << " | "; 
    }
    std::cout << "\n";
    
    std::cout << "Le dernier est: " << vec[N]  << "\n";
        // vous êtes certains de la numérotation ?
    
    vec.push_back(b+3.);
    
    std::vector<double> w(N+3);
    for (int i = 0; i < N+3; i++)
        // que fait-on réellement ?
    {
        w[i] = vec[i]*vec[i]+1.;
    }
    double sw = 0.;
    for (int i = 0; i < N+3; i++)
        // que fait-on là encore ?
        // vous êtes toujours certains de la taille ?
    {
        sw += w[i];
    }
    
    std::cout << "Valeur de la somme: " << sw  << "\n"; 
    
	return 0;
}

