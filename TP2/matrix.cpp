#include <iostream>
#include <fstream>
#include <chrono>

#include <Eigen/Dense>
#include <Eigen/Sparse>

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixDouble;
typedef Eigen::SparseMatrix<double> SparseDouble;

// Q.2.1
MatrixDouble puissance(const MatrixDouble &M, int n){
    if(n==0){ 
        return MatrixDouble::Identity(M.rows(),M.cols()); 
    }
    else if(n==1){ 
        return M; 
    }
    else {
        return M*puissance(M,n-1);
    }
}

// Q.2.4
MatrixDouble puissance2(const MatrixDouble &M, int n){
    if(n==0){
        return MatrixDouble::Identity(M.rows(),M.cols());
    } else if(n==1){
        return M;
    } else if(n%2) {
        MatrixDouble pow = puissance(M, (n-1)/2);
        return M*pow*pow;
    } else {
        MatrixDouble pow = puissance(M, (n)/2);
        return M*pow*pow;
    }
    return M;
}

// Q.2.6
SparseDouble puissance_sparse(const SparseDouble &M, int n){
    if(n==0){
        SparseDouble Id(M.rows(), M.cols());
        Id.setIdentity();
        return Id; 
    } else if(n%2) {
        SparseDouble pow = puissance_sparse(M, (n-1)/2);
        return M*pow*pow;
    } else {
        SparseDouble pow = puissance_sparse(M, (n)/2);
        return M*pow*pow;
    }
}

int main() {

    // Q.2.2
    Eigen::Matrix3d A;
    A << 0.4, 0.6, 0,
         0.75, 0.25, 0,
         0, 0, 1;

    std::cout << " A = " << std::endl << A << std::endl;
    std::cout << " A^100 = " << std::endl << puissance(A,100) << std::endl;

    // Q.2.3
    // If we do not use the ampersand this has to copy each value. It is N*M*m
    // So for 100 is 900 and so on.

    // Q.2.4
    std::cout << " A^100 (optimized) = " << std::endl << puissance2(A,100) << std::endl;

    // Q.2.5
    int N = 30;
    std::ifstream o("matrice.dat");
    MatrixDouble B(N,N);
    for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                o >> B(i,j) ; // MUST BE IN THIS ORDER NOT REVERSE!
            }
    }
    std::cout << " Matrice.dat = " << std::endl << B << std::endl;

    MatrixDouble PuisB(N,N);
    auto t1 = std::chrono::system_clock::now();
    PuisB = puissance(B,100);
    auto t2 = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = t2-t1;
    std::cout << "puissance took " << diff.count() << "s." << std::endl;

    MatrixDouble PuisB2(N,N);
    auto t3 = std::chrono::system_clock::now();
    PuisB2 = puissance2(B,100);
    auto t4 = std::chrono::system_clock::now();
    std::chrono::duration<double> diff2 = t4-t3;
    std::cout << "puissance2 took " << diff2.count() << "s." << std::endl; 

    // Q.2.7
    // Convert matrix to sparse matrix
    SparseDouble C(N,N);// Conversion de B en matrice sparse
    for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                // We have to check every value. 0 values do not have to be in the matrix
				if( B(i,j) >= 1.e-10 ) C.coeffRef(i,j) = B(i,j) ;
                // coeffRef is write access
            }
    }

    SparseDouble PuisC(N,N);
    auto t5 = std::chrono::system_clock::now();
    PuisC = puissance_sparse(C,100);
    auto t6 = std::chrono::system_clock::now();
    std::chrono::duration<double> diff3 = t6-t5;
    std::cout << "puissance_sparse took " << diff3.count() << "s." << std::endl;
}