#include <bits/stdc++.h>
using namespace std;
// Movie Ticket Booking - Admin and User
class Screen {
    int id; int seats;
    vector<bool> booked;
public:
    Screen(int i,int s):id(i),seats(s),booked(s,false){}
    string info() const { string r= "Screen "+to_string(id)+": "; for(bool b:booked) r += (b?'X':'O'); return r; }
    bool book(int s){ if(s<0||s>=seats) return false; if(booked[s]) return false; booked[s]=true; return true; }
    int getId() const { return id; }
};

class DB { public: vector<Screen> screens; };

class Admin {
    DB &db;
public:
    Admin(DB &d):db(d){}
    void add(){ int id,s; cout<<"id seats: "; cin>>id>>s; db.screens.emplace_back(id,s); cout<<"Added\n"; }
    void view(){ for(auto &sc:db.screens) cout<<sc.info()<<"\n"; }
};

class User {
    DB &db;
public:
    User(DB &d):db(d){}
    void view(){ for(auto &sc:db.screens) cout<<sc.info()<<"\n"; }
    void book(){ int id,seat; cout<<"screen seat-index: "; cin>>id>>seat; for(auto &sc:db.screens) if(sc.getId()==id){ cout<<(sc.book(seat)?"Booked\n":"Fail\n"); return;} cout<<"Not found\n"; }
};

int main(){
    DB db; Admin admin(db); User user(db);
    int role;
    while(true){
        cout<<"\n1.Admin 2.User 3.Exit\nChoice: "; cin>>role;
        if(role==1){ int a; cout<<"1.Add 2.View\n"; cin>>a; if(a==1)admin.add(); else admin.view();}
        else if(role==2){ int a; cout<<"1.View 2.Book\n"; cin>>a; if(a==1)user.view(); else user.book(); }
        else break;
    }
    return 0;
}