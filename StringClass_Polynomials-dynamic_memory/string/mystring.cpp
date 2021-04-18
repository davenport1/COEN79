//FILE: mystring.cpp
//CLASS IMPLEMENTED: string (see mystring.h for documentation)
//
// COEN 79
//  --- Matthew Davenport, COEN 79, SCU ---
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "mystring.h"
#include "assert.h"

namespace coen79_lab5 {
    string::string(const char str[ ]) {
        //default argument is empty string
        //Precondition: str is an ordinary null-terminated string.
        //Postcondition: The string contains the sequence of chars from str.
        current_length = strlen(str);
        allocated = current_length + 1;
        characters = new char[allocated];
        strncpy(characters, str, allocated);
    }

    string::string(char c) {
        //Postcondition: The string contains c and then the null character.
        current_length = 1;
        reserve(current_length);
        characters[0] = c;
        characters[1] = '\0';
    }

    string::string(const string& source) {
        //Postcondition: The string becomes a copy of the source string.
        current_length = 0;
        reserve(source.length());
        strncpy(characters, source.characters, allocated);

    }

    string::~string( ) {
        delete [] characters;
    }

    // MODIFICATION MEMBER FUNCTIONS
    void string::operator +=(const string& addend) {
        //Postcondition: addend has been catenated to the end of the string.
        current_length = current_length + addend.length();    //set the current
        reserve(current_length);
        strncat(characters, addend.characters, addend.length());
    }

    void string::operator +=(const char addend[ ]) {
        //Precondition: addend is an ordinary null-terminated string.
        //Postcondition: addend has been catenated to the end of the string.
        current_length = current_length + strlen(addend);                
        reserve(current_length);                                             
        strncat(characters, addend, strlen(addend)); 
    }

    void string::operator +=(char addend) {
        //Postcondition: The single character addend has been catenated to the
        //end of the string.
        reserve(++current_length);
        characters[current_length] = addend;
    }

    void string::reserve(size_t n) {
        //Postcondition: All functions will now work efficiently (without
        //     allocating new memory) until n characters are in the string.
        allocated = n + 1;
        if(current_length > 0) {
            char* temp = new char[allocated];
            strncpy(temp, characters, allocated);
            delete [] characters;
            characters = temp;
            return;
        }
        characters = new char[allocated];
    }

