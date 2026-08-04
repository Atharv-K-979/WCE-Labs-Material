#include<iostream>
using namespace std;

class A {
    public:
        void functionA() {
            cout << "Function A \n";
        }
};

class B: public A {
    public:
        void functionB() {
            cout << "Function B \n";
        }
};

class C: public B {
    public:
};

int main(){
    C derived;
    derived.functionA();
    derived.functionB();
}