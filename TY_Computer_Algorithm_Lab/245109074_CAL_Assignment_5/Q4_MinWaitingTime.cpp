#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void minWaitingTime(vector<int> jobs){
    int n=jobs.size();

    sort(jobs.begin(),jobs.end());

    vector<int> waitTime(n,0);
    long long totalWait=0;

    for(int i=1;i<n;i++){
        waitTime[i]=waitTime[i-1]+jobs[i-1];
        totalWait+=waitTime[i];
    }

    cout<<"Total jobs: "<<n<<endl;
    cout<<"Order of printing: ";
    for(int d:jobs) cout<<d<<" ";
    cout<<endl;

    cout<<"Waiting times: ";
    for(int i=0;i<n;i++)
        cout<<waitTime[i]<<" ";
    cout<<endl;

    cout<<"Total waiting time = "<<totalWait<<" sec"<<endl;
    cout<<"Average waiting time = "<<(double)totalWait/n<<" sec"<<endl;
}

int main(){
    // Test Case 1
    cout<<" Test Case 1 \n";
    minWaitingTime({45,120,30,80,200});

    // Test Case 2
    cout<<"\n Test Case 2 \n";
    minWaitingTime({10,20,30,40});

    // Test Case 3
    cout<<"\n Test Case 3 \n";
    minWaitingTime({100,1,50,25,75});

    // Test Case 4
    cout<<"\n Test Case 4 \n";
    minWaitingTime({300,200,100,50,10,5});

    // Test Case 5
    cout<<"\n Test Case 5 \n";
    minWaitingTime({60,60,20,40,80});

    return 0;
}
