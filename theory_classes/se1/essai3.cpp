#include <iostream>
#include <Eigen/Dense>  // chemin vers bibliothèque

int main()
{
    Eigen::Matrix<double,4,4> A;
    A << 1, 2 , 3, 4 , 1,-1,1,-1,4,3,2,1,1,-1,0,0 ;
    
    std::cout << "La matrice A est:\n" << A << "\n";
    
    std::cout << "Son determinant est: " 
              << A.determinant() << "\n";
              
    std::cout << "Son inverse est:\n" 
              << A.inverse() << "\n";
  
    return 0;
}
