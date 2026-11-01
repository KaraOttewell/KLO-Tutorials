// Kara Ottewell's STL Course
//
// Example 4.3                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Demonstrate use of priority_queue container adaptor
//          by using a task/priority structure
//
// ---- A priority_queue of tasks ("example_4_3.cpp") ------------------------

// C++ Standard Library Headers
#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class TaskObject {
public:
    friend class PrioritizeTasks;
    friend ostream & operator<<( ostream &os, const TaskObject &task );
    TaskObject( const char *newProcessName = "", unsigned int newPriority = 4 )
      : priority( newPriority ), processName( newProcessName ) {}
private:
    unsigned int priority;
    string processName;
};

// Friend function for "printing" TaskObject to an output stream
ostream & operator<<( ostream &os, const TaskObject &task )
{
    os << "Process: " << task.processName << " Priority: " << task.priority;
    return ( os );
}

// Friend class with function object for comparison of TaskObjects
class PrioritizeTasks {
public :
    bool operator()( const TaskObject &x, const TaskObject &y ) const
    {
      return x.priority < y.priority;
    }
};

int main()
{
    priority_queue<TaskObject, vector<TaskObject>, PrioritizeTasks> taskQueue;

    const TaskObject tasks[] = { "JAF", "ROB", "KARA", "JOHN"
                                ,TaskObject("OPCOM",6)  , TaskObject("Swapper",16)
                                ,TaskObject("NETACP",8) , TaskObject("REMACP",8) };

    for ( const TaskObject &task : tasks )
      taskQueue.push( task );

    while ( !taskQueue.empty() ) {
        cout << taskQueue.top() << endl; taskQueue.pop();
    }
    cout << endl;

    return( EXIT_SUCCESS );
}
