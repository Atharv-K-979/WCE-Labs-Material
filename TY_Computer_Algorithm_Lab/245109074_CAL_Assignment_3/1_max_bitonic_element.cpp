#include<iostream>
#include<vector>
using namespace std;
int maxBitonic(vector<int>&arr){
    int low=0,high=arr.size()-1;
    while(low<high){
        int mid=(low+high)/2;
        if(arr[mid]<arr[mid+1])
            low=mid+1;
        else
            high=mid;
    }
    return arr[low];
}
int main(){
    vector<vector<int>>tests={
        {1,3,8,12,4,2},
        {1,2,3,4,5},
        {9,7,5,3,1},
        {1,5,10,15,20,18,10,5},
        {2,4,6,8,10,9,7,3,1}
    };
    for(int i=0;i<(int)tests.size();i++)
        cout<<"test case "<<i+1<<": maximum element is "<<maxBitonic(tests[i])<<endl;
    return 0;
}
