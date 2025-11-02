#include <iostream>
#include <string>
using namespace std;

class BankAccount
{
private:
    int accountNumber; // data members
    string accountHolderName;
    double accountBalance;

public:
    void createAccount()
    { // ceration of account
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cin.ignore();
        cout << "Enter Account Holder Name: ";
        getline(cin, accountHolderName);
        cout << "Enter Initial Balance: ";
        cin >> accountBalance;
    }

    void depositAmount(double depositValue)
    { // deposit amount
        accountBalance += depositValue;
        cout << "Amount Deposited Successfully!\n";
    }

    void withdrawAmount(double withdrawValue)
    {
        if (withdrawValue <= accountBalance)
        { // imp condition if(balance is sufficient)
            accountBalance -= withdrawValue;
            cout << "Amount Withdrawn Successfully!\n";
        }
        else
        {
            cout << "Insufficient Balance!\n";
        }
    }

    void displayAccountDetails()
    {
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Account Holder Name: " << accountHolderName << "\n";
        cout << "Current Balance: " << accountBalance << "\n";
    }
};

int main()
{
    BankAccount account;
    int choice;
    double amount;

    while (true)
    {
        cout << "\nBANK MENU\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Display Account Details\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if(choice > 4) return 0;
        switch (choice)
        {
        case 1:
            account.createAccount();
            break;

        case 2:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            account.depositAmount(amount);
            break;

        case 3:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            account.withdrawAmount(amount);
            break;

        case 4:
            cout << "\nAccount Details:\n";
            account.displayAccountDetails();
            break;
        }
    }
}
