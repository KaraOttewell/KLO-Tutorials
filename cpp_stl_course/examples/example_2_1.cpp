// Kara Ottewell's STL Course
//
// Example 2.1                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Demonstrate simple function template
//
// ---- A function template, and a "real" function ("example_2_1.cpp") -------

// C++ Standard Library Headers
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// Template function
template <class T>
T MyMin( T firstValue, T secondValue )
{
   return( (firstValue < secondValue) ? firstValue : secondValue );
}

// "Real" function
double MyMin( double firstValue, double secondValue )
{
// Here be found Porkies !!
   return( (firstValue > secondValue) ? firstValue : secondValue );
//                     ^
//                     |
//                     Wrong sign just to show which function is being called
}

int main()
{
    string firstString("yo"), secondString("boys"), stringMinimum;
    int firstInteger = 123, secondInteger = 456, integerMinimum;
    double firstDouble = 3.1415926535898, secondDouble = 1.6180339887499, doubleMinimum;
//  End of declarations ...

    integerMinimum = MyMin( firstInteger, secondInteger );
    cout << "Minimum of " << firstInteger << " and " << secondInteger
         << " is " << integerMinimum << endl;

    stringMinimum = MyMin( firstString, secondString );
    cout << "Minimum of " << firstString << " and " << secondString
         << " is " << stringMinimum << endl;

    doubleMinimum = MyMin( firstDouble, secondDouble );
    cout << "$ SET PORKY/ON" << endl;
    cout << "Wrong answer if \"real\" MyMin called instead of template" << endl;
    cout << "Minimum of " << firstDouble << " and " << secondDouble
         << " is " << doubleMinimum << endl;

    return( EXIT_SUCCESS );
}
