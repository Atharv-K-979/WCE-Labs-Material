#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int rollNumber;
    string studentName;  // name
    float studentMarks;  // marks

public:
    void getDetails() {
        cout << "Enter Roll Number: ";
        cin >> rollNumber;
        cin.ignore();    // to clear prev input
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
    int choice;
    bool detailsEntered = false;   // to check if details are entered

    while (true) {
        cout << "\nSTUDENT MENU\n";
        cout << "1. Enter Student Details\n";
        cout << "2. Display Student Details\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if(choice > 2) return 0;
        switch (choice) {
        case 1:
            student1.getDetails();
            detailsEntered = true;
            break;

        case 2:
            if (detailsEntered) {
                cout << "\nStudent Details:\n";
                student1.displayDetails();
            } else {
                cout << "Please enter details first!\n";
            }
            break;
        }
    }
}
