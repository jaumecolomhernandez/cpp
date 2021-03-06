#include <iostream>
#include <vector>

int main()
{
    int N = 3;
	std::vector<double> vec(N);
    vec[0]= 1.;
    vec[1]= -2.5;
    vec[2]= 4.;
    
    std::cout << "vec: ";
    for (int i = 0; i < N; i++) 
    {
        std::cout << vec[i] << " | "; 
    }
    std::cout << "\n";
    
    
    double b=-4.3;
    vec.push_back(b);
    vec.push_back(b);
    
    std::cout << "vec: ";
    for (int i = 0; i < N+2; i++)
    {
        std::cout << vec[i] << " | "; 
    }
    std::cout << "\n";
    
    std::cout << "Le dernier est: " << vec[N]  << "\n";
    
    vec.push_back(b+3.);
    
    std::vector<double> w(N+3);
    for (int i = 0; i < N+3; i++)
    {
        w[i] = vec[i]*vec[i]+1.;
    }
    double sw = 0.;
    for (int i = 0; i < N+3; i++)
    {
        sw += w[i];
    }
    
    std::cout << "Valeur de la somme: " << sw  << "\n"; 
    
	return 0;
}

