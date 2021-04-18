//FILE: random.h
//CLASS PROVIDED: rand_gen
//
// COEN 89
// --- Matthew Davenport, COEN, SCU ---
// A class to generate a sequence of pseudorandom integers using the linear congruence method
// This class is part of the namespace coen79_2B
//
// CONSTRUCTORS
//  rand_gen(int s, int m, int i, int mod)
//      post condition: new rand_gen object has been intialized with
//      passed values
//
// PUBLIC MODIFICATION member functions for rand_gen class:
//  void set_seed(int newSeed) 
//      post condition: seed is set for the rand_gen object
//
//  int next()
//      post condition: random number has been generated and seed is updated
//
// PUBLIC CONSTANT member functions for rand_gen class
//  void print_info()
//      post condition: all information about the current rand_gen object is printed


#ifndef RAND_H
#define RAND_H

namespace coen79_lab2 {

    class rand_gen {
        private: 
            int multiplier; 
            int seed;
            int increment;
            int modulus;
        public: 
            //CONSTRUCTORS
            rand_gen(int s, int m, int i, int mod);
            //PUBLIC MODIFICATION MEMBER FUNCTIONS
            void set_seed(int newSeed);
            int next();
            //PUBLIC MEMBER FUNCTIONS
            void print_info();
    }; //end class definition
} //end namespace

#endif