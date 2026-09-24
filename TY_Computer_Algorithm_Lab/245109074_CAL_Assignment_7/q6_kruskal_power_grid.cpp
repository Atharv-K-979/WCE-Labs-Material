#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Edge{int u,v,cost;};
vector<int>parent,rnk;
int findSet(int x){
    if(parent[x]!=x)
        parent[x]=findSet(parent[x]);
    return parent[x];
}
bool unite(int a,int b){
    a=findSet(a);
    b=findSet(b);
    if(a==b)
        return false;
    if(rnk[a]<rnk[b])
        swap(a,b);
    parent[b]=a;
    if(rnk[a]==rnk[b])
        rnk[a]++;
    return true;
}
void kruskal(int tc,int n,vector<Edge>edges){
    parent.assign(n,0);
    rnk.assign(n,0);
    for(int i=0;i<n;i++)
        parent[i]=i;
    sort(edges.begin(),edges.end(),[](const Edge&a,const Edge&b){
        return a.cost<b.cost;
    });
    int total=0;
    vector<Edge>chosen;
    for(Edge&e:edges){
        if(unite(e.u,e.v)){
            total+=e.cost;
            chosen.push_back(e);
        }
    }
    vector<vector<int>>comp(n);
    for(int i=0;i<n;i++)
        comp[findSet(i)].push_back(i);
    int parts=0;
    for(int i=0;i<n;i++){
        if(!comp[i].empty())
            parts++;
    }
    cout<<"test case "<<tc<<": ";
    if(parts==1)
        cout<<"graph is connected, total minimum cost is "<<total<<endl;
    else{
        cout<<"graph is disconnected with "<<parts<<" components, ";
        cout<<"minimum spanning forest cost is "<<total<<endl;
    }
    for(Edge&e:chosen){
        cout<<"  selected edge: city "<<e.u<<" - city "<<e.v;
        cout<<" (cost "<<e.cost<<")"<<endl;
    }
    if(parts>1){
        int id=1;
        for(int i=0;i<n;i++){
            if(comp[i].empty())
                continue;
            cout<<"  component "<<id++<<":";
            for(int city:comp[i])
                cout<<" "<<city;
            cout<<endl;
        }
    }
}
int main(){
    kruskal(1,6,{{0,1,4},{0,2,4},{1,2,2},{2,3,3},{2,5,2},{2,4,4},{3,4,3},
        {5,4,3}});
    kruskal(2,6,{{0,1,3},{1,2,1},{0,2,4},{3,4,2},{4,5,5},{3,5,6}});
    kruskal(3,5,{{0,1,7},{1,2,2},{0,2,9}});
    kruskal(4,4,{});
    kruskal(5,5,{{0,1,1},{1,2,2},{2,3,3},{3,4,4},{4,0,5},{0,2,6},{1,3,7},
        {2,4,8}});
    return 0;
}
