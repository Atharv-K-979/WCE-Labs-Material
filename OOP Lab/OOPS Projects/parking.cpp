#include <bits/stdc++.h>
using namespace std;
// Parking Management - Admin and User
struct Spot { int id; bool occupied; Spot(int i):id(i),occupied(false){} string info() const { return "Spot "+to_string(id)+(occupied?" occupied":" free"); } };

class DB { public: vector<Spot> spots; };

class Admin {
    DB &db;
public:
    Admin(DB &d):db(d){}
    void init(){ int n; cout<<"num spots: "; cin>>n; db.spots.clear(); for(int i=1;i<=n;i++) db.spots.emplace_back(i); cout<<"Init done\n"; }
    void view(){ for(auto &s:db.spots) cout<<s.info()<<"\n"; }
};

class User {
    DB &db;
public:
    User(DB &d):db(d){}
    int park(){ for(auto &s:db.spots) if(!s.occupied){ s.occupied=true; cout<<"Parked at "<<s.id<<"\n"; return s.id; } cout<<"Full\n"; return -1; }
    void leave(){ int id; cout<<"spot id to leave: "; cin>>id; for(auto &s:db.spots) if(s.id==id){ s.occupied=false; cout<<"Left\n"; return;} cout<<"Not found\n"; }
    void view(){ for(auto &s:db.spots) cout<<s.info()<<"\n"; }
};

int main(){
    DB db; Admin admin(db); User user(db);
    int role;
    while(true){
        cout<<"\n1.Admin 2.User 3.Exit\nChoice: "; cin>>role;
        if(role==1){ int a; cout<<"1.Init 2.View\n"; cin>>a; if(a==1)admin.init(); else admin.view(); }
        else if(role==2){ int a; cout<<"1.Park 2.Leave 3.View\n"; cin>>a; if(a==1)user.park(); else if(a==2)user.leave(); else user.view(); }
        else break;
    }
    return 0;
}