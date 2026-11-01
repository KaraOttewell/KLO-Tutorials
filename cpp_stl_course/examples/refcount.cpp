// Kara Ottewell's STL Course
//
// RefCount supplementary example     © Kara Ottewell 1997-2026
//
// Purpose:
//         Shows how copy assignment and copy constructors work with containers
//
// ---- Watching containers copy and destroy objects ("refcount.cpp") --------

// C++ Standard Library Headers
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

// Every MyClass copied from the same original shares one reference count.
// Because MyClass declares its own copy constructor, copy assignment and
// destructor, the compiler does not give it move operations, so when the
// vector grows it copies the elements across rather than moving them.
class MyClass {
public:
    MyClass()
    {
        referenceCount = new int;
        *referenceCount = 1;
        cout << "MyClass Constructor: Refcount = " << *referenceCount
             << " for pointer " << referenceCount << " this = " << this << endl;
    }

    // Copy constructor
    MyClass( const MyClass &mc )
    {
        // Don't use the Copy Assignment in here !
        referenceCount = mc.referenceCount;
        ++*referenceCount;
        cout << "MyClass Copy Constructor: Refcount = " << *referenceCount
             << " pointer " << referenceCount << " this = " << this << endl;
    }

    // Copy assignment
    MyClass & operator =( const MyClass &mcRHS )
    {
        // Avoid self-assignment
        if ( this != &mcRHS ) {
            cout << "MyClass Copy Assignment: Refcount = " << *referenceCount
                 << " before re-assignment for pointer " << referenceCount
                 << " this = " << this << endl;
            if ( 0 == --*referenceCount ) {
                // If no one else is referencing current value of LHS before
                // assignment it can safely be destroyed
                cout << "MyClass Copy Assignment: Deleted pointer" << endl;
                delete referenceCount;
            }
            // Copy RHS to LHS
            referenceCount = mcRHS.referenceCount;
            // Increase reference count
            ++*referenceCount;
        }
        cout << "MyClass Copy Assignment: Refcount = " << *referenceCount
             << " pointer " << referenceCount << " this = " << this << endl;
        return( *this );
    }

    ~MyClass()
    {
        if ( 0 == --*referenceCount ) {
            // Can destroy object's sub parts if no more references
            cout << "MyClass Destructor: Deleted pointer data for pointer "
                 << referenceCount << " this = " << this
                 << " because it had 0 references" << endl;
            delete referenceCount;
        } else {
            cout << "MyClass Destructor: Refcount = " << *referenceCount
                 << " pointer " << referenceCount << " this = " << this
                 << " after decrement" << endl;
        }
    }
private:
    int *referenceCount;
};

int main()
{
    MyClass myTemp;
    vector<MyClass> values;

    // Initialize the vector with values
    cout << "Add some myTemps to vector ..." << endl;
    for ( int j = 0; j < 3; j++ ) {
        values.push_back( myTemp );
    }
    cout << "Erase myTemps from vector ..." << endl;
    while ( !values.empty() ) {
        values.erase( values.begin() );
    }

    cout << "End of program - destructors should come soon ..." << endl;
    return( EXIT_SUCCESS );
}
