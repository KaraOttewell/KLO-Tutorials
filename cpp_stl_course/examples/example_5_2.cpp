// Kara Ottewell's STL Course
//
// Example 5.2                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Transform an arithmetic expression into reverse Polish
//          notation, substitute symbols and evaluate.
//
// ---- An expression evaluator using strings, stacks and a map ("example_5_2.cpp")

// C++ Standard Library Headers
#include <cctype>
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

// Function prototypes
string FormatNumber( double value );
double PerformOperation( char operation, double firstOperand, double secondOperand );
int Precedence( char operation );

int main( int argc, char *argv[] )
{
    size_t position;
    double firstOperand, secondOperand;
    char nextCharacter;
    string expression, item;
    stack< string > outputStack;      // Reverse Polish order, last item on top
    stack< string > operatorStack;    // Operators waiting to go on outputStack
    stack< string > evaluationOrder;  // outputStack turned over, first item on top
    stack< double > operandStack;     // Values waiting for an operator
    map< string, double > symbolValues;
//  End of declarations ...

//  Set a few built-in symbols (CODATA 2018 values)
    symbolValues["pi"] = 3.14159265358979;
    symbolValues["c"]  = 299792458.0;        // Speed of light, m/s (exact)
    symbolValues["e"]  = 1.602176634e-19;    // Electron charge, Coulombs (exact)
    symbolValues["me"] = 9.1093837015e-31;   // Electron rest mass, kg
    symbolValues["mp"] = 1.67262192369e-27;  // Proton rest mass, kg
    symbolValues["mn"] = 1.67492749804e-27;  // Neutron rest mass, kg

    if ( argc < 2 ) {
      cout << "Enter expression: ";
      getline( cin, expression );
    } else {
      expression = argv[1]; // Use expression from command line if given
    }

//  Junk everything except alphanumerics, decimal points, brackets and operators
    position = 0;
    while ( position < expression.length() ) {
      nextCharacter = expression.at( position );
      if ( isspace( (unsigned char)nextCharacter ) ||
           ( !isalnum( (unsigned char)nextCharacter ) && !Precedence( nextCharacter ) &&
             nextCharacter != '.' && nextCharacter != '(' && nextCharacter != ')' ) ) {
        expression.erase( position, 1 );
      } else {
        ++position;
      }
    }
    if ( expression.empty() ) {
      cout << "Bye" << endl;
      return( EXIT_SUCCESS );
    }

//  Add space as an end of expression marker and to allow final pass thru loop
    expression += " ";

//  Process the expression, moving operators to outputStack in precedence order
    while ( !expression.empty() ) {
      nextCharacter = expression.at( 0 );
      if ( nextCharacter == '(' ) {
        operatorStack.push( expression.substr( 0, 1 ) ); // Push '(' onto operator stack
        expression.erase( 0, 1 );

      } else if ( nextCharacter == ')' ) {
        while ( !operatorStack.empty() ) { // If right bracket loop until left bracket reached
          item = operatorStack.top(); operatorStack.pop();
          if ( item.at( 0 ) == '(' ) {
            break;
          } else {
            outputStack.push( item );
          }
        }
        expression.erase( 0, 1 );

      } else if ( !Precedence( nextCharacter ) ) {
//      If not brackets or operator stick value or variable on stack
        position = expression.find_first_of( "^*/+-() " );
        if ( position == string::npos ) position = expression.length();
        item = expression.substr( 0, position );
        outputStack.push( item ); // Push value string onto stack
        expression.erase( 0, position );

      } else {
//      nextCharacter is an operator, or the space at the end
        while ( true ) {
          if ( operatorStack.empty() ) {
            operatorStack.push( expression.substr( 0, 1 ) );
            break;
          }

          item = operatorStack.top(); operatorStack.pop();
//        ^ works right to left, so 2^3^2 is 2^(3^2): a ^ never pushes out an earlier ^
          if ( item.at( 0 ) == '(' || Precedence( nextCharacter ) > Precedence( item.at( 0 ) ) ||
               ( nextCharacter == '^' && item.at( 0 ) == '^' ) ) {
            operatorStack.push( item );
            operatorStack.push( expression.substr( 0, 1 ) );
            break;
          } else {
            outputStack.push( item );
          }
        }
        expression.erase( 0, 1 );
      }
    }

//  Turn outputStack over, so the first item to evaluate is on top
    while ( !outputStack.empty() ) {
      evaluationOrder.push( outputStack.top() ); outputStack.pop();
    }

//  Now evaluate, using operandStack to hold values until we meet an operator
    cout << "Reverse Polish:";
    while ( !evaluationOrder.empty() ) {
      item = evaluationOrder.top(); evaluationOrder.pop();
      cout << " " << item;
      nextCharacter = item.at( 0 );
      if ( item.length() == 1 && Precedence( nextCharacter ) ) {
        if ( operandStack.empty() ) {
          cout << endl << "Operator " << item << " has nothing to work on" << endl;
          return( EXIT_FAILURE );
        }
//      A leading minus has only one value to work on: -5 means 0 - 5
        secondOperand = operandStack.top(); operandStack.pop();
        firstOperand = 0.0;
        if ( !operandStack.empty() ) {
          firstOperand = operandStack.top(); operandStack.pop();
        }
        operandStack.push( PerformOperation( nextCharacter, firstOperand, secondOperand ) );
      } else if ( isdigit( (unsigned char)nextCharacter ) || nextCharacter == '.' ) {
        operandStack.push( atof( item.c_str() ) ); // A number
      } else {
        operandStack.push( symbolValues[item] );   // Not oper or number, must be a symbol
      }
    }
    cout << endl;

    if ( operandStack.size() != 1 ) {
      cout << "That doesn't look like a complete expression" << endl;
      return( EXIT_FAILURE );
    }
    cout << "Result: " << FormatNumber( operandStack.top() ) << endl;

    return( EXIT_SUCCESS );
}

string FormatNumber( double value )
{
//  Show as many significant digits as a double reliably holds
    ostringstream formatted;
    formatted << setprecision( DBL_DIG ) << value;
    return( formatted.str() );
}

int Precedence( char operation )
{
//  Returns the precedence of an operator, or 0 if it isn't a known operator
//  Known Operators: " ","+","-","*","/","^"
//                    |                   |
//                  Do nothing           Raise to power

    if ( operation == '^' ) return( 4 );
    if ( operation == '*' || operation == '/' ) return( 3 );
    if ( operation == '+' || operation == '-' ) return( 2 );
    if ( operation == ' ' ) return( 1 );
    return( 0 ); // Not operator
}

double PerformOperation( char operation, double firstOperand, double secondOperand )
{
//  Return the result of performing the required operation on the operands.

    if ( operation == '^' ) return( pow( firstOperand, secondOperand ) );
    if ( operation == '*' ) return( firstOperand * secondOperand );
    if ( operation == '/' ) return( firstOperand / secondOperand );
    if ( operation == '+' ) return( firstOperand + secondOperand );
    if ( operation == '-' ) return( firstOperand - secondOperand );
    return( 0.0 ); // Invalid operator
}
