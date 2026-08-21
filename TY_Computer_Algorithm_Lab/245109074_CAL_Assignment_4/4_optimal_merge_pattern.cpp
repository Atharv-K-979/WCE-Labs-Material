#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int optimalMerge(vector<int>sizes){
    priority_queue<int,vector<int>,greater<int>>pq(sizes.begin(),sizes.end());
    int totalcost=0;
    while(pq.size()>1){
        int a=pq.top();
        pq.pop();
        int b=pq.top();
        pq.pop();
        int merged=a+b;
        totalcost+=merged;
        pq.push(merged);
    }
    return totalcost;
}
int main(){
    vector<int>branchA={35,110,180,8};
    vector<int>branchB={25,12,240,85,55};
    vector<int>branchC={95,65,30,50,80,40};
    vector<int>branchD={480,290,140,20,65};
    vector<int>allBranches={35,110,180,8,25,12,240,85,55,95,65,30,50,80,40,480,290,140,20,65};
    cout<<"test case 1: minimum merge cost is "<<optimalMerge(branchA)<<endl;
    cout<<"test case 2: minimum merge cost is "<<optimalMerge(branchB)<<endl;
    cout<<"test case 3: minimum merge cost is "<<optimalMerge(branchC)<<endl;
    cout<<"test case 4: minimum merge cost is "<<optimalMerge(branchD)<<endl;
    cout<<"test case 5: minimum merge cost is "<<optimalMerge(allBranches)<<endl;
    return 0;
}



// Optimal Merge Pattern
// O(n log n)
// O(n log n)
// O(n log n)