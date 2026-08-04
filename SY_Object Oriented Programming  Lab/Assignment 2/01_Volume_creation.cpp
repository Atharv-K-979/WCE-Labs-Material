#include <iostream>
using namespace std;

class Cube
{
private:
    double side;
    static int created;
    static int destroyed;

public:
    // Constructor
    Cube(double s)
    {
        side = s;
        created++;
        cout << "Cube created with side = " << side << endl;
    }

    // Destructor
    ~Cube()
    {
        destroyed++;
        cout << "Cube destroyed." << endl;
    }

    double calculateVolume()
    {
        return side * side * side;
    }

    // Static getters
    static int getCreated() { return created; }
    static int getDestroyed() { return destroyed; }
};

// Define static members
int Cube::created = 0;        // this is space resolution operator
int Cube::destroyed = 0;

int main()
{
    int n;
    cout << "Enter number of cubes: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Number of cubes must be positive." << endl;
        return 0;
    }

    // Create array of Cube pointers
    Cube *cubes[n];

    for (int i = 0; i < n; i++)
    {
        double s;
        cout << "Enter side length for cube " << i + 1 << ": ";
        cin >> s;

        // Input validation
        if (s <= 0)
        {
            cout << "Side length must be positive. Try again." << endl;
            i--;
            continue;
        }

        cubes[i] = new Cube(s);
        cout << "Volume of cube " << i + 1 << " = " << cubes[i]->calculateVolume() << endl;
    }

    // Delete all dynamically created objects
    for (int i = 0; i < n; i++)
    {
        delete cubes[i];
    }

    cout << "Total cubes created: " << Cube::getCreated() << endl;
    cout << "Total cubes destroyed: " << Cube::getDestroyed() << endl;

    return 0;
}
