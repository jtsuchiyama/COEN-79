// FILE: poly.cpp
// CLASS IMPLEMENTED: polynomial

// INVARIANTS for the polynomial class:
// The index of the poly array corresponds to the exponent of the coefficient
// The MAXIMUM+1 constant gives the maximum size of the poly array 

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include <iomanip>   // Provides setprecision
#include "poly.h"
#include <math.h>
#include <climits>

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4 {
    // Helper member functions for the polynomial class
    void polynomial::update_current_degree() {
        current_degree = degree();
    }

    // Constructor
    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        for(int i=0;i<=MAXIMUM_DEGREE;i++) {
        // Iterate through poly to declare the coefficents
            if(i == exponent)
            // If the specified exponent is reached, set the approriate coefficient
                poly[i] = c;

            else 
            // Else, the coefficient is zero
                poly[i] = 0;
        }
    }

    // Modification member functions for the polynomial class
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        poly[exponent] = coefficient;
        return;
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        poly[exponent] += amount;
        return;
    }

    void polynomial::clear() {
        for(int i=0;i<=MAXIMUM_DEGREE;i++) 
        // Iterate through the entire poly loop setting the coefficients to zero
            poly[i] = 0;
    }

    // Constant member functions for the polynomial class
    polynomial polynomial::antiderivative() const {
        assert(degree() < MAXIMUM_DEGREE);
        polynomial temp;
        for(int i=0;i<MAXIMUM_DEGREE;i++) {
        // Iterate through the poly array
            temp.poly[i+1] = poly[i] / (i+1); // Coefficient divided by the next exponent
        }
        return temp;
    }

    double polynomial::coefficient(unsigned int exponent) const {
        if(exponent <= MAXIMUM_DEGREE)
        // If the exponent <= MAXIMUM_DEGREE, then return the corresponding coefficient
            return poly[exponent];

        else
        // If the exponent > MAXIMUM_DEGREE, then return 0 as desired
            return 0;
    }

    double polynomial::definite_integral(double x0, double x1) const {
    /*
    The definite integral is calculated analytically. The lower bound is given by x0, and the upper bound is given by x1.
    We will evaluate the antiderivative at lower and upper bounds. The resulting upper value will be subtracted by the resulting lower value, 
    netting the definite integral
    */
        polynomial temp = antiderivative(); // Creating the antiderivative polynomial
        double lower = temp(x0); // Antiderivative evaluated at lower bound
        double upper = temp(x1); // Antiderivative evaluated at upper bound
        return upper-lower; // Subtract the antiderivatives evaluated at the top bound by the lower bound
    }

    unsigned int polynomial::degree() const {
        for(int i=MAXIMUM_DEGREE;i>=0;i--) {
        // Iterates through poly in reversed order
            if(poly[i] != 0)
            // If the coefficient is not zero, then this is the largest exponent with a non-zero coeff.
                return i;
        }
        // If all coefficients are zero, then return zero as desired
        return 0;
    }

    polynomial polynomial::derivative() const {
        polynomial temp;
        for(int i=1;i<=MAXIMUM_DEGREE;i++) {
        // Iterate through the poly array
            temp.poly[i-1] = i * poly[i]; // Exponent * coefficent
        }
        return temp;
    }

    double polynomial::eval(double x) const {
        double sum;
        for(int i=0;i<=MAXIMUM_DEGREE;i++) {
        // Iterate through the poly array
            sum += poly[i] * pow(x,i); // Summing coefficient * x^i
        }
        return sum;
    }

    bool polynomial::is_zero() const {
        for(int i=0;i<=MAXIMUM_DEGREE;i++) {
        // Iterate through the poly array
            if(poly[i] != 0)
            // If a non-zero coefficient is found, then it is not a zero polynomial
                return false;
        }
        // If the poly array is all zeroes, then it is a zero polynomial
        return true;
    }

    unsigned int polynomial::next_term(unsigned int e) const {
        for(int i=e+1;i<=MAXIMUM_DEGREE;i++) {
        // Iterate through the rest of the poly array
            if(poly[i] != 0)
            // If the coefficient is non-zero, then return it
                return i;  
        }
        // If none of the next coefficents are non-zero or there is no next coefficient, then return zero as desired
        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const {
        for(int i=e-1;i>=0;i--) {
        // Iterate through the rest of the poly array
            if(poly[i] != 0)
            // If the coefficient is non-zero, then return it
                return i;
        }
        // If none of the prior coefficients are non-zero or there is no prior coefficient, then return UINT_MAX
        return UINT_MAX;
    }

    // Constant operators for the polynomial class
    double polynomial::operator() (double x) const {
        return eval(x);
    }

    // Non-member binary operators
    polynomial operator + (const polynomial& p1, const polynomial& p2) {
        polynomial temp;
        for(int i=0;i<=polynomial::MAXIMUM_DEGREE;i++) {
        // Iterate through both p1 and p2 and add their coefficients into temp
            temp.assign_coef(p1.coefficient(i)+p2.coefficient(i), i);
        }
        return temp;
    }

    polynomial operator - (const polynomial& p1, const polynomial& p2) {
        polynomial temp;
        for(int i=0;i<=polynomial::MAXIMUM_DEGREE;i++) {
        // Iterate through both p1 and p2 and subtract their coefficients into temp
            temp.assign_coef(p1.coefficient(i)-p2.coefficient(i), i);
        }
        return temp;
    }

    polynomial operator * (const polynomial& p1, const polynomial& p2) {
        assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
        polynomial temp;
        for(int i=0;i<=p1.degree();i++) {
        // Iterate through p1
            for(int j=0;j<=p2.degree();j++) {
            // Iterate through p2
                temp.add_to_coef(p1.coefficient(i)*p2.coefficient(j), i+j); // Multiply the coeff. and sum to approriate coefficient
            }
        }
        return temp;
    }
    
    // Non-member output functions
    std::ostream& operator << (std::ostream& out, const polynomial& p) {
        streamsize temp = out.precision(); // Store the default precision
        out << fixed; // Allows for control over amount of decimal places for floating points
        out << setprecision(1); // Set the decimal places to 1
        for(int i=p.degree();i>=0;i--) {
        // Iterate through the poly array
            if(p.coefficient(i) != 0) {
            // Only print if the coefficient is non-zero
                if (i != p.degree()) {
                    if(p.coefficient(i) >= 0) {
                    // Check if a + should be printed
                        out << " + ";
                    }
                    else {
                    // Check if a - should be printed
                        out << " - ";
                    }
                }

                if(i == 0) {
                // If the exponent is zero, then do not include x and exponent
                    out << p.coefficient(i);
                }

                else if(i == 1) {
                // If the exponent is one, then do not include exponent
                    out << p.coefficient(i) << "x";
                }

                else {
                // If the exponent is greater than 1, then include x and exponent
                    out << p.coefficient(i) << "x^" << i;
                }
            }
        }
        out << setprecision(temp); // Set the decimal places back to the default
        return out;
    }
}