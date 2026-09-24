#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;
double optimalBST(int n,vector<double>&p,vector<double>&q,
    vector<vector<int>>&root){
    vector<vector<double>>e(n+2,vector<double>(n+1,0));
    vector<vector<double>>w(n+2,vector<double>(n+1,0));
    root.assign(n+2,vector<int>(n+1,0));
    for(int i=1;i<=n+1;i++){
        e[i][i-1]=q[i-1];
        w[i][i-1]=q[i-1];
    }
    for(int len=1;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            e[i][j]=1e18;
            w[i][j]=w[i][j-1]+p[j]+q[j];
            for(int r=i;r<=j;r++){
                double t=e[i][r-1]+e[r+1][j]+w[i][j];
                if(t<e[i][j]){
                    e[i][j]=t;
                    root[i][j]=r;
                }
            }
        }
    }
    return e[1][n];
}
void showTree(vector<vector<int>>&root,vector<string>&keys,int i,int j,
    int parent,string side){
    if(i>j)
        return;
    int r=root[i][j];
    if(parent==0){
        cout<<"    "<<keys[r]<<" is the root of keys ";
        cout<<keys[i]<<" to "<<keys[j]<<endl;
    }
    else{
        cout<<"    "<<keys[r]<<" is the "<<side<<" child of "<<keys[parent];
        cout<<" (keys "<<keys[i]<<" to "<<keys[j]<<")"<<endl;
    }
    showTree(root,keys,i,r-1,r,"left");
    showTree(root,keys,r+1,j,r,"right");
}
void run(int tc,vector<string>words,vector<double>p,vector<double>q){
    int n=words.size();
    vector<string>keys(1,"");
    for(string&s:words)
        keys.push_back(s);
    p.insert(p.begin(),0.0);
    vector<vector<int>>root;
    double cost=optimalBST(n,p,q,root);
    cout<<"test case "<<tc<<": minimum expected search cost is "<<cost<<endl;
    cout<<"  root of every subrange:"<<endl;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            cout<<"    keys "<<keys[i]<<" to "<<keys[j];
            cout<<" -> root "<<keys[root[i][j]]<<endl;
        }
    }
    cout<<"  tree structure:"<<endl;
    showTree(root,keys,1,n,0,"");
}
int main(){
    cout<<fixed<<setprecision(4);
    run(1,{"array","binary","cache","debug","event"},
        {0.15,0.10,0.05,0.10,0.20},{0.05,0.10,0.05,0.05,0.05,0.10});
    run(2,{"cat","dog","fox"},{0.5,0.3,0.2},{0,0,0,0});
    run(3,{"ant","bee","cow"},{34,8,50},{0,0,0,0});
    run(4,{"spell"},{1.0},{0,0});
    run(5,{"check","edit","find","open"},{0.25,0.15,0.20,0.10},
        {0.06,0.06,0.06,0.06,0.06});
    return 0;
}
