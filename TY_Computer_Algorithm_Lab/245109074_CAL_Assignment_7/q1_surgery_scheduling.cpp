#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
struct Surgery{int start,finish,priority,id;};
vector<Surgery>ops;
map<pair<int,vector<int>>,int>memo;
int solveRooms(int i,vector<int>busy){
    if(i==(int)ops.size())
        return 0;
    for(int&f:busy){
        if(f<=ops[i].start)
            f=0;
    }
    sort(busy.begin(),busy.end());
    pair<int,vector<int>>key=make_pair(i,busy);
    auto it=memo.find(key);
    if(it!=memo.end())
        return it->second;
    int best=solveRooms(i+1,busy);
    if(busy[0]==0){
        vector<int>nxt=busy;
        nxt[0]=ops[i].finish;
        best=max(best,ops[i].priority+solveRooms(i+1,nxt));
    }
    memo[key]=best;
    return best;
}
int multiRoom(vector<Surgery>all,int k,vector<pair<Surgery,int>>&plan){
    sort(all.begin(),all.end(),[](const Surgery&a,const Surgery&b){
        if(a.start!=b.start)
            return a.start<b.start;
        return a.finish<b.finish;
    });
    ops=all;
    memo.clear();
    int total=solveRooms(0,vector<int>(k,0));
    vector<int>busy(k,0);
    vector<Surgery>chosen;
    for(int i=0;i<(int)ops.size();i++){
        for(int&f:busy){
            if(f<=ops[i].start)
                f=0;
        }
        sort(busy.begin(),busy.end());
        int skip=solveRooms(i+1,busy);
        int take=-1;
        vector<int>nxt=busy;
        if(busy[0]==0){
            nxt[0]=ops[i].finish;
            take=ops[i].priority+solveRooms(i+1,nxt);
        }
        if(take>skip){
            chosen.push_back(ops[i]);
            busy=nxt;
        }
    }
    vector<int>roomFree(k,0);
    for(Surgery&s:chosen){
        for(int r=0;r<k;r++){
            if(roomFree[r]<=s.start){
                roomFree[r]=s.finish;
                plan.push_back(make_pair(s,r+1));
                break;
            }
        }
    }
    return total;
}
int singleRoom(vector<Surgery>all,vector<Surgery>&chosen){
    sort(all.begin(),all.end(),[](const Surgery&a,const Surgery&b){
        return a.finish<b.finish;
    });
    int n=all.size();
    vector<int>dp(n+1,0),before(n+1,0);
    for(int i=1;i<=n;i++){
        int lo=0,hi=i-1;
        while(lo<hi){
            int mid=(lo+hi+1)/2;
            if(all[mid-1].finish<=all[i-1].start)
                lo=mid;
            else
                hi=mid-1;
        }
        before[i]=lo;
        dp[i]=max(dp[i-1],all[i-1].priority+dp[lo]);
    }
    int i=n;
    while(i>0){
        if(dp[i]==dp[i-1])
            i--;
        else{
            chosen.push_back(all[i-1]);
            i=before[i];
        }
    }
    reverse(chosen.begin(),chosen.end());
    return dp[n];
}
vector<Surgery>build(vector<vector<int>>data){
    vector<Surgery>all;
    for(int i=0;i<(int)data.size();i++){
        Surgery s;
        s.start=data[i][0];
        s.finish=data[i][1];
        s.priority=data[i][2];
        s.id=i+1;
        all.push_back(s);
    }
    return all;
}
void run(int tc,vector<Surgery>all,int k){
    vector<pair<Surgery,int>>plan;
    int best=multiRoom(all,k,plan);
    cout<<"test case "<<tc<<": rooms="<<k;
    cout<<", maximum priority is "<<best<<endl;
    for(auto&p:plan){
        Surgery&s=p.first;
        cout<<"  surgery "<<s.id<<" ("<<s.start<<"-"<<s.finish;
        cout<<", priority "<<s.priority<<") -> room "<<p.second<<endl;
    }
    if(k==1){
        vector<Surgery>chosen;
        cout<<"  single room dp result is "<<singleRoom(all,chosen)<<endl;
    }
}
int main(){
    vector<Surgery>s1=build({{1,2,50},{3,5,20},{6,19,100},{2,100,200}});
    vector<Surgery>s2=build({{9,12,40},{10,14,50},{11,13,30},
        {12,15,60},{13,16,20}});
    vector<Surgery>s3=build({{1,4,10},{2,6,20},{3,5,15},
        {5,8,25},{7,10,30},{4,9,12}});
    run(1,s1,1);
    run(2,s1,2);
    run(3,s2,1);
    run(4,s2,3);
    run(5,s3,2);
    return 0;
}
