#include <bits/stdc++.h>
using namespace std;
// Bank Account Management - Admin and User
class Account {
protected:
    int id; double bal;
public:
    Account(int i,double b):id(i),bal(b){}
    virtual bool withdraw(double amt)=0;
    void deposit(double amt){ bal+=amt; }
    double getBalance() const { return bal; }
    int getId() const { return id; }
    virtual string info() const = 0;
    virtual ~Account()=default;
};

class Savings: public Account {
public:
    Savings(int i,double b):Account(i,b){}
    bool withdraw(double amt) override { if(bal-amt>=0){ bal-=amt; return true;} return false; }
    void addInterest(){ bal*=1.04; }
    string info() const override { return "Savings "+to_string(id)+" bal "+to_string(bal); }
};

class Checking: public Account {
public:
    Checking(int i,double b):Account(i,b){}
    bool withdraw(double amt) override { if(bal-amt>=-500){ bal-=amt; return true;} return false; }
    string info() const override { return "Checking "+to_string(id)+" bal "+to_string(bal); }
};

class DB { public: vector<unique_ptr<Account>> accts; };

class Admin {
    DB &db;
public:
    Admin(DB &d):db(d){}
    void addSavings(){ int id; double b; cout<<"id bal: "; cin>>id>>b; db.accts.emplace_back(make_unique<Savings>(id,b)); }
    void addChecking(){ int id; double b; cout<<"id bal: "; cin>>id>>b; db.accts.emplace_back(make_unique<Checking>(id,b)); }
    void view(){ for(auto &a:db.accts) cout<<a->info()<<"\n"; }
};

class User {
    DB &db;
public:
    User(DB &d):db(d){}
    void deposit(){ int id; double amt; cout<<"id amt: "; cin>>id>>amt; for(auto &a:db.accts) if(a->getId()==id){ a->deposit(amt); cout<<"Deposited\n"; return;} cout<<"Not found\n"; }
    void withdraw(){ int id; double amt; cout<<"id amt: "; cin>>id>>amt; for(auto &a:db.accts) if(a->getId()==id){ cout<<(a->withdraw(amt)?"Withdrawn\n":"Failed\n"); return;} cout<<"Not found\n"; }
    void view(){ for(auto &a:db.accts) cout<<a->info()<<"\n"; }
};

int main(){
    DB db; Admin admin(db); User user(db);
    int role;
    while(true){
        cout<<"\n1.Admin 2.User 3.Exit\nChoice: "; cin>>role;
        if(role==1){ int a; cout<<"1.AddSavings 2.AddChecking 3.View\n"; cin>>a; if(a==1)admin.addSavings(); else if(a==2)admin.addChecking(); else admin.view();}
        else if(role==2){ int a; cout<<"1.View 2.Deposit 3.Withdraw\n"; cin>>a; if(a==1)user.view(); else if(a==2)user.deposit(); else user.withdraw(); }
        else break;
    }
    return 0;
}