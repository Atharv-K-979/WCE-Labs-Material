#include <iostream>
using namespace std;

class Calculator {
private:
    double number1;
    double number2;

public:
    void inputNumbers() {
        cout << "Enter first number: ";
        cin >> number1;
        cout << "Enter second number: ";
        cin >> number2;
    }

    double addNumbers() { return number1 + number2; }
    double subtractNumbers() { return number1 - number2; }
    double multiplyNumbers() { return number1 * number2; }
    double divideNumbers() { 
        if (number2 != 0) return number1 / number2; 
        else {
            cout << "Error: Division by zero!\n";
            return 0;
        }
    }
};

int main() {
    Calculator calc;
    int choice;

    calc.inputNumbers();
    cout << "\n=== Menu ===\n";
    cout << "1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: cout << "Result: " << calc.addNumbers(); break;
        case 2: cout << "Result: " << calc.subtractNumbers(); break;
        case 3: cout << "Result: " << calc.multiplyNumbers(); break;
        case 4: cout << "Result: " << calc.divideNumbers(); break;
        default: cout << "Invalid choice!";
    }
    return 0;
}
