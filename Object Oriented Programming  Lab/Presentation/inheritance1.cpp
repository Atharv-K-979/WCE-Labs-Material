#include<iostream>
using namespace std;

class ParentClass{
    public:
        void function() {
            cout << "Inherited";
        }
};
class DerivedClass : public ParentClass {
};

int main(){
    DerivedClass derived;
    derived.function();
}