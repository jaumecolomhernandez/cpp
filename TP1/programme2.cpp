#include <iostream>
#include <vector>
#include <fstream>

int main () {

    // Read user data
    int n;
    std::cout << "Entrez un nombre entier <100: " << std::endl;
    std::cin >> n;

    // Compute squares
    std::vector<int> tableau(n);
    for (int i=0; i<n;  i++) {
        tableau[i]=i*i;
    }

    // Open file and write (reverse order)
    std::ofstream fichier("donnees.dat");
    fichier << "Voici les carrés des entiers:" << std::endl;
    for (int i=n-1; i>=0; i--) {
        fichier << i <<": " <<tableau[i] <<": " <<i*i*i <<std::endl;
    }
    fichier.close();
}