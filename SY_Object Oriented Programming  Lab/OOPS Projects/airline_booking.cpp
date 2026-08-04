#include <bits/stdc++.h>
using namespace std;
// Airline Booking - Admin and User (fare strategy)
class FareStrategy
{
public:
    virtual double fare(double base) = 0;
    virtual ~FareStrategy() = default;
};
class Economy : public FareStrategy
{
public:
    double fare(double b) override { return b; }
};
class Business : public FareStrategy
{
public:
    double fare(double b) override { return b * 2; }
};

struct Flight
{
    int id;
    double base;
    unique_ptr<FareStrategy> strat;
    bool booked = false;
    Flight(int i, double b, unique_ptr<FareStrategy> s) : id(i), base(b), strat(move(s)) {}
    string info() const { return to_string(id) + ": base " + to_string(base) + (booked ? " (Booked)" : ""); }
};

class DB
{
public:
    vector<Flight> flights;
};

class Admin
{
    DB &db;

public:
    Admin(DB &d) : db(d) {}
    void add()
    {
        int id;
        double base;
        int t;
        cout << "id base type(1=eco,2=bus): ";
        cin >> id >> base >> t;
        if (t == 1)
            db.flights.emplace_back(id, base, make_unique<Economy>());
        else
            db.flights.emplace_back(id, base, make_unique<Business>());
    }
    void view()
    {
        for (auto &f : db.flights)
            cout << f.info() << " fare " << f.strat->fare(f.base) << "\n";
    }
};

class User
{
    DB &db;

public:
    User(DB &d) : db(d) {}
    void view()
    {
        for (auto &f : db.flights)
            cout << f.info() << " fare " << f.strat->fare(f.base) << "\n";
    }
    void book()
    {
        int id;
        cout << "flight id to book: ";
        cin >> id;
        for (auto &f : db.flights)
            if (f.id == id)
            {
                if (!f.booked)
                {
                    f.booked = true;
                    cout << "Booked\n";
                }
                else
                    cout << "Already\n";
                return;
            }
        cout << "Not found\n";
    }
};

int main()
{
    DB db;
    Admin admin(db);
    User user(db);
    int role;
    while (true)
    {
        cout << "\n1.Admin 2.User 3.Exit\nChoice: ";
        cin >> role;
        if (role == 1)
        {
            int a;
            cout << "1.Add 2.View\n";
            cin >> a;
            if (a == 1)
                admin.add();
            else
                admin.view();
        }
        else if (role == 2)
        {
            int a;
            cout << "1.View 2.Book\n";
            cin >> a;
            if (a == 1)
                user.view();
            else
                user.book();
        }
        else
            break;
    }
    return 0;
}