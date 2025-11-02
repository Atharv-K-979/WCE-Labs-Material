#include <bits/stdc++.h>
using namespace std;
// Car Rental - Admin and User
class Car {
protected:
    string plate; bool rented;
public:
    Car(string p):plate(p),rented(false){}
    virtual double rate() const = 0;
    virtual string type() const = 0;
    string info() const { return type()+" "+plate+(rented?" (Rented)":""); }
    string getPlate() const { return plate; }
    bool isRented() const { return rented; }
    void setRented(bool v){ rented=v; }
};

class Sedan: public Car { public: Sedan(string p):Car(p){} double rate() const override { return 50; } string type() const override { return "Sedan"; } };
class SUV: public Car { public: SUV(string p):Car(p){} double rate() const override { return 80; } string type() const override { return "SUV"; } };

class DB { public: vector<unique_ptr<Car>> fleet; };

class Admin {
    DB &db;
public:
    Admin(DB &d):db(d){}
    void addSedan(){ string p; cout<<"plate: "; cin>>p; db.fleet.emplace_back(make_unique<Sedan>(p)); }
    void addSUV(){ string p; cout<<"plate: "; cin>>p; db.fleet.emplace_back(make_unique<SUV>(p)); }
    void view(){ for(auto &c:db.fleet) cout<<c->info()<<" rate "<<c->rate()<<"\n"; }
};

class User {
    DB &db;
public:
    User(DB &d):db(d){}
    void view(){ for(auto &c:db.fleet) cout<<c->info()<<" rate "<<c->rate()<<"\n"; }
    void rent(){ string plate; cout<<"plate to rent: "; cin>>plate; for(auto &c:db.fleet) if(c->getPlate()==plate && !c->isRented()){ c->setRented(true); cout<<"Rented\n"; return;} cout<<"Not available\n"; }
    void ret(){ string plate; cout<<"plate to return: "; cin>>plate; for(auto &c:db.fleet) if(c->getPlate()==plate && c->isRented()){ c->setRented(false); cout<<"Returned\n"; return;} cout<<"Not found\n"; }
};

int main(){
    DB db; Admin admin(db); User user(db);
    int role;
    while(true){
        cout<<"\n1.Admin 2.User 3.Exit\nChoice: "; cin>>role;
        if(role==1){ int a; cout<<"1.AddSedan 2.AddSUV 3.View\n"; cin>>a; if(a==1)admin.addSedan(); else if(a==2)admin.addSUV(); else admin.view();}
        else if(role==2){ int a; cout<<"1.View 2.Rent 3.Return\n"; cin>>a; if(a==1)user.view(); else if(a==2)user.rent(); else user.ret(); }
        else break;
    }
    return 0;
}