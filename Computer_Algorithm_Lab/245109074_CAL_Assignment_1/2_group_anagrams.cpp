#include<bits/stdc++.h>
using namespace std;
void groupanagrams(vector<string>&arr){
    unordered_map<string,vector<string>>mp;
    for(string word:arr){
        string key=word;
        sort(key.begin(),key.end());
        mp[key].push_back(word);
    }
    for(auto group:mp){
        for(string word:group.second)
            cout<<word<<" ";
    }
}
int main(){
    int n;
    cout<<"enter number of words: ";
    cin>>n;
    vector<string>arr(n);
    cout<<"enter "<<n<<" words: ";
    for(int i=0;i<n;i++)
        cin>>arr[i];
    cout<<"grouped anagrams: ";
    groupanagrams(arr);
    return 0;
}
