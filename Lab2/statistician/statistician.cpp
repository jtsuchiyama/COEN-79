// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2 {
	statistician::statistician() {
		reset(); // Sets all private variables to 0 initially
	}

	void statistician::next(double in) {
		len ++;
		total += in;

		if (length() == 1) {
		// If the first value is added, then it is both the max and min
			max = in;
			min = in;		
		}
		else {
			if (in > max)
			// Check if the input is greater than the current maximum and replace if so
				max = in;
			if (in < min)
			// Check if the input is smaller than the current minimum and replace if so
				min = in;
		}
	}

	int statistician::length() const {
		return len;
	}

	double statistician::sum() const {
		return total;
	}

	double statistician::mean() const {
		assert(len > 0);
		return total / len;
	}

	double statistician::minimum() const {
		assert(len > 0);
		return min;
	}

	double statistician::maximum() const {
		assert(len > 0);
		return max;
	}

	void statistician::reset() {
		total = 0;
		len = 0;
		max = 0;
		min = 0;
	}

	statistician operator + (const statistician &s1, const statistician &s2) {
		statistician temp;
		temp.len = s1.length() + s2.length();
		temp.total = s1.sum() + s2.sum();

		if (s1.maximum() >= s2.maximum()) // Determine which is the new maximum
			temp.max = s1.maximum();
		else
			temp.max = s2.maximum();

		if (s1.minimum() <= s2.minimum()) // Determine which is the new minimum
			temp.min = s1.minimum();
		else
			temp.min = s2.minimum();
		
		return temp;
	}

	statistician operator * (double scale, const statistician &s) {
		statistician temp;
		temp.len = s.length();
		temp.total = scale * s.sum();

		if (scale >= 0) {
		// If the scale is positive, the max and min are correct
			temp.max = scale * s.maximum();
			temp.min = scale * s.minimum(); 
		}
		else {
		// If the scale is negative, the max and min need to be flipped
			temp.max = scale * s.minimum();
			temp.min = scale * s.maximum();
		}
		
		return temp;
	}

	bool operator == (const statistician &s1, const statistician &s2) {
		if (s1.length() == 0 & s2.length() == 0) // If both lengths are zero, then they are both empty and thus the same
			return true;
		else if (s1.length() == s2.length() & s1.sum() == s2.sum() & s1.mean() == s2.mean() & s1.minimum() == s2.minimum() & s1.maximum() == s2.maximum()) // If all private variables the same
			return true;
		else // If they are not the same, then they are different
			return false;
	}
}


