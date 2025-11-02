#include <bits/stdc++.h>
using namespace std;
// Employee Payroll - Admin and User
class Employee {
protected:
    int id; string name;
public:
    Employee(int i,string n):id(i),name(n){}
    virtual double pay() const = 0;
    virtual string info() const { return to_string(id)+": "+name; }
    int getId() const { return id; }
    virtual ~Employee()=default;
};

class Salaried: public Employee {
    double salary;
public:
    Salaried(int i,string n,double s):Employee(i,n),salary(s){}
    double pay() const override { return salary/12.0; }
};

class Hourly: public Employee {
    double rate,hours;
public:
    Hourly(int i,string n,double r,double h):Employee(i,n),rate(r),hours(h){}
    double pay() const override { return rate*hours; }
};

class DB { public: vector<unique_ptr<Employee>> emps; };

class Admin {
    DB &db;
public:
    Admin(DB &d):db(d){}
    void addSalary(){ int id; string n; double s; cout<<"id name salary: "; cin>>id>>n>>s; db.emps.emplace_back(make_unique<Salaried>(id,n,s)); }
    void addHourly(){ int id; string n; double r,h; cout<<"id name rate hours: "; cin>>id>>n>>r>>h; db.emps.emplace_back(make_unique<Hourly>(id,n,r,h)); }
    void view(){ for(auto &e:db.emps) cout<<e->info()<<" pays "<<e->pay()<<"\n"; }
};

class User {
    DB &db;
public:
    User(DB &d):db(d){}
    void viewPays(){ for(auto &e:db.emps) cout<<e->info()<<" -> "<<e->pay()<<"\n"; }
};

int main(){
    DB db; Admin admin(db); User user(db);
    int role;
    while(true){
        cout<<"\n1.Admin 2.User 3.Exit\nChoice: "; cin>>role;
        if(role==1){ int a; cout<<"1.AddSalaried 2.AddHourly 3.View\n"; cin>>a; if(a==1)admin.addSalary(); else if(a==2)admin.addHourly(); else admin.view();}
        else if(role==2){ user.viewPays(); }
        else break;
    }
    return 0;
}