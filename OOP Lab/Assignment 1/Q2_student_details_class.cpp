#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int rollNumber;
    string studentName;
    float studentMarks;

public:
    void getDetails() {
        cout << "Enter Roll Number: ";
        cin >> rollNumber;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, studentName);
        cout << "Enter Marks: ";
        cin >> studentMarks;
    }

    void displayDetails() {
        cout << "Roll Number: " << rollNumber << "\n";
        cout << "Name: " << studentName << "\n";
        cout << "Marks: " << studentMarks << "\n";
    }
};

int main() {
    Student student1;
    cout << "=== Enter Student Details ===\n";
    student1.getDetails();

    cout << "\n=== Student Details ===\n";
    student1.displayDetails();
    return 0;
}
