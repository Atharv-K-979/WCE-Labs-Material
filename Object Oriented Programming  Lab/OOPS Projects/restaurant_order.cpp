#include <bits/stdc++.h>
using namespace std;
// Restaurant Ordering - Admin and User
struct MenuItem { int id; string name; double price; MenuItem(int i,string n,double p):id(i),name(n),price(p){} string info() const { return to_string(id)+": "+name+" $"+to_string(price); } };

class DB { public: vector<MenuItem> menu; };

class Admin {
    DB &db;
public:
    Admin(DB &d):db(d){}
    void add(){ int id; string n; double p; cout<<"id name price: "; cin>>id>>n>>p; db.menu.emplace_back(id,n,p); cout<<"Added\n"; }
    void view(){ for(auto &m:db.menu) cout<<m.info()<<"\n"; }
};

class User {
    DB &db;
public:
    User(DB &d):db(d){}
    void view(){ for(auto &m:db.menu) cout<<m.info()<<"\n"; }
    void order(){ int id; cout<<"item id to order: "; cin>>id; for(auto &m:db.menu) if(m.id==id){ cout<<"Ordered "<<m.name<<"\n"; return;} cout<<"Not found\n"; }
};

int main(){
    DB db; Admin admin(db); User user(db);
    int role;
    while(true){
        cout<<"\n1.Admin 2.User 3.Exit\nChoice: "; cin>>role;
        if(role==1){ int a; cout<<"1.Add 2.View\n"; cin>>a; if(a==1)admin.add(); else admin.view(); }
        else if(role==2){ int a; cout<<"1.View 2.Order\n"; cin>>a; if(a==1)user.view(); else user.order(); }
        else break;
    }
    return 0;
}