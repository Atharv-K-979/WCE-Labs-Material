#include <iostream>
#include <string>
using namespace std;

class ElectricityBill {
private:
    string consumerName;
    int units;
    double totalBill;

public:
    // Constructor
    ElectricityBill(string name, int u) {
        consumerName = name;
        units = u;
        totalBill = 0;
    }

    // Method to calculate bill
    void calculateBill() {
        if (units <= 100) {
            totalBill = units * 5;
        } else if (units <= 300) {
            totalBill = (100 * 5) + ((units - 100) * 7);
        } else {
            totalBill = (100 * 5) + (200 * 7) + ((units - 300) * 10);
        }
    }

    // Method to display bill details
    void displayBill() {
        cout << "\n--- Electricity Bill Details ---" << endl;
        cout << "Consumer Name: " << consumerName << endl;
        cout << "Units Consumed: " << units << endl;
        cout << "Total Bill Amount: ₹" << totalBill << endl;
    }
};

int main() {
    string name;
    int units;

    cout << "Enter Consumer Name: ";
    getline(cin, name);
    cout << "Enter Units Consumed: ";
    cin >> units;

    ElectricityBill bill(name, units);
    bill.calculateBill();
    bill.displayBill();

    return 0;
}
