#include <bits/stdc++.h>
using namespace std;
// Inventory Management - Admin and User
class Product {
    int id; string name; int qty;
public:
    Product(int i,string n,int q):id(i),name(n),qty(q){}
    string info() const { return to_string(id)+": "+name+" qty="+to_string(qty); }
    int getId() const { return id; }
    void restock(int x){ qty+=x; }
    bool consume(int x){ if(qty>=x){ qty-=x; return true;} return false; }
};

class DB { public: vector<Product> products; };

class Admin {
    DB &db;
public:
    Admin(DB &d):db(d){}
    void add(){ int id,q; string n; cout<<"id name qty: "; cin>>id>>n>>q; db.products.emplace_back(id,n,q); cout<<"Added\n"; }
    void view(){ for(auto &p:db.products) cout<<p.info()<<"\n"; }
    void restock(){ int id,x; cout<<"id qty: "; cin>>id>>x; for(auto &p:db.products) if(p.getId()==id){ p.restock(x); cout<<"Done\n"; return;} cout<<"Not found\n"; }
};

class User {
    DB &db;
public:
    User(DB &d):db(d){}
    void view(){ for(auto &p:db.products) cout<<p.info()<<"\n"; }
    void purchase(){ int id,x; cout<<"id qty: "; cin>>id>>x; for(auto &p:db.products) if(p.getId()==id){ cout<<(p.consume(x)?"Purchased\n":"Insufficient\n"); return;} cout<<"Not found\n"; }
};

int main(){
    DB db; Admin admin(db); User user(db);
    int role;
    while(true){
        cout<<"\n1.Admin 2.User 3.Exit\nChoice: "; cin>>role;
        if(role==1){ int a; cout<<"1.Add 2.View 3.Restock\n"; cin>>a; if(a==1)admin.add(); else if(a==2)admin.view(); else admin.restock();}
        else if(role==2){ int a; cout<<"1.View 2.Purchase\n"; cin>>a; if(a==1)user.view(); else user.purchase(); }
        else break;
    }
    return 0;
}