#include<iostream>
using namespace std;
void merge(int arr[],int n,int brr[],int m){
    int i=n-1;
    int j=m-1;
    int k=m+n-1;
    while(i>=0&&j>=0){
        if(arr[i]>brr[j]){
            arr[k]=arr[i];
            i--;
            k--;
        }
        else{
            arr[k]=brr[j];
            j--;
            k--;
        }
    }
    while(j>=0){
        arr[k]=brr[j];
        j--;
        k--;
    }
}
int main(){
    int n,m;
    cout<<"enter size of array a: ";
    cin>>n;
    cout<<"enter size of array b: ";
    cin>>m;
    int arr[n+m];
    int brr[m];
    cout<<"enter "<<n<<" sorted elements of array a: ";
    for(int i=0;i<n;i++)
        cin>>arr[i];
    cout<<"enter "<<m<<" sorted elements of array b: ";
    for(int i=0;i<m;i++)
        cin>>brr[i];
    merge(arr,n,brr,m);
    cout<<"merged array: ";
    for(int i=0;i<n+m;i++)
        cout<<arr[i]<<" ";
    return 0;
}
