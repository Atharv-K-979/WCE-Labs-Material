#include<iostream>
using namespace std;
int main(){
    long long n,k;
    cout<<"enter number of boxes: ";
    cin>>n;
    cout<<"enter candy number to locate: ";
    cin>>k;
    long long len=(n==1)?1:2*(n-1);
    long long r=(k-1)%len;
    long long box=(r<n)?r+1:2*n-r-1;
    cout<<"kth candy is in box number "<<box;
    return 0;
}
