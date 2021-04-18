//FILE: rand_gen.cpp
//CLASS IMPLEMENTED: rand_gen (see rand_gen.h for documentation)

#include <iostream>
#include "random.h"

namespace coen79_lab2 {
    //CONSTRUCTOR
    rand_gen::rand_gen(int s, int m, int i, int mod) {
        seed = s;
        multiplier = m; 
        increment = i; 
        modulus = mod;
    }
    //MODIFICATION 
    void rand_gen::set_seed(int s) { seed = s; }
    
    //MEMBER FUNCTIONS
    int rand_gen::next() {
        int randNum = (multiplier * seed + increment) % modulus;
        seed = randNum;
        return randNum;
    } 
    void rand_gen::print_info() {
        std::cout << "Seed: " << seed << std::endl;
        std::cout << "Multiplier: " << multiplier << std::endl;
        std::cout << "Increment: " << increment << std::endl;
        std::cout << "Modulus: " << modulus << std::endl; 
    }

    //end class implementation

} //end namespace