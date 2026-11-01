// Kara Ottewell's STL Course
//
// Example 5.1                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Demonstrate use of standard string class
//
// ---- The string class in use ("example_5_1.cpp") --------------------------

// C++ Standard Library Headers
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    size_t position;
    string needle = "needle";     // Initialize with C style string literal
    string line("my string");     // Ditto
    string haystack(line,3,6);    // Initialize with another string, line,
                                  // starting at element 3, i.e. "string"
    string firstTwo(line,0,2);    // Initialize with first 2 characters of
                                  // line, i.e. "my"
    string firstString;           // INITIALIZING with a single character, e.g.
    string secondString;          // = 'A' or ('A'), or with an integer, is
                                  // NOT ALLOWED - use string(1,'A') instead.
                                  // These will currently have .length() of zero
    string dashes(80,'-');        // You can initialize using a character like
                                  // this, and character ASSIGNMENT is legal

    char oldCString[64];

//  Concatenation using + operator
    firstString = "Now is the Winter ";
    secondString = "of our discontent made Summer";
    cout << "firstString = \"" << firstString << "\", secondString = \"" << secondString << "\"\n"
         << "firstString + secondString = \"" << firstString + secondString << "\"" << endl
         << dashes << endl;

//  Find a substring in a string
    haystack = "Where is that " + needle + ", eh ?";
    cout << "haystack = \"" << haystack << "\"" << endl;
    position = haystack.find(needle);
//  Use substr function to get substring - use string::npos (the "too large"
//  character count) to get the rest of the string
    cout << "position = haystack.find(needle) found \""
         << haystack.substr(position,string::npos)
         << "\" at position " << position << endl << dashes << endl;

//  Demonstrate use of Algorithms with strings
    line = "a man a Plan a canal Panama";
    cout << line << " [Algorithm: reverse(line.begin(),line.end())]" << endl;
    reverse( line.begin(), line.end() );
    cout << line << " [line.length() = " << line.length() << "]" << endl
         << dashes << endl;

//  Passing a string to a function requiring a C style string
    line = "copyright";
    strncpy( oldCString, line.c_str(), sizeof(oldCString)-1 );
    oldCString[sizeof(oldCString)-1] = '\0';
    cout << "strncpy \"" << line << "\" to C string which now contains \""
         << oldCString << "\"" << endl << dashes << endl;

//  Insert into a string
    firstString = "piggy middle";
    secondString = "in the ";
    cout << "firstString = \"" << firstString << "\", secondString = \"" << secondString << "\"" << endl;
    firstString.insert(6,secondString); // Insert secondString in firstString
    cout << "firstString.insert(6,secondString) = " << firstString << endl << dashes << endl;

//  Erase
    cout << "[Use firstString.erase(position,4) to get rid of \"the \"]" << endl;
    position = firstString.find("the");
    if ( position != string::npos ) firstString.erase( position, 4 ); // Note check on ::npos
    cout << firstString << endl << dashes << endl;

//  Replace
    cout << "[Use firstString.replace(position,2,\"is not in the\") to replace "
         << "\"in\" with \"is not in the\"]" << endl;
    position = firstString.find("in");
//  Note inequality check on string::npos to see if search string was found
    if ( position != string::npos ) firstString.replace( position, 2, "is not in the" );
    cout << firstString << endl << dashes << endl;

    return( EXIT_SUCCESS );
}
