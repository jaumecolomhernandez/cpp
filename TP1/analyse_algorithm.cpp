#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>

#include <algorithm>
#include <numeric>
#include <map>

using namespace std;

typedef struct {
    string prenom;
    string ville;
    int age {0};
    double temps {0.};
} Fiche;

int main() {
    // Open file 
    ifstream fichier("smalldata.txt");
    
    // Read data (dynamically read)
    vector<Fiche> tableau;

    Fiche person;
    while( fichier >> person.prenom >> person.ville >> person.age >> person.temps ) {
        tableau.push_back(person);
    }

    int N = tableau.size();

    // (a) Combien de personnes habitent Lyon? Quelle est le pourcentage de Lyonnais?
    auto is_from_lyon = [](const Fiche f){
        return (f.ville == "Lyon");
    };

    int count_a = count_if(tableau.begin(), tableau.end(), is_from_lyon);

    cout << "(a) Number of people in Lyon: " << count_a <<" ("<< (double)count_a/N*100 << "%)\n";

    // (b) Combien de personnes habitent Lyon et ont strictement moins de 30 ans?
    auto is_from_lyon_under_thirty = [](const Fiche f){
        return (f.ville=="Lyon" && f.age<30);
    };

    int count_b = count_if(tableau.begin(), tableau.end(), is_from_lyon_under_thirty);

    cout << "(b) Number of people in Lyon and below 30: " << count_b <<" ("<< count_b/(double)N*100 << "%)\n";

    // (c) Existe-t-il un Toulosain dont le prénom commence par la lettre A?
    
    int count_c = count_if(tableau.begin(), tableau.end(), [](const Fiche f){
        return (f.ville=="Toulosse" && f.prenom[0]=='A');});
    
    cout << "(c) Is there a 'Toulossain' with name starting by A? ";
    if (count_c>0){
        cout << "Yes\n";
    }else{
        cout << "No\n";
    }

    // (d) Quel est l'age minimal? L'age maximal? Comment s'appele le plus jeune/age?
    auto elements = minmax_element(tableau.begin(), tableau.end(), 
        [](const Fiche f1, const Fiche f2){ return f1.age<f2.age; });

    cout << "(d.1) The youngest person is: " << elements.first->prenom 
        << " with age: " << elements.first->age << "\n";
    cout << "(d.2) The oldest person is: " << elements.second->prenom  
        << " with age: " << elements.second->age << "\n";

    // (e) Quel est l'age moyen des personnes du fichier? Quel est l'ecart-type de leur age?
    auto summation = accumulate(tableau.begin(),tableau.end(),0.,[](double s, const Fiche f){return s+f.age;});
    auto summation_sq = accumulate(tableau.begin(),tableau.end(),0.,[](double s, const Fiche f){return s+f.age*f.age;});
    
    double mean = summation/(double)N;
    double std = summation_sq/(double)N - mean*mean;
    cout << "(e.1) The mean is: " << mean << "\n";
    cout << "(e.2) The std is: " << std << "\n";

    // (f) Les Parisiens sont-ils en moyenne plus rapides au 100 
    // mètres que les Marseillais?

    auto sum_paris = accumulate(tableau.begin(), tableau.end(), 0., 
        [](double s, const Fiche f){return s+ (f.ville=="Paris")?f.temps:0.;});
    auto count_paris = count_if(tableau.begin(), tableau.end(), 
        [](const Fiche f){return f.ville=="Paris";});
    auto sum_marseille = accumulate(tableau.begin(), tableau.end(), 0., 
        [](double s, const Fiche f){return s+ (f.ville=="Marseille")?f.temps:0.;});
    auto count_marseille = count_if(tableau.begin(), tableau.end(), 
        [](const Fiche f){return f.ville=="Marseille";});

    double p_avg = sum_paris/count_paris;
    double m_avg = sum_marseille/count_marseille;

    if (p_avg<m_avg){
        cout << "(f) Parisiens are faster than Marseillais (" << p_avg <<" vs "<< m_avg <<")\n";
    }else{
        cout << "(f) Marseillais are faster than Parisiens (" << m_avg <<" vs "<< p_avg <<")\n";
    };

    // (g) Produire un fichier toulosains.txt qui contient toutes les informations
    // sur les personnes qui habitent Toulose. On remplacera dans ce fichier leur age
    // par leur date de naissance (on supposera que les ages ont ete declares en 2018)

    ofstream toulosains("toulosains.txt");
    auto print_toulose = [&toulosains](const Fiche & s) {
        if (s.ville == "Toulouse") {
            const int current_year = 2018;
            toulosains << s.prenom << "\t"
                    << s.ville << "\t"
                    << current_year-s.age << "\t"
                    << s.temps << "\n";
        }
    };
    for_each(tableau.begin(), tableau.end(),print_toulose);
    toulosains.close();
    cout << "(g) Le fichier toulosains.txt has been created.\n";

    // (h) Quelle est la covariance empirique entre age et temps a l'épreuve du 100
    // mètres sur cet échantillon de Toulosains?

    auto time_toulouse = accumulate(tableau.begin(), tableau.end(), 0., 
        [](double s, const Fiche f)->double {return s+ (f.ville=="Toulouse")?f.temps:0.;});

    auto age_toulouse = accumulate(tableau.begin(), tableau.end(), 0., 
        [](double s, const Fiche f)->double {return s+ (f.ville=="Toulouse")?f.age:0.;});

    auto age_time_toulouse = accumulate(tableau.begin(), tableau.end(), 0., 
        [](double s, const Fiche f)->double {return s+ (f.ville=="Toulouse")?f.age*f.temps:0.;});

    int count_toulouse = count_if(tableau.begin(), tableau.end(), 
        [](const Fiche f){return f.ville=="Toulouse";});

    
    time_toulouse /= double(count_toulouse);
    age_toulouse /= double(count_toulouse);
    age_time_toulouse /= double(count_toulouse);
    age_time_toulouse -= time_toulouse * time_toulouse;

    cout << "(h) The covariance between time and age in people from Toulosse is: " << age_time_toulouse << "\n";

    // (i) Afficher dans le terminal la liste de villes représentees
    std::set<std::string> villes;

    std::for_each(tableau.begin(), tableau.end(), 
        [&villes](const Fiche s){villes.insert(s.ville);});

    cout << "(i) List of unique cities: \n";

    std::for_each(villes.begin(), villes.end(),
        [](string name){cout << "\t" << name << "\n";});
    
    // Question 2: Produire un fichier data_tri.txt qui contient les 100 persones
    // les plus rapides au 100 metres trees par vitesse decroissante

    auto compare = [](const Fiche &f1, const Fiche &f2){
        return f1.temps<f2.temps;
    };

    std::sort(tableau.begin(), tableau.end(), compare);

    std::ofstream top100("data_tri.txt");
    std::for_each(tableau.begin(), tableau.begin()+100, 
        [&top100](const Fiche f){top100 << f.prenom << "\t" << f.ville << "\t" << f.age << "\t" << f.temps << "\n";});

    cout << "Q2 - Fichier data_tri.txt has been created\n";

    // Section 1.3
    // Q1. Smallest difference between two times
    std::vector<double> time_data;
    std::for_each(tableau.begin(), tableau.end(), 
        [&time_data](const Fiche f){time_data.push_back(f.temps);});

    std::sort(time_data.begin(), time_data.end(), 
        [](double t1, double t2){return t1<t2;});

    std::vector<double> time_diff(N);
    std::adjacent_difference(time_data.begin(), time_data.end(), time_diff.begin());

    std::cout << "The smallest element is -> " 
        << *(std::min_element(time_diff.begin(), time_diff.end()))
        << " seconds\n\n";

    // Smart/Hacky solution to keep runner info
    auto fiche_difference = [](const Fiche &f1, const Fiche &f2){
        Fiche st;
        st.prenom = f1.prenom+", "+f1.ville+", "+std::to_string(f1.age)+", "+std::to_string(f1.temps)+"s";
        st.ville = f2.prenom+", "+f2.ville+", "+std::to_string(f2.age)+", "+std::to_string(f2.temps)+"s";
        st.age = 0.;
        st.temps = f1.temps-f2.temps;
        return st;
    };

    std::vector<Fiche> differences_info(N);
    std::adjacent_difference(tableau.begin(), tableau.end(), differences_info.begin(), fiche_difference);

    auto diff_temps = [](const Fiche & s,const Fiche & t) { return s.temps < t.temps; };
	Fiche mindiff= *(std::min_element(differences_info.begin()+1, differences_info.end(),diff_temps)) ;
	std::cout	<< "Le plus petit écart est " << mindiff.temps 
				<< " secondes\net il est entre les personnes " << mindiff.prenom
				<< " et " << mindiff.ville << "\n\n";

    // Q2. Split Fiches in >40 and <=40
    std::vector<Fiche> young, old;
    auto test_age = [](const Fiche &f) {
        const int agelimit=40;
        return f.age <= agelimit;
    };

    std::partition_copy(tableau.begin(), tableau.end(), std::back_inserter(young), std::back_inserter(old), test_age);

    // Q3. Sort people according to various criteria

    // Easy comparison function

    // Q4. Histogram of the ages-
    std::map<int, int> Histogram;
    for (const auto &fiche: tableau){
        Histogram[fiche.age]++;
    }
    std::cout << "4/ Histogramme des ages: \n";
    std::for_each(Histogram.begin(), Histogram.end(),
        [](std::pair<int,int> v){ std::cout << "Age: " << v.first <<"  \t Quant: " << v.second << "\n";});
}