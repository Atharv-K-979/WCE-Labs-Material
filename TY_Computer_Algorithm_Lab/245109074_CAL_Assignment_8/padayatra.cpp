#include<bits/stdc++.h>
using namespace std;

using ll=long long;
const ll INF=(1LL<<62);

struct Edge{
    int u,v;
    ll w;
};

ll solve(istream&in){
    int M;
    in>>M;

    vector<Edge>edges(M);
    int V=0;

    for(int i=0;i<M;++i){
        in>>edges[i].u>>edges[i].v>>edges[i].w;
        V=max(V,max(edges[i].u,edges[i].v));
    }

    vector<vector<pair<int,int>>>adj(V+1);

    for(int id=0;id<M;++id){
        adj[edges[id].u].push_back({edges[id].v,id});
        adj[edges[id].v].push_back({edges[id].u,id});
    }

    ll answer=INF;
    vector<ll>dist(V+1);
    vector<int>parentEdge(V+1);

    for(int s=1;s<=V;++s){
        fill(dist.begin(),dist.end(),INF);
        fill(parentEdge.begin(),parentEdge.end(),-1);

        priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>pq;

        dist[s]=0;
        pq.push({0,s});

        while(!pq.empty()){
            auto[du,u]=pq.top();
            pq.pop();

            if(du!=dist[u])
                continue;

            for(auto[v,id]:adj[u]){
                const Edge&e=edges[id];
                ll nd=du+e.w;

                if(nd<dist[v]){
                    dist[v]=nd;
                    parentEdge[v]=id;
                    pq.push({nd,v});
                }
            }
        }

        for(int id=0;id<M;++id){
            const Edge&e=edges[id];

            if(parentEdge[e.u]==id||parentEdge[e.v]==id)
                continue;

            if(dist[e.u]==INF||dist[e.v]==INF)
                continue;

            ll candidate=dist[e.u]+e.w+dist[e.v];
            answer=min(answer,candidate);
        }
    }

    return answer;
}


// CHP JUDGE MAIN
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout<<solve(cin)<<'\n';

    return 0;
}

// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     ifstream fin("testcases.txt");
//     ofstream fout("output.txt");

//     if(!fin){
//         cerr<<"Error: testcases.txt not found\n";
//         return 1;
//     }

//     if(!fout){
//         cerr<<"Error: output.txt could not be created\n";
//         return 1;
//     }

//     int T;
//     fin>>T;

//     for(int tc=1;tc<=T;++tc){
//         fout<<solve(fin)<<'\n';
//     }

//     fin.close();
//     fout.close();

//     cout<<"Processed "<<T<<" test cases. Results written to output.txt\n";

//     return 0;
// }




// g++ -std=c++17 -O2 padayatra.cpp -o padayatra
// ./padayatra