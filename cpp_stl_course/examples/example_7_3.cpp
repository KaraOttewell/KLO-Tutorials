// Kara Ottewell's STL Course
//
// Example 7.3                  © Kara Ottewell 2026
//
// Purpose:
//          Demonstrate an unordered_map (a hash table), and compare its
//          order with a map's
//
// ---- Counting words with an unordered_map ("example_7_3.cpp") -------------

// C++ Standard Library Headers
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
    const string quotation = "Bring out your dead. I'm not dead. Yes he is. I'm not dead yet.";
    unordered_map< string, int > wordCounts;   // Hash table: in no particular order
    istringstream words( quotation );
    string word;
//  End of declarations ...

//  Read word by word, folding to lower case and dropping punctuation
    while ( words >> word ) {
      string cleanWord;
      for ( char character : word ) {
        if ( isalpha( (unsigned char)character ) || character == '\'' )
          cleanWord += (char)tolower( (unsigned char)character );
      }
//    [] adds a word it hasn't seen before with a count of 0, then ++ counts it
      if ( !cleanWord.empty() ) ++wordCounts[cleanWord];
    }

//  auto works out the type, and [wordText, count] unpacks each pair
    cout << "In the unordered_map's own (hash) order, which may vary:" << endl;
    for ( const auto &[wordText, count] : wordCounts )
      cout << "  " << wordText << " " << count << endl;

//  Copy into a map to see the same words in key order
    map< string, int > sortedCounts( wordCounts.begin(), wordCounts.end() );
    cout << "In a map, sorted by key:" << endl;
    for ( const auto &[wordText, count] : sortedCounts )
      cout << "  " << wordText << " " << count << endl;

//  Use count() or find() to ask without adding, as [] would
    if ( wordCounts.count( "parrot" ) == 0 )
      cout << "No \"parrot\": this parrot is no more" << endl;

    return( EXIT_SUCCESS );
}
