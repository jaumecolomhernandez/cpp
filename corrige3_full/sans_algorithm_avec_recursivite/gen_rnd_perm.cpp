#include "permutation.hpp"

#include <fstream>

int main() {
    int n=16384;
    std::mt19937 g(456);
    Permutation s(n,g);
    Permutation t(n,g);
    std::ofstream file_s("./file_s.dat");
    std::ofstream file_t("./file_t.dat");

    file_s << s;
    file_t << t;
    file_s.close();
    file_t.close();
    return 0;
}
