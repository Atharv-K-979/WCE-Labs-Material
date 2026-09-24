#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;
struct Job{int time,deadline,penalty,id;};
int minPenalty(vector<Job>jobs,vector<int>&order){
    sort(jobs.begin(),jobs.end(),[](const Job&a,const Job&b){
        return a.deadline<b.deadline;
    });
    int n=jobs.size(),total=0;
    for(Job&j:jobs)
        total+=j.time;
    const int INF=INT_MAX/2;
    vector<vector<int>>dp(n+1,vector<int>(total+1,INF));
    vector<vector<int>>onTime(n+1,vector<int>(total+1,0));
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        Job&j=jobs[i-1];
        for(int t=0;t<=total;t++){
            if(dp[i-1][t]>=INF)
                continue;
            if(dp[i-1][t]+j.penalty<dp[i][t]){
                dp[i][t]=dp[i-1][t]+j.penalty;
                onTime[i][t]=0;
            }
            if(t+j.time<=j.deadline&&dp[i-1][t]<dp[i][t+j.time]){
                dp[i][t+j.time]=dp[i-1][t];
                onTime[i][t+j.time]=1;
            }
        }
    }
    int bestT=0;
    for(int t=1;t<=total;t++){
        if(dp[n][t]<dp[n][bestT])
            bestT=t;
    }
    int result=dp[n][bestT];
    vector<int>early,late;
    int t=bestT;
    for(int i=n;i>=1;i--){
        if(onTime[i][t]){
            early.push_back(jobs[i-1].id);
            t-=jobs[i-1].time;
        }
        else
            late.push_back(jobs[i-1].id);
    }
    reverse(early.begin(),early.end());
    reverse(late.begin(),late.end());
    order=early;
    order.insert(order.end(),late.begin(),late.end());
    return result;
}
void run(int tc,vector<vector<int>>data){
    vector<Job>jobs;
    for(int i=0;i<(int)data.size();i++){
        Job j;
        j.time=data[i][0];
        j.deadline=data[i][1];
        j.penalty=data[i][2];
        j.id=i+1;
        jobs.push_back(j);
    }
    vector<int>order;
    int best=minPenalty(jobs,order);
    cout<<"test case "<<tc<<": minimum penalty is "<<best<<endl;
    cout<<"  job order:";
    for(int id:order)
        cout<<" J"<<id;
    cout<<endl;
    int clock=0;
    for(int id:order){
        Job&j=jobs[id-1];
        clock+=j.time;
        cout<<"  J"<<id<<" finishes at "<<clock;
        cout<<" (deadline "<<j.deadline<<") ";
        if(clock>j.deadline)
            cout<<"late, penalty "<<j.penalty<<endl;
        else
            cout<<"on time"<<endl;
    }
}
int main(){
    run(1,{{2,3,10},{1,2,20},{3,7,15},{2,6,5},{4,9,25}});
    run(2,{{4,4,10},{3,5,20},{2,6,30}});
    run(3,{{3,3,5},{3,3,8},{3,3,6}});
    run(4,{{5,20,40},{2,4,10},{3,8,25},{4,9,30},{1,3,15},{2,10,12}});
    run(5,{{6,5,50}});
    return 0;
}
