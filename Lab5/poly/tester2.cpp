// FILE: polytest0.cxx
// An Interactive test program for the polynomial ADT
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//


#include <cctype>          // Provides toupper
#include <iostream>        // Provides cout and cin
#include <cstdlib>         // Provides EXIT_SUCCESS
#include "poly.h"         // Provides the polynomial class

#include "polygif.cpp"

using namespace std;
using namespace coen79_lab5;

const unsigned int MANY = 3; // Number of polynomials allowed in this test program.


// PROTOTYPES for functions used by this test program:
void print_menu();
// Postcondition: The menu has been written to cout.

size_t set_current( );
// Postcondition: Return value is index for a new current polynomial.

char get_command();
// Postcondition: The user has been prompted for a character.
// The entered charatcer will be returned, translated to upper case.

void view(const polynomial& test);
//Postcondition:  The polynomial passed has been sent to cout.

void view_all(const polynomial a[]);
//Postcondition:  All polynomials has been written to cout.

void test_add(polynomial& test);
// Postcondition: The user has been prompted for a coefficent and degree of
// the term added.  The resulting polynomial has been written to cout.

void test_assign(polynomial& test);
// Postcondition: The user has been prompted for the degree and the coeffinient
// to be set.  The resulting polynomial has been written to cout.

void test_clear(polynomial& test);
// Postcondition: test.clear( ) has been activated.
// to be set.  The resulting polynomial has been written to cout.

void test_gif(const polynomial& test);
// Postcondition:  The user has been prompted for the range of the gif file.
// The gif file of the graph of the polynomial has been written to disk.

void test_eval(const polynomial& test);
// Post conditon:  The user has been prompted for the x value.  The evaluation
// of the polynomial is written to cout.

void test_np(const polynomial& test);
// Post conditon:  The user has been prompted for the e value.  The
// value of test.next_term(e) and test.previous_term(e) are written to cout.

void test_anti(const polynomial& test);
// Post condition: the antiderivative with a constant C = 0 is displayed
// for the current polynomial 

void test_definite_integral(const polynomial& test);
// Post condition: the definite integral is calculated  with the bounds of the given 
// values from the user

void test_copy_constructor(const polynomial& test);
// Post condition: The passed polynomial is copied to a new polynomial and displayed

void test_assignment(const polynomial& test);
// Post condition: New polynomial created using the assignment operator with the 
// current polynomial




int main()
{
    polynomial p[MANY];
    size_t current_index = 0;
    char command;
    size_t i;

    cout << "Polynomials ";
    for (i = 0; i < MANY; ++i)
	cout << char('A' + i) << ' ';
    cout << "have all been initialized." << endl;

    do
    {
        print_menu();
        command = toupper(get_command());

        switch(command)
        {
	case 'S':  current_index = set_current( );
	    break;
	case '1':  test_assign(p[current_index]);
	    break;
	case '2':  test_add(p[current_index]);
	    break;
	case 'C':  test_clear(p[current_index]);
	    break;
	case 'V':
	    cout << char(current_index + 'A') << ": ";
	    view(p[current_index]);
	    break;
	case 'A':  view_all(p);
	    break;
	case 'D':
	    cout << char(current_index + 'A') << ".derivative: ";
	    view(p[current_index].derivative( ));
	    break;
	case 'E':  test_eval(p[current_index]);
	    break;
	case 'G':  test_gif(p[current_index]);
	    break;
	case 'N':  test_np(p[current_index]);
	    break;
	case '+':
	    cout << "A + B: ";
	    view(p[0] + p[1]);
	    break;
	case '-':
	    cout << "A - B: ";
	    view(p[0] - p[1]);
	    break;
	case '*':
	    cout << "A * B: ";
	    view(p[0] * p[1]);
	    break;
    case 'M':
        test_assignment(p[current_index]);
        break;
    case 'O':
        test_copy_constructor(p[current_index]);
        break;
    case 'F':
        test_anti(p[current_index]);
        break;
    case 'I':
        test_definite_integral(p[current_index]);
        break;
	case 'Q':  // Do nothing..
	    break;
	default:   cout << "Invalid command." << endl;
	    break;
        }
    }
    while(command != 'Q');

    return (EXIT_SUCCESS);
}

void print_menu()
{
    cout << "----------------- The Commands -----------------" << endl;
    cout << "S - set the current Polynomial to work on" << endl;
    cout << "  -   -   -   -   -   -   -   -   -   -   -   -" << endl;
    cout << "1 - use the assign_coef function" << endl;
    cout << "2 - use the add_to_coef function" << endl;
    cout << "C - use the clear function" << endl;
    cout << "V - view the current polynomial by using <<" << endl;
    cout << "A - view all polynomials by using <<" << endl;
    cout << "D - view derivative of current polynomial" << endl;
    cout << "E - evaluate current polynomial by using () op" << endl;
    cout << "G - use the gif function" << endl;
    cout << "N - use the next_term and previous_term functions" << endl;
    cout << "+ - view A + B" << endl;
    cout << "- - view A - B" << endl;
    cout << "* - view A * B" << endl;
    cout << "M - test assignment operators\n";
    cout << "O - test copy constructor with current polynomial\n";
    cout << "F - calculate the antiderivative of the current polynomial\n";
    cout << "I - calculate the definite integral of the current polynomial with given bounds\n";
    cout << "  -   -   -   -   -   -   -   -   -   -   -   -" << endl;
    cout << "Q - quit this interactive test program" << endl;
    cout << "-------------------------------------------------" << endl;
}

