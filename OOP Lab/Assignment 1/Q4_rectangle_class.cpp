#include <iostream>
using namespace std;

class Rectangle {
private:
    double length;
    double breadth;

public:
    void acceptDimensions() {
        cout << "Enter Length: ";
        cin >> length;
        cout << "Enter Breadth: ";
        cin >> breadth;
    }

    double calculateArea() {
        return length * breadth;
    }

    double calculatePerimeter() {
        return 2 * (length + breadth);
    }
};

int main() {
    Rectangle rect;
    rect.acceptDimensions();
    cout << "Area: " << rect.calculateArea() << "\n";
    cout << "Perimeter: " << rect.calculatePerimeter() << "\n";
    return 0;
}
