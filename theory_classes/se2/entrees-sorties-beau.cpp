#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

struct Enseignant {
    std::string firstname;
    std::string name;
    int office;
};

std::istream & operator>>(std::istream & input, Enseignant & E) {
    return input >> E.firstname >> E.name >> E.office;
}

std::ostream & operator<<(std::ostream & output, const Enseignant & E) {
    return output << E.firstname << " " << E.name << " " << E.office << " ";
}

int main() {
    using namespace std;//toujours la STL ici!
    
    auto source = ifstream{"data.dat"};
    
    // purge de la première ligne
    auto junk = string{};
    getline(source,junk);
    
    // Lecture des données:
    auto team = vector<Enseignant>{};
    
    copy(
        istream_iterator<Enseignant>{source},
        istream_iterator<Enseignant>{},
        back_inserter(team)
    );
    
    // Vérification par affichage
    auto new_format_Enseignant = 
        [](const Enseignant & E) -> string {
            return "(" + E.firstname  + ", " + E.name 
                         +  ", 16.26." + std::to_string(E.office) 
                         + ")";
        };
    transform(
        begin(team), end(team),
        ostream_iterator<string>(cout,"\n"),
        new_format_Enseignant
    );
    
    return 0;
}
