#include<iostream>
#include<vector>
using namespace std;
int search(vector<string>&arr,string target){
    int low=0,high=arr.size()-1;
    while(low<=high){
        int mid=(low+high)/2;
        while(mid<=high&&arr[mid]=="")
            mid++;
        if(mid>high){
            high=(low+high)/2-1;
            continue;
        }
        if(arr[mid]==target)
            return mid;
        if(arr[mid]<target)
            low=mid+1;
        else
            high=mid-1;
    }
    return -1;
}
int main(){
    int n;
    cout<<"enter size of array: ";
    cin>>n;
    vector<string>arr(n);
    cout<<"enter "<<n<<" strings use hyphen for empty string: ";
    for(int i=0;i<n;i++){
        cin>>arr[i];
        if(arr[i]=="-")
            arr[i]="";
    }
    string target;
    cout<<"enter string to search: ";
    cin>>target;
    int idx=search(arr,target);
    if(idx!=-1)
        cout<<"string found at index "<<idx;
    else
        cout<<"string not found";
    return 0;
}
