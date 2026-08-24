#include<iostream>
#include<vector>
#include<set>
using namespace std;

void setCover(int totalSegments,vector<set<int>> channels){
    set<int> universe;
    for(int i=1;i<=totalSegments;i++)
        universe.insert(i);

    set<int> covered;
    vector<int> chosenChannels;

    while(covered.size()<universe.size()){
        int bestChannel=-1;
        int bestGain=0;
        set<int> bestNew;

        for(int i=0;i<(int)channels.size();i++){
            set<int> newlyCovered;

            for(int seg:channels[i])
                if(covered.find(seg)==covered.end())
                    newlyCovered.insert(seg);

            if((int)newlyCovered.size()>bestGain){
                bestGain=newlyCovered.size();
                bestChannel=i;
                bestNew=newlyCovered;
            }
        }

        if(bestChannel==-1) break;

        chosenChannels.push_back(bestChannel+1);
        for(int seg:bestNew)
            covered.insert(seg);
    }

    cout<<"Universe size: "<<totalSegments<<endl;
    cout<<"Channels selected: "<<chosenChannels.size()<<endl;
    cout<<"Selected channels: ";
    for(int c:chosenChannels)
        cout<<"Channel"<<c<<" ";
    cout<<endl;

    if(covered.size()<universe.size())
        cout<<"Warning: some segments could not be covered"<<endl;
    else
        cout<<"All segments covered"<<endl;
}

int main(){
    // Test Case 1
    cout<<" Test Case 1 \n";
    setCover(6,{
        {1,2,3},{2,4},{3,5},{4,5,6},{1,6}
    });

    // Test Case 2
    cout<<"\n Test Case 2 \n";
    setCover(8,{
        {1,2,3},{3,4,5},{5,6},{6,7,8},{1,8}
    });

    // Test Case 3
    cout<<"\n Test Case 3 \n";
    setCover(5,{
        {1,2},{2,3},{3,4},{4,5},{1,5}
    });

    // Test Case 4
    cout<<"\n Test Case 4 \n";
    setCover(10,{
        {1,2,3,4},{4,5,6},{6,7,8},{8,9,10},{2,5,9}
    });

    // Test Case 5 - impossible to cover all segments
    cout<<"\n Test Case 5 \n";
    setCover(7,{
        {1,2},{2,3},{4,5},{5,6}
    });

    return 0;
}
