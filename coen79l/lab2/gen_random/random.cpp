// FILE: rand_gen.cpp
// CLASS IMPLEMENTED: rand_gen (see rand_gen.h for documentation)

#include "random.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2 {

    //Constructor: the members are set to the provided values.
    rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus) {
        this->seed = seed;
        this->multiplier = multiplier;
        this->increment = increment;
        this->modulus = modulus;
    }
    //sets the seed with the given seed.
    void rand_gen::set_seed(int new_seed) {
        seed = new_seed;
    }
    
    //calculates the next value with the linear congruence method and returns it
    int rand_gen::next() {
        int next = (multiplier* seed+ increment) %modulus;
        seed = next;
        return next;
    }
    
    //Prints rand_gen members in a specific format
    void rand_gen::print_info() {
        std::cout << "Seed: " << seed << endl;
        std::cout << "Multiplier: " << multiplier << endl;
        std::cout << "Increment: " << increment << endl;
        std::cout << "Modulus: " << modulus << endl;
    }
}