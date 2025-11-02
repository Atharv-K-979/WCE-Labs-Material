#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Base Class
class Notification {
protected:
    string recipient, message;
public:
    void setDetails(string r, string m) {
        recipient = r;
        message = m;
    }
    virtual void send() = 0; // pure virtual
    virtual string getUrgencyLevel() { return "Normal"; }
    virtual ~Notification() {}
};

// Derived: Email
class EmailNotification : public Notification {
    string emailAddress, subject;
public:
    void setEmail(string addr, string sub) {
        emailAddress = addr;
        subject = sub;
    }
    void send() override {
        cout << "Sending Email to " << recipient << " at " << emailAddress
             << " | Subject: " << subject << " | Message: " << message << "\n";
    }
    string getUrgencyLevel() override { return "Low"; }
};

// Derived: SMS
class SMSNotification : public Notification {
    string phoneNumber;
public:
    void setPhone(string num) { phoneNumber = num; }
    void send() override {
        cout << "Sending SMS to " << recipient << " at " << phoneNumber
             << " | Message: " << message << "\n";
    }
    string getUrgencyLevel() override { return "High"; }
};

// Derived: Push
class PushNotification : public Notification {
    string deviceToken;
public:
    void setToken(string token) { deviceToken = token; }
    void send() override {
        cout << "Sending Push Notification to " << recipient
             << " [Device: " << deviceToken << "] | Message: " << message << "\n";
    }
    string getUrgencyLevel() override { return "Medium"; }
};

// Derived: In-App
class InAppNotification : public Notification {
    string userId;
public:
    void setUserId(string id) { userId = id; }
    void send() override {
        cout << "Showing In-App Notification to " << recipient
             << " [UserID: " << userId << "] | Message: " << message << "\n";
    }
    string getUrgencyLevel() override { return "Normal"; }
};

// Main
int main() {
    vector<shared_ptr<Notification>> notifications;
    int choice;

    do {
        cout << "\nChoose Notification Type:\n";
        cout << "1. Email\n2. SMS\n3. Push\n4. In-App\n5. Exit\nChoice: ";
        cin >> choice;

        if (choice == 5) break;

        string name, msg;
        cout << "Enter Recipient Name: ";
        cin >> name;
        cout << "Enter Message: ";
        cin.ignore();
        getline(cin, msg);

        if (choice == 1) {
            auto email = make_shared<EmailNotification>();
            email->setDetails(name, msg);
            string addr, sub;
            cout << "Enter Email Address: "; cin >> addr;
            cout << "Enter Subject: "; cin >> sub;
            email->setEmail(addr, sub);
            notifications.push_back(email);
        } else if (choice == 2) {
            auto sms = make_shared<SMSNotification>();
            sms->setDetails(name, msg);
            string num; cout << "Enter Phone Number: "; cin >> num;
            sms->setPhone(num);
            notifications.push_back(sms);
        } else if (choice == 3) {
            auto push = make_shared<PushNotification>();
            push->setDetails(name, msg);
            string token; cout << "Enter Device Token: "; cin >> token;
            push->setToken(token);
            notifications.push_back(push);
        } else if (choice == 4) {
            auto inapp = make_shared<InAppNotification>();
            inapp->setDetails(name, msg);
            string id; cout << "Enter User ID: "; cin >> id;
            inapp->setUserId(id);
            notifications.push_back(inapp);
        }
    } while (choice != 5);

    cout << "\n--- Sending All Notifications ---\n";
    for (auto &n : notifications) {
        n->send();
        cout << "Urgency Level: " << n->getUrgencyLevel() << "\n\n";
    }

    return 0;
}

