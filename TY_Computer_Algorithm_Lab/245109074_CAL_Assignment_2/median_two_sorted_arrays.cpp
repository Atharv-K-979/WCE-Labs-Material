#include<iostream>
#include<climits>
using namespace std;
int main(){
    int m,n;
    cout<<"enter size of array a: ";
    cin>>m;
    int a[m];
    cout<<"enter "<<m<<" sorted elements of array a: ";
    for(int i=0;i<m;i++)
        cin>>a[i];
    cout<<"enter size of array b: ";
    cin>>n;
    int b[n];
    cout<<"enter "<<n<<" sorted elements of array b: ";
    for(int i=0;i<n;i++)
        cin>>b[i];
    int *x=a,*y=b,xn=m,yn=n;
    if(xn>yn){
        x=b;
        y=a;
        int t=xn;
        xn=yn;
        yn=t;
    }
    int low=0,high=xn,half=(xn+yn+1)/2;
    while(low<=high){
        int cutx=(low+high)/2;
        int cuty=half-cutx;
        int xleft=(cutx==0)?INT_MIN:x[cutx-1];
        int xright=(cutx==xn)?INT_MAX:x[cutx];
        int yleft=(cuty==0)?INT_MIN:y[cuty-1];
        int yright=(cuty==yn)?INT_MAX:y[cuty];
        if(xleft<=yright&&yleft<=xright){
            int bigleft=(xleft>yleft)?xleft:yleft;
            int smallright=(xright<yright)?xright:yright;
            if((xn+yn)%2==0)
                cout<<"median is "<<(bigleft+smallright)/2.0;
            else
                cout<<"median is "<<bigleft;
            return 0;
        }
        else if(xleft>yright)
            high=cutx-1;
        else
            low=cutx+1;
    }
    return 0;
}
