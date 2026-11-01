// Kara Ottewell's STL Course
//
// Example 3.3                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Demonstrate list container
//
// ---- Finding and inserting in a list ("example_3_3.cpp") ------------------

// C++ Standard Library Headers
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>

using namespace std;

int main()
{
    const string names[] = { "JAF", "ROB", "KARA", "ELLIOTT", "ANDRZEJ" };
    list< string > staffList;
    list< string >::iterator staffIterator;
//  End of declarations ...

    for ( const string &name : names ) staffList.push_back( name );
    for ( staffIterator = staffList.begin(); staffIterator != staffList.end(); ++staffIterator )
      cout << *staffIterator << endl;

//  Find "ELLIOTT"
    cout << "\nNow look for ELLIOTT" << endl;
    staffIterator = find( staffList.begin(), staffList.end(), "ELLIOTT" );

//  Mary should be ahead of Elliott
    if ( staffIterator != staffList.end() ) {
      cout << "\nInsert MARY before ELLIOTT" << endl;
      staffList.insert( staffIterator, "MARY" );
    } else {
      cout << "\nCouldn't find ELLIOTT" << endl;
    }
    for ( staffIterator = staffList.begin(); staffIterator != staffList.end(); ++staffIterator )
      cout << *staffIterator << endl;

    return( EXIT_SUCCESS );
}
