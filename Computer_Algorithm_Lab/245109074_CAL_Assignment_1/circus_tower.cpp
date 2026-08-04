#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct person{
    int height;
    int weight;
};
bool compare(person a,person b){
    if(a.height==b.height)
        return a.weight<b.weight;
    return a.height<b.height;
}
int main(){
    int n;
    cout<<"enter number of people: ";
    cin>>n;
    vector<person>people(n);
    cout<<"enter height and weight of "<<n<<" people: ";
    for(int i=0;i<n;i++)
        cin>>people[i].height>>people[i].weight;
    sort(people.begin(),people.end(),compare);
    vector<int>dp(n,1),parent(n,-1);
    int maxlen=1,last=0;
    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++){
            if(people[i].height>people[j].height&&people[i].weight>people[j].weight&&dp[j]+1>dp[i]){
                dp[i]=dp[j]+1;
                parent[i]=j;
            }
        }
        if(dp[i]>maxlen){
            maxlen=dp[i];
            last=i;
        }
    }
    vector<person>ans;
    while(last!=-1){
        ans.push_back(people[last]);
        last=parent[last];
    }
    reverse(ans.begin(),ans.end());
    cout<<"longest tower length is "<<maxlen<<endl;
    cout<<"tower from top to bottom: ";
    for(auto p:ans)
        cout<<"("<<p.height<<","<<p.weight<<") ";
    return 0;
}
