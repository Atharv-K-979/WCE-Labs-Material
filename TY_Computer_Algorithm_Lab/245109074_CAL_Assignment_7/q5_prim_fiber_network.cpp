#include<iostream>
#include<vector>
#include<climits>
using namespace std;
struct Edge{int u,v,cost;};
void primMST(int tc,int n,vector<Edge>edges,int hub){
    vector<vector<int>>g(n,vector<int>(n,0));
    for(Edge&e:edges){
        g[e.u][e.v]=e.cost;
        g[e.v][e.u]=e.cost;
    }
    vector<int>key(n,INT_MAX),parent(n,-1);
    vector<bool>used(n,false);
    vector<Edge>cables;
    key[hub]=0;
    int total=0,reached=0;
    for(int step=0;step<n;step++){
        int u=-1;
        for(int v=0;v<n;v++){
            if(!used[v]&&(u==-1||key[v]<key[u]))
                u=v;
        }
        if(key[u]==INT_MAX)
            break;
        used[u]=true;
        reached++;
        if(parent[u]!=-1){
            total+=key[u];
            cables.push_back({parent[u],u,key[u]});
        }
        for(int v=0;v<n;v++){
            if(g[u][v]>0&&!used[v]&&g[u][v]<key[v]){
                key[v]=g[u][v];
                parent[v]=u;
            }
        }
    }
    cout<<"test case "<<tc<<": hub town is "<<hub<<endl;
    if(reached<n){
        cout<<"  network cannot reach all towns, only "<<reached;
        cout<<" of "<<n<<" towns connected"<<endl;
        return;
    }
    cout<<"  total minimum cost is "<<total<<endl;
    for(Edge&c:cables){
        cout<<"  cable: town "<<c.u<<" - town "<<c.v;
        cout<<" (cost "<<c.cost<<")"<<endl;
    }
}
int main(){
    primMST(1,5,{{0,1,2},{0,3,6},{1,2,3},{1,3,8},{1,4,5},{2,4,7},{3,4,9}},0);
    primMST(2,4,{{0,1,10},{0,2,6},{0,3,5},{1,3,15},{2,3,4}},2);
    primMST(3,6,{{0,1,4},{0,2,4},{1,2,2},{2,3,3},{2,5,2},{2,4,4},{3,4,3},
        {5,4,3}},3);
    primMST(4,2,{{0,1,7}},1);
    primMST(5,4,{{0,1,3},{2,3,5}},0);
    return 0;
}
