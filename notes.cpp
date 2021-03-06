// 1ST PARTIAL EXAM NOTES

// TP1 First program, input/output and statistics
/* 
A FIRST PROGRAM  
- A program is consituted of imports function declaration and main function
- cout is to print and cin is to read
- Always add ; at the end of a statement
*/
#include <iostream>
#include <cmath>

double aire_du_cercle(double x) {return M_PI*x*x;}

int main(){
    double r;
    std::cout << "Introduce data: " << std::endl;
    std::cin >> r;
    std::cout << "Son aire est " << aire_du_cercle(r) << std::endl;
    return 0;
}


// A SECOND PROGRAM
// - There are for, while and do while loops
for (int i=0; i<10; i++){
    std::cout << i;
}

int i = 0;
while (i<10){
    std::cout << i;
}

int i
do {
    std::cout << i;
}while {i<10}

// - ofstream writes to file and ifstream reads from file
std::ofstream fichier("donnees.dat");
fichier << "Voici les carrés des entiers:" << std::endl;
fichier << blabla;
fichier.close(); // Always close the files!

// ANALYZING DATA PROGRAM
// - Struct are data containers with field. Data accessible with dot notation
struct Fiche {
    string prenom;
    string ville;
    int age;
    double temps;
};
// - Reading tabular data from file
ifstream fichier("smalldata.txt"); // Open file
int N = 2500; // Read data (defined number of lines)
std::vector<Fiche> tableau(N);
for (int i=0; i<N; i++){
    fichier 
        >> tableau[i].prenom 
        >> tableau[i].ville 
        >> tableau[i].age 
        >> tableau[i].temps;
}
// - (Dynamically) Reading tabular data from file
ifstream fichier("smalldata.txt"); // Open file
std::vector<Fiche> tableau2;
Fiche person;
while( fichier >> person.prenom >> person.ville >> person.age >> person.temps ) {
    tableau.push_back(person);
}
int N = tableau.size();
// - Sets can be used to get unique values
#include <set>
std::set<string> villes;
for (int i=0; i<N; i++){
    villes.insert(tableau[i].ville);
};
// - Algorithm/Numerics library provide functional programming capabilities
#include <numeric>
#include <algorithm>
// count if
int count = count_if(t.begin(), t.end(), 
    [](const Fiche f) {return (f.ville == "Lyon" && f.age < 10);});
// minmax
auto elements = minmax_element(tableau.begin(), tableau.end(), 
        [](const Fiche f1, const Fiche f2){ return f1.age<f2.age;});
// accumulate -> summation, product, division, etc.
auto summation_sq = accumulate(tableau.begin(),tableau.end(),0.,
    [](double s, const Fiche f){return s+f.age*f.age;}); // Can be products or divisions
// for each
auto print_things = [&ref](const Fiche &s){ref << s};
for_each(tableau.begin(), tableau.end(),print_things);
// accumulate with ternary operator
auto time_toulouse = accumulate(tableau.begin(), tableau.end(), 0., // Interesting use of the ternary operator
    [](double s, const Fiche f)->double {return s+ (f.ville=="Toulouse")?f.temps:0.;});
// sort with custom compare
auto compare = [](const Fiche &f1, const Fiche &f2){ return f1.temps<f2.temps;};
std::sort(tableau.begin(), tableau.end(), compare);
// adjancent_difference
std::adjacent_difference(time_data.begin(), time_data.end(), 
    time_diff.begin()); // Can be added custom_function, hacky way to preserve information
// partition_copy
std::partition_copy(tableau.begin(), tableau.end(), std::back_inserter(young), 
    std::back_inserter(old), test_age); // Test age is a boolean funcion with single input

// - How to create simple histogram
std::map<int, int> Histogram;
    for (const auto &fiche: tableau){ // This is a for each
        Histogram[fiche.age]++;
    }
    std::cout << "4/ Histogramme des ages: \n";
    std::for_each(Histogram.begin(), Histogram.end(),
        [](std::pair<int,int> v){ std::cout << "Age: " << v.first <<"  \t Quant: " << v.second << "\n";});

