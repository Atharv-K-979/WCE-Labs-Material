#include<iostream>
#include<vector>
using namespace std;
long long uniquePaths(vector<vector<int>>&grid){
    int m=grid.size(),n=grid[0].size();
    vector<vector<long long>>dp(m,vector<long long>(n,0));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]==1){
                dp[i][j]=0;
                continue;
            }
            if(i==0&&j==0){
                dp[i][j]=1;
                continue;
            }
            long long fromtop=(i>0)?dp[i-1][j]:0;
            long long fromleft=(j>0)?dp[i][j-1]:0;
            dp[i][j]=fromtop+fromleft;
        }
    }
    return dp[m-1][n-1];
}
int main(){
    vector<vector<int>>test1={{0,0,0},{0,1,0},{0,0,0}};
    vector<vector<int>>test2={{0,1},{0,0}};
    vector<vector<int>>test3={{1,0}};
    vector<vector<int>>test4={{0,0},{0,0}};
    vector<vector<int>>test5={{0,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,0}};
    cout<<"test case 1: number of paths is "<<uniquePaths(test1)<<endl;
    cout<<"test case 2: number of paths is "<<uniquePaths(test2)<<endl;
    cout<<"test case 3: number of paths is "<<uniquePaths(test3)<<endl;
    cout<<"test case 4: number of paths is "<<uniquePaths(test4)<<endl;
    cout<<"test case 5: number of paths is "<<uniquePaths(test5)<<endl;
    return 0;
}
