#include <bits/stdc++.h>
using namespace std;
// Contact Management - Admin and User
struct Contact {
    int id; string name,phone,email;
    Contact(int i,string n,string p,string e):id(i),name(n),phone(p),email(e){}
    string info() const { return to_string(id)+": "+name+" | "+phone+" | "+email; }
};

class DB { public: vector<Contact> contacts; };

class Admin {
    DB &db;
public:
    Admin(DB &d):db(d){}
    void add(){
        int id; string n,p,e; cout<<"id name phone email: "; cin>>id>>n>>p>>e;
        db.contacts.emplace_back(id,n,p,e); cout<<"Added\n";
    }
    void view(){ for(auto &c:db.contacts) cout<<c.info()<<"\n"; }
    void remove(){
        int id; cout<<"id to remove: "; cin>>id;
        auto &v = db.contacts;
        v.erase(remove_if(v.begin(),v.end(),[&](const Contact&c){return c.id==id;}), v.end());
        cout<<"Removed if existed\n";
    }
};

class User {
    DB &db;
public:
    User(DB &d):db(d){}
    void search(){
        string q; cout<<"search name: "; cin>>q;
        for(auto &c:db.contacts) if(c.name.find(q)!=string::npos) cout<<c.info()<<"\n";
    }
    void viewAll(){ for(auto &c:db.contacts) cout<<c.info()<<"\n"; }
};

int main(){
    DB db; Admin admin(db); User user(db);
    int role;
    while(true){
        cout<<"\n1.Admin 2.User 3.Exit\nChoice: "; cin>>role;
        if(role==1){ int a; cout<<"1.Add 2.View 3.Remove\n"; cin>>a; if(a==1)admin.add(); else if(a==2)admin.view(); else admin.remove();}
        else if(role==2){ int a; cout<<"1.Search 2.ViewAll\n"; cin>>a; if(a==1)user.search(); else user.viewAll(); }
        else break;
    }
    return 0;
}