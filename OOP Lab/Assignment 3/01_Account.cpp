#include <iostream>
#include <cmath>
#include <string>
using namespace std;
class Account {             // Base class
protected:
    string customerName;
    int accountNumber;
    string accountType;
    double balance;

public:
    void initialize(string name, int accNo, string type, double bal) {
        customerName = name;
        accountNumber = accNo;
        accountType = type;
        balance = bal;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << "\n";
    }

    void displayBalance() {
        cout << "Account Holder: " << customerName << "\n";
        cout << "Account No: " << accountNumber << "\n";
        cout << "Account Type: " << accountType << "\n";
        cout << "Balance: " << balance << "\n";
    }

    double getBalance() {
        return balance;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            cout << "Withdrawn: " << amount << "\n";
        }
    }
};
class Sav_Acct : public Account {               // Derived class for Savings Account
public:
    void computeInterest(double rate, int time) {
        double interest = balance * pow((1 + rate / 100.0), time) - balance;
        balance += interest;
        cout << "Interest added: " << interest << "\n";
    }
};
class Cur_Acct : public Account {             // Derived class for Current Account
private:
    const double minimumBalance = 500.0;
    const double serviceCharge = 50.0;

public:
    void checkMinimumBalance() {
        if (balance < minimumBalance) {
            balance -= serviceCharge;
            cout << "Balance below minimum! Service charge of " 
                 << serviceCharge << " imposed.\n";
        }
    }
    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            cout << "Withdrawn: " << amount << "\n";
            checkMinimumBalance();
        }
    }
};
int main() {
    Sav_Acct sav;
    Cur_Acct cur;
    sav.initialize("Alice", 1001, "Savings", 2000.0);       // Initialize accounts
    cur.initialize("Bob", 2001, "Current", 1000.0);
    cout << "\n--- Savings Account ---\n";
    sav.displayBalance();
    sav.deposit(500);
    sav.computeInterest(5, 2);                                   // 5% rate, 2 years
    sav.withdraw(1000);
    sav.displayBalance();
    cout << "\n--- Current Account ---\n";
    cur.displayBalance();
    cur.deposit(300);
    cur.withdraw(900); 
    cur.displayBalance();
    return 0;
}
