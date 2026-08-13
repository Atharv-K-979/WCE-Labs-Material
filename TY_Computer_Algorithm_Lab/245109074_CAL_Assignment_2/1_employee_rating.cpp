#include<iostream>
#include<vector>
using namespace std;
int employeeRating(vector<int>&workload){
    int count=0,maxcount=0;
    for(int i=0;i<(int)workload.size();i++){
        if(workload[i]>6)
            count++;
        else
            count=0;
        if(count>maxcount)
            maxcount=count;
    }
    return maxcount;
}
int main(){
    vector<vector<int>>tests={
        {10,9,8,3,7,8,9,1,6},
        {7,7,7,7},
        {1,2,3,4,5,6},
        {8,2,9,10,11,3,3,7,8,9,10},
        {8}
    };
    for(int i=0;i<(int)tests.size();i++)
        cout<<"test case "<<i+1<<": employee rating is "<<employeeRating(tests[i])<<endl;
    return 0;
}
