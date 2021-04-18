/** Problem 3
 * @author Matthew Davenport
 * read in each line from a txt file
 * if 10 alpha-characters or longer: 
 *      convert to uppercase, and print to screen 
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

//readFromFile recieves vector of strings and string file name and inputs lines from file into vector
void readFromFile(vector<string> &inputs, string fileName);
//modifyInput revieves vector of lines from file and empty vector. inputs modified lines into empty vector
void modifyInputs(vector<string> &inputs, vector<string> &outputs);
//outputMod will recieve a vector of modified strings and display them
void outputMod(const vector<string> &outputs);

//driver
int main(int argc, char* argv[]) {
    vector<string> inputs;  //capture lines from read file
    vector<string> outputs;     //stores strings of 10 alnum chars to output
    string filePath = argv[1];

    readFromFile(inputs,filePath);  //pass filePath in form of string, and empty input vectors by reference
    
    modifyInputs(inputs,outputs);   //pass vector of strings read from file, and empty vector for outputs by reference

    outputMod(outputs); // pass outputs as a const vector by reference to output strings of 10 alnum chars


    return 0;
}

/** readFromFile
 * pre conditions: 
 *      passed a vector of strings by referece and filePath in form of a string
 * post conditions
 *      reads file lines into strings and adds them to the vector of inputs
 *       
 * will read each line in the file, and input the string into the vector
 **/
void readFromFile(vector<string> &inputs,string filePath) {
    string input = ""; //hold line read from file
    ifstream tfile(filePath);   //open txt file
    if(!tfile.is_open()) {
        cout << "Could not open file!\n"; 
        exit(50);
    }
    //while next line is not NULL, read entire line into string input and push onto vector
    while(getline(tfile, input )) {
        if(input.size() > 0) {
            inputs.push_back(input);
        }
    }
    tfile.close();//close file
}

/** modifyInputs
 * pre conditions:
 *      passed a vector of strings by reference containing inputs from read file
 *      passed an empty vector of strings by reference to hold the converted
 *          strings to output
 * will test each line for strings containing 10 or more alphabetical characters
 * adds all strings=10 or more alpha chars to output vector in uppercase
 * post conditions: 
 *      modifies strings in the inputs vector that matches pre conditions
 * **/

void modifyInputs(vector<string> &inputs, vector<string> &outputs) {
    int n = 0;
    string current = "";
    int alphaChar = 0;
    string mod = "";

    //iterate through each element of the inputs vector.
    for(auto i = inputs.begin(); i < inputs.end(); i++) {
        current = *i;
        //iterate through each character of the current inputs element
        for(auto i2 = current.cbegin(); i2 != current.cend(); i2++) {
            //test if current char is alpha, if it is, append it onto the string
            if(isalpha(*i2)) {
                alphaChar++;
                mod += *i2;
            }
            //if current char is a space, or if at end of string, reset counter and mod string
            //  if the last mod string was 10+ alpha chars, push string onto the outputs vector
        
            if(*i2 == ' '|| i2 + 1 == current.cend()) {
                if(mod.length() > 9) {
                    transform(mod.begin(), mod.end(), mod.begin(), ::toupper);
                    outputs.push_back(mod);
                }
                mod = "";
                alphaChar = 0;
            } 
        }
        mod = "";
        alphaChar = 0;
    }
}

/**outputMod
 * pre-conditions: 
 *      passed const vector of strings by reference to display on the screen
 * post conditions: 
 *      vector of outputs has been displayed 
 **/
void outputMod(const vector<string> &outputs) {
    for(auto i = outputs.begin(); i < outputs.end(); i++) {
        cout << *i << endl; 
    }
}