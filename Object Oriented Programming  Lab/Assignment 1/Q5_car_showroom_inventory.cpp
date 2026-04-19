#include <iostream>
#include <string>
using namespace std;

class Car {
private:
    string modelName;
    double price;
    int yearOfManufacture;

public:
    void inputCarDetails() {
        cout << "Enter Model Name: ";
        cin.ignore();
        getline(cin, modelName);
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Year of Manufacture: ";
        cin >> yearOfManufacture;
    }

    void displayCarDetails() {
        cout << "Model Name: " << modelName << "\n";
        cout << "Price: " << price << "\n";
        cout << "Year: " << yearOfManufacture << "\n";
    }
};

int main() {
    Car cars[3];
    for (int i = 0; i < 3; i++) {
        cout << "\nEnter details for Car " << i + 1 << ":\n";
        cars[i].inputCarDetails();
    }

    cout << "\nCar Inventory\n";
    for (int i = 0; i < 3; i++) {
        cout << "\nCar " << i + 1 << ":\n";
        cars[i].displayCarDetails();
    }
    return 0;
}
