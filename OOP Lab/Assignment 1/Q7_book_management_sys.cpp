#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    float price;

public:
    // Method to input book details
    void inputDetails() {
       
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
        cout << "Enter Book Price: ";
        cin >> price;
        cin.ignore(); // clear buffer before getline each time
    }

    // Method to display book details
    void displayDetails() {
        cout << "Title : " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "Price : " << price << "\n";
        cout << "--------------------------\n";
    }
};

int main() {
    Book books[5];  // array of 5 Book objects

    cout << "Enter details of 5 books:\n";
    for (int i = 0; i < 5; i++) {
        cout << "\nBook " << i + 1 << ":\n";
        books[i].inputDetails();
    }

    cout << "\nBook Details\n";
    for (int i = 0; i < 5; i++) {
        cout << "Book " << i + 1 << ":\n";
        books[i].displayDetails();
    }

    return 0;
}
