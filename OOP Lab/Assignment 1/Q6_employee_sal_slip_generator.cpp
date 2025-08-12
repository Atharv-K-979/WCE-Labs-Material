#include <iostream>
#include <string>
using namespace std;

class EmployeeSalary {
private:
    int employeeID;
    string employeeName;
    double basicSalary;

public:
    void getEmployeeDetails() {
        cout << "Enter Employee ID: ";
        cin >> employeeID;
        cin.ignore();
        cout << "Enter Employee Name: ";
        getline(cin, employeeName);
        cout << "Enter Basic Salary: ";
        cin >> basicSalary;
    }

    double calculateHRA() {
        return 0.10 * basicSalary; // 10% of basic salary
    }

    double calculateDA() {
        return 0.05 * basicSalary; // 5% of basic salary
    }

    double calculateTotalSalary() {
        return basicSalary + calculateHRA() + calculateDA();
    }

    void displaySalarySlip() {
        cout << "\n=== Employee Salary Slip ===\n";
        cout << "Employee ID: " << employeeID << "\n";
        cout << "Employee Name: " << employeeName << "\n";
        cout << "Basic Salary: " << basicSalary << "\n";
        cout << "HRA (10%): " << calculateHRA() << "\n";
        cout << "DA (5%): " << calculateDA() << "\n";
        cout << "Total Salary: " << calculateTotalSalary() << "\n";
    }
};

int main() {
    EmployeeSalary emp;
    emp.getEmployeeDetails();
    emp.displaySalarySlip();
    return 0;
}
