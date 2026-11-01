// Kara Ottewell's STL Course
//
// Example 8.1                  © Kara Ottewell 1997-2026
//
// Purpose:
//          "It's the wrong iterators Gromit, and they're going berserk !"
//                       (Apologies to Nick Park and Aardman Animations)
//
//          This program DELIBERATELY DOES NOT COMPILE: sort() needs random
//          access iterators, and a set only has bidirectional ones. It is
//          in the Visual Studio solution for reading, but is not built.
//
// ---- The wrong iterators for an algorithm ("example_8_1.cpp") -------------

// C++ Standard Library Headers
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>

void PrintIntegerSet( const std::set<int> &integers );
int TechnoTrousers( std::set<int> &exNasa );

int main()
{
    std::set<int> integers = { 4,9,2,8,17,3 };
    PrintIntegerSet( integers );
    std::cout << "Smallest element is: " << TechnoTrousers( integers ) << std::endl;
    return 0; // Compile and note error messages
}

void PrintIntegerSet( const std::set<int> &integers )
{
    std::cout << "Set of integers:" << std::endl;
    for ( std::set<int>::const_iterator setIterator = integers.begin();
          setIterator != integers.end(); ++setIterator )
    {
        std::cout << *setIterator << " ";
    }
    std::cout << std::endl;
}

int TechnoTrousers( std::set<int> &exNasa )
{
    // Oh dear - sort() needs random access iterators, which a set doesn't have
    std::sort( exNasa.begin(), exNasa.end() ); // To make this work, comment out this line
    // min_element() only needs forward iterators, so it works with a set
    return *std::min_element( exNasa.begin(), exNasa.end() );
}
