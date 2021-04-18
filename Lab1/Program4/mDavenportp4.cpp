/**Problem4
 * @author Matthew Davenport
 * ask user to think of a number between 1 and 20
 * make successive guesses for the number and display the number of guesses needed
 **/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

//guessNum asks user to think of a number between 1 and 20 and guesses the number
int guessNum();

//driver
int main() {
    int numOfGuesses = guessNum();
    return 0;
}

/**guessNum
 * pre-conditions: 
 *  none
 * asks user to think of number between 1 and 20 and guesses for their number
 * counts number of guesses taken
 * post condition: 
 *      returns num of guesses needed once user inputs Y
 **/
int guessNum() {
    int numOfGuesses = 0;
    bool guessed = false;
    char userInp = ' ';
    int possibleNum[20];
    int nums = 1;
    //intitialize array of digits from 1 to 20
    for(int i = 0; i < 20; i++) {
        possibleNum[i] = nums;
        nums++;
    }
    cout << "Think of any number between 1 and 20. Please press enter once you are ready\n";
    cin.ignore();
    int i = 0;
    while(!guessed && i < 20) { 
        cout << "Is your number " << possibleNum[i] << " ? Y or N\n";
        char temp = getchar();
        //clear accidental multiple inputs
        while(temp!='\n') {
            temp = getchar();
        }
        cin >> userInp;
        //validate user input
        if(userInp != 'Y' && userInp != 'N') {
            cout << "Please enter a valid input of Y for yes or N for no\n";
            cin >> userInp;
        }
        //if user input acceptable, increment to continue to step through array
        else if(userInp == 'Y') {
            guessed = true;
            i++;
            numOfGuesses++;
        }
        else {
            i++;
            numOfGuesses++;
        }

    }
    if(!guessed) {
        cout << "We have a cheater!\n";
    }
    else {
        cout << "I guessed your number in " << numOfGuesses << " guesses! Thanks for playing!\n";
    }
    return numOfGuesses;
}