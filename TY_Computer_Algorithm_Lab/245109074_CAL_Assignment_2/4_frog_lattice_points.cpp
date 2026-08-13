#include<iostream>
using namespace std;
long long frogPoints(long long x,long long y,long long s,long long t){
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
    return count;
}
int main(){
    long long x[]={0,1,0,2,0};
    long long y[]={0,1,0,3,0};
    long long s[]={0,1,2,1,5};
    long long t[]={2,3,2,4,5};
    for(int i=0;i<5;i++)
        cout<<"test case "<<i+1<<": number of valid points is "<<frogPoints(x[i],y[i],s[i],t[i])<<endl;
    return 0;
}
