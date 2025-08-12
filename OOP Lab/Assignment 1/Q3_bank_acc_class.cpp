#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string accountHolderName;
    double accountBalance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cin.ignore();
        cout << "Enter Account Holder Name: ";
        getline(cin, accountHolderName);
        cout << "Enter Initial Balance: ";
        cin >> accountBalance;
    }

    void depositAmount(double depositValue) {
        accountBalance += depositValue;
        cout << "Amount Deposited Successfully!\n";
    }

    void withdrawAmount(double withdrawValue) {
        if (withdrawValue <= accountBalance) {
            accountBalance -= withdrawValue;
            cout << "Amount Withdrawn Successfully!\n";
        } else {
            cout << "Insufficient Balance!\n";
        }
    }

    void displayAccountDetails() {
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Account Holder Name: " << accountHolderName << "\n";
        cout << "Current Balance: " << accountBalance << "\n";
    }
};

int main() {
    BankAccount account;
    account.createAccount();
    account.depositAmount(500);
    account.withdrawAmount(200);
    cout << "\n=== Account Details ===\n";
    account.displayAccountDetails();
    return 0;
}
