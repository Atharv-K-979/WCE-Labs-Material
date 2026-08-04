#include <iostream>
#include <map>
#include <chrono>
#include <iomanip>
#include <ctime>
using namespace std;

class Employee {
private:
    int id;
    string name;
    static int nextId;
    static map<int, string> registry;

    // Helper function for timestamp
    string currentTime() {
        auto now = chrono::system_clock::now();
        time_t now_t = chrono::system_clock::to_time_t(now);
        tm local_tm;
#ifdef _WIN32
        localtime_s(&local_tm, &now_t);
#else
        localtime_r(&now_t, &local_tm);
#endif
        char buffer[30];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_tm);
        return string(buffer);
    }

public:
    // Constructor
    Employee(string empName) {
        id = ++nextId;
        name = empName;
        registry[id] = name;
        cout << "[CREATED] Employee ID: " << id 
             << ", Name: " << name 
             << " at " << currentTime() << "\n";
    }

    // Destructor
    ~Employee() {
        cout << "[DESTROYED] Employee ID: " << id 
             << ", Name: " << name 
             << " at " << currentTime() << "\n";
        registry.erase(id);
    }

    // Static function to display registry
    static void showRegistry() {
        cout << "\n=== Active Employee Registry ===\n";
        if (registry.empty()) {
            cout << "No active employees.\n";
        } else {
            for (auto &pair : registry) {
                cout << "ID: " << pair.first << " | Name: " << pair.second << "\n";
            }
        }
    }
};

// Static member definitions
int Employee::nextId = 0;
map<int, string> Employee::registry;

int main() {
    Employee* e1 = new Employee("Alice");
    Employee::showRegistry();

    Employee* e2 = new Employee("Bob");
    Employee::showRegistry();

    Employee* e3 = new Employee("Charlie");
    Employee::showRegistry();

    delete e2;
    Employee::showRegistry();

    delete e1;
    Employee::showRegistry();

    delete e3;
    Employee::showRegistry();

    return 0;
}
