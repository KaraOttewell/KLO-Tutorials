// Kara Ottewell's STL Course
//
// Example 6.1                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Demonstrate input and output iterators from and to a file
//
// ---- Stream iterators writing and reading a file ("example_6_1.cpp") ------

// C++ Standard Library Headers
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main()
{
    const int numbers[] = { 1,3,5,7,11,13,17,19 };
    vector<int> writtenValues( begin(numbers), end(numbers) );
    vector<int> readValues;
//  End of declarations ...

//  Write writtenValues to the file through an output iterator
    ofstream outputFile( "vector.dat" );
    copy( writtenValues.begin(), writtenValues.end(), ostream_iterator<int>( outputFile, " " ) );
    outputFile.close();
    cout << "Wrote vector writtenValues to file vector.dat" << endl;

//  Read it back into readValues through an input iterator
    ifstream inputFile( "vector.dat" );
    copy( istream_iterator<int>( inputFile ),  // Start of inputFile
          istream_iterator<int>(),             // Value that means end of file
          back_inserter( readValues ) );       // Adds each value with push_back()

    cout << "Read vector readValues from file vector.dat" << endl;
    for ( vector<int>::const_iterator valueIterator = readValues.begin();
          valueIterator != readValues.end(); ++valueIterator )
      cout << *valueIterator << " ";
    cout << endl;

    return( EXIT_SUCCESS );
}
