#include<iostream>
#include<vector>
using namespace std;
void runTestCase(int tc,int n){
    int capacity=1;
    int size=0;
    long long totalCost=0;
    cout<<"test case "<<tc<<": n = "<<n<<endl;
    cout<<"operation\tactual cost\ttotal cost\tamortized cost"<<endl;
    for(int i=1;i<=n;i++){
        long long cost=1;
        if(size==capacity){
            cost+=capacity;
            capacity*=2;
        }
        size++;
        totalCost+=cost;
        double amortized=(double)totalCost/i;
        cout<<"insert "<<i<<"\t\t"<<cost<<"\t\t"<<totalCost<<"\t\t"<<amortized<<endl;
    }
    cout<<"final amortized cost per insertion: "<<(double)totalCost/n<<endl;
    cout<<endl;
}
int main(){
    vector<int>n={8,16,20,10,32};
    for(int tc=0;tc<(int)n.size();tc++)
        runTestCase(tc+1,n[tc]);
    return 0;
}