    string& string::operator =(const string& source) {
        current_length = source.current_length;
        reserve(current_length);
        strncpy(characters, source.characters, current_length);
        return *this;
    }
    void string::insert(const string& source, unsigned int position) {
        //Precondtion: position <= length()
        //Postcondition: The source string is inserted into this string before
        //     the character at the given index.
        assert(position < length());
        char* temp;
        if(position != length() - 1) {
            temp = new char[length() - position];
            for(int i = position, j = 0; i < length(); ++i, ++j) {
                temp[j] = characters[i];
            }
        }
        current_length += source.length();
        if(allocated <= current_length) {
            reserve(current_length);
        }
        strncpy(&characters[position], source.characters, source.length());
        if(temp != NULL) 
            strncat(&characters[position + source.length()], temp, strlen(temp));
    }
    void string::dlt(unsigned int position, unsigned int num) {
        //Precondition: (position + num) <= length( ).
        //Postcondition: num characters are deleted from the sequence, starting
        //     at index position.
        assert((position + num) <= length());
        string temp(this->characters);
        delete [] characters;
        allocated -= num;
        current_length = allocated - 1;
        characters = new char[allocated];
        for(int i = 0; i < position; ++i) {
            characters[i] = temp.characters[i];
        }
        for(int i = position; i < allocated; ++i) {
            characters[i] = temp.characters[i + num];
        }
        characters[allocated] = '\0';
    }
    void string::replace(char c, unsigned int position) {
        //Precondition: position < length()
        //Postcondtion: the character at the given position in the string is
        //     replaced with c.
        assert(position < length());
        characters[position] = c;
    }
    void string::replace(const string& source, unsigned int position) {
        //Precondition: (position + source.length()) <= length()
        //Postcondtion: the characters in this string starting at position are
        //     replaced with those in the source string.
        assert(position + source.length() <= length());
        string temp;
        temp.current_length = position + source.length();
        temp.reserve(temp.current_length);
        strncpy(temp.characters, characters, position);
        strncat(&temp.characters[position], source.characters, source.length());
        delete [] characters; 
        allocated = temp.allocated;
        current_length = temp.current_length;
        characters = temp.characters;
    }
    // CONSTANT MEMBER FUNCTIONS
    char string::operator [ ](size_t position) const {
        //Precondition: position < length( ).
        //Postcondition: The value returned is the character at the specified
        //     position of the string. A string's positions start from 0 at the start
        //     of the sequence and go up to length( )-1 at the right end.
        assert(position < length());
        return this->characters[position];
    }
    int string::search(char c) const {
        //Postcondition: The location of the first occurence of the character c
        //     within this string is returned. If the string does not contain c, -1 is
        //     is returned.
        for(int i = 0; i < length(); ++i) {
            if(characters[i] == c)
                return i;
        }
        return -1;
    }
    int string::search(const string& substring) const {
        //Returns the index of the start of the first instance of
        //     the given substring inside of this string. If the substring is not found,
        //     this function returns -1. 
        char firstChar = substring.characters[0];
        bool exists = false;
        for(int i = 0; i < length(); ++i) {
            if(characters[i] == firstChar) {
                exists = true;
                for(int j = 0, k = i; j < substring.length(); ++j, ++k) {
                        if(characters[k] != substring.characters[j]) 
                            exists = false;
                }
                if(exists == true) 
                    return i;
            }
        }
        return -1;
    }
    unsigned int string::count(char c) const {
        //Postcondition: The count of the occurence of the character c within this
        //     string is returned.
        unsigned int count = 0;
        for(int i = 0; i < length(); ++i) {
            if(characters[i] == c) 
                ++count;
        }
        return count;
    }

    // FRIEND FUNCTIONS
    std::ostream& operator <<(std::ostream& outs, const string& source) {
        //Postcondition: The sequence of characters in source has been written
        //     to outs. The return value is the ostream outs.
        outs << source.characters;
        
        return outs;
    }
    bool operator ==(const string& s1, const string& s2) {
        return strcmp(s1.characters, s2.characters) == 0;
    }
    bool operator !=(const string& s1, const string& s2) {
        return strcmp(s1.characters, s2.characters) != 0;
    }
    bool operator > (const string& s1, const string& s2) {
        return strcmp(s1.characters, s2.characters) > 0;
    }
    bool operator < (const string& s1, const string& s2) {
        return strcmp(s1.characters, s2.characters) < 0;
    }
    bool operator >=(const string& s1, const string& s2) {
        return strcmp(s1.characters, s2.characters) >= 0; 
    }
    bool operator <=(const string& s1, const string& s2) {
        return strcmp(s1.characters, s2.characters) <= 0; 
    }

    // NON-MEMBER FUNCTIONS for the string class
    string operator +(const string& s1, const string& s2) {
        string added;
        added += s1;
        added += s2;
        return added;
    }
    string operator +(const string& s1, const char addend[ ]) {
        string added;
        added += s1;
        added += addend;
        return added;
    }
    std::istream& operator >> (std::istream& ins, string& target) {
        //Postcondition: A string has been read from the istream ins, and the
        //     istream ins is then returned by the function. The reading operation
        //     skips white space (i.e., blanks, newlines, tabs) at the start of ins.
        //     Then the string is read up to the next white space or the end of the
        //     file. The white space character that terminates the string has not
        //     been read.
        while(ins && isspace(ins.peek())) {                      
            ins.ignore();
        }
        
        char* input = new char[100];                                                       
        ins >> input;                                                  
        target = input;                                        
        return ins;
    }

}

