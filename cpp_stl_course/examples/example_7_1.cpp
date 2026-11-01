// Kara Ottewell's STL Course
//
// Example 7.1                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Use map to implement a simple token database
//
// ---- A map as a token database read from a file ("example_7_1.cpp") ------

// C++ Standard Library Headers
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main( int argc, char *argv[] )
{
    size_t equalsPosition, position;
    size_t lineNumber = 0;
    ifstream tokenFile;
    string fileName, line, token, value;
    map< string, double > tokenData;
//  End of declarations ...

    if ( argc > 1 ) {
      fileName = argv[1];
    } else {
      fileName = "tokens.dat";
    }

//  Open the file for reading
    cout << "Opening data file: " << fileName << endl;
    tokenFile.open( fileName );
    if ( !tokenFile ) {
      cerr << "Cannot open " << fileName << endl;
      return( EXIT_FAILURE );
    }

//  Read each line and parse it; getline() is false at end of file
    while ( getline( tokenFile, line ) ) {
//    Parse out the tokens and values
      ++lineNumber;
      equalsPosition = line.find( '=' );
      if ( equalsPosition == string::npos ) {
        cerr << "Invalid Line " << lineNumber << ": " << line << endl;
        continue;
      }
//    The token is everything before the "=", without trailing spaces
      token = line.substr( 0, equalsPosition );
      position = token.find_last_not_of( " \t" );
      token.erase( position == string::npos ? 0 : position + 1 );

      value = line.substr( equalsPosition + 1 );
      position = value.find_first_of( "0123456789.+-" );
      if ( position != string::npos ) {
//      Store token and value; a later line with the same token replaces it
        value = value.substr( position );
        tokenData[token] = atof( value.c_str() );
      } else {
        cerr << "Bad value at line " << lineNumber << ": " << token << " =" << value << endl;
      }
    }

    if ( !lineNumber ) {
      cerr << "Invalid or empty file: " << fileName << endl;
    } else {
      map< string, double >::iterator mapIterator;
      for ( mapIterator = tokenData.begin(); mapIterator != tokenData.end(); ++mapIterator )
        cout << "\"" << mapIterator->first << "\"  = " << mapIterator->second << endl;

      cout << "Enter token name: ";
      getline( cin, token );

//    Use the find function so we can spot a "miss"
      mapIterator = tokenData.find( token );
      if ( mapIterator != tokenData.end() ) {
        cout << " Found \"" << mapIterator->first << "\"  = "
             << mapIterator->second << endl;
      } else {
        cout << "tokenData.find(...) shows no token matches \""
             << token << "\"" << endl;
        cout << "Lookup using tokenData[\""
             << token << "\"] would have given "
             << tokenData[token] << endl;
      }
    }

    return( EXIT_SUCCESS );
}
