// Kara Ottewell's STL Course
//
// Example 4.2                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Demonstrate use of queue container adaptor
//
// ---- A queue adapter on the default deque ("example_4_2.cpp") -------------

// C++ Standard Library Headers
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    queue< const char * > wordQueue;

//  Push onto the back of the queue in the correct order
    wordQueue.push("First");
    wordQueue.push("come");
    wordQueue.push("first");
    wordQueue.push("served");
    wordQueue.push("- why");
    wordQueue.push("don't");
    wordQueue.push("bars");
    wordQueue.push("do");
    wordQueue.push("this ?");

//  Pop off front of queue which preserves the order
    while ( !wordQueue.empty() ) {
      cout << wordQueue.front() << " "; wordQueue.pop();
    }
    cout << endl;

    return( EXIT_SUCCESS );
}
