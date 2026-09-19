#include<iostream>
#include<vector>
using namespace std;
int knapsack(vector<int>weights,vector<int>values,int capacity){
    int n=weights.size();
    vector<vector<int>>dp(n+1,vector<int>(capacity+1,0));
    for(int i=1;i<=n;i++){
        for(int w=0;w<=capacity;w++){
            dp[i][w]=dp[i-1][w];
            if(weights[i-1]<=w){
                int taken=dp[i-1][w-weights[i-1]]+values[i-1];
                if(taken>dp[i][w])
                    dp[i][w]=taken;
            }
        }
    }
    return dp[n][capacity];
}
int main(){
    vector<int>w1={1,3,4,5};
    vector<int>v1={1,4,5,7};
    vector<int>w2={2,3,4,5};
    vector<int>v2={3,4,5,6};
    vector<int>w3={10,20,30};
    vector<int>v3={60,100,120};
    vector<int>w4={1,2,3};
    vector<int>v4={10,15,40};
    vector<int>w5={5};
    vector<int>v5={10};
    cout<<"test case 1: maximum value is "<<knapsack(w1,v1,7)<<endl;
    cout<<"test case 2: maximum value is "<<knapsack(w2,v2,5)<<endl;
    cout<<"test case 3: maximum value is "<<knapsack(w3,v3,50)<<endl;
    cout<<"test case 4: maximum value is "<<knapsack(w4,v4,6)<<endl;
    cout<<"test case 5: maximum value is "<<knapsack(w5,v5,3)<<endl;
    return 0;
}
