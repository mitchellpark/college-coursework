#include "sequence1.h"
#include <cassert>
#include <cmath>

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3 {
	
	sequence::sequence() {
		used = 0;
        current_index = 0;
	}

    /* Set the current index to point to the first item*/
	void sequence::start() {
		current_index = 0;
	}

    /* Set the item at the given index as the d value */
    void sequence::setIndex(size_t i, double d){
        assert(i<size());
        data[i] = d;
    }

    /* Set the current index to point to the last item */
    void sequence::end() {
        current_index = size()-1;
    }
    
    /* Sets the current index to CAPACITY-1 */
    void sequence::last(){
        current_index = CAPACITY-1;
    }

    /* If the index is greater than 0, decrement the current index */
    void sequence::retreat(){
        if(current_index>0){
            current_index--;
        }
    }

    /* Checks if the current index is valid, and returns the item at the current index */
    sequence::value_type sequence::current() const {
        assert(current_index<CAPACITY);
        return data[current_index];
    }
    
    /* Makes sure that the current item is not empty, and increments the current index if is valid */
    void sequence::advance() {
        assert(is_item());
        if(current_index<used){
            current_index++;
        }
    }

    /* Returns true if the current index points to an item */
    bool sequence::is_item() const {
        return current_index<size();
    }
    
    /* Entry is inserted before the current item. The new item is now the current item of the sequence.*/
	void sequence::insert(const value_type& entry) {
		assert(size() < CAPACITY);

        //If there is no current item,the new entry gets inserted in the front.  
        current_index = (current_index<size()) ? current_index : 0; 
        for (size_type i=used; i>current_index; i--){
            data[i]=data[i - 1];
        }
        data[current_index] = entry;
        used++;
	}

    /* An entry is inserted after the current item. If there is no current item, then it is
     * attached to the end.
     */
    void sequence::attach(const value_type& entry) {
    	assert(size() < CAPACITY);
        //If there is no current item, then the index is set to the last index.
        current_index = (current_index+1 < size()) ? current_index+1 : size();
        for (size_type i=used; i>current_index; i--){
            data[i]=data[i - 1];
        }
        data[current_index] = entry;
        used++;

    }

    /*
     * The current item is removed, and the current item becomes the item after.
     */
    void sequence::remove_current() {
    	assert(is_item());
        for(size_type i = current_index; i < size() - 1; i++){
            data[i]=data[i + 1];
        }
        used--;
    }

    /*
     * Entry has been inserted in the front. The new item is the current item of the sequence.
     */
	void sequence::insert_front(const value_type& entry) {
		assert(size() < CAPACITY);
        for(int i=used; i>0; i--){
            data[used] = data[used-1];
        }
        data[0] = entry;
        start();
	}

     /* The item at the front is removed, and the current item points to the front of the sequence. */
	void sequence::remove_front() {
		assert(is_item());
        for(size_type i=0; i < used-1; i++)
            data[i]=data[i+1];
        start();
        used--;
	}

    /*
     * Entry has been inserted in the back. The new item is the current item of the sequence. 
     */
	void sequence::attach_back(const value_type& entry) {
		assert(size() < CAPACITY);
        data[used] = entry;
        used++;
        end();
	}

   

    /* Returns the number of items in the sequence*/
	sequence::size_type sequence::size() const {
        return used;
	}
    
    /* Returns the sequence's value of at the given index. */
    sequence::value_type sequence::operator[](int index) const {
        assert(index<used);
        return data[index];
    }
    
    /* Returns a new sequence object whose values are the added values of lhs and rhs. */
	sequence operator+(sequence& lhs, sequence& rhs) {
		assert(lhs.size() + rhs.size()<=sequence::CAPACITY);
        sequence(s);
        s += lhs;
        s += rhs;
        return s;
	}

    /* Sets the size as the given number */
    void sequence::setSize(double i){
        used = i;
    }

    /* Given that the sum of the sizes of lhs and rhs does not exceed lhs's capacity, 
     * we add rhs values to the lhs values.
     */
    sequence operator+=(sequence& lhs, sequence& rhs) {
		assert((lhs.size() + rhs.size()) < lhs.CAPACITY);
        for(int i=0; i<rhs.size(); i++){
            lhs.setIndex(lhs.current(), rhs[i]);
            lhs.advance();
        }
	}


    /* Returns the mean of the sequence. */
	double sequence::mean() const {
        return summation(*this)/size();
	}

    /* Returns the standard deviation of the sequence. */
	double sequence::standardDeviation() const{
		double sdSum = 0.0;
        double mean = sequence::mean();
        for(int i=0; i<used; i++) {
            sdSum += pow(data[i] - mean, 2);
        }
        return sqrt(sdSum/used);
	}

    /* Returns the sum of all sequence values */
	sequence::value_type summation(const sequence &s){
        int sum = 0;
        for(int i = 0; i < s.size(); i++){
            sum += s[i];
        }
        return sum;
	}

}