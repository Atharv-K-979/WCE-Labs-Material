#include<iostream>
using namespace std;
int main(){
    int m,n;
    cout<<"enter number of rows: ";
    cin>>m;
    cout<<"enter number of columns: ";
    cin>>n;
    int arr[m][n];
    cout<<"enter matrix elements each row sorted ascending: ";
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            cin>>arr[i][j];
    int target;
    cout<<"enter element to search: ";
    cin>>target;
    bool found=false;
    for(int i=0;i<m;i++){
        if(target<arr[i][0]||target>arr[i][n-1])
            continue;
        int low=0,high=n-1;
        while(low<=high){
            int mid=(low+high)/2;
            if(arr[i][mid]==target){
                found=true;
                break;
            }
            if(arr[i][mid]<target)
                low=mid+1;
            else
                high=mid-1;
        }
        if(found)
            break;
    }
    if(found)
        cout<<"true";
    else
        cout<<"false";
    return 0;
}