// TP2 Linear Algebra Library : Eigen
// 1. Matrix manipulation program
// Imports and typedefs
#include <Eigen/Dense>
#include <Eigen/Sparse>
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixDouble;
typedef Eigen::SparseMatrix<double> SparseDouble;
// Identity of matrices (dense and sparse)
MatrixDouble::Identity(M.rows(),M.cols()); 
SparseDouble Id(M.rows(), M.cols());
Id.setIdentity();
// Matrix assignation (code)
Eigen::Matrix3d A;
A << 0.4, 0.6, 0,
     0.75, 0.25, 0,
     0, 0, 1;
// Matrix assignation (file)
int N = 30;
std::ifstream o("matrice.dat");
MatrixDouble B(N,N);
for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            o >> B(i,j) ; // MUST BE IN THIS ORDER NOT REVERSE!
        }
}
// Counting time Chrono library
MatrixDouble PuisB(N,N);
auto t1 = std::chrono::system_clock::now();
PuisB = puissance(B,100);
auto t2 = std::chrono::system_clock::now();
std::chrono::duration<double> diff = t2-t1; // Important step
std::cout << "puissance took " << diff.count() << "s." << std::endl;
// Dense to sparse matrix
SparseDouble C(N,N);// Conversion de B en matrice sparse
for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
        // We have to check every value. 0 values do not have to be in the matrix
        if( B(i,j) >= 1.e-10 ) C.coeffRef(i,j) = B(i,j) ;
        // coeffRef is write access
    }
}
// Solving EDP exercise
// Understand that to solve an edp we can just  get the x from Ax=B
// by solving a linear equation
// - Solving a linear equation with Eigen
Eigen::SimplicialCholesky<SpMat> laplacian_solver =  // left side
    Eigen::SimplicialCholesky<SpMat>(
        make_sparse_laplacian_matrix2(P)
);
auto f = laplacian_solver.solve(source); // source is right side and f is the solution to the EDP
// - Instantiate the laplacian and the source/boundary conditions
// CHECK EDP.CPP file

// Random ensemble matrix and better histogram
// - Create random numbers (with distribution)
typedef std::mt19937_64 MersenneTwister;
MersenneTwister G(time(nullptr));
std::normal_distribution<double> Loi_diag(0,1);
double rand = Loi_diag(G) // rand is a random number
// - Get matrix eigenvalues
Eigen::EigenSolver<MatrixDouble> Solver(M); // M is the matrix
double eigen_val = Solver.eigenvalues()[x] 
// - Create a better histogram
std::vector<double> hist(nb_boxes, 0);
for (int & value: values){
    // a,b are min and max value, nb_boxes is the number of bins
    int indice = std::floor((lambda_normalized-a)/(b-a)*nb_boxes);
    if (0<indice && indice<nb_boxes){
        hist[indice]+=1.;
    }
}
for (auto &x: hist){  // Normalize them to 1
    x /= double(simul*N);
}
std::ofstream output2("eigenvalues.dat"); // Ouput to file
for(int i=0; i<hist.size();i++){ // Observe how to get the og value
    output2 << a+(2*i+1)*(b-a)/(2.*nb_boxes) << "\t" << hist[i] <<std::endl;
}
output2.close();

// TP3. Classes and permutations
// The first step is to get a class on combinatorics and more specifically permutations
// Summary: Successive permutations have intrinsic cycles in it. If the permutation
// preserves one position is a fixed point. If we have two permutations and we 
// multiply them (weird) we get a new permutation (bigger permutation), the order 
// (size of the biggest cycle) is the MCM of the two original permutations. 
// So that is what we are going to do!
/* - Header files and classes
On header files we have the declaration of classes -> functions, operators, etc.
In theory we should not have implementations on header files but with modern cpp
you can do it (you are almost encouraged). */
/* - Private and public fields
Classes have private and public fields. Parameters and setters should usually be private
unless you have a good reason to make them public. Everything else public.*/
/* - Constructors
Constructor overloading. Different constructors for different use cases, cpp automatically
uses the one it need for the task.*/
/* - Custom operators
Add friend to get access to private values and the name should have operator and the symbol 
you want to replace. For writing pass and return a std::ostream and the value we want to manipulate.
The use of parameter passing is very extended. 
Use ostream_iterator<type> name(outstream, " ") when have to print the contents of a container.*/

// Interesting constructor from a file
Permutation::Permutation(std::istream &f) {
    f >> n;
    images.resize(n);

    std::istream_iterator<unsigned> flux(f), eof;
    std::copy(flux, eof, images.begin());

    /* non STL
    for(unsigned i=0; i<n; ++i) {
        f >> images[i];
    }
    */
}

