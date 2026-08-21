#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Job{
    int deadline;
    int payout;
};
bool cmpPayout(Job a,Job b){
    return a.payout>b.payout;
}
int jobSequencing(vector<Job>jobs,int slots){
    sort(jobs.begin(),jobs.end(),cmpPayout);
    vector<bool>slotUsed(slots+1,false);
    int total=0;
    for(auto job:jobs){
        for(int t=min(slots,job.deadline);t>=1;t--){
            if(!slotUsed[t]){
                slotUsed[t]=true;
                total+=job.payout;
                break;
            }
        }
    }
    return total;
}
int main(){
    vector<Job>test1={{2,450},{1,300},{3,220},{2,600},{1,150},{4,700},{3,90},{2,500},{4,260},{1,800}};
    vector<Job>test2={{1,20},{2,15},{1,10},{3,5}};
    vector<Job>test3={{1,100},{1,50}};
    vector<Job>test4={{5,10},{4,20},{3,30},{2,40},{1,50}};
    vector<Job>test5={{1,100}};
    cout<<"test case 1: maximum payout is "<<jobSequencing(test1,10)<<endl;
    cout<<"test case 2: maximum payout is "<<jobSequencing(test2,3)<<endl;
    cout<<"test case 3: maximum payout is "<<jobSequencing(test3,2)<<endl;
    cout<<"test case 4: maximum payout is "<<jobSequencing(test4,5)<<endl;
    cout<<"test case 5: maximum payout is "<<jobSequencing(test5,0)<<endl;
    return 0;
}


// Job Sequencing
// O(n log n)
// O(n²)
// O(n²)