#include<iostream>
#include<vector>
using namespace std;
bool isSafeColor(vector<vector<int>>&graph,vector<int>&colors,int v,int c){
    int n=graph.size();
    for(int u=0;u<n;u++){
        if(graph[v][u]&&colors[u]==c)
            return false;
    }
    return true;
}
bool colorGraph(vector<vector<int>>&graph,int m,vector<int>&colors,int v){
    int n=graph.size();
    if(v==n)
        return true;
    for(int c=1;c<=m;c++){
        if(isSafeColor(graph,colors,v,c)){
            colors[v]=c;
            if(colorGraph(graph,m,colors,v+1))
                return true;
            colors[v]=0;
        }
    }
    return false;
}
bool verifyColoring(vector<vector<int>>&graph,vector<int>&colors){
    int n=graph.size();
    for(int u=0;u<n;u++)
        for(int v=0;v<n;v++)
            if(graph[u][v]&&colors[u]==colors[v])
                return false;
    return true;
}
void runTestCase(int tc,vector<vector<int>>graph){
    int n=graph.size();
    vector<int>colors(n,0);
    int chromaticNumber=n;
    for(int m=1;m<=n;m++){
        fill(colors.begin(),colors.end(),0);
        if(colorGraph(graph,m,colors,0)){
            chromaticNumber=m;
            break;
        }
    }
    cout<<"test case "<<tc<<": vertices = "<<n<<endl;
    cout<<"minimum number of colors required: "<<chromaticNumber<<endl;
    cout<<"coloring assignment: ";
    for(int i=0;i<n;i++)
        cout<<"vertex "<<i<<"->color "<<colors[i]<<" ";
    cout<<endl;
    cout<<"valid coloring: "<<(verifyColoring(graph,colors)?"yes":"no")<<endl;
    cout<<endl;
}
int main(){
    vector<vector<int>>g1={{0,1,1},{1,0,1},{1,1,0}};
    vector<vector<int>>g2={{0,1,0,1},{1,0,1,0},{0,1,0,1},{1,0,1,0}};
    vector<vector<int>>g3={{0,1,0,0,1},{1,0,1,0,0},{0,1,0,1,0},{0,0,1,0,1},{1,0,0,1,0}};
    vector<vector<int>>g4={{0,1,1,1},{1,0,1,1},{1,1,0,1},{1,1,1,0}};
    vector<vector<int>>g5={{0,1,0,0,0,1},{1,0,1,0,0,0},{0,1,0,1,0,0},{0,0,1,0,1,0},{0,0,0,1,0,1},{1,0,0,0,1,0}};
    runTestCase(1,g1);
    runTestCase(2,g2);
    runTestCase(3,g3);
    runTestCase(4,g4);
    runTestCase(5,g5);
    return 0;
}
