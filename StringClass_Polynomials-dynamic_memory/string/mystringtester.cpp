//FILE: mystringtester.cpp
// Small demo of my string because the other one fucks my shit up
//
// COEN 79
//  ---  Matthew Davenport, COEN79, SCU ---     
//

#include <iostream>
#include "mystring.h"
#include <cstdlib>

using namespace coen79_lab5;

void displayString(const string& str) {
    std::cout << "String is: " << str << std::endl;
}


int main() {
    string string1;
    string string2("String Example");
    string string3('a');
    string string4(string2);
    string string5 = string2;
    std::cout << string2 << std::endl; std::cout << string2.length() << std::endl;
    std::cout << string4 << std::endl;

    if(string2 == string4)
        std::cout << string2 << " is equal to " << string4 << std::endl;
    else
        std::cout << string2 << " is not equal to " << string4 << std::endl;

    if(string2 == string3)
        std::cout << string2 << " is equal to " << string3 << std::endl;
    else
        std::cout << string2 << " is not equal to " << string3 << std::endl;
    
    std::cout << string5 << std::endl;
    string1.insert(string2, 0);
    std::cout << string1 << std::endl;
    string1.insert(string2, string1.length());
    std::cout << string1 << std::endl;

    string1 += string2;
    std::cout << string1 << std::endl;
    
    string2 += 'f';
    string2 += 'f';
    std::cout << string2 << std::endl;
    string2 += string1;
    std::cout << string2 << std::endl;

    char* charArr = new char[10];
    for(int i = 0; i < 10; ++ i) {
        charArr[i] = 'a';
    }

    string5 += "aaaaaaaaaa";
    std::cout << string5 << std::endl;
    string5.dlt(14, 10);
    std::cout << string5 << std::endl;
    string5.dlt(2, 2);
    std::cout << string5 << std::endl;

    std::cout << "E at: " << string5.search('E') << std::endl;
    std::cout << "Z? " << string5.search('Z') << std::endl;

    string string6("Another Test");
    std::cout << string6 << std::endl;
    string string7("no");
    string6.replace(string7 , 8);
    std::cout << string6 << std::endl;
    string6.replace(string7 , 0);
    std::cout << string6 << std::endl;

    string string8;
    std::cout << "enter your first name: " << std::endl; 
    std::cin >> string8;
    std::cout << string8 << std::endl;
    std::cout << "enter last name: " << std::endl; 
    string string9;
    std::cin >> string9;
    std::cout << string9 << std::endl;

    string BLANK(" ");
    std::cout << "BLANK initialized" << std::endl;
    std::cout << BLANK.length() << std::endl;
    std::cout << BLANK << std::endl;

    string string10;
    string10 += string8;
    string10 += BLANK;
    string10 += string9;
    std::cout << string10 << std::endl;

    string string11("abcabcabc");
    displayString(string11);
    std::cout << "a's: " << string11.count('a') << std::endl;
    std::cout << "b's: " << string11.count('b') << std::endl;
    std::cout << "c's: " << string11.count('c') << std::endl;
    std::cout << "d's: " << string11.count('d') << std::endl;

    string string12;
    
    string12 = string8;
    std::cout << "after assignment, " << string12  << "should be  " << string8 << std::endl;
    string12 = string12 + string9;
    displayString(string8);
    displayString(string9);
    displayString(string12);
    
    std::cout << "Now chaining 3 together: " << std::endl;
    string string13 = string8 +     BLANK + string9;
    displayString(string13);

    std::cout << "Now testing adding array of characters(cstring) to string: " << std::endl;
    string string14 = string8 + " " + "dave";
    std::cout << string14 << std::endl;


    std::cout << "Search testing: \n";
    string searchtest1("Search Test");
    string falsetest1("flyz");
    string falsetest2("earhg");
    string truetest1("a");
    string truetest2("Tes");
    string nulltest;

    std::cout << "Search test 1 (false):       " << searchtest1.search(falsetest1) << std::endl;
    std::cout << "Search test 2 (false):       " << searchtest1.search(falsetest2) << std::endl;
    std::cout << "Search test 3 (true):        " << searchtest1.search(truetest1) << std::endl;
    std::cout << "Search test 4 (true):        " << searchtest1.search(truetest2) << std::endl;
    std::cout << "Search test 5 (false: null): " << searchtest1.search(nulltest) << std::endl;
    

    std::cout << "Testing  relational operators: \n";
    string equalstring1("equal");
    string equalstring2("equal");
    if(equalstring1 == equalstring2)
        std::cout <<"Passed" << std::endl;
    else
        std::cout <<"Failed" << std::endl;

    std::cout << "Type in 'equal' " << std::endl;
    string inputstring;
    std::cin >> inputstring;
    displayString(inputstring);
    if(inputstring == equalstring2)
        std::cout <<"Passed" << std::endl;
    else
        std::cout <<"Failed" << std::endl;
    string equalstring3;
    equalstring3.insert(equalstring2, 0);
    if(equalstring3 == equalstring2)
        std::cout <<"Passed" << std::endl;
    else
        std::cout <<"Failed" << std::endl;

    string equalstring4;
    equalstring4 += 'e';
    equalstring4 += 'q';
    equalstring4 += 'u';
    equalstring4 += 'a';
    equalstring4 += 'l';

    string equalstring5;
    equalstring5 += "equal";

    if(equalstring4 == equalstring2)
        std::cout <<"Passed" << std::endl;
    else
        std::cout <<"Failed" << std::endl;

    if(equalstring4 == equalstring2)
        std::cout <<"Passed" << std::endl;
    else
        std::cout <<"Failed" << std::endl;

    return 0;
}

