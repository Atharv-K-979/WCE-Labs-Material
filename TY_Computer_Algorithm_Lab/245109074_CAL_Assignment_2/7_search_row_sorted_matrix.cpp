#include<iostream>
#include<vector>
using namespace std;
bool searchMatrix(vector<vector<int>>&arr,int target){
    for(int i=0;i<(int)arr.size();i++){
        int n=arr[i].size();
        if(target<arr[i][0]||target>arr[i][n-1])
            continue;
        int low=0,high=n-1;
        while(low<=high){
            int mid=(low+high)/2;
            if(arr[i][mid]==target)
                return true;
            if(arr[i][mid]<target)
                low=mid+1;
            else
                high=mid-1;
        }
    }
    return false;
}
int main(){
    vector<vector<vector<int>>>matrices={
        {{1,4,7},{2,5,8},{3,6,9}},
        {{1,4,7},{2,5,8},{3,6,9}},
        {{1,2,3},{10,11,12},{20,21,22}},
        {{1,2,3},{10,11,12},{20,21,22}},
        {{5}}
    };
    int targets[]={5,10,21,15,5};
    for(int i=0;i<5;i++){
        bool found=searchMatrix(matrices[i],targets[i]);
        cout<<"test case "<<i+1<<": "<<(found?"true":"false")<<endl;
    }
    return 0;
}
