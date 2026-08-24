#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<string>
using namespace std;

void dijkstra(vector<string> name, vector<vector<pair<int,int>>> adj, int src, int target){
    int n=name.size();
    vector<int> dist(n,INT_MAX);
    vector<int> parent(n,-1);
    dist[src]=0;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,src});

    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u]) continue;

        for(auto &[v,w]:adj[u]){
            if(dist[u]!=INT_MAX && dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                parent[v]=u;
                pq.push({dist[v],v});
            }
        }
    }

    cout<<"Shortest distance from "<<name[src]<<" to "<<name[target]<<": ";
    if(dist[target]==INT_MAX){
        cout<<"unreachable\n";
        return;
    }

    cout<<dist[target]<<" ms\n";
    cout<<"Shortest path: ";
    vector<int> path;
    for(int v=target;v!=-1;v=parent[v]) path.push_back(v);

    for(int i=path.size()-1;i>=0;i--){
        cout<<name[path[i]];
        if(i>0) cout<<" -> ";
    }
    cout<<"\n";
}

int main(){
    // Test Case 1
    {
        vector<string> name={"S","A","B","C","D"};
        vector<vector<pair<int,int>>> adj(5);
        adj[0]={{1,4},{2,8}};
        adj[1]={{2,2},{3,5}};
        adj[2]={{3,1},{4,7}};
        adj[3]={{4,3}};
        cout<<" Test Case 1 \n";
        dijkstra(name,adj,0,4);
    }

    // Test Case 2
    {
        vector<string> name={"S","A","B","C"};
        vector<vector<pair<int,int>>> adj(4);
        adj[0]={{1,10},{2,3}};
        adj[2]={{1,2},{3,8}};
        adj[1]={{3,1}};
        cout<<"\n Test Case 2 \n";
        dijkstra(name,adj,0,3);
    }

    // Test Case 3
    {
        vector<string> name={"S","A","B","C","D"};
        vector<vector<pair<int,int>>> adj(5);
        adj[0]={{1,5}};
        adj[1]={{2,4}};
        adj[2]={{3,2}};
        adj[3]={{4,1}};
        cout<<"\n Test Case 3 \n";
        dijkstra(name,adj,0,4);
    }

    // Test Case 4
    {
        vector<string> name={"S","A","B","C","D"};
        vector<vector<pair<int,int>>> adj(5);
        adj[0]={{1,2},{2,1}};
        adj[1]={{3,2}};
        adj[2]={{3,6}};
        adj[3]={{4,3}};
        cout<<"\n Test Case 4 \n";
        dijkstra(name,adj,0,4);
    }

    // Test Case 5 - unreachable destination
    {
        vector<string> name={"S","A","B","C"};
        vector<vector<pair<int,int>>> adj(4);
        adj[0]={{1,4}};
        adj[1]={{2,5}};
        cout<<"\n Test Case 5 \n";
        dijkstra(name,adj,0,3);
    }

    return 0;
}
