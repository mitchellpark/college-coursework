#include <cassert>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "sequence1.h"

using namespace std;

namespace coen79_lab3 {
    
    sequence::sequence(){
        used = 0;
        current_index = 0;
    }

    
    void sequence::start(){
       current_index = 0;
    }
    
    void sequence::end(){
        current_index = size () - 1;
    }
    
    void sequence::last(){
        current_index = CAPACITY - 1;
        
    }
    
    void sequence::advance(){
        assert(is_item());
        if(current_index < used)
            current_index++;
    }
    
    void sequence::retreat(){
        if(current_index > 0)
            current_index--;
    }
    
    void sequence::insert(const value_type& entry){
        assert(size() < CAPACITY);
        current_index = (current_index < size()) ? current_index : 0;
        for (size_type i = used; i > current_index; i--){
            data[i] = data[i - 1];
        }
        data[current_index] = entry;
        used++;
    }

    void sequence::attach(const value_type& entry){
        assert(size() < CAPACITY);
        current_index = (current_index + 1 < size()) ? current_index + 1 : size();
            for (size_type i = used; i > current_index; i--){
                data[i] = data[i - 1];
            }
            data[current_index] = entry;
            
            used++;
        }
    
    void sequence::remove_current(){
        assert(is_item());
        for(size_type i = current_index; i < size() - 1; i++){
            data[i]=data[i + 1];
        }
        used--;
    }
    
    void sequence::insert_front(const value_type& entry){
        assert(size() < CAPACITY);
        current_index = 0;
        insert(entry);
        used++;
    }
    
    void sequence::attach_back(const value_type& entry) {
        assert(size() < CAPACITY);
        data[used] = entry;
        current_index = size();
        used++;
    }
   
    void sequence::remove_front() {
        assert(is_item());
        for(size_type i = 0; i < used - 1; ++i)
            data[i]=data[i+1];
        used--;
    }
    
    void sequence::operator +=(const sequence& rhs){
        assert(used + rhs.size() < CAPACITY);
        size_type tmp = rhs.used;
        for(int i = 0; i < tmp; i++) {
            data[used++] = rhs.data[i];
        }
    }

    sequence::size_type sequence::size() const{
        return used;
    }
    
    bool sequence::is_item() const {
        return current_index < size();
    }

    sequence::value_type sequence::current() const{
        assert(is_item());
        return data[current_index];
    }
    
    sequence::value_type sequence::operator[](int index) const{
        assert(index < used);
        return data[index];
    }
    
    double sequence::mean() const {
        double temp = 0;
            for(size_type i = 0; i < size(); i++){
                temp += data[i];
            }
            return temp/size();
        }

    double sequence::standardDeviation() const {
        value_type stdev = 0.0;
        value_type mean = sequence::mean();
        for(int i = 0; i < used; ++i) {
            stdev += pow(data[i] - mean, 2);
        }
        return sqrt(stdev/used);
    }
    
    sequence operator+(const sequence& lhs, const sequence& rhs){
        assert((lhs.size() + rhs.size()) <= sequence::CAPACITY);
        sequence(tmp);
        tmp += lhs;
        tmp += rhs;
        return tmp;
    }
    
    sequence::value_type summation(const sequence &s){
        sequence temp = s;
        sequence::value_type sum = 0;
        temp.start();
        for(sequence::size_type i = 0; i < temp.size(); i++){
            sum += temp.current();
            temp.advance();
        }
        return sum;
    }
}