#include <bits/stdc++.h>
using namespace std;
// Library Management - Admin and User
class Book {
    int id; string title; bool borrowed;
public:
    Book(int i,string t):id(i),title(t),borrowed(false){}
    string info() const { return to_string(id)+": "+title+(borrowed?" (Borrowed)":""); }
    int getId() const { return id; }
    bool isBorrowed() const { return borrowed; }
    void borrow(){ borrowed=true; }
    void ret(){ borrowed=false; }
};

class DB { public: vector<Book> books; };

class Admin {
    DB &db;
public:
    Admin(DB &d):db(d){}
    void add(){ int id; string t; cout<<"id title: "; cin>>id; getline(cin,t); getline(cin,t); db.books.emplace_back(id,t); cout<<"Added\n"; }
    void view(){ for(auto &b:db.books) cout<<b.info()<<"\n"; }
};

class User {
    DB &db;
public:
    User(DB &d):db(d){}
    void borrow(){ int id; cout<<"book id: "; cin>>id; for(auto &b:db.books) if(b.getId()==id && !b.isBorrowed()){ b.borrow(); cout<<"Borrowed\n"; return;} cout<<"Not available\n"; }
    void ret(){ int id; cout<<"book id to return: "; cin>>id; for(auto &b:db.books) if(b.getId()==id && b.isBorrowed()){ b.ret(); cout<<"Returned\n"; return;} cout<<"Not found\n"; }
    void view(){ for(auto &b:db.books) cout<<b.info()<<"\n"; }
};

int main(){
    DB db; Admin admin(db); User user(db);
    int role;
    while(true){
        cout<<"\n1.Admin 2.User 3.Exit\nChoice: "; cin>>role;
        if(role==1){ int a; cout<<"1.Add 2.View\n"; cin>>a; if(a==1)admin.add(); else admin.view(); }
        else if(role==2){ int a; cout<<"1.View 2.Borrow 3.Return\n"; cin>>a; if(a==1)user.view(); else if(a==2)user.borrow(); else user.ret(); }
        else break;
    }
    return 0;
}