#include <bits/stdc++.h>
using namespace std;
// Student Management - Admin and User
class Student {
protected:
    int id; string name; double gpa;
public:
    Student(int i,string n,double g):id(i),name(n),gpa(g){}
    virtual string info() const { return to_string(id)+": "+name+" GPA:"+to_string(gpa); }
    int getId() const { return id; }
    void setGpa(double g){ gpa=g; }
};

class DB { public: vector<unique_ptr<Student>> students; };

class Admin {
    DB &db;
public:
    Admin(DB &d):db(d){}
    void add(){ int id; string n; double g; cout<<"id name gpa: "; cin>>id>>n>>g; db.students.emplace_back(make_unique<Student>(id,n,g)); cout<<"Added\n"; }
    void view(){ for(auto &s:db.students) cout<<s->info()<<"\n"; }
    void update(){
        int id; double g; cout<<"id newgpa: "; cin>>id>>g;
        for(auto &s:db.students) if(s->getId()==id){ s->setGpa(g); cout<<"Updated\n"; return; }
        cout<<"Not found\n";
    }
};

class User {
    DB &db;
public:
    User(DB &d):db(d){}
    void viewAll(){ for(auto &s:db.students) cout<<s->info()<<"\n"; }
    void viewOne(){ int id; cout<<"id: "; cin>>id; for(auto &s:db.students) if(s->getId()==id) cout<<s->info()<<"\n"; }
};

int main(){
    DB db; Admin admin(db); User user(db);
    int role;
    while(true){
        cout<<"\n1.Admin 2.User 3.Exit\nChoice: "; cin>>role;
        if(role==1){ int a; cout<<"1.Add 2.View 3.Update\n"; cin>>a; if(a==1)admin.add(); else if(a==2)admin.view(); else admin.update();}
        else if(role==2){ int a; cout<<"1.ViewAll 2.ViewOne\n"; cin>>a; if(a==1)user.viewAll(); else user.viewOne(); }
        else break;
    }
    return 0;
}