#include<iostream>
using namespace std;

class ParentClass_A{
    public:
        void functionA() {
            cout << "Function A \n";
        }
};

class ParentClass_B{
    public:
        void functionB() {
            cout << "Function B \n";
        }
};

class DerivedClass : public ParentClass_A, public ParentClass_B {
    public:
};

int main(){
    DerivedClass derived;
    derived.functionA();
    derived.functionB();
}