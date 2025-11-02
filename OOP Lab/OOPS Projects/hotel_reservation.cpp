#include <bits/stdc++.h>
using namespace std;
// Hotel Reservation - Admin and User
class Room {
protected: int number; bool booked;
public:
    Room(int n):number(n),booked(false){}
    virtual double price() const = 0;
    virtual string type() const = 0;
    string info() const { return type()+" "+to_string(number)+(booked?" (Booked)":""); }
    int getNumber() const { return number; }
    bool isBooked() const { return booked; }
    void setBooked(bool v){ booked=v; }
    virtual ~Room()=default;
};

class Single: public Room { public: Single(int n):Room(n){} double price() const override { return 50; } string type() const override { return "Single"; } };
class DoubleRoom: public Room { public: DoubleRoom(int n):Room(n){} double price() const override { return 90; } string type() const override { return "Double"; } };

class DB { public: vector<unique_ptr<Room>> rooms; };

class Admin {
    DB &db;
public:
    Admin(DB &d):db(d){}
    void addSingle(){ int num; cout<<"room number: "; cin>>num; db.rooms.emplace_back(make_unique<Single>(num)); }
    void addDouble(){ int num; cout<<"room number: "; cin>>num; db.rooms.emplace_back(make_unique<DoubleRoom>(num)); }
    void view(){ for(auto &r:db.rooms) cout<<r->info()<<" price "<<r->price()<<"\n"; }
};

class User {
    DB &db;
public:
    User(DB &d):db(d){}
    void view(){ for(auto &r:db.rooms) cout<<r->info()<<" price "<<r->price()<<"\n"; }
    void book(){ int num; cout<<"room number to book: "; cin>>num; for(auto &r:db.rooms) if(r->getNumber()==num && !r->isBooked()){ r->setBooked(true); cout<<"Booked\n"; return;} cout<<"Not available\n"; }
    void checkout(){ int num; cout<<"room number to checkout: "; cin>>num; for(auto &r:db.rooms) if(r->getNumber()==num && r->isBooked()){ r->setBooked(false); cout<<"Checked out\n"; return;} cout<<"Not found\n"; }
};

int main(){
    DB db; Admin admin(db); User user(db);
    int role;
    while(true){
        cout<<"\n1.Admin 2.User 3.Exit\nChoice: "; cin>>role;
        if(role==1){ int a; cout<<"1.AddSingle 2.AddDouble 3.View\n"; cin>>a; if(a==1)admin.addSingle(); else if(a==2)admin.addDouble(); else admin.view();}
        else if(role==2){ int a; cout<<"1.View 2.Book 3.Checkout\n"; cin>>a; if(a==1)user.view(); else if(a==2)user.book(); else user.checkout(); }
        else break;
    }
    return 0;
}