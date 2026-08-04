#include <bits/stdc++.h>
using namespace std;
// Flight Reservation System - Admin and User
class Flight {
    int id; string from,to; int seats;
public:
    Flight(int i,string f,string t,int s):id(i),from(f),to(t),seats(s){}
    int getId() const { return id; }
    string info() const { return to_string(id)+": "+from+"->"+to+" seats="+to_string(seats); }
    bool book(){ if(seats>0){ --seats; return true;} return false; }
    void addSeats(int x){ seats+=x; }
};

class SystemData {
public:
    vector<Flight> flights;
};

class Admin {
    SystemData &db;
public:
    Admin(SystemData &d):db(d){}
    void addFlight(){
        int id,s; string f,t;
        cout<<"Flight id: "; cin>>id; cout<<"From: "; cin>>f; cout<<"To: "; cin>>t; cout<<"Seats: "; cin>>s;
        db.flights.emplace_back(id,f,t,s);
        cout<<"Added.\n";
    }
    void viewFlights(){ for(auto &fl:db.flights) cout<<fl.info()<<"\n"; }
    void restock(){
        int id,x; cout<<"Flight id to add seats: "; cin>>id; cout<<"Seats to add: "; cin>>x;
        for(auto &fl:db.flights) if(fl.getId()==id){ fl.addSeats(x); cout<<"Updated.\n"; return; }
        cout<<"Not found.\n";
    }
};

class User {
    SystemData &db;
public:
    User(SystemData &d):db(d){}
    void view(){ for(auto &fl:db.flights) cout<<fl.info()<<"\n"; }
    void book(){
        int id; cout<<"Enter flight id to book: "; cin>>id;
        for(auto &fl:db.flights) if(fl.getId()==id){ cout<<(fl.book()?"Booked\n":"No seats\n"); return; }
        cout<<"Not found\n";
    }
};

int main(){
    SystemData db;
    // seed
    db.flights.emplace_back(1,"DEL","BOM",2);
    db.flights.emplace_back(2,"BLR","DEL",1);

    Admin admin(db); User user(db);
    int c=0;
    while(true){
        cout<<"\n1.Admin 2.User 3.Exit\nChoice: "; cin>>c;
        if(c==1){
            int a; cout<<"1.Add flight 2.View flights 3.Restock\nAction: "; cin>>a;
            if(a==1) admin.addFlight();
            else if(a==2) admin.viewFlights();
            else if(a==3) admin.restock();
        } else if(c==2){
            int a; cout<<"1.View flights 2.Book\nAction: "; cin>>a;
            if(a==1) user.view();
            else if(a==2) user.book();
        } else break;
    }
    return 0;
}