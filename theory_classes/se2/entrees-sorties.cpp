#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Enseignant {
    std::string firstname;
    std::string name;
    int office;
};// un peu pauvre en outil... Lire ? Ecrire ? 

// ce fichier est très très moche !!! Presque du C !

int main() {
    
    std::ifstream source("data.dat"); 
    // parenthèses: Constructeur ? function ?
    
    std::string junk;
    std::getline(source,junk);
    // parenthèses: Constructeur ? function ?

    
    int n=3; 
    /* ça vient d'où ? 
     * Et si on change la taille ? 
     * Et si on n'a pas le fichier sous la main ?
     * */
    
    std::vector<Enseignant> team(n);
    // encore des parenthèses: contenu ? taille ?
    
    for (int i = 0; i < n; i++)// quel lien entre n et team ? 
    {
        source >> team[i].firstname >> team[i].name >> team[i].office;
        // on lit toujours cette structure comme ça, non ?
    }
    
    for (int i = 0; i < n; i++)
        // quel lien entre n et team ? 
        // et si on se trompe ?
    {
        std::cout << "(" <<team[i].firstname 
                    << ", " << team[i].name 
                    << ", 16.26." << team[i].office
                    << ")\n";
    } //on veut faire quoi au fait ?
    return 0;
}
