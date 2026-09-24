#include<iostream>
#include<vector>
#include<utility>
using namespace std;
const int INF=1000000000;
const int HIGH=7;
int n;
vector<int>adj,weight;
vector<char>indep;
void setup(int count,vector<pair<int,int>>conflicts,vector<int>w){
    n=count;
    weight=w;
    adj.assign(n,0);
    for(auto&c:conflicts){
        adj[c.first]|=1<<c.second;
        adj[c.second]|=1<<c.first;
    }
    indep.assign(1<<n,1);
    for(int mask=0;mask<(1<<n);mask++){
        for(int i=0;i<n;i++){
            if(((mask>>i)&1)&&(adj[i]&mask))
                indep[mask]=0;
        }
    }
}
int minSlots(){
    int full=(1<<n)-1;
    vector<int>dp(full+1,INF);
    dp[0]=0;
    for(int mask=1;mask<=full;mask++){
        int low=mask&-mask;
        for(int sub=mask;sub>0;sub=(sub-1)&mask){
            if((sub&low)&&indep[sub]&&dp[mask^sub]+1<dp[mask])
                dp[mask]=dp[mask^sub]+1;
        }
    }
    return dp[full];
}
int pairCost(int a,int b){
    int cost=0;
    for(int i=0;i<n;i++){
        if(!((a>>i)&1))
            continue;
        for(int j=0;j<n;j++){
            if(((b>>j)&1)&&((adj[i]>>j)&1)&&weight[i]>=HIGH&&weight[j]>=HIGH)
                cost+=weight[i]+weight[j];
        }
    }
    return cost;
}
int arrange(int slots,vector<int>&slotOf){
    int full=(1<<n)-1;
    vector<vector<int>>table(full+1,vector<int>(full+1,INF));
    vector<vector<vector<int>>>dp(slots+1,table);
    table.assign(full+1,vector<int>(full+1,-1));
    vector<vector<vector<int>>>par(slots+1,table);
    for(int s=1;s<=full;s++){
        if(indep[s])
            dp[1][s][s]=0;
    }
    for(int j=1;j<slots;j++){
        for(int mask=1;mask<=full;mask++){
            for(int last=mask;last>0;last=(last-1)&mask){
                int cur=dp[j][mask][last];
                if(cur>=INF)
                    continue;
                int rest=full^mask;
                for(int nxt=rest;nxt>0;nxt=(nxt-1)&rest){
                    if(!indep[nxt])
                        continue;
                    int c=cur+pairCost(last,nxt);
                    if(c<dp[j+1][mask|nxt][nxt]){
                        dp[j+1][mask|nxt][nxt]=c;
                        par[j+1][mask|nxt][nxt]=last;
                    }
                }
            }
        }
    }
    int best=INF,bestLast=0;
    for(int last=1;last<=full;last++){
        if(dp[slots][full][last]<best){
            best=dp[slots][full][last];
            bestLast=last;
        }
    }
    int mask=full,last=bestLast;
    slotOf.assign(n,0);
    for(int j=slots;j>=1;j--){
        for(int i=0;i<n;i++){
            if((last>>i)&1)
                slotOf[i]=j;
        }
        int before=par[j][mask][last];
        mask^=last;
        last=before;
    }
    return best;
}
void run(int tc,int count,vector<pair<int,int>>conflicts,vector<int>w){
    setup(count,conflicts,w);
    int k=minSlots();
    vector<int>slotOf;
    int penalty=arrange(k,slotOf);
    cout<<"test case "<<tc<<": minimum number of slots is "<<k<<endl;
    for(int s=1;s<=k;s++){
        cout<<"  slot "<<s<<":";
        for(int i=0;i<n;i++){
            if(slotOf[i]==s)
                cout<<" E"<<i+1<<"(d="<<weight[i]<<")";
        }
        cout<<endl;
    }
    cout<<"  total adjacent difficulty penalty is "<<penalty<<endl;
}
int main(){
    run(1,5,{{0,1},{0,2},{1,2},{2,3},{3,4}},{8,9,7,3,8});
    run(2,6,{{0,1},{1,2},{2,3},{3,4},{4,5},{5,0}},{9,4,8,3,9,8});
    run(3,4,{{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}},{9,2,8,7});
    run(4,7,{},{5,9,3,8,7,2,10});
    run(5,8,{{0,1},{1,2},{2,3},{3,4},{4,0},{5,6},{6,7},{5,7},{0,5},{2,6}},
        {8,7,9,3,10,8,2,9});
    return 0;
}
