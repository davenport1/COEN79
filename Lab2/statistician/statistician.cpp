// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

//#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;

namespace coen79_lab2
{
    //CONSTRUCTOR
    statistician::statistician() {
        /**Postcondition: The object has been initialized, and is ready to accept
            *   a sequence of numbers. Various statistics will be calculated about the
            *    sequence. **/
        total = 0;
        size = 0;
        min = 0;
        max = 0;
        avg = 0;
    }
    statistician::statistician(double t, int s, double mi, double ma, double mean) {
        total = t;
        size = s;
        min = mi;
        max = ma;
        avg = mean;
    }

    //PUBLIC MODIFICATION MEMBER FUNCTIONS
    void statistician::next(double r) {
        /** Post condition: The number r has been given to the statistician as the next number in
            *     its sequence of numbers. **/
            if(size == 0) { //if no values are held in statistician, initialize all values with r
                total = r;
                min = r;
                max = r; 
                avg = r;
                size++;
            }
            else {
                total += r;
                size++;
                if(r > max) { //set max and min to their proper values depending on the new value r
                    max = r; 
                }
                if(r < min) {
                    min = r;
                }
                avg = (total/size); //calculate average
            }
    }
    
    
    void statistician::reset() {
        /** Postcondition: The statistician has been cleared, as if no numbers had
            *     yet been given to it. **/
        total = 0;
        size = 0;
        min = 0;
        max = 0;
        avg = 0;
    }

    //CONSTANT MEMBER FUNCTIONS
    int statistician::length() const {
        /** Postcondition: The return value is the length of the sequence that has
         *     been given to the statistician (i.e., the number of times that the
         *     next(r) function has been activated). **/
        return size;
    }

    double statistician::sum() const {
        /** Postcondition: The return value is the sum of all the numbers in the        
         *     statistician's sequence. **/
        return total;
    }

    double statistician::mean() const {
        /** Precondition: length( ) > 0
         *      Postcondition: The return value is the arithmetic mean (i.e., the
         *      average of all the numbers in the statistician's sequence). **/
        return avg;
    }

    double statistician::minimum() const {
        /** Precondition: length( ) > 0
         *      Postcondition: The return value is the tiniest number in the
         *      statistician's sequence. **/
        return min;
    }

    double statistician::maximum() const {
        /** Precondition: length( ) > 0
         *      Postcondition: The return value is the largest number in the
         *      statistician's sequence. **/
        return max;
    }

    //NON-MEMBER FUNCTIONS FOR STATISTICIAN CLASS
    statistician operator +(const statistician& s1, const statistician& s2) {
        /** Postcondition: The statistician that is returned contains all the
         *      numbers of the sequences of s1 and s2. **/
        double total = (s1.sum() + s2.sum());
        int size = (s1.length() + s2.length());
        double min;
        double max;
        //assign minimums and maximums based on the mins and maxes of s1 and s2
        if(s1.minimum() < s2.minimum()) { 
            min = s1.minimum();
        }
        else {
            min = s2.minimum();
        }
        if(s1.maximum() > s2.maximum()) {
            max = s1.maximum();
        }
        else {
            max = s2.maximum();
        } //end max and min ifs

        //calculate new average
        double avg = (total/size);
        //use 2nd constructor to return new statistician object
        statistician newStats(total, size, min, max, avg);
        return newStats;
    }

    statistician operator *(double scale, const statistician& s) {
        /** Postcondition: The statistician that is returned contains the same
         *      numbers that s does, but each number has been multiplied by the
         *      scale number. **/
        double total = (s.sum()*scale);
        int size = s.length(); //size remains the same
        double min = (s.minimum() * scale);
        double max = (s.maximum() * scale);
        double temp; //temporary variable for potential min max switch
        //if statement for min/max switch if multiplied by a negative number
        if(min > max) {
            temp = min; 
            min = max; 
            max = temp;
        }
        //calculate average and return new stats object with recalculated values
        double avg = (total/size);
        statistician newStats(total, size, min, max, avg);
        return newStats;
    }

    bool operator ==(const statistician& s1, const statistician& s2) {
        /** Postcondition: The return value is true if s1 and s2 have the zero
         *      length. Also, if the length is greater than zero, then s1 and s2 must
         *      have the same length, the same  mean, the same minimum, 
         *      the same maximum, and the same sum. **/
        //will return true if size is zero, since all other values will be 0 as well.
        return(s1.sum() == s2.sum() && s1.length() == s2.length() && s1.maximum() == s2.maximum()
                         && s1.minimum() == s2.minimum() && s1.mean() == s2.mean());
    }

}


