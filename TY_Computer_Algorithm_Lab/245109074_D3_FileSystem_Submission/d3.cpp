#include <bits/stdc++.h>
using namespace std;

struct Change{
    string type,text;
};

vector<vector<int>> buildDP(const vector<string>& a,const vector<string>& b){
    int m=a.size(),n=b.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1));
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            if(a[i-1]==b[j-1]) dp[i][j]=dp[i-1][j-1]+1;
            else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
    return dp;
}

vector<string> reconstructLCS(const vector<string>& a,const vector<string>& b,const vector<vector<int>>& dp){
    int i=a.size(),j=b.size();
    vector<string> lcs;
    while(i&&j){
        if(a[i-1]==b[j-1]){
            lcs.push_back(a[i-1]);
            i--;j--;
        }else if(dp[i-1][j]>=dp[i][j-1]) i--;
        else j--;
    }
    reverse(lcs.begin(),lcs.end());
    return lcs;
}

vector<Change> trackChanges(const vector<string>& a,const vector<string>& b,const vector<vector<int>>& dp){
    int i=a.size(),j=b.size();
    vector<Change> changes;
    while(i&&j){
        if(a[i-1]==b[j-1]){
            changes.push_back({"UNCHANGED",a[i-1]});
            i--;j--;
        }else if(dp[i-1][j]>=dp[i][j-1]){
            changes.push_back({"REMOVED",a[i-1]});
            i--;
        }else{
            changes.push_back({"ADDED",b[j-1]});
            j--;
        }
    }
    while(i) changes.push_back({"REMOVED",a[--i]});
    while(j) changes.push_back({"ADDED",b[--j]});
    reverse(changes.begin(),changes.end());
    return changes;
}

bool readDocument(const string& file,vector<string>& doc){
    ifstream fin(file);
    if(!fin) return false;
    int n;
    if(!(fin>>n)) return false;
    string s;
    getline(fin,s);
    doc.resize(n);
    for(string& p:doc) getline(fin,p);
    return true;
}

void twoWayDiff(const vector<string>& v1,const vector<string>& v2){
    auto dp=buildDP(v1,v2);
    auto lcs=reconstructLCS(v1,v2,dp);
    auto changes=trackChanges(v1,v2,dp);

    cout<<"LCS Length = "<<lcs.size()<<"\n";
    cout<<"LCS:\n";
    if(lcs.empty()) cout<<"[]\n";
    else for(const auto& p:lcs) cout<<p<<"\n";

    cout<<"\nTrack Changes:\n";
    if(changes.empty()) cout<<"No changes.\n";
    else for(const auto& c:changes) cout<<c.type<<": "<<c.text<<"\n";
}

void threeWayMerge(const vector<string>& base,const vector<string>& v1,const vector<string>& v2){
    cout<<"\nThree-Way Merge / Conflict Detection:\n";
    int n=max({base.size(),v1.size(),v2.size()});
    for(int i=0;i<n;i++){
        string b=i<(int)base.size()?base[i]:"<MISSING>";
        string a=i<(int)v1.size()?v1[i]:"<MISSING>";
        string c=i<(int)v2.size()?v2[i]:"<MISSING>";

        if(a==c) cout<<"MERGED: "<<a<<"\n";
        else if(a==b) cout<<"TAKE V2: "<<c<<"\n";
        else if(c==b) cout<<"TAKE V1: "<<a<<"\n";
        else{
            cout<<"CONFLICT:\n";
            cout<<"  BASE: "<<b<<"\n";
            cout<<"  V1:   "<<a<<"\n";
            cout<<"  V2:   "<<c<<"\n";
        }
    }
}

int main(int argc,char* argv[]){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if(argc==3){
        vector<string> v1,v2;
        if(!readDocument(argv[1],v1)||!readDocument(argv[2],v2)){
            cerr<<"Error: could not read one or both document files.\n";
            return 1;
        }
        cout<<"TWO-WAY DOCUMENT DIFF\n";
        cout<<"Version 1: "<<argv[1]<<"\nVersion 2: "<<argv[2]<<"\n\n";
        twoWayDiff(v1,v2);
        return 0;
    }

    if(argc==4){
        vector<string> base,v1,v2;
        if(!readDocument(argv[1],base)||!readDocument(argv[2],v1)||!readDocument(argv[3],v2)){
            cerr<<"Error: could not read one or more document files.\n";
            return 1;
        }
        cout<<"THREE-WAY MERGE\n";
        cout<<"Base: "<<argv[1]<<"\nVersion 1: "<<argv[2]<<"\nVersion 2: "<<argv[3]<<"\n";
        threeWayMerge(base,v1,v2);
        return 0;
    }

    cerr<<"Usage:\n";
    cerr<<"  ./d3 version1.txt version2.txt\n";
    cerr<<"  ./d3 base.txt version1.txt version2.txt\n";
    return 1;
}
