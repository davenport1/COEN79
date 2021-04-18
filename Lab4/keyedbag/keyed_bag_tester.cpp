//
//  COEN 79
//  
//

#include <iostream>
#include "keyed_bag.h"

using namespace std;
using coen79_lab4::keyed_bag;

void Insert(const int val, const string& key, keyed_bag& kb) {
    cout << "Inserting "<<val<<" with key \""<<key<<"\"." << endl;
    kb.insert(val, key);
}

void Erase(const string& key, keyed_bag& kb) {
    cout << "Erasing \""<< key <<"\"." << endl;
    kb.erase(key);
}

void Get(const string & key, const keyed_bag& kb) {
    cout << "Value for \""<<key<<"\": " << kb.get(key) << endl;
}

void Has(const string & key, const keyed_bag& kb) {
    cout << "Has "<<key<<": " << kb.has_key(key) << endl;
}

void Count(const int val, const keyed_bag& kb) {
    cout << "Number of "<< val <<"'s in the bag: " << kb.count(val) << endl;
}

void bSize(const keyed_bag& kb) {
    cout << "Bag size: " << kb.size() << endl;
}

int main(int argc, char const *argv[]) {
    keyed_bag kb1, kb2, kb4;

    Insert(5,"five",kb1);
    Insert(3,"three",kb1);
    Insert(1,"one",kb1);

    Get("one", kb1);
    Get("three", kb1);
    Get("five", kb1);

    Has("five", kb1);
    Has("two", kb1);

    bSize(kb1);
    Erase("five", kb1);
    bSize(kb1);
    Has("five", kb1);
    Has("three", kb1);

    Insert(-8, "neg_eight", kb1);
    bSize(kb1);
    Has("neg_eight", kb1);
    Get("neg_eight", kb1);
    Count(9, kb1);
    Count(1, kb1);
    Insert(1, "ONE", kb1);
    Count(1, kb1);
    Insert(7,"seven",kb1);
    Insert(9,"nine",kb1);
    Insert(11,"eleven",kb1);
    bSize(kb1);
    Erase("eleven",kb1);
    bSize(kb1);
    Erase("ONE",kb1);
    bSize(kb1);

    // Do some stuff with bag 2.


    // BEGIN STUDENT TESTING


    keyed_bag kb5, kb6;
    //following code attempts to insert 32 values into the bag and fails assertion
    //fails as expected
    /* while(true) {
        try
        {
            int i = 0;
            char count = 'a';
            for(int j = 0; j < 31; ++j) {
                string s{count};
                Insert(j, s, kb2);
                ++count;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "out of bounds passed" << '\n';
        }
        
    } */

    //following code attemps to add to the end of one bag too many elements from another bag
    //fails as expected
    /* while(true) {
        try
        {
            
            char count = 'a';
            for(int j = 0; j < 16; ++j) {
                string s{count};
                Insert(j, s, kb2);
                ++count;
            }
            count = 'a';
            for(int j = 0; j < 16; ++j) {
                string s{count};
                Insert(j, s, kb4);
                ++count;
            }

            kb2 += kb4; //should fail based on too many elements to be moved into kb2 of capacity 31

        }
        catch(const std::exception& e)
        {
            std::cerr << "out of bounds passed" << '\n';
        }
        
    } */
    cout << endl;
    cout << "Begin student testing: " << endl << endl;
    cout << "Passes test trying to insert too many elements and adding too many elements (see comments)" << endl;
    Insert(8, "eight", kb2);
    Insert(2, "two", kb2);
    Insert(9, "nine", kb2);
    Insert(7, "seven", kb2);
    
    cout << "has eight: (should be true)" << kb2.has_key("eight") << endl; //pass
    cout << "has four: (should be false)" <<kb2.has_key("four") << endl; //fail
    cout << "whitespace: (should be false)" << kb2.has_key(" ") << endl; //fail

    Insert(1, "one", kb2);
    cout << "Has a duplicate? (should be true): " << kb2.hasDuplicateKey(kb1) << endl;
    Erase("one",kb2);
    Erase("seven",kb2);
    Erase("nine",kb2);
    cout << "Has a duplicate? (should be false): " << kb2.hasDuplicateKey(kb1) << endl;
    cout << "Has a duplicate? (no elements in second bag): " << kb2.hasDuplicateKey(kb5) << endl;
    Insert(2, "another_two", kb2);
    Count(2, kb2);
    Erase("two", kb2);
    Count(2, kb2);

    
    cout << endl << "Testing with two empty bags: " << endl;
    
    cout << "Has a duplicate? (should be false): " << kb5.hasDuplicateKey(kb6) << endl;
    
    bSize(kb5);
    Has("fakekey", kb5);
    Count(5, kb5);
    //Passes Assertion Get("fakekey", kb5);
    //Passes assertion Erase("fakekey", kb5);
    Insert(1, "one", kb5);
    Insert(2, "two", kb5);
    bSize(kb5);
    kb5.erase();
    cout << "If size = 0, kb5 has been erased: "; bSize(kb5);
    kb5 += kb2; //testing += 
    //kb5 should have been concatenated with kb2
    cout <<"kb2 has been concatenated to kb5 which is empty before += operator" << endl;
    
    cout << "Has two (should be true): " << kb5.has_key("another_two") << endl; //passes
    cout << "Passes test trying to get/erase element that does not exist" << endl;

    cout << endl << "End student testing" << endl << endl;




    //END STUDENT TESTING 

    



    // Testing add.
    keyed_bag kb3;
    kb3 = kb1+kb2;
    bSize(kb3);
    Has("1",kb3);
    Has("one",kb3);
    Has("turkey",kb3);
    Count(1,kb3);
    Count(9,kb3);
    Count(-5,kb3);
    Get("three",kb3);
    cout << "Erasing all of kb2." << endl;
    kb2.erase();
    bSize(kb2);
    Insert(22,"I'm feelin'", kb2);
    Get("I'm feelin'", kb2);

    return 0;
}
