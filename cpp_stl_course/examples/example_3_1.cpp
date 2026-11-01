// Kara Ottewell's STL Course
//
// Example 3.1                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Demonstrate use of a vector
//
// ---- Some of the vector access functions in use ("example_3_1.cpp") -------

// C++ Standard Library Headers
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

// Print every element, then the size, using an iterator
void PrintVector( const char *title, const vector<int> &values )
{
    cout << title << ": ";
    for ( vector<int>::const_iterator valueIterator = values.begin();
          valueIterator != values.end(); ++valueIterator )
      cout << *valueIterator << " ";
    cout << " [size() = " << values.size() << "]" << endl;
}

int main()
{
    const int years[] = { 1975, 1969, 1983, 1979, 1971 };
    vector<int> values;
//  End of declarations ...

    cout << "empty() is " << (values.empty() ? "true" : "false") << " to start with" << endl;

//  push_back() adds to the end, growing the vector as needed
    for ( int year : years )
      values.push_back( year );
    PrintVector( "After push_back()", values );

//  sort() takes a range: begin() up to, but not including, end()
    sort( values.begin(), values.end() );
    PrintVector( "After sort()", values );

//  [] and at() give random access; only at() checks the index
    cout << "values[1] = " << values[1] << ", values.at(2) = " << values.at(2) << endl;
    try {
      cout << values.at( 99 ) << endl;
    } catch ( const out_of_range & ) {
      cout << "values.at(99) threw out_of_range" << endl;
    }

//  insert() in the middle shuffles the later elements along, O(N)
    values.insert( values.begin() + 2, 1974 );
    PrintVector( "After insert() at position 2", values );

//  erase() in the middle shuffles them back again
    values.erase( values.begin() );
    PrintVector( "After erase() of the first", values );

//  pop_back() destroys the last element, cheaply
    values.pop_back();
    PrintVector( "After pop_back()", values );

//  reserve() makes room in advance; capacity() is at least size()
    values.reserve( 100 );
    cout << "After reserve(100), capacity() is at least " << values.capacity() << endl;

    values.clear();
    PrintVector( "After clear()", values );

    return( EXIT_SUCCESS );
}
