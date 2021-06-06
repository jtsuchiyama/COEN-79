// FILE: sequence1.cpp
// CLASS IMPLEMENTED: sequence

// INVARIANTS for the sequence class:
//    If the sequence is empty, then the count = 0
//    The count represents the number of entries in the sequence
//    The iterator is the index of the current item, which can be used to perform actions on the sequence
//    The capacity of the sequence is 50

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "sequence1.h"
#include <math.h>

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3 {
    sequence::sequence() {
    // Initiates the private member variables with appropriate values
        iterator = 0;
        count = 0;
    }

    void sequence::start() {
        iterator = 0;
    }

    void sequence::end() {
        iterator = count - 1;
    }

    void sequence::last() {
        iterator = CAPACITY - 1;
    }

    void sequence::advance() {
        assert(is_item());
        if (iterator < count)
        // Ensures the iterator is not at the end of the sequence
            iterator++;
    }

    void sequence::retreat() {
        if (iterator != 0)
        // Ensures the iterator is not at the beginning of the sequence
            iterator --;
    }

    void sequence::insert(const value_type &entry) {
        assert(size() < CAPACITY);
        if (count == 0) {
        // If the sequence is empty, insert at the front
            array[0] = entry;
            iterator = 0; 
        }

        else {  
        // If the sequence is not empty, then perform shifts and insert
            for(sequence::size_type i=count;i>iterator;i--) {
            // Shifts the items to make room for entry
                array[i] = array[i-1];
                cout << array[i] << "\n";
            }
            array[iterator] = entry;
        }
        count++;
    }

    void sequence::attach(const value_type &entry) {
        assert(size() < CAPACITY);
        if (!is_item()) {
        // If there is no current item, then attach to the end 
            array[count] = entry;
        }

        else {
        // If there is a current item, then performs shifts and attach
            for(sequence::size_type i=count-1;i>iterator;i--) {
                array[i+1] = array[i];
            }
            array[iterator+1] = entry;
            iterator++;
        }
        count++;
    }

    void sequence::remove_current() {
        assert(is_item());
        for(sequence::size_type i=iterator;i<count;i++)
        // Performs the shifts which delete the current entry
            array[i] = array[i+1];

        count--;
    }

    void sequence::insert_front(const value_type &entry) {
        assert(size() < CAPACITY);
        iterator = 0;
        insert(entry);
    }

    void sequence::attach_back(const value_type &entry) {
        assert(size() < CAPACITY);
        iterator = count;
        array[count] = entry;
        count++;
    }

    void sequence::remove_front() {
        assert(is_item());
        for(sequence::size_type i=1;i<count;i++) {
        // Performs the shift which deletes the front entry
            array[i-1] = array[i];
        }
        count--;
    }

    void sequence::operator += (const sequence &rhs) {
        assert(count + rhs.count <= CAPACITY);
        sequence::size_type rhs_count = rhs.count;
        for(sequence::size_type i=0;i<rhs_count;i++) {
        // Iterates through rhs and adds its entries to array[]
            array[count+i] = rhs.array[i];
            count++;
        }
    }

    sequence::size_type sequence::size() const {
        return count;
    }

    bool sequence::is_item() const {
        if(iterator < count)
        // Checks if the current item is valid
            return true;
        else
            return false;
    }

    sequence::value_type sequence::current() const {
        assert(is_item());
        return array[iterator];
    }

    sequence::value_type sequence::operator [] (int index) const {
        assert(index < count);
        return array[index];
    }

    double sequence::mean() const {
        double sum = 0;
        for(sequence::size_type i=0;i<count;i++) {
        // Iterates through array[] to calculate the sum
            sum += array[i];
        }
        return sum / count;
    }

    double sequence::standardDeviation() const {
        double sum = 0;
        for(sequence::size_type i=0;i<count;i++) {
        // Squares the difference of the entry and mean and sums it
            sum += pow(array[i]-mean(),2);
        }
        sum /= count;
        return sqrt(sum);
    }

    sequence operator + (const sequence &lhs, const sequence &rhs) {
        assert(lhs.size() + rhs.size() <= sequence::CAPACITY);
        sequence temp;
        temp += lhs;
        temp += rhs;
        return temp;
    }

    sequence::value_type summation(const sequence &s) {
        sequence::value_type sum = 0;
        for (sequence::size_type i=0;i<s.size();i++) {
        // Iterates through s to calculate the sum
            sum += s[i];
        }
        return sum;
    }
}