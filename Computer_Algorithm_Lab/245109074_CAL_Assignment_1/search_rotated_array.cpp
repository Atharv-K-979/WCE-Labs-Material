#include<iostream>
using namespace std;
int search(int arr[],int n,int target){
    int low=0,high=n-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]==target)
            return mid;
        if(arr[low]<=arr[mid]){
            if(target>=arr[low]&&target<arr[mid])
                high=mid-1;
            else
                low=mid+1;
        }
        else{
            if(target>arr[mid]&&target<=arr[high])
                low=mid+1;
            else
                high=mid-1;
        }
    }
    return -1;
}
int main(){
    int n;
    cout<<"enter size of array: ";
    cin>>n;
    int arr[n];
    cout<<"enter "<<n<<" rotated sorted elements: ";
    for(int i=0;i<n;i++)
        cin>>arr[i];
    int target;
    cout<<"enter element to search: ";
    cin>>target;
    int idx=search(arr,n,target);
    if(idx!=-1)
        cout<<"element found at index "<<idx;
    else
        cout<<"element not found";
    return 0;
}
