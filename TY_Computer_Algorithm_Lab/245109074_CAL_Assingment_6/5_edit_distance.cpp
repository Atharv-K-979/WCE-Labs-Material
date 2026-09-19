#include<iostream>
#include<vector>
using namespace std;
int editDistance(string a,string b){
    int n=a.size(),m=b.size();
    vector<vector<int>>dp(n+1,vector<int>(m+1,0));
    for(int i=0;i<=n;i++)
        dp[i][0]=i;
    for(int j=0;j<=m;j++)
        dp[0][j]=j;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i-1]==b[j-1])
                dp[i][j]=dp[i-1][j-1];
            else{
                int sub=dp[i-1][j-1];
                int del=dp[i-1][j];
                int ins=dp[i][j-1];
                int best=sub;
                if(del<best)
                    best=del;
                if(ins<best)
                    best=ins;
                dp[i][j]=1+best;
            }
        }
    }
    return dp[n][m];
}
int main(){
    cout<<"test case 1: edit distance is "<<editDistance("GATTACA","GCATGCU")<<endl;
    cout<<"test case 2: edit distance is "<<editDistance("kitten","sitting")<<endl;
    cout<<"test case 3: edit distance is "<<editDistance("abc","abc")<<endl;
    cout<<"test case 4: edit distance is "<<editDistance("","abc")<<endl;
    cout<<"test case 5: edit distance is "<<editDistance("intention","execution")<<endl;
    return 0;
}
