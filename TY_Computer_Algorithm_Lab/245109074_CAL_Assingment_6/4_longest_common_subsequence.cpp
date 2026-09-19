#include<iostream>
#include<vector>
using namespace std;
string lcs(string a,string b,int&length){
    int n=a.size(),m=b.size();
    vector<vector<int>>dp(n+1,vector<int>(m+1,0));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i-1]==b[j-1])
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=(dp[i-1][j]>dp[i][j-1])?dp[i-1][j]:dp[i][j-1];
        }
    }
    length=dp[n][m];
    string result="";
    int i=n,j=m;
    while(i>0&&j>0){
        if(a[i-1]==b[j-1]){
            result=a[i-1]+result;
            i--;
            j--;
        }
        else if(dp[i-1][j]>=dp[i][j-1])
            i--;
        else
            j--;
    }
    return result;
}
int main(){
    int length;
    string result;
    result=lcs("abcde","ace",length);
    cout<<"test case 1: lcs length "<<length<<" subsequence "<<result<<endl;
    result=lcs("abc","abc",length);
    cout<<"test case 2: lcs length "<<length<<" subsequence "<<result<<endl;
    result=lcs("abc","def",length);
    cout<<"test case 3: lcs length "<<length<<" subsequence "<<result<<endl;
    result=lcs("AGGTAB","GXTXAYB",length);
    cout<<"test case 4: lcs length "<<length<<" subsequence "<<result<<endl;
    result=lcs("machine","learning",length);
    cout<<"test case 5: lcs length "<<length<<" subsequence "<<result<<endl;
    return 0;
}
