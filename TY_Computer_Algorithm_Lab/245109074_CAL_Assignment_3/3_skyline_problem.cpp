#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Building{
    int left;
    int height;
    int right;
};
bool cmpLeft(Building a,Building b){
    return a.left<b.left;
}
vector<pair<int,int>> merge(vector<pair<int,int>>&sky1,vector<pair<int,int>>&sky2){
    int h1=0,h2=0,i=0,j=0;
    vector<pair<int,int>>result;
    while(i<(int)sky1.size()&&j<(int)sky2.size()){
        int x;
        if(sky1[i].first<sky2[j].first){
            x=sky1[i].first;
            h1=sky1[i].second;
            i++;
        }
        else if(sky2[j].first<sky1[i].first){
            x=sky2[j].first;
            h2=sky2[j].second;
            j++;
        }
        else{
            x=sky1[i].first;
            h1=sky1[i].second;
            h2=sky2[j].second;
            i++;
            j++;
        }
        int maxh=(h1>h2)?h1:h2;
        if(result.empty()||result.back().second!=maxh)
            result.push_back({x,maxh});
    }
    while(i<(int)sky1.size()){
        result.push_back(sky1[i]);
        i++;
    }
    while(j<(int)sky2.size()){
        result.push_back(sky2[j]);
        j++;
    }
    return result;
}
vector<pair<int,int>> computeSkyline(vector<Building>&buildings,int low,int high){
    if(low==high){
        vector<pair<int,int>>s;
        s.push_back({buildings[low].left,buildings[low].height});
        s.push_back({buildings[low].right,0});
        return s;
    }
    int mid=(low+high)/2;
    vector<pair<int,int>>left=computeSkyline(buildings,low,mid);
    vector<pair<int,int>>right=computeSkyline(buildings,mid+1,high);
    return merge(left,right);
}
void runCase(vector<Building>buildings){
    sort(buildings.begin(),buildings.end(),cmpLeft);
    vector<pair<int,int>>skyline=computeSkyline(buildings,0,buildings.size()-1);
    for(auto p:skyline)
        cout<<"("<<p.first<<","<<p.second<<") ";
    cout<<endl;
}
int main(){
    vector<vector<Building>>tests={
        {{1,11,5},{2,6,7},{3,13,9},{12,7,16},{14,3,25},{19,18,22},{23,13,29},{24,4,28}},
        {{1,5,4},{2,8,6}},
        {{1,10,5}},
        {{1,5,3},{6,7,9},{10,4,13}},
        {{1,5,5},{5,5,10}}
    };
    for(int i=0;i<(int)tests.size();i++){
        cout<<"test case "<<i+1<<": ";
        runCase(tests[i]);
    }
    return 0;
}
