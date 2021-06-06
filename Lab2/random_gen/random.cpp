// FILE: random.cpp
// CLASS IMPLEMENTED: random

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "random.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2 {
    rand_gen::rand_gen(int randSeed, int randMultiplier, int randIncrement, int randModulus) {
		seed = randSeed;
        multiplier = randMultiplier;
        increment = randIncrement;
        modulus = randModulus;
	}

    void rand_gen::set_seed(int newSeed) {
        seed = newSeed;
    }

    int rand_gen::next() {
        int new_seed = (multiplier * seed + increment) % modulus; // Equation for the next seed
        seed = new_seed;
        return new_seed;
    }

    void rand_gen::print_info() const {
        // The below code is commented out for testing the output vs the expected_output.txt
        //cout << "Seed: " << seed << "\n";
        //cout << "Multiplier: " << multiplier << "\n";
        //cout << "Increment: " << increment << "\n";
        //cout << "Modulus: " << modulus << "\n\n";
    }
}
