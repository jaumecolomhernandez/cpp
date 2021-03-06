#include <vector>
#include <iostream>
#include <list>
#include <set>
#include <random>

class Permutation;
class Cycle;

class Permutation{
    private:
        // Parameters
        unsigned n;
        std::vector<int> images;

        // Private (dangerous) operations
        Permutation extend(int m) const;
        int & operator[](int i) {return images[i];} // No sense to edit specific point (it is a bijection!)
    
    public:
        // Constructor(s) (initialization in header file)
        Permutation(int _n=0): n(_n), images(_n) { for(unsigned i=0; i<_n; ++i){ images[i] = i; } }
        Permutation(const std::vector<int> &v): n(v.size()), images(v) {} // With vector
        Permutation(std::istream & flux);
        Permutation(unsigned _n, std::mt19937 &g);

        // Getters
        int size() const {return n;} // Access n
        int operator[](int i) const {return images[i];} // Access by index (value/copy)

        // Operators (friend allow to access external values by reference)
        friend Permutation operator*(const Permutation &, const Permutation &);
        friend std::ostream & operator<<(std::ostream &, const Permutation &);

        // Permutation functions
        std::vector<int> fixedPoints() const;
        Permutation inverse() const;
        std::list<Cycle> cycles() const;
        bool is_derangement() const;
        unsigned order() const;
};

class Cycle{
    private:
        std::list<int> elem;
    public:
        // Constructor
        Cycle(std::list<int> l): elem(l) {};
        // Getter
        unsigned order() const {return elem.size();};

        // Operators
        friend bool operator<(const Cycle &, const Cycle &);
        friend std::ostream & operator<<(std::ostream &, const Cycle &);
        friend std::ostream & operator<<(std::ostream & out, std::list<Cycle> & l);

        // Function
        template <typename T>
        void permute(std::vector<T> &v) const;
};