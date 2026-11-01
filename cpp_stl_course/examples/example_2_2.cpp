// Kara Ottewell's STL Course
//
// Example 2.2                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Demonstrate simple class template
//
// ---- A class template with a type and a size ("example_2_2.cpp") ----------

// C++ Standard Library Headers
#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

template <class T, int Capacity>
class MyVector
{
  public:
    MyVector() : maximumSize( Capacity ), usedCount( 0 ), objectList( new T[ Capacity ] ) {}
    ~MyVector() { delete [] objectList; }

//  Copying would leave two MyVectors deleting the same objectList, so
//  forbid it (the "rule of three": a class that needs a destructor
//  usually needs its own copy constructor and copy assignment too)
    MyVector( const MyVector & ) = delete;
    MyVector &operator=( const MyVector & ) = delete;

    void Append( const T &newObject ) { if ( usedCount < maximumSize )
                                          objectList[usedCount++] = newObject; }

    T &operator[]( int index )
    {
       if ( index < 0 || index >= usedCount ) {
         throw out_of_range( "up" ); // barf on error
       }
       return( objectList[index] );
    }

  private:
    int maximumSize;
    int usedCount;
    T *objectList;
};

int main()
{
    const int maximumElements = 10;
    MyVector< int, maximumElements > karasList;
//  End of declarations ...

//  Populate the list
    for ( int i = 0; i < maximumElements; i++ )
      karasList.Append( i );

//  Print out the list
    for ( int i = 0; i < maximumElements; i++ )
      cout << karasList[i] << " ";

    cout << endl;

    return( EXIT_SUCCESS );
}
