#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixDouble;
typedef std::mt19937_64 MersenneTwister;

MatrixDouble generate_GOE_matrix(MersenneTwister &G, int N) {
    MatrixDouble M(N, N);
    std::normal_distribution<double> Loi_diag(0,1);
    std::normal_distribution<double> Loi_hors_diag(0,2);

    for(int j=0; j<N; ++j){
        M(j,j) = Loi_diag(G);
        for(int i=j+1;i<N; ++i){
            M(i,j) = Loi_hors_diag(G);
            M(j,j) = M(i,j); 
        }
    }

    return M;
}

int main(){
    // Parametres
    MersenneTwister G(time(nullptr));
    const int N = 150;
    const int nb_boxes = 20;
    double a = -3.;
    double b = 3.;
    int simul = 50;

    std::vector<double> hist(nb_boxes, 0);
    MatrixDouble M;
    
    // Generation des matrices et calcul des valeurs propres
    for(int sample=0; sample<simul; sample++){
        M = generate_GOE_matrix(G,N);
        Eigen::EigenSolver<MatrixDouble> Solver(M);
        for(int i=0; i<N; i++){
            double lambda_normalized = Solver.eigenvalues()[i].real()/(2.*sqrt(N));
            int indice = std::floor((lambda_normalized-a)/(b-a)*nb_boxes);
            if (0<indice && indice<nb_boxes){
                hist[indice]+=1.;
            }
        }
    }
    
    // Normalize them to 1
    for (auto &x: hist){
        x /= double(simul*N);
    }

    std::ofstream output2("eigenvalues.dat");
    for(int i=0; i<hist.size();i++){
        output2 << a+(2*i+1)*(b-a)/(2.*nb_boxes) << "\t" << hist[i] <<std::endl;
    }
    output2.close();

    std::cout << "Histogram exported to eigenvalues.dat";

    return 0;
}