#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class LibraryItem {
protected:
    string title;
    string author;
public:
    void setDetails(const string &t, const string &a) {
        title = t;
        author = a;
    }
    virtual void displayInfo() = 0;
    virtual ~LibraryItem() {}
};

class Book : public LibraryItem {
    int pageCount;
public:
    void setBookDetails(const string &t, const string &a, int pages) {
        setDetails(t, a);
        pageCount = pages;
    }
    void displayInfo() override {
        cout << "[Book] Title: " << title << ", Author: " << author
             << ", Pages: " << pageCount << endl;
    }
};

class Magazine : public LibraryItem {
    int issueNumber;
public:
    void setMagazineDetails(const string &t, const string &a, int issue) {
        setDetails(t, a);
        issueNumber = issue;
    }
    void displayInfo() override {
        cout << "[Magazine] Title: " << title << ", Editor: " << author
             << ", Issue: " << issueNumber << endl;
    }
};

class DVD : public LibraryItem {
    int duration;
public:
    void setDVDDetails(const string &t, const string &a, int dur) {
        setDetails(t, a);
        duration = dur;
    }
    void displayInfo() override {
        cout << "[DVD] Title: " << title << ", Director: " << author
             << ", Duration: " << duration << " mins" << endl;
    }
};

int main() {
    vector<shared_ptr<LibraryItem>> collection;

    auto book = make_shared<Book>();
    book->setBookDetails("The Great Gatsby", "F. Scott Fitzgerald", 218);
    collection.push_back(book);

    auto magazine = make_shared<Magazine>();
    magazine->setMagazineDetails("National Geographic", "Susan Goldberg", 125);
    collection.push_back(magazine);

    auto dvd = make_shared<DVD>();
    dvd->setDVDDetails("Inception", "Christopher Nolan", 148);
    collection.push_back(dvd);

    cout << "--- Library Collection ---\n";
    for (auto &item : collection) {
        item->displayInfo();
    }

    return 0;
}