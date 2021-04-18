/**Program1 
 *  Will take user's inputted text and count number of alphanumberic
 *        and non-alphanumeric characters
 * Outputs number of both alphanumeric and non-alphanumeric characters
 * 
**/

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

int main() {
    string userIn = ""; //string to hold input string
    int alnum = 0;  //int to hold alphanumerics
    int nonAlnum = 0;   //int to hold non-alphanumerics

    //take input
    cout << "Please input something";
    cout << endl;
    getline(cin,userIn); //take input from user

    //get number of characters in string and convert to character array
    int n = userIn.length();

    //for loop to iterate through char array and count characters
    for(int i = 0; i < n; i++) {
        if(isalnum(userIn[i])) {
            alnum++;
        }
        else if(!isalnum(userIn[i]) && userIn[i] != ' ') {
            nonAlnum++;
        }

    }
    cout << endl;
    cout << left << setw(20) << "Alphanumerics: " << alnum << endl; 
    cout << left << setw(20) << "Non-alphanumerics: " << nonAlnum << endl; 

}