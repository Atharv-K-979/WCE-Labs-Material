#include<iostream>
using namespace std;
int main(){
    long long x,y,s,t;
    cout<<"enter x y s and t: ";
    cin>>x>>y>>s>>t;
    long long count=0;
    for(long long i=x;i<=x+s;i++){
        if(i<0||i>t)
            continue;
        long long ylow=(y>0)?y:0;
        long long ymax=t-i;
        long long yhigh=(y+s<ymax)?y+s:ymax;
        if(yhigh>=ylow)
            count+=yhigh-ylow+1;
    }
    cout<<"number of valid points is "<<count;
    return 0;
}
