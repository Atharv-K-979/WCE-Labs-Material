#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Academics {
    void displayCourses(vector<string> courses) {
        cout << "Available Courses:\n";
        for (const auto& course : courses) {
            cout << " - " << course << endl;
        }
        cout << "\n";
    }

    void calculateCGPA(vector<pair<int, int>> grades) {
        int sum = 0, totalCredits = 0;
        for (const auto& grade : grades) {
            sum += grade.first * grade.second;
            totalCredits += grade.second;
        }
        float cgpa = static_cast<float>(sum) / totalCredits;
        cout << "CGPA: " << cgpa << "\n\n";
    }

    void showTimetable(vector<pair<string, string>> timetable) {
        cout << "Timetable:\n";
        for (const auto& entry : timetable) {
            cout << entry.first << ": " << entry.second << endl;
        }
        cout << "\n";
    }
}

namespace Administration {
    void generateIDCard(string name, int id) {
        cout << "ID Card Generated for " << name << " with ID: " << id << "\n\n";
    }

    void trackAttendance(string studentName, int attended, int totalClasses) {
        float percentage = (static_cast<float>(attended) / totalClasses) * 100;
        cout << "Attendance for " << studentName << ": " << percentage << "%\n\n";
    }

    void issueNotice(string message) {
        cout << "Notice Issued: " << message << "\n\n";
    }
}

namespace Facilities {
    void bookLab(string labName, string timeSlot) {
        cout << "Lab " << labName << " booked for " << timeSlot << "\n\n";
    }

    void reportMaintenance(string issue) {
        cout << "Maintenance reported for: " << issue << "\n\n";
    }

    void checkAvailability(string resourceName) {
        cout << "Checking availability for: " << resourceName << "\n\n";
    }
}

int main() {
    cout << "CAMPUS MANAGEMENT SYSTEM\n\n";
    Academics::displayCourses({"Math", "Physics", "Chemistry"});
    Academics::calculateCGPA({{9, 3}, {8, 2}, {10, 3}});
    Academics::showTimetable({{"Monday", "DS"}, {"Tuesday", "CN"}});
    using Administration::generateIDCard;
    using Administration::trackAttendance;
    generateIDCard("Atharv", 74);
    trackAttendance("Atharv", 18, 21);
    namespace Adm = Administration;
    Adm::issueNotice("Semester exams begin from next Monday.");
    using namespace Facilities;
    bookLab("OOPs Lab", "10:00 AM - 12:00 PM");
    reportMaintenance("Projector in Seminar Hall");
    checkAvailability("Database Lab");

    cout << "End of Simulation\n";
    return 0;
}
