#include <bits/stdc++.h>
using namespace std;
// Lost and Found - Admin and User
class Item {
    int id; string desc; bool found;
public:
    Item(int i,string d):id(i),desc(d),found(false){}
    string info() const { return to_string(id)+": "+desc + (found?" (Found)":" (Lost)"); }
    int getId() const { return id; }
    void markFound(){ found=true; }
    bool isFound() const { return found; }
};

class DB { public: vector<Item> items; };

class Admin {
    DB &db;
public:
    Admin(DB &d):db(d){}
    void add(){ int id; string d; cout<<"id desc: "; cin>>id; getline(cin,d); getline(cin,d); db.items.emplace_back(id,d); cout<<"Added\n"; }
    void view(){ for(auto &it:db.items) cout<<it.info()<<"\n"; }
    void markFound(){ int id; cout<<"id to mark found: "; cin>>id; for(auto &it:db.items) if(it.getId()==id){ it.markFound(); cout<<"Marked\n"; return;} cout<<"Not found\n"; }
};

class User {
    DB &db;
public:
    User(DB &d):db(d){}
    void report(){ cout<<"To report, contact admin. (demo)\n"; }
    void viewFound(){ for(auto &it:db.items) if(it.isFound()) cout<<it.info()<<"\n"; }
};

int main(){
    DB db; Admin admin(db); User user(db);
    int role;
    while(true){
        cout<<"\n1.Admin 2.User 3.Exit\nChoice: "; cin>>role;
        if(role==1){ int a; cout<<"1.Add 2.View 3.MarkFound\n"; cin>>a; if(a==1)admin.add(); else if(a==2)admin.view(); else admin.markFound();}
        else if(role==2){ int a; cout<<"1.Report 2.ViewFound\n"; cin>>a; if(a==1)user.report(); else user.viewFound(); }
        else break;
    }
    return 0;
}