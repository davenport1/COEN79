//
// main.cpp
// PROVIDES: A test file for deque and its iterator
//
// COEN 79


#include <iostream>
#include "deque.h"

using namespace coen79_lab8;

int main(int argc, const char * argv[]) {
    //construct two empty deques for testing
    coen79_lab8::deque<int> testdeque1, testdeque2;
    
    std::cout << "--- Two empty deques constructed ---" << std::endl;

    //begin push_back tests, 0 - 20
    std::cout << std::endl << "--- Testing push_back ---" << std::endl;
    for(int i = 0; i < 21; ++i) {
        testdeque1.push_back(i);
        std::cout << testdeque1.back();
    }
    //begin push_front tests, 0 - 20
    std::cout << std::endl << "--- Testing push_front ---" << std::endl;
    for(int i = 1; i < 21; ++i) {
        testdeque1.push_front(i);
        std::cout << testdeque1.front();
    }
    
    //testing copy constructor and assignment operator, first with empty deques
    std::cout << std::endl << "--- Testing copy and assignment with empty deques ---" << std::endl;
    coen79_lab8::deque<int> emptydeque;
    coen79_lab8::deque<int> copyofemptydeque(emptydeque);
    coen79_lab8::deque<int> assignedemptydeque = emptydeque;
    //ensure tht the deques t
    if(copyofemptydeque.isEmpty()) 
        std::cout << "Copying an empty deque passed\n";
    else 
        std::cout << "Copied empty deque contains something!\n";
    if(assignedemptydeque.isEmpty()) 
        std::cout << "Assigning an empty deque passed\n";
    else   
        std::cout << "Assigned empty deque contains something!\n";
    
    std::cout << std::endl << "--- Testing copy constructor and iterator ---" << std::endl;
    coen79_lab8::deque<int> copieddeque(testdeque1);
    testdeque2 = testdeque1;
    std::cout << "Copied testdeque 1\n";
    std::cout << std::endl << "Contents of testdeque 1 using iterator: ";
    for(deque<int>::iterator it = testdeque1.begin(); it != testdeque1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl << "Contents of copy of testdeque 1:        ";
    for(deque<int>::iterator it = copieddeque.begin(); it != copieddeque.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl << "Contents of deque assigned testdeque 1: ";
    for(deque<int>::iterator it = testdeque2.begin(); it != testdeque2.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "\n --- Testing poping from front and back --- \n";
    for(int i = 1; i < 4; ++ i) {
        testdeque1.pop_front();
        copieddeque.pop_front();
        testdeque2.pop_front();
        testdeque1.pop_back();
        copieddeque.pop_back();
        testdeque2.pop_back();
    }

    std::cout << std::endl << "Contents of testdeque 1 using iterator: ";
    for(deque<int>::iterator it = testdeque1.begin(); it != testdeque1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl << "Contents of copy of testdeque 1:        ";
    for(deque<int>::iterator it = copieddeque.begin(); it != copieddeque.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl << "Contents of deque assigned testdeque 1: ";
    for(deque<int>::iterator it = testdeque2.begin(); it != testdeque2.end(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << std::endl;
    std::cout << "\n --- Testing iterator dereferencing and conditionals --- \n";
    deque<int> testdeque3;
    std::cout << "Contents of testdeque3: ";
    for(int i = 17; i > -18; --i) {
        testdeque3.push_back(i);
        std::cout << testdeque3.back() << " ";
    }
    std::cout << std::endl;

    deque<int>::iterator it1 = testdeque1.begin();
    deque<int>::iterator it2 = copieddeque.begin();
    deque<int>::iterator it3 = testdeque3.begin();
    bool is_equal = true;
    while(it1 != testdeque1.end() && it2 != copieddeque.end()) {
        if(*it1 != *it2)
            is_equal = false;
        ++it1;
        ++it2;
    }
    if(is_equal) 
        std::cout << "Passed, the two deques are equal\n\n";
    else
        std::cout << "Failed\n\n";
    std::cout << "Now testing two unequal deques\n";
    it1 = testdeque1.begin();
    while(it1 != testdeque1.end() && it3 != testdeque3.end()) {
        if(*it1 != *it3) {
            is_equal = false;
        }
        ++it1;
        ++it3;
    }
    if(!is_equal) 
        std::cout << "Passed, the two deques are not equal\n\n";
    else   
        std::cout << "Failed\n\n";

    it1 = testdeque1.begin();
    it2 = testdeque1.begin();
    if(it1 == it2) 
        std::cout << "Iterators are equal\n";
    else
        std::cout << "Failed equality test\n";
    while(it1 != testdeque1.end() && it2 != testdeque1.end()) {
        ++it1;
        ++it2;
    }
    if(!(it1 != it2)) 
        std::cout << "Iterators stayed equal\n";
    else
        std::cout << "Failed\n";
        
}
