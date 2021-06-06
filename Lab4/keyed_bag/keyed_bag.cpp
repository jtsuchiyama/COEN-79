// FILE: keyed_bag.cpp
// CLASS IMPLEMENTED: keyed_bag

// INVARIANTS for the keyed_bag class:
// The length represents the number of keys and values
// The number of keys and values should always be equal
// The index of the keys and values should correspond to each other
// When length = 0, there should be no keys nor values

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "keyed_bag.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4 {
    // Constructor 
    keyed_bag::keyed_bag() {
    // Initiates the private member variable with the approriate starting value
        erase();
    }

    // Modification member functions for the keyed_bag class
    void keyed_bag::erase() {
        length = 0;
    }

    bool keyed_bag::erase(const key_type &key) {
        if(has_key(key)) {
        // If the key is in keyed_bag, then remove key and its value
            for(size_type i=0;i<length;i++) {
                // Iterate through keys until the key is found
                if(keys[i] == key) {
                    for(size_type j=i+1;j<length;j++) {
                    // Iterate through both arrays to delete the key and its corresponding entry
                        keys[j-1] = keys[j];
                        data[j-1] = data[j];     
                    }
                    length--;
                    return true;
                }
            }
        }

        else
        // If the key is not in keyed_bag, then let it alone
            return false;
    }

    void keyed_bag::insert(const value_type &entry, const key_type &key) {
        assert(size() < CAPACITY); 
        assert(!has_key(key)); // Ensures that the keyed_bag does not contain the given key
        data[length] = entry;
        keys[length] = key;
        length++;
    }

    void keyed_bag::operator += (const keyed_bag &addend) {
        assert(size() + addend.size() <= CAPACITY);
        assert(!hasDuplicateKey(addend));
        size_type count = length; // Create a temporary length to dictate where the entry should be inserted
        for(size_type i=0;i<addend.length;i++) {
        // Iterate through the addend array
            data[count+i] = addend.data[i];
            keys[count+i] = addend.keys[i];
            length++;
        }
    }

    // Constant member functions for the keyed_bag class
    bool keyed_bag::has_key(const key_type &key) const {
        for(size_type i=0;i<length;i++) {
        // Iterate through the keys array
            if(keys[i] == key)
            // If the desired key is found, return true
                return true;
        }
        // If the desired key is not found, return false
        return false;
    }
    
    keyed_bag::value_type keyed_bag::get(const key_type &key) const {
        assert(has_key(key));
        for(size_type i=0;i<length;i++) {
        // Iterate through the key array
            if(keys[i] == key)
                return data[i];
        }
    }

    keyed_bag::size_type keyed_bag::size() const {
        return length;
    }

    keyed_bag::size_type keyed_bag::count(const value_type &target) const {
        size_type count = 0;
        for(size_type i=0;i<length;i++) {
        // Iterate through the entire data array
            if(data[i] == target)
            // If the target is found, then iterate the count
                count++;
        }
        return count;
    }

    bool keyed_bag::hasDuplicateKey(const keyed_bag &otherBag) const {
        for(size_type i=0;i<length;i++) {
        // Iterate through the first object
            for(size_type j=0;j<otherBag.length;j++) {
            // Iterate through the second object
                if(keys[i] == otherBag.keys[j])
                // If there is a duplicate key, return true
                    return true;    
            }
        }
        // If there is no duplicate key, return false
        return false;
    }

    // Non-member functions for the keyed_bag class
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2) {
        assert(b1.size() + b2.size() <= keyed_bag::CAPACITY);
        assert(!b1.hasDuplicateKey(b2));
        keyed_bag temp;
        temp += b1;
        temp += b2;
        return temp;
    }
}