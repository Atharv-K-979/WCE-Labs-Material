#include<iostream>
#include<vector>
using namespace std;
bool isSafeVertex(vector<vector<int>>&graph,vector<int>&path,int v,int pos){
    if(!graph[path[pos-1]][v])
        return false;
    for(int i=0;i<pos;i++)
        if(path[i]==v)
            return false;
    return true;
}
bool hamCycleUtil(vector<vector<int>>&graph,vector<int>&path,int pos){
    int n=graph.size();
    if(pos==n)
        return graph[path[pos-1]][path[0]]==1;
    for(int v=1;v<n;v++){
        if(isSafeVertex(graph,path,v,pos)){
            path[pos]=v;
            if(hamCycleUtil(graph,path,pos+1))
                return true;
            path[pos]=-1;
        }
    }
    return false;
}
void runTestCase(int tc,vector<vector<int>>graph){
    int n=graph.size();
    vector<int>path(n,-1);
    path[0]=0;
    cout<<"test case "<<tc<<": vertices = "<<n<<endl;
    if(hamCycleUtil(graph,path,1)){
        cout<<"hamiltonian cycle exists: ";
        for(int v:path)
            cout<<v<<" ";
        cout<<path[0]<<endl;
    }
    else
        cout<<"no hamiltonian cycle exists"<<endl;
    cout<<endl;
}
int main(){
    vector<vector<int>>g1={{0,1,0,1,0},{1,0,1,1,1},{0,1,0,0,1},{1,1,0,0,1},{0,1,1,1,0}};
    vector<vector<int>>g2={{0,1,0,1},{1,0,1,0},{0,1,0,1},{1,0,1,0}};
    vector<vector<int>>g3={{0,1,1,1,1},{1,0,1,1,1},{1,1,0,1,1},{1,1,1,0,1},{1,1,1,1,0}};
    vector<vector<int>>g4={{0,1,0,0},{1,0,1,0},{0,1,0,1},{0,0,1,0}};
    vector<vector<int>>g5={{0,1,0,0,0,1},{1,0,1,0,0,0},{0,1,0,1,0,0},{0,0,1,0,1,0},{0,0,0,1,0,1},{1,0,0,0,1,0}};
    runTestCase(1,g1);
    runTestCase(2,g2);
    runTestCase(3,g3);
    runTestCase(4,g4);
    runTestCase(5,g5);
    return 0;
}
