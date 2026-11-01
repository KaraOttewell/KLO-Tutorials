// Kara Ottewell's STL Course
//
// Example 7.2                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Demonstrate the use of a set.
//
// ---- Sets, and the set algorithms ("example_7_2.cpp") ---------------------

// C++ Standard Library Headers
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <set>

using namespace std;

// Function object comparing the strings that two pointers point at. Without
// it, the set would sort the pointers themselves, by address.
struct LessThanString
{
  bool operator()( const char *first, const char *second ) const
  { return strcmp( first, second ) < 0; }
};

int main()
{
  const char *namesA[] = { "Gray", "Pete", "Oggy", "Karen", "JAF", "Simon", "Nick",
                           "Elliott", "Roy", "David", "Tony", "Nigel" };
  const char *namesB[] = { "Sandy", "John", "Andrzej", "Rob", "Kara", "Happy",
                           "Elliott", "Roy", "David", "Tony", "Nigel" };

  set<const char *, LessThanString> setA( begin(namesA), end(namesA) );
  set<const char *, LessThanString> setB( begin(namesB), end(namesB) );
  set<const char *, LessThanString> setC;

  cout << "Set A: ";
  copy( setA.begin(), setA.end(), ostream_iterator<const char *>( cout, " " ) );
  cout << endl;
  cout << "Set B: ";
  copy( setB.begin(), setB.end(), ostream_iterator<const char *>( cout, " " ) );
  cout << endl;

  cout << "Union: ";
  set_union( setA.begin(), setA.end(), setB.begin(), setB.end(),
             ostream_iterator<const char *>( cout, " " ), LessThanString() );
  cout << endl;

  cout << "Intersection: ";
  set_intersection( setA.begin(), setA.end(), setB.begin(), setB.end(),
                    ostream_iterator<const char *>( cout, " " ), LessThanString() );
  cout << endl;

  set_difference( setA.begin(), setA.end(), setB.begin(), setB.end(),
                  inserter( setC, setC.begin() ), LessThanString() );
  cout << "Set C (difference of A and B, i.e. in A but not B): ";
  copy( setC.begin(), setC.end(), ostream_iterator<const char *>( cout, " " ) );
  cout << endl;

  setC.clear(); // Empty setC before using it again
  set_symmetric_difference( setA.begin(), setA.end(), setB.begin(), setB.end(),
                            inserter( setC, setC.begin() ), LessThanString() );
  cout << "Set C (symmetric difference of A and B,"
          " i.e. in A OR B but not both): ";
  copy( setC.begin(), setC.end(), ostream_iterator<const char *>( cout, " " ) );
  cout << endl;

  return( EXIT_SUCCESS );
}
