#include <iostream>
using namespace std;

class Temperature {
private:
    double celsius;

public:
    void inputTemperature() {
        cout << "Enter Temperature in Celsius: ";
        cin >> celsius;
    }

    double convertToFahrenheit() {
        return (celsius * 9/5) + 32; // Formula conversion
    }

    void displayTemperatures() {
        cout << "Celsius: " << celsius << "\n";
        cout << "Fahrenheit: " << convertToFahrenheit() << "\n";
    }
};

int main() {
    Temperature temp;
    temp.inputTemperature();
    temp.displayTemperatures();
    return 0;
}
