#include<iostream>
using namespace std;
int main(){
    int n;
    cout<<"enter number of timestamps: ";
    cin>>n;
    int timestamps[n];
    cout<<"enter "<<n<<" sorted timestamps: ";
    for(int i=0;i<n;i++)
        cin>>timestamps[i];
    int missing=-1;
    for(int i=1;i<n;i++){
        if(timestamps[i]-timestamps[i-1]>1){
            missing=timestamps[i-1]+1;
            break;
        }
    }
    if(missing!=-1)
        cout<<"first missing timestamp is "<<missing;
    else
        cout<<"no timestamp is missing";
    return 0;
}
