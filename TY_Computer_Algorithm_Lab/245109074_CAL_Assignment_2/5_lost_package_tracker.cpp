#include<iostream>
#include<vector>
using namespace std;
int findMissing(vector<int>&timestamps){
    for(int i=1;i<(int)timestamps.size();i++){
        if(timestamps[i]-timestamps[i-1]>1)
            return timestamps[i-1]+1;
    }
    return -1;
}
int main(){
    vector<vector<int>>tests={
        {1001,1002,1004,1005},
        {5,6,7,8,9},
        {10,12},
        {100,101,102,105,106},
        {2000,2001,2002,2003,2005,2006}
    };
    for(int i=0;i<(int)tests.size();i++){
        int missing=findMissing(tests[i]);
        if(missing!=-1)
            cout<<"test case "<<i+1<<": first missing timestamp is "<<missing<<endl;
        else
            cout<<"test case "<<i+1<<": no timestamp is missing"<<endl;
    }
    return 0;
}
