// Kara Ottewell's STL Course
//
// Example 8.2                  © Kara Ottewell 2026
//
// Purpose:
//          Demonstrate lambda expressions as the predicates, comparisons
//          and actions that algorithms need
//
// ---- Lambda expressions with the algorithms ("example_8_2.cpp") ----------

// C++ Standard Library Headers
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

void PrintYears( const char *title, const vector<int> &years )
{
    cout << title << ":";
    for ( int year : years ) cout << " " << year;
    cout << endl;
}

int main()
{
    vector<int> years = { 1969, 1975, 1979, 1983, 1971, 1997, 2001, 1996 };
    const int cutOff = 1997;
    int total = 0;
//  End of declarations ...

    PrintYears( "Years", years );

//  find_if with a lambda: the first year after cutOff. [cutOff] captures the
//  variable by value so the lambda can use it. This replaces the old
//  find_if( ..., bind2nd( greater<int>(), 1997 ) ), removed in C++17.
    auto found = find_if( years.begin(), years.end(),
                          [cutOff]( int year ) { return year > cutOff; } );
    if ( found != years.end() )
      cout << "First year after " << cutOff << ": " << *found << endl;

//  count_if with a lambda predicate
    auto seventiesCount = count_if( years.begin(), years.end(),
                                    []( int year ) { return year >= 1970 && year < 1980; } );
    cout << "Years in the 1970s: " << seventiesCount << endl;

//  sort with a lambda comparison, newest first; greater<>() would do the same
    sort( years.begin(), years.end(), []( int first, int second ) { return first > second; } );
    PrintYears( "Newest first", years );

//  for_each with a lambda that captures total by reference, so it can change it
    for_each( years.begin(), years.end(), [&total]( int year ) { total += year; } );
    cout << "Total " << total << ", and accumulate() agrees: "
         << accumulate( years.begin(), years.end(), 0 ) << endl;

//  remove_if shuffles the unwanted years to the end and returns where they
//  start; erase() then gets rid of them (the "erase-remove idiom")
    years.erase( remove_if( years.begin(), years.end(),
                            []( int year ) { return year < 1975; } ),
                 years.end() );
    PrintYears( "Without the years before 1975", years );

    return( EXIT_SUCCESS );
}
