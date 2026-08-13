#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;
double findMedian(vector<int>A,vector<int>B){
    if(A.size()>B.size())
        swap(A,B);
    int xn=A.size(),yn=B.size();
    int low=0,high=xn,half=(xn+yn+1)/2;
    while(low<=high){
        int cutx=(low+high)/2;
        int cuty=half-cutx;
        int xleft=(cutx==0)?INT_MIN:A[cutx-1];
        int xright=(cutx==xn)?INT_MAX:A[cutx];
        int yleft=(cuty==0)?INT_MIN:B[cuty-1];
        int yright=(cuty==yn)?INT_MAX:B[cuty];
        if(xleft<=yright&&yleft<=xright){
            if((xn+yn)%2==0)
                return (max(xleft,yleft)+min(xright,yright))/2.0;
            else
                return max(xleft,yleft);
        }
        else if(xleft>yright)
            high=cutx-1;
        else
            low=cutx+1;
    }
    return -1;
}
int main(){
    vector<vector<int>>arrA={{1,3},{1,2,3,4},{},{1,3,5,7,9},{5}};
    vector<vector<int>>arrB={{2},{5,6},{1},{2,4,6,8,10,12},{}};
    for(int i=0;i<5;i++)
        cout<<"test case "<<i+1<<": median is "<<findMedian(arrA[i],arrB[i])<<endl;
    return 0;
}
