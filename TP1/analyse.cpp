#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>

using namespace std;

struct Fiche {
    string prenom;
    string ville;
    int age;
    double temps;
};

int main() {
    // Open file 
    ifstream fichier("smalldata.txt");
    
    // Read data (defined number of lines)
    int N = 2500;
    vector<Fiche> tableau(N);
    for (int i=0; i<N; i++){
        fichier 
            >> tableau[i].prenom 
            >> tableau[i].ville 
            >> tableau[i].age 
            >> tableau[i].temps;
    }

    // (a) Combien de personnes habitent Lyon? Quelle est le pourcentage de Lyonnais? 
    int count_a = 0;
    for (int i=0; i<N; i++){
        if (tableau[i].ville == "Lyon"){
            count_a++;
        };
    }
    cout << "(a) Number of people in Lyon: " << count_a <<" ("<< (double)count_a/N*100 << "%)\n";

    // (b) Combien de personnes habitent Lyon et ont strictement moins de 30 ans?
    int count_b = 0;
    for (int i=0; i<N; i++){
        if (tableau[i].ville == "Lyon" && tableau[i].age < 30){
            count_b++;
        };
    }
    cout << "(b) Number of people in Lyon and below 30: " << count_b <<" ("<< count_b/(double)N*100 << "%)\n";

    // (c) Existe-t-il un Toulosain dont le prénom commence par la lettre A?
    int count_c = 0;
    for (int i=0; i<N; i++){
        if (tableau[i].ville == "Toulosse" && tableau[i].prenom[0] == 'A'){
            count_c++;
        };
    }
    cout << "(c) Is there a 'Toulossain' with name starting by A? ";
    if (count_c>0){
        cout << "Yes\n";
    }else{
        cout << "No\n";
    }

    // (d) Quel est l'age minimal? L'age maximal? Comment s'appele le plus jeune/age?
    int max_age = 0;
    int min_age = 999; // Here we assume that there is no one older than 999 years old
    int  i_max;
    int i_min;

    for (int i=0; i<N; i++){
        if (tableau[i].age < min_age){
            min_age = tableau[i].age;
            i_min = i;
        }else if (tableau[i].age > max_age){
            max_age = tableau[i].age;
            i_max = i;
        };
    }
    cout << "(d.1) The youngest person is: " << tableau[i_min].prenom 
        << " with age: " << min_age << "\n";
    cout << "(d.2) The oldest person is: " << tableau[i_max].prenom  
        << " with age: " << max_age << "\n";

    // (e) Quel est l'age moyen des personnes du fichier? Quel est l'ecart-type de leur age?
    int sum = 0;
    int sq_sum = 0;
    for (int i=0; i<N; i++){
        sum += tableau[i].age;
        sq_sum += tableau[i].age*tableau[i].age;
    }
    double mean = sum/(double)N;
    double std = sq_sum/(double)N - mean*mean;
    cout << "(e.1) The mean is: " << mean << "\n";
    cout << "(e.2) The std is: " << std << "\n";

    // (f) Les Parisiens sont-ils en moyenne plus rapides au 100 
    // mètres que les Marseillais?
    double p_times = 0;
    double m_times = 0;
    int p_count = 0;
    int m_count = 0;
    for (int i=0; i<N; i++){
        if (tableau[i].ville == "Paris"){
            p_times += tableau[i].temps;
            p_count++;
        } else if (tableau[i].ville == "Marseille"){
            m_times += tableau[i].temps;
            m_count++;
        }
    }
    double p_avg = p_times/m_count;
    double m_avg = m_times/m_count;
    if (p_avg<m_avg){
        cout << "(f) Parisiens are faster than Marseillais (" << p_avg <<" vs "<< m_avg <<")\n";
    }else{
        cout << "(f) Marseillais are faster than Parisiens (" << m_avg <<" vs "<< p_avg <<")\n";
    };

    // (h) Quelle est la covariance empirique entre age et temps a l'épreuve du 100
    // mètres sur cet échantillon de Toulosains?
    int t_count = 0;
    double t_temps = 0;
    int t_age = 0;
    // First compute means of time and age
    for (int i=0; i<N; i++){
        if (tableau[i].ville == "Toulouse"){
            t_temps += tableau[i].temps;
            t_age += tableau[i].age;
            t_count++;
        }
    }
    double mean_age = t_age/t_count;
    double mean_temps = t_temps/t_count;
    double cov = 0;
    // Then compute empirical covariance
    for (int i=0; i<N; i++){
        if (tableau[i].ville == "Toulouse"){
            cov += (tableau[i].temps-mean_temps)*(tableau[i].age-mean_age);
        }
    }
    cov = cov/t_count;
    cout << "(h) The covariance between time and age in people from Toulosse is: " << cov << "\n";

    // (i) Afficher dans le terminal la liste de villes représentees
    set<string> villes;

    for (int i=0; i<N; i++){
        villes.insert(tableau[i].ville);
    };

    cout << "(i) List of unique cities: \n";
    for (const string& ville : villes){ cout << "\t" << ville << '\n'; };

}