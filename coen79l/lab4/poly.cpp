#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <climits>
#include "poly.h"
using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4
{
    // CONSTANTS
    const unsigned int polynomial::MAXIMUM_DEGREE;

    // HELPER FUNCTIONS
    void polynomial::setDegree(unsigned int i) {
        current_degree = i;
    }


    // CONSTRUCTOR
	polynomial::polynomial(double c, unsigned int exponent){
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {   //Initializing all coefficients to 0
            coef[i] = 0;
        }
        coef[exponent] = c;
        current_degree = exponent;
    }

	// MODIFICATION MEMBER FUNCTIONS
    
    /*Changes the coefficient of the given exponent*/
	void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);     
        coef[exponent] = coefficient;
        if(exponent>current_degree) current_degree = exponent;
    }

    /*Adds to the coefficient of the given exopnent by specified amount.*/
    void polynomial::add_to_coef(double amount, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        coef[exponent] += amount;
        if(exponent>current_degree) current_degree = exponent;      //Updating current_degree
    }

    /* All coefficients become zero. */
	void polynomial::clear( ) {
        for(int i = 0; i < current_degree; i++) {
            coef[i] = 0;
        }
        current_degree = 0;

    }

	// // CONSTANT MEMBER FUNCTIONS

    /*Performs an antiderivative for the polynomial.*/
    polynomial polynomial::antiderivative( ) const {
        polynomial p(0,0);      
        for(int i = 0; i <= current_degree; i++){
            p.assign_coef((coef[i]/(i+1)), i+1);   
        }
        return p;  
    }

    /*returns the coefficient of the specified degree number.*/
	double polynomial::coefficient(unsigned int exponent) const {
        // If exponent is greater than the maximum degree, we return 0.
        if(exponent > MAXIMUM_DEGREE)
            return 0;
        else
            return coef[exponent];
    }

    /*
     * Performs a definite integral with the given endpoints.
     * Upper is the value when the upper bound is plugged into the antiderivative,
     * and lower is for the lower bound.
    */
    double polynomial::definite_integral(double x0, double x1) const {
        double upper = 0.0, lower = 0.0;    
        polynomial a = antiderivative();

        for(int i = 0; i <=a.current_degree; i++){
            lower += (a.coef[i] * pow(x0,i));
            upper += (a.coef[i] * pow(x1,i));
        }
        return upper - lower;
    }

    /* Returns the derivaitve in a new polynomial object.*/
	polynomial polynomial::derivative( ) const {
        polynomial a;
        for(int i = 1; i <= current_degree; ++i) {
            a.assign_coef((coef[i] * i), i-1);
        }
        return a;       //a should be of degree i-1;
    }

    /* Returns the value we get from plugging in the given double value in the polynomial.*/
	double polynomial::eval(double x) const {
        double sum = 0.0;
        for(int i = 0; i <= current_degree; i++){
            sum += (coef[i] * pow(x, i));
        }
        return sum;
    }

    /* returns false as soon as we run into a nonzero value for a coefficient.*/
    bool polynomial::is_zero( ) const {
        for(int i = 0; i < MAXIMUM_DEGREE; i++){
            if(coef[i] != 0) {
                return false;
            }
        }
        return true;    //Returns true if all values pass the test and are indeed 0.
    }

    /* Returns the next valid exponent.*/
	unsigned int polynomial::next_term(unsigned int e) const {
        for(int i = e+1; e < MAXIMUM_DEGREE; i++){
            if(coef[i] != 0)
                    return i;
        }
        return 0;
    }

    /* Returns the previous valid exponent.*/
	unsigned int polynomial::previous_term(unsigned int e) const {
        for(int i = e-1; i >= 0; i--){
            if(coef[i] != 0)
                return i;
        }
        return UINT_MAX;
    }

    // // NON-MEMBER BINARY OPERATORS

    /*Returns a new polynomial object that is the sum of p1 and p2.*/
    polynomial operator +(const polynomial& p1, const polynomial& p2)
    {
        polynomial p;
        for(int i=0; i<=max(p2.degree(), p1.degree()); i++)
            p.assign_coef(p1.coefficient(i)+p2.coefficient(i), i);
        return p;   
    }

    /*Returns a new polynomial object that is the difference of p1 and p2.*/
    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        polynomial p;
        for(int i=0; i<=max(p1.degree(), p2.degree()); i++)
            p.assign_coef(p1.coefficient(i)-p2.coefficient(i), i);
        return p;
    }

    /*Returns a new polynomial object that is the product of p1 and p2.*/
    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        assert( (p1.degree() + p2.degree()) <= polynomial::MAXIMUM_DEGREE);     //The product will have greatest degree that is the sum of the degrees of p1 and p2
        polynomial p;
        for(int i=p1.degree(); i>=0; i--){
            for(int j=p2.degree(); j>=0; j--){
                p.add_to_coef((p1.coefficient(i) * p2.coefficient(j)), i+j);
                if(i+j>p.degree()) p.setDegree(i+j);
            }
        }

        return p;
    }

    // NON-MEMBER OUTPUT FUNCTIONS
    /*Prints the polynomial.*/
    std::ostream& operator << (std::ostream& out, const polynomial& p)
    {
        int deg = p.degree();
        streamsize s = out.precision();
        out << fixed;
        out << setprecision(1);
        if(deg == 0){
            if(p.coefficient(0)==0) out << "0.0";
            else out << p.coefficient(0);
        }else{
            out << p.coefficient(deg) << "x";
            if(deg>1)out << "^" << deg;     //If the exponent was 1, then we wouldn't want to say x^1.

            for (int i=deg-1; i>=0; i--){ 
                if (p.coefficient(i)!=0){
                    //if coefficient is negative or positive
                    if (p.coefficient(i)<0) out<< " - ";
                    else if (p.coefficient(i)>0) out<< " + ";

                    out << abs(p.coefficient(i)); 

                    //If the exponent is greater 1, write the x^i. If it is 1, we don't.
                    if (i>1){
                        out << "x^" << i; 
                    }else if(i==1) cout << "x";
                }
            }
        }
        out.unsetf(ios_base::floatfield);
        out << setprecision(s);
        return out;

    }
}
