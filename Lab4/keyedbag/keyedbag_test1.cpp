//
//  COEN 79 Lab4
//  Matthew Davenport test for Lab Partner 
// 

#include <iostream>
#include "keyed_bag.h"
#include <string>

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
    keyed_bag kb1, kb2, kb3;
    cout << "Testing insert:\n\n" << "Positive tests:\n";
    Insert(5,"five",kb1);
    Insert(4,"four",kb1);
    Insert(6,"six",kb1);
    cout << endl;
    Insert(1,"one",kb2);
    Insert(3,"three",kb2);
    Insert(2,"two",kb2);
    cout << "Negative test:\n:";
    try
    {
        int i = 0;
        char count = 'a'; 
        
        for(int j = 0; j < 31; ++j) {
            std::string s
            Insert(i, s, kb3);
            ++i;
            if(count == 'z') {
                count = 'a';
            }
            ++count;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    


}