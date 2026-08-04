#include<iostream>
using namespace std;
int main(){
    int m,n;
    cout<<"enter number of rows: ";
    cin>>m;
    cout<<"enter number of columns: ";
    cin>>n;
    int arr[m][n];
    cout<<"enter matrix elements row wise sorted and column wise sorted: ";
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            cin>>arr[i][j];
    int target;
    cout<<"enter element to search: ";
    cin>>target;
    int i=0,j=n-1;
    bool found=false;
    while(i<m&&j>=0){
        if(arr[i][j]==target){
            cout<<"found at "<<i<<" "<<j;
            found=true;
            break;
        }
        if(arr[i][j]>target)
            j--;
        else
            i++;
    }
    if(!found)
        cout<<"not found";
    return 0;
}
