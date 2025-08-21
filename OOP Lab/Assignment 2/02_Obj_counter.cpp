#include <iostream>
using namespace std;

class Counter
{
private:
    static int objectCount; // static variable to count objects
    int id;                 // to show which object is created
    static int nextId;      // for assigning unique id

public:
    Counter()
    {
        nextId++;
        id = nextId;
        objectCount++;
        cout << "Constructor: Object" << id << " created. Total objects = " << objectCount << endl;
    }
    ~Counter()
    {
        cout << "Destructor : Object" << id << " destroyed." << endl;
        objectCount--;
        cout << "Now total objects = " << objectCount << endl;
    }
    static int getCount()
    {
        return objectCount;
    }
};

int Counter::objectCount = 0;
int Counter::nextId = 0;

int main()
{
    cout << "Program started. Current count = " << Counter::getCount() << endl;
    Counter c1, c2;
    cout << "After creating c1 and c2, count = " << Counter::getCount() << endl;
    {
        Counter c3;
        cout << "Inside block, count = " << Counter::getCount() << endl;
    }
    cout << "After block, count = " << Counter::getCount() << endl;
    Counter *p1 = new Counter();
    cout << "After creating p1 dynamically, count = " << Counter::getCount() << endl;

    delete p1;
    cout << "After deleting p1, count = " << Counter::getCount() << endl;
    int n = 3;
    Counter *arr[n];
    cout << "\nCreating array of " << n << " dynamic objects...\n";
    for (int i = 0; i < n; i++)
    {
        arr[i] = new Counter();
    }
    cout << "After creating array, count = " << Counter::getCount() << endl;
    cout << "\nDeleting array objects...\n";
    for (int i = 0; i < n; i++)
    {
        delete arr[i];
    }
    cout << "After deleting array, count = " << Counter::getCount() << endl;

    cout << "Program ended. Final count = " << Counter::getCount() << endl;
    return 0;
}
