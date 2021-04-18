//FILE: sequence1.cpp
//CLASS IMPLEMENTED: sequence (see sequence1.h for documentation)

#include <assert.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "sequence1.h"

namespace coen79_lab3 {
    //CONSTRUCTOR
    sequence::sequence() {
        data[CAPACITY];
        current_index = 0;
        used = 0;
    }

    //MODIFICATION MEMBER FUNCTIONS
    void sequence::start() {
        /** Poscondition: The iterator is reset to position 0; **/
        current_index = 0;
    }

    void sequence::end() {
        /** Poscondition: The iterator points to the last item in the sequence; **/
        if(used > 0) {
            current_index = (size() - 1);
        }
    }

    void sequence::last() {
        /**  Poscondition: The iterator is reset to CAPACITY - 1, 
         *      regardless of the number of items in the sequence **/
        current_index = (CAPACITY -1);
    }

    void sequence::advance() {
        /** Precondtion: isitem() returns true
        *  Postcondition: The iterator's value is increased by 1, 
        *       unless it is already at the end of the sequence. **/
        assert(is_item());
        ++current_index;
    }

    void sequence::retreat() {
        /** Postcondition: The iterator's value is reduced by 1, 
         *      unless it is already at the beginning of the sequence. **/
        if(current_index != 0) { 
            --current_index;
        }
    }

    void sequence::insert(const value_type& entry) {
        /** Precondition: size() < CAPACITY
        *      Postcondition: A new copy of entry has been inserted in the sequence
        *      before the current item. If there was no current item, the new entry
        *      has been inserted at the front. In either case, the new item is now the current item**/
        assert(size() < CAPACITY);
        if(!is_item()) { //if no item yet
            current_index = 0;
        }
        for(int i = used; i > current_index; --i) {
            data[i] = data[i-1];
        }
        data[current_index] = entry;
        ++used;
    }

    void sequence::attach(const value_type& entry) {
        /** Precondition: size() < CAPACITY
        *      Postcondition: A new copy of entry has been inserted in the sequence
        *      after the current item. If there was no current item, the new entry
        *      has been attached to the end. In either case, the new item is now the current item**/
        assert(size() < CAPACITY);
        if(!is_item()) { // if no item
            current_index = 0;
            data[current_index] = entry;
            ++used;
        }
        else { //else execute loop and iterate the current index to keep up with attached entry
            for(int i = used; i > current_index + 1; --i) {
                data[i] = data[i - 1];
            }
            ++current_index;
            data[current_index] = entry;
            ++used;
        }
    }

    void sequence::remove_current() {
        /** Precondtion: isitem() returns true
        *      Postcondition: The current item has been removed from the sequence,
        *      and the item after this (if there is one) is now the current item. **/
        assert(is_item());
        size_type i = current_index;
        if(current_index < (used-1)) { //rearrange sequence to remove the current item
            for(i; i < used; ++i) {
                data[i] = data[i+1];
            }
        }
        --used; 
    }

    void sequence::insert_front(const value_type& entry) {
        /** Precondition: size() < CAPACITY
        *      Postcondition: A new copy of entry has been inserted in the sequence
        *      at the front. The new item is now the current item of the sequence. **/
        assert(size() < CAPACITY);

        current_index = 0;
        size_type i = used;
        for(i; i > current_index; --i) { //shift sequence back one index
            data[i] = data[i-1];
        }
        data[current_index] = entry;
        ++used;
    }

    void sequence::attach_back(const value_type& entry) {
        /** Precondition: size() < CAPACITY
        *      Postcondition: A new copy of entry has been inserted in the sequence
        *      at the back. The new item is now the current item of the sequence. **/
        assert(size() < CAPACITY);
        current_index = used;
        data[current_index] = entry;
        ++used;
    }

    void sequence::remove_front() {
        /** Precondtion: isitem() returns true
        *      Postcondition: The item at the front of the sequence has been removed from the sequence,
        *      and the current item points at the front of the sequence. **/
        current_index = 0;
        assert(is_item());
        size_type i = current_index;
        for(i; i < used - 1; ++i) { //shift all entries forward one index
            data[i] = data[i + 1];
        }
        --used;
    }

    void sequence::operator +=(const sequence& rhs) {
        /** Postcondition: Adds the items of rhs to the lhs. Also returns a copy of lhs.**/
        assert(used + rhs.used < 30);
        size_type i = 0;
        size_type j = used;
        used += rhs.used;
        for(i; i < rhs.used; ++i) { //concatenate rhs sequence to this sequence
            data[j] = rhs.data[i];
            ++j;
        }
    }

    //CONSTANT MEMBER FUNCTIONS
    sequence::size_type sequence::size() const {
        /** Postcondition: The return value is the number of items in the sequence. **/
        return used;
    }

    bool sequence::is_item() const {
        /** Postcondition: A true return value indicates that there is a valid
        *     "current" item that may be retrieved by activating the current
        *     member function (listed below). A false return value indicates that
        *     there is no valid current item. **/
        return(used > 0 && current_index < used);
    }

    sequence::value_type sequence::current() const {
        /** Precondtion: isitem() returns true
        *      Poscondition: Returns the item in the sequence at the current position of the iterator. **/
        assert(is_item());
        return data[current_index];
    }

    sequence::value_type sequence::operator[](int index) const {
        /** Precondition: index < used
        *     Postcondition: The item returned is the item stored at "index" **/
        assert(index < used);
        return data[index];
    }

    double sequence::mean() const {
        /** Postcondition: The value returned is the mean of the values stored in the sequence. **/
        size_type i = 0;
        double sum;
        double mean;
        if(size() > 1) { //ensure the size of the sequence is larger than one
            for(i; i < used; ++i) {
                sum += data[i];
            }
            mean = (sum / used);
        }
        else { //else mean = only entry
            mean = data[0];
        }

        return mean;
    }

    double sequence::standardDeviation() const {
        /**Postcondition: The value returned is the stadard deviation of the values stored in the sequence. **/
        double sum = 0;
        double avg = mean();
        size_type i = 0;
        for(i; i < used; ++i) { //evaluate sum of all elements minus the average of the sequence
            sum = sum + (data[i] - avg);                     
            std::cout << "Sum: " << sum << std::endl;
        }
        double sd = sqrt((sum * sum) / (used - 1)); //evaluate standard deviation using the sum
        return sd;
    }

    //NON-MEMBER FUNCTIONS FOR SEQUENCE CLASS
    sequence operator +(const sequence& lhs, const sequence& rhs) {
        //pre condition: lhs.size() + rhs.size() < 30
        /**Postcondition: The sequence that is returned contains all the
        *     numbers of the sequences of lhs and rhs. **/
        assert((lhs.size() + rhs.size()) < 30);
        sequence s(lhs);
        sequence s2(rhs);
        s+=s2; //use overloaded += operator
        return (s);
    }

    sequence::value_type summation(const sequence &s) {
        /** Postcondition: The value returned is the summation of the values stored in the sequence s. **/
        sequence::value_type sum = 0;
        sequence toSum(s);
        toSum.start();
        while(toSum.is_item()) {
            sum += toSum.current();
            toSum.advance();
        }
        return sum;
    }
}