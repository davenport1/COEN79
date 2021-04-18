//FILE: sequence1.cpp
//CLASS IMPLEMENTED: sequence (see sequence1.h for documentation)

#include <assert.h>
#include <iostream>
#include "sequence1.h"

namespace coen79_lab3 {
    //CONSTRUCTOR
    sequence::sequence() {
    }

    //MODIFICATION MEMBER FUNCTIONS
    void sequence::start() {
        /** Poscondition: The iterator is reset to position 0; **/
    }

    void sequence::end() {
        /** Poscondition: The iterator points to the last item in the sequence; **/
    }

    void sequence::last() {
        /**  Poscondition: The iterator is reset to CAPACITY - 1, 
         *      regardless of the number of items in the sequence **/
    }

    void sequence::advance() {
        /** Precondtion: isitem() returns true
        *  Postcondition: The iterator's value is increased by 1, 
        *       unless it is already at the end of the sequence. **/
    }

    void sequence::retreat() {
        /** Postcondition: The iterator's value is reduced by 1, 
         *      unless it is already at the beginning of the sequence. **/
    }

    void sequence::insert(const value_type& entry) {
        /** Precondition: size() < CAPACITY
        *      Postcondition: A new copy of entry has been inserted in the sequence
        *      before the current item. If there was no current item, the new entry
        *      has been inserted at the front. In either case, the new item is now the
    }

    void sequence::attach(const value_type& entry) {
        /** Precondition: size() < CAPACITY
        *      Postcondition: A new copy of entry has been inserted in the sequence
        *      after the current item. If there was no current item, the new entry
        *      has been attached to the end. In either case, the new item is now the **/
    }

    void sequence::remove_current() {
        /** Precondtion: isitem() returns true
        *      Postcondition: The current item has been removed from the sequence,
        *      and the item after this (if there is one) is now the current item. **/
    }

    void sequence::insert_front(const value_type& entry) {
        /** Precondition: size() < CAPACITY
        *      Postcondition: A new copy of entry has been inserted in the sequence
        *      at the front. The new item is now the current item of the sequence. **/
    }

    void sequence::attach_back(const value_type& entry) {
        /** Precondition: size() < CAPACITY
        *      Postcondition: A new copy of entry has been inserted in the sequence
        *      at the back. The new item is now the current item of the sequence. **/
    }

    void sequence::remove_front() {
        /** Precondtion: isitem() returns true
        *      Postcondition: The item at the front of the sequence has been removed from the sequence,
        *      and the current item points at the front of the sequence. **/
       
    }

    void sequence::operator +=(const sequence& rhs) {
        /** Postcondition: Adds the items of rhs to the lhs. Also returns a copy of lhs.**/
    }

    //CONSTANT MEMBER FUNCTIONS
    sequence::size_type sequence::size() const {
        /** Postcondition: The return value is the number of items in the sequence. **/
    }

    bool sequence::is_item() const {
        /** Postcondition: A true return value indicates that there is a valid
        *     "current" item that may be retrieved by activating the current
        *     member function (listed below). A false return value indicates that
        *     there is no valid current item. **/

    }

    sequence::value_type sequence::current() const {
        /** Precondtion: isitem() returns true
        *      Poscondition: Returns the item in the sequence at the current position of the iterator. **/
    }

    sequence::value_type sequence::operator[](int index) const {
        /** Precondition: index < used
        *     Postcondition: The item returned is the item stored at "index" **/
    }

    double sequence::mean() const {
        /** Postcondition: The value returned is the mean of the values stored in the sequence. **/
    }

    double sequence::standardDeviation() const {
        /**Postcondition: The value returned is the stadard deviation of the values stored in the sequence. **/
    }

    //NON-MEMBER FUNCTIONS FOR SEQUENCE CLASS
    sequence operator +(const sequence& lhs, const sequence& rhs) {
        /**Postcondition: The sequence that is returned contains all the
        *     numbers of the sequences of lsh and rhs. **/
    }

    sequence::value_type summation(const sequence &s) {
        /** Postcondition: The value returned is the summation of the values stored in the sequence s. **/
    }
}