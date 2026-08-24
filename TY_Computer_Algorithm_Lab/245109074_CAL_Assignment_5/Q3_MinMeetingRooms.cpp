#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void minMeetingRooms(vector<pair<int,int>> meetings){
    int n=meetings.size();
    vector<int> start(n),end_(n);

    for(int i=0;i<n;i++){
        start[i]=meetings[i].first;
        end_[i]=meetings[i].second;
    }

    sort(start.begin(),start.end());
    sort(end_.begin(),end_.end());

    int rooms=0,maxRooms=0;
    int i=0,j=0;

    while(i<n && j<n){
        if(start[i]<end_[j]){
            rooms++;
            i++;
            maxRooms=max(maxRooms,rooms);
        }else{
            rooms--;
            j++;
        }
    }

    cout<<"Total meetings: "<<n<<endl;
    cout<<"Minimum meeting rooms required: "<<maxRooms<<endl;
}

int main(){
    // Test Case 1
    cout<<" Test Case 1 \n";
    minMeetingRooms({{900,1000},{930,1030},{1000,1100},{1030,1130}});

    // Test Case 2
    cout<<"\n Test Case 2 \n";
    minMeetingRooms({{900,1000},{1000,1100},{1100,1200}});

    // Test Case 3
    cout<<"\n Test Case 3 \n";
    minMeetingRooms({{900,1200},{930,1100},{1000,1130},{1030,1230}});

    // Test Case 4
    cout<<"\n Test Case 4 \n";
    minMeetingRooms({{800,900},{850,950},{900,1000},{920,1030},{1000,1100}});

    // Test Case 5
    cout<<"\n Test Case 5 \n";
    minMeetingRooms({{900,930},{930,1000},{1000,1030},{1030,1100},{1100,1130}});

    return 0;
}
