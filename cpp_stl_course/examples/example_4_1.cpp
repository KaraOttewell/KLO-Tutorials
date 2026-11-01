// Kara Ottewell's STL Course
//
// Example 4.1                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Demonstrate use of stack container adaptor
//
// ---- A stack adapter on a vector ("example_4_1.cpp") ----------------------

// C++ Standard Library Headers
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main()
{
    stack< const char *, vector<const char *> > wordStack;

//  Push on stack in reverse order
    wordStack.push("order");
    wordStack.push("correct"); // Oh no it isn't !
    wordStack.push("the");
    wordStack.push("in");
    wordStack.push("is");
    wordStack.push("This");

//  Pop off stack which reverses the push() order
    while ( !wordStack.empty() ) {
      cout << wordStack.top() << " "; wordStack.pop(); // Oh yes it is !
    }
    cout << endl;

    return( EXIT_SUCCESS );
}
