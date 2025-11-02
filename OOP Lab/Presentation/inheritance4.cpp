#include<iostream>
using namespace std;


class Ground {                // base class
    int Rooms;                // private (default) → accessible only inside Ground
protected:
    void put();               // protected → accessible in Ground + derived classes
public:
    void get();               // public → accessible everywhere
};

class Middle : private Ground {  // middle derived class from  ground class
    int Labs;                    // private → only inside Middle
public:
    void Take();                 // public → accessible everywhere
    void Give();                 // public → accessible everywhere
};

class Top : public Middle {
    int Roof;                 // private → only inside Top
public:
    void In();                // public
    void Out();               // public
};

// Which type of inheritance is this..?

// Middle : private Ground → Private inheritance (so all public and protected members of Ground become private in Middle).
// Top : public Middle → Public inheritance (so all public members of Middle stay public in Top).
// Overall: This is a Hybrid Inheritance (mix of private and public inheritance).

// Write the members, which are directly accessibleby the member function Give() of class Middle.
// Answer: Labs, Take(), Give(), put(), get()

// Write the names of all the members, which are directly accesible by the member function Out() of class Top.
// Roof, In(), Out(), Take(), Give()

// Write the names of all the members, which are directly accesible by the object T of class Top
//  declared in main() function.
// In(), Out(), Take(), Give()
