#include<iostream>
#include<vector>
using namespace std;
bool isSafe(vector<int>&cols,int row,int col){
    for(int r=0;r<row;r++){
        if(cols[r]==col)
            return false;
        if(abs(cols[r]-col)==abs(r-row))
            return false;
    }
    return true;
}
void solve(int n,int row,vector<int>&cols,vector<vector<int>>&solutions){
    if(row==n){
        solutions.push_back(cols);
        return;
    }
    for(int col=0;col<n;col++){
        if(isSafe(cols,row,col)){
            cols[row]=col;
            solve(n,row+1,cols,solutions);
        }
    }
}
void runTestCase(int tc,int n){
    vector<int>cols(n,-1);
    vector<vector<int>>solutions;
    solve(n,0,cols,solutions);
    cout<<"test case "<<tc<<": n = "<<n<<endl;
    cout<<"number of solutions: "<<solutions.size()<<endl;
    for(int i=0;i<(int)solutions.size();i++){
        cout<<"solution "<<i+1<<": ";
        for(int c:solutions[i])
            cout<<c<<" ";
        cout<<endl;
    }
    cout<<endl;
}
int main(){
    runTestCase(1,1);
    runTestCase(2,4);
    runTestCase(3,5);
    runTestCase(4,6);
    runTestCase(5,8);
    return 0;
}
