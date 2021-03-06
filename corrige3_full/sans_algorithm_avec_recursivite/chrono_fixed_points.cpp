#include "permutation.hpp"

#include <iostream>
#include <chrono>

int main() {
    std::mt19937 g;
    const int N_samples=10000;
    
    
    auto t1 = std::chrono::system_clock::now();
    long s=0;
    int seed=42;
    g.seed(seed);
    
    
    for(int i=0; i<N_samples; ++i) {
        s = +Permutation(N_samples, g).fixed_points().size();
    }
    auto t2 = std::chrono::system_clock::now();
    std::chrono::duration<double> diff =t2-t1;
    std::cout << "list: " << s << " " << diff.count() << std::endl;

    g.seed(seed);
    t1 = std::chrono::system_clock::now();
    for(int i=0; i<N_samples; ++i) {
        s = +Permutation(N_samples, g).fixed_points_v().size();
    }
    t2 = std::chrono::system_clock::now();
    diff =t2-t1;
    std::cout << "vect: " << s << " " << diff.count() << std::endl;

    return 0;
}
