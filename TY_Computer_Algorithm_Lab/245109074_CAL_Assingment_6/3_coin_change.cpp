#include<iostream>
#include<vector>
#include<climits>
using namespace std;
int minCoins(vector<int>coins,int amount){
    vector<int>dp(amount+1,INT_MAX);
    dp[0]=0;
    for(int i=1;i<=amount;i++){
        for(int c:coins){
            if(c<=i&&dp[i-c]!=INT_MAX){
                if(dp[i-c]+1<dp[i])
                    dp[i]=dp[i-c]+1;
            }
        }
    }
    return (dp[amount]==INT_MAX)?-1:dp[amount];
}
long long countWays(vector<int>coins,int amount){
    vector<long long>dp(amount+1,0);
    dp[0]=1;
    for(int c:coins){
        for(int i=c;i<=amount;i++)
            dp[i]+=dp[i-c];
    }
    return dp[amount];
}
int main(){
    vector<int>c1={1,2,5};
    vector<int>c2={2};
    vector<int>c3={1,3,4};
    vector<int>c4={1,5,10,25};
    vector<int>c5={1,2,5};
    cout<<"test case 1: min coins "<<minCoins(c1,11)<<" ways "<<countWays(c1,11)<<endl;
    cout<<"test case 2: min coins "<<minCoins(c2,3)<<" ways "<<countWays(c2,3)<<endl;
    cout<<"test case 3: min coins "<<minCoins(c3,6)<<" ways "<<countWays(c3,6)<<endl;
    cout<<"test case 4: min coins "<<minCoins(c4,30)<<" ways "<<countWays(c4,30)<<endl;
    cout<<"test case 5: min coins "<<minCoins(c5,0)<<" ways "<<countWays(c5,0)<<endl;
    return 0;
}
