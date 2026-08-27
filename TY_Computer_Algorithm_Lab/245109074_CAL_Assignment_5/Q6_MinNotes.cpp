#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void minNotes(vector<int> denom,int amount){
    sort(denom.rbegin(),denom.rend());
    vector<pair<int,int>> used;
    int totalNotes=0;
    int remaining=amount;
    for(int d:denom){
        if(remaining<=0) break;
        int count=remaining/d;
        if(count>0){
            used.push_back({d,count});
            totalNotes+=count;
            remaining-=d*count;
        }
    }
    cout<<"Amount: "<<amount<<endl;
    if(remaining!=0){
        cout<<"Cannot form the exact amount with the given denominations.\n";
        return;
    }
    cout<<"Notes used: ";
    for(auto &p:used)
        cout<<p.first<<"x"<<p.second<<" ";
    cout<<endl;
    cout<<"Total notes used: "<<totalNotes<<endl;
}

int main(){
    // Test Case 1 - standard denominations
    cout<<" Test Case 1 \n";
    minNotes({1,2,5,10,20,50,100,200,500},1287);

    // Test Case 2
    cout<<"\n Test Case 2 \n";
    minNotes({1,5,10,20,50,100},275);

    // Test Case 3
    cout<<"\n Test Case 3 \n";
    minNotes({1,2,5,10,20},47);

    // Test Case 4 - greedy is not optimal for arbitrary denominations
    cout<<"\n Test Case 4 \n";
    minNotes({1,3,4},6);
    cout<<"Note: Greedy gives 4+1+1 = 3 notes, while optimal is 3+3 = 2 notes.\n";

    // Test Case 5 - exact amount cannot be formed
    cout<<"\n Test Case 5 \n";
    minNotes({5,10,20},13);

    return 0;
}
