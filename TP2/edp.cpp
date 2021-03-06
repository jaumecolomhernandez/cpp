#include <iostream>
#include <fstream>
#include <chrono>

#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>

using SpMat = Eigen::SparseMatrix<double>;
using Vec = Eigen::VectorXd;
using Triplet = Eigen::Triplet<double>;

inline int point_index(int P, int i, int j) {return j*P+i;}

// Question 2.8
Eigen::SparseMatrix<double> make_sparse_laplacian_matrix(int P) {
    auto init = std::vector<Triplet>(); // i,j,value !
    init.reserve(P*P*4); // 4 entries for each point in grid
    for (int j=0; j<P; j++){
        for (int i=0; i<P; i++){
            init.emplace_back(point_index(P,i,j),point_index(P,i,j),-4.);
            
            if ( i>0 ) init.emplace_back(point_index(P,i,j),point_index(P,i-1,j),1.);
            if ( i<P-1 ) init.emplace_back(point_index(P,i,j),point_index(P,i+1,j),1.);
            if ( j>0 ) init.emplace_back(point_index(P,i,j),point_index(P,i,j-1),1.);
            if ( j<P-1 ) init.emplace_back(point_index(P,i,j),point_index(P,i,j+1),1.);
        }
    }

    // Accumulate (sum) all values in same position i,j
    auto result = Eigen::SparseMatrix<double>(P*P,P*P);
    result.setFromTriplets(init.begin(), init.end());

    return result;
}

// Question 2.8 (ALTERNATIVE)
SpMat make_sparse_laplacian_matrix2(int P) {
    auto resultat = SpMat(P*P,P*P);
    resultat.reserve(Eigen::VectorXi::Constant(P*P,4));
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < P; j++)
        {
            resultat.insert(point_index(P,i,j),point_index(P,i,j)) = -4.;
            if ( i > 0 )    resultat.insert(point_index(P,i,j),point_index(P,i-1,j)) = 1.;
            if ( i < P-1 )  resultat.insert(point_index(P,i,j),point_index(P,i+1,j)) = 1.;
            if ( j > 0 )    resultat.insert(point_index(P,i,j),point_index(P,i,j-1)) = 1.;
            if ( j < P-1 )  resultat.insert(point_index(P,i,j),point_index(P,i,j+1)) = 1.;
        }
    }
    // std::cout << resultat;
    resultat.makeCompressed();
    // std::cout << resultat;
    return resultat;
}

// Question 2.9
Eigen::VectorXd make_source_and_boundary_condition(int P){
    auto v= Vec(P*P);
    const double epsilon_square = 1./((P+1.)*(P+1.));
    // Source
    for (int j=0; j<P; j++){
        for (int i=0; i<P; i++){
            double x= (i+1.)/(P+1.); // From 0 to 1
            double y= (j+1.)/(P+1.);
            v(point_index(P,i,j)) = epsilon_square*320*x*(1.-x)*y*(y-1);
        }
    }
    // Boundaries
    for (int i = 0; i < P; i++) { // x index
		double x= (i+1.)/(P+1.);
        v(point_index(P,i,0)) += (x > 0.75)?-1.:0.;  // bottom
        v(point_index(P,i,P-1)) += (x > 0.25)?-1.:0.; // up
    }
    for (int j = 0; j < P; j++) { // y index
        v(point_index(P,0,j)) += 0.; // left side
        v(point_index(P,P-1,j)) += -1.; // right side
    }

    return v;
}

// Q.2.10
void squareprint_eigen_vector( const Eigen::VectorXd & f,
                            std::ostream & output,
                            int P, int Q) {
    for (int j=0; j<Q; j++){
        for (int i=0; i<P; i++){
            output << f(point_index(P,i,j)) << " ";
        }
        output << "\n";
    }
}

int main(){
    const int P=50;
    std::cout << "Resolution: " << P << "\n";

    // 1. Set up the solver with the laplacian (left side)
    // Modern cpp
    Eigen::SimplicialCholesky<SpMat> laplacian_solver = 
        Eigen::SimplicialCholesky<SpMat>(
            make_sparse_laplacian_matrix2(P)
    );

    // Old cpp (I prefer this one)
    // Eigen::SimplicialCholesky<SpMat> laplacian_solver2(make_sparse_laplacian_matrix(P));

    // 2. Set up the right side
    auto source = make_source_and_boundary_condition(P);

    // 3. Solve the linear equation (we want f)
    auto f = laplacian_solver.solve(source);

    auto file_res = std::ofstream("solution.dat");
    squareprint_eigen_vector(f,file_res,P,P);   
    file_res.close();

    return 0;
    // TODO: Add timers
}