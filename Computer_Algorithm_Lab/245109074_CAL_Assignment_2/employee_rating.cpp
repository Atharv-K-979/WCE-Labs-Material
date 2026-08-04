#include<iostream>
using namespace std;
int main(){
    int n;
    cout<<"enter number of days: ";
    cin>>n;
    int workload[n];
    cout<<"enter "<<n<<" workload hours: ";
    for(int i=0;i<n;i++)
        cin>>workload[i];
    int count=0,maxcount=0;
    for(int i=0;i<n;i++){
        if(workload[i]>6)
            count++;
        else
            count=0;
        if(count>maxcount)
            maxcount=count;
    }
    cout<<"employee rating is "<<maxcount;
    return 0;
}
