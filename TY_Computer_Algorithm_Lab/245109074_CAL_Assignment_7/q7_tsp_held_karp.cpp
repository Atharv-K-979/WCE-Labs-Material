#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1000000000;
int heldKarp(vector<vector<int>>&dist,int base,vector<int>&route){
    int n=dist.size();
    route.clear();
    if(n==1){
        route.push_back(base);
        route.push_back(base);
        return 0;
    }
    int full=(1<<n)-1;
    vector<vector<int>>dp(1<<n,vector<int>(n,INF));
    vector<vector<int>>par(1<<n,vector<int>(n,-1));
    dp[1<<base][base]=0;
    for(int mask=0;mask<=full;mask++){
        if(!((mask>>base)&1))
            continue;
        for(int last=0;last<n;last++){
            if(!((mask>>last)&1)||dp[mask][last]>=INF)
                continue;
            for(int nxt=0;nxt<n;nxt++){
                if((mask>>nxt)&1)
                    continue;
                int nm=mask|(1<<nxt);
                int c=dp[mask][last]+dist[last][nxt];
                if(c<dp[nm][nxt]){
                    dp[nm][nxt]=c;
                    par[nm][nxt]=last;
                }
            }
        }
    }
    int best=INF,lastCity=-1;
    for(int last=0;last<n;last++){
        if(last==base||dp[full][last]>=INF)
            continue;
        if(dp[full][last]+dist[last][base]<best){
            best=dp[full][last]+dist[last][base];
            lastCity=last;
        }
    }
    int mask=full,cur=lastCity;
    while(cur!=-1){
        route.push_back(cur);
        int before=par[mask][cur];
        mask^=1<<cur;
        cur=before;
    }
    reverse(route.begin(),route.end());
    route.push_back(base);
    return best;
}
void run(int tc,vector<vector<int>>dist,int base){
    vector<int>route;
    int best=heldKarp(dist,base,route);
    cout<<"test case "<<tc<<": base warehouse is "<<base;
    cout<<", minimum route distance is "<<best<<endl;
    cout<<"  route:";
    for(int i=0;i<(int)route.size();i++){
        if(i>0)
            cout<<" ->";
        cout<<" "<<route[i];
    }
    cout<<endl;
}
int main(){
    vector<vector<int>>d1={{0,10,15,20},{10,0,35,25},{15,35,0,30},
        {20,25,30,0}};
    vector<vector<int>>d2={{0,2,9,10,7},{1,0,6,4,3},{15,7,0,8,3},
        {6,3,12,0,11},{9,7,5,6,0}};
    vector<vector<int>>d3={{0,3,4,2,7,5},{3,0,4,6,3,8},{4,4,0,5,8,2},
        {2,6,5,0,6,4},{7,3,8,6,0,5},{5,8,2,4,5,0}};
    run(1,d1,0);
    run(2,d1,2);
    run(3,d2,0);
    run(4,{{0,12},{12,0}},1);
    run(5,d3,3);
    return 0;
}
