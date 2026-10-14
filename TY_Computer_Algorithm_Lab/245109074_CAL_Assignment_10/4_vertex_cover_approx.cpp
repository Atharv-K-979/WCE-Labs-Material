#include<iostream>
#include<vector>
#include<set>
using namespace std;
set<int>approxVertexCover(int n,vector<pair<int,int>>edges){
    vector<bool>covered(edges.size(),false);
    set<int>cover;
    for(int i=0;i<(int)edges.size();i++){
        if(!covered[i]){
            int u=edges[i].first;
            int v=edges[i].second;
            cover.insert(u);
            cover.insert(v);
            for(int j=0;j<(int)edges.size();j++){
                if(edges[j].first==u||edges[j].second==u||edges[j].first==v||edges[j].second==v)
                    covered[j]=true;
            }
        }
    }
    return cover;
}
bool isCover(int n,vector<pair<int,int>>&edges,vector<int>&subset){
    set<int>s(subset.begin(),subset.end());
    for(auto&e:edges)
        if(!s.count(e.first)&&!s.count(e.second))
            return false;
    return true;
}
int optimalVertexCover(int n,vector<pair<int,int>>edges){
    for(int size=0;size<=n;size++){
        vector<int>subset;
        for(int mask=0;mask<(1<<n);mask++){
            if(__builtin_popcount(mask)!=size)
                continue;
            subset.clear();
            for(int i=0;i<n;i++)
                if(mask&(1<<i))
                    subset.push_back(i);
            if(isCover(n,edges,subset))
                return size;
        }
    }
    return n;
}
void runTestCase(int tc,int n,vector<pair<int,int>>edges){
    set<int>approx=approxVertexCover(n,edges);
    int optimal=optimalVertexCover(n,edges);
    cout<<"test case "<<tc<<": vertices = "<<n<<", edges = "<<edges.size()<<endl;
    cout<<"approximate vertex cover: ";
    for(int v:approx)
        cout<<v<<" ";
    cout<<endl;
    cout<<"approximate size: "<<approx.size()<<endl;
    cout<<"optimal size: "<<optimal<<endl;
    cout<<"ratio achieved: "<<(double)approx.size()/optimal<<" (bound is 2.0)"<<endl;
    cout<<endl;
}
int main(){
    vector<pair<int,int>>e1={{0,1},{1,2},{2,3},{3,0}};
    vector<pair<int,int>>e2={{0,1},{0,2},{0,3},{0,4}};
    vector<pair<int,int>>e3={{0,1},{1,2},{2,0}};
    vector<pair<int,int>>e4={{0,1},{1,2},{2,3},{3,4},{4,5}};
    vector<pair<int,int>>e5={{0,1},{0,2},{1,2},{1,3},{2,4},{3,4},{3,5},{4,5}};
    runTestCase(1,4,e1);
    runTestCase(2,5,e2);
    runTestCase(3,3,e3);
    runTestCase(4,6,e4);
    runTestCase(5,6,e5);
    return 0;
}
