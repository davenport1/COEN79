/**Program 2
 * Will take a string of 10 numbers and reverse the string
 * prints the string and reversed string 5 times each in the 
 *      correct format
**/

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    string str = "";    //hold user input
    string reversed = "";   //reversed user input

    cout << "Please type a string of 10 digits (0 to 9) with no space" << endl; 
    cin >> str; //get input
    int n = str.length();

    //validate user inputted exactly 10 digits
    if(n!=10) {
        while(n!=10) {
            cout << "Please ensure that the string you entered is 10 digits!" << endl;
            cin >> str;
            n = str.length();
        }
    }
    int k = n -1; 

    //assign reversed the reversed characters of the user input
    for(int i = 0; i < n; i++) {
        reversed = reversed + str[k];
        k--;
    }
    //display the original string and reversed string in required format
    for(int i = 0; i < 5; i++) {
        if (i == 0) { //no spaces nescessary on first iteration
            cout << setw(15) << left << str << reversed << endl;
        }
        else {
            //put required spaces in front of the output based on iteration of output loop
            for(k = 0; k < i; k++) {
                cout << " ";
            }
            cout << setw(15) << left << str << reversed << endl;
        }

    }
}