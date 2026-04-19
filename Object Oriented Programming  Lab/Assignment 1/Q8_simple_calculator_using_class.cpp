#include <iostream>
using namespace std;

class Calculator
{
private:
    double number1;
    double number2;

public:
    void inputNumbers()
    {
        cout << "Enter first number: ";
        cin >> number1;
        cout << "Enter second number: ";
        cin >> number2;
    }

    double addNumbers() { return number1 + number2; }
    double subtractNumbers() { return number1 - number2; }
    double multiplyNumbers() { return number1 * number2; }
    double divideNumbers()
    {
        if (number2 != 0)
            return number1 / number2;
        else
        {
            cout << "Error: Division by zero!\n";
            return 0;
        }
    }
};

int main()
{
    Calculator calc;
    int choice;

    while (true)
    {
        cout << "\nMenu\n";
        cout << "1. Enter Numbers\n";
        cout << "2. Addition\n";
        cout << "3. Subtraction\n";
        cout << "4. Multiplication\n";
        cout << "5. Division\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if(choice > 5 )return 0;
        switch (choice)
        {
        case 1:
            calc.inputNumbers();
            break;
        case 2:
            cout << "Result: " << calc.addNumbers() << endl;
            break;
        case 3:
            cout << "Result: " << calc.subtractNumbers() << endl;
            break;
        case 4:
            cout << "Result: " << calc.multiplyNumbers() << endl;
            break;
        case 5:
            cout << "Result: " << calc.divideNumbers() << endl;
            break;
        }
    }
}
