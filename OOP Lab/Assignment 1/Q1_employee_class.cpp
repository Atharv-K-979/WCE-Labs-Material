#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    int employeeCode;
    string employeeName;

public:
    // Accept employee details from user
    void getData() {
        cout << "Enter Employee Code: ";
        cin >> employeeCode;
        cin.ignore(); // Clear input buffer before getline
        cout << "Enter Employee Name: ";
        getline(cin, employeeName);
    }

    // Display employee details
    void displayData() {
        cout << "Employee Code: " << employeeCode << "\n";
        cout << "Employee Name: " << employeeName << "\n";
    }
};

int main() {
    const int totalEmployees = 4; // As per requirement
    Employee employees[totalEmployees];

    cout << "=== Enter Employee Details ===\n";
    for (int i = 0; i < totalEmployees; i++) {
        cout << "\nEmployee " << i + 1 << ":\n";
        employees[i].getData();
    }

    cout << "\n=== Employee Details Entered ===\n";
    for (int i = 0; i < totalEmployees; i++) {
        cout << "\nEmployee " << i + 1 << ":\n";
        employees[i].displayData();
    }
    return 0;
}