char get_command()
{
    char command;

    cout << ">";
    cin >> command;

    return(toupper(command));
}

void view(const polynomial& test)
{
    cout << test
	 << " (degree is " << test.degree( ) << ")" << endl;
}

size_t set_current( )
{
    size_t i;
    char command;
    
    do
    {
	cout << "Polynomials ";
	for (i = 0; i < MANY; ++i)
	    cout << char('A' + i) << ' ';
	cout << "." << endl;
	cout << "Enter the polynomial you want to work on: ";
	command = toupper(get_command());
    }
    while ((command < 'A') || (command >= char('A' + MANY)));
    return command - 'A';
}

void test_add(polynomial& test)
{
    double coefficient;
    unsigned int exponent;

    cout << "Enter exponent: ";
    cin >> exponent;
    cout << "Enter coefficient: ";
    cin >> coefficient;

    test.add_to_coef(coefficient, exponent);
    cout << "After adding: ";
    view(test);
}

void test_assign(polynomial& test)
{
    double coefficient;
    unsigned int exponent;

    cout << "Enter exponent: ";
    cin >> exponent;
    cout << "Enter coefficient: ";
    cin >> coefficient;

    test.assign_coef(coefficient, exponent);
    cout << "After assigning: ";
    view(test);
}

void test_gif(const polynomial& test)
{
    char file_name[20];
    double high_x, low_x, high_y, low_y;

    cout << "Enter file name to write: ";
    cin >> file_name;
    cout << "Enter upper x bound: ";
    cin >> high_x;
    cout << "Enter lower x bound: ";
    cin >> low_x;
    cout << "Enter upper y bound: ";
    cin >> high_y;
    cout << "Enter lower y bound: ";
    cin >> low_y;

    make_gif(test, file_name, low_x, high_x, low_y, high_y);
    cout << "The file has been written" << endl;
}

void test_eval(const polynomial& test)
{
    double x_value;
    cout << "Enter the x value: ";
    cin >> x_value;

    cout << "For the poly: ";
    view(test);
    cout << "The evaluation returned is " << test(x_value) << endl;
}

void view_all(const polynomial p[])
{
    size_t i;
    
    cout << endl;

    for (i = 0; i < MANY; ++i)
    {
	cout << char(i + 'A') << ": ";
	view(p[i]);
    }
}


void test_clear(polynomial& test)
{
    test.clear( );
    cout << "After clearing: ";
    view(test);
}

void test_np(const polynomial& test)
{
    unsigned int exponent;

    cout << "Enter exponent: ";
    cin >> exponent;

    cout << "For polynomial: ";
    view(test);
    cout << "next_term(" << exponent << ") = "
	 << test.next_term(exponent) << endl;
    cout << "previous_term(" << exponent << ") = "
	 << test.previous_term(exponent) << endl;
}

void test_anti(const polynomial& test) {
    cout << "Anti-derivative of current polynomial ";
    view(test.antiderivative());
}

void test_definite_integral(const polynomial& test) {
    int x1, x0 = 0;
    cout << "Enter the bounds you would like to evaluate the integral at: \n";
    cout << "Upper bound: "; cin >> x1; cout << endl;
    cout << "Lower bound: "; cin >> x0; cout << endl;
    cout << test.definite_integral(x0,x1) << endl;
}

void test_copy_constructor(const polynomial& test) {
    polynomial temp(test);
    cout << "Copy of current is : " << temp << endl;
    cout << "Should be: " << test << endl;
}

void test_assignment(const polynomial& test) {
    char choice;
    double num = 0;
    polynomial assign;
    cout << "Test assignment with double or current polynomial? (D/P) \n";
    do {
        cin.ignore();
        cin >> choice;
        switch(choice) {
            case 'D': 
                cout << "Enter the double you'd like to assign: "; cin >> num; cout << endl;
                assign = num;
                cout << "Polynomial assigned is: " << assign << cout << endl;
                cout << "Should be:              " << num    << cout << endl;
                break;
            case 'P':
                assign = test;
                cout << "Polynomial assigned is: " << assign << cout << endl;
                cout << "Should be:              " << test    << cout << endl;
                break;
            default: cout << "Invalid command." << endl;
                break;                
        }
    }   while(choice != 'D' && choice != 'P');
}
