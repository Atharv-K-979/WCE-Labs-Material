#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void activitySelection(vector<pair<int,int>> matches){
    sort(matches.begin(),matches.end(),[](const pair<int,int>&a,const pair<int,int>&b){
        return a.second<b.second;
    });

    vector<pair<int,int>> selected;
    int lastEnd=-1;

    for(auto &m:matches){
        if(m.first>=lastEnd){
            selected.push_back(m);
            lastEnd=m.second;
        }
    }

    cout<<"Total activities: "<<matches.size()<<endl;
    cout<<"Maximum non-overlapping activities: "<<selected.size()<<endl;
    cout<<"Selected activities: ";
    for(auto &m:selected)
        cout<<"("<<m.first<<","<<m.second<<") ";
    cout<<endl;
}

int main(){
    // Test Case 1
    cout<<" Test Case 1 \n";
    activitySelection({{1,3},{2,5},{4,7},{6,9},{8,10}});

    // Test Case 2
    cout<<"\n Test Case 2 \n";
    activitySelection({{0,6},{1,2},{3,4},{5,7},{8,9},{5,9}});

    // Test Case 3
    cout<<"\n Test Case 3 \n";
    activitySelection({{1,2},{2,3},{3,4},{4,5},{5,6}});

    // Test Case 4
    cout<<"\n Test Case 4 \n";
    activitySelection({{1,10},{2,3},{3,4},{5,7},{8,9},{10,12}});

    // Test Case 5
    cout<<"\n Test Case 5 \n";
    activitySelection({{1,4},{2,3},{3,5},{5,7},{6,8},{8,10},{9,11}});

    return 0;
}
