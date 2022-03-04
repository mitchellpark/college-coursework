/*
 * Author: Mitchell Park
 * This file provides implementation for the statistician class.
 */
#include <iostream>  
#include "statistician.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2
{
    //Constructor; every value should initially be 0
	statistician::statistician( ){
        total = 0;
        size = 0;
        min = 0;
        max = 0;
        avg = 0;
    }
    
    /*
     * Correctly rganizes a double value into all member variables.
     */
    void statistician::next(double r){
        total += r;
        size++;

        //If we are adding the first element, we can set the minimum and maximum as that value.
        if(size==1 || r<min) min = r;
        if(size==1 || r>max) max = r;
        avg = total/size;
    }
    
    void statistician::reset( ){
        total = 0;
        size = 0;
        min = 0;
        max = 0;
        avg = 0;   
    }
    
    //simply gets the avg value.
    double statistician::mean( ) const
    {
        return avg;
    }
    
    //simply gets the min value.
    double statistician::minimum( ) const
    {
        return min;
    }

    //simply gets the max value.
    double statistician::maximum( ) const
    {
        return max;
    }

    //simply  gets the total value.
    double statistician::sum() const{
        return total;
    }

    //simply gest the size value.
    int statistician::length() const{
        return size;
    }
    
    // Postcondition: The statistician that is returned contains all the
    // numbers of the sequences of s1 and s2.
    statistician operator +(const statistician& s1, const statistician& s2)
    {
        statistician s;
        s.size = s1.size + s2.size;
        s.total = s1.total + s2.total;
        s.avg = s.total/s.size;

        //The smaller minimum value should be the combined minimum, and 
        //the bigger maximum value should be the combined maximum.
        s.min = (s1.min < s2.min )? s1.min : s2.min;
        s.max = (s1.max >s2.max) ? s1.max : s2.max;
        return s;
    }

    // Postcondition: The return value is true if s1 and s2 have the zero
    // length. Also, if the length is greater than zero, then s1 and s2 must
    // have the same length, the samemean, the same minimum,
    // the same maximum, and the same sum.
    bool operator ==(const statistician& s1, const statistician& s2){
        bool output = s1.length() == s2.length()  && s1.maximum() == s2.maximum() && s1.minimum() == s2.minimum();
        bool cotd =  s1.mean() == s2.mean() && s1.sum() == s2.sum();
        return output && cotd;
    }
    
    // Postcondition: The statistician that is returned contains the same
    // numbers that s does, but each number has been multiplied by the
    // scale number.
    statistician operator *(double scale, const statistician& p){
        statistician s;
        s.avg = p.mean() * scale;
        s.max = scale < 0 ? p.maximum() : p.minimum();
        s.min = scale < 0 ? p.minimum() : p.maximum();
        s.total =  p.sum() * scale;
        return s;
    }
    
}


