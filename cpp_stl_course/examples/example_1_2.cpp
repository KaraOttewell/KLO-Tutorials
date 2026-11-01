// Kara Ottewell's STL Course
//
// Example 1.2                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Simple vector and sort demonstration using the STL
//
// ---- Expanding, sorted integer array using the STL ("example_1_2.cpp") -----

// C++ Standard Library Headers
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int inputValue;
    int itemCount = 0;
    vector<int> values;

    cout << "Enter integers, <Enter> after each, <Ctrl>Z <Enter> to finish:" << endl;

//  The stream converts to false at end of file, or at anything not a number
    while ( cin >> inputValue ) {
      values.push_back( inputValue );
      cout.width(6);
      cout << itemCount << ": " << values[itemCount] << endl;
      ++itemCount;
    }

    if ( itemCount ) {
      sort( values.begin(), values.end() );
      for ( vector<int>::const_iterator valueIterator = values.begin();
            valueIterator != values.end(); ++valueIterator )
        cout << *valueIterator << " ";
      cout << endl;
    }

    return( EXIT_SUCCESS );
}
