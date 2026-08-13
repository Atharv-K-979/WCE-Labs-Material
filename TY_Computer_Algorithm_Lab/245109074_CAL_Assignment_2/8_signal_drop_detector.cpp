#include<iostream>
#include<vector>
using namespace std;
int countDrops(vector<int>&signal){
    int run=1,drops=0;
    for(int i=1;i<(int)signal.size();i++){
        if(signal[i]<signal[i-1])
            run++;
        else{
            if(run>=3)
                drops++;
            run=1;
        }
    }
    if(run>=3)
        drops++;
    return drops;
}
int main(){
    vector<vector<int>>tests={
        {5,4,3,6,7,4,3,2},
        {1,2,3,4,5},
        {9,8,7,6,5},
        {10,9,5,4,3,2,1,8,7,6},
        {1,1,1}
    };
    for(int i=0;i<(int)tests.size();i++)
        cout<<"test case "<<i+1<<": number of signal drops is "<<countDrops(tests[i])<<endl;
    return 0;
}
