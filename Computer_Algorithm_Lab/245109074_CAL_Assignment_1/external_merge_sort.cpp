#include<bits/stdc++.h>
using namespace std;
void createchunks(vector<string>&data,int chunksize,vector<string>&filenames){
    int idx=0;
    while(idx<(int)data.size()){
        vector<string>chunk;
        for(int i=0;i<chunksize&&idx<(int)data.size();i++,idx++)
            chunk.push_back(data[idx]);
        sort(chunk.begin(),chunk.end());
        string fname="chunk"+to_string(filenames.size())+".txt";
        ofstream fout(fname);
        for(string s:chunk)
            fout<<s<<"\n";
        fout.close();
        filenames.push_back(fname);
    }
}
void mergechunks(vector<string>&filenames,string outfile){
    vector<ifstream>files(filenames.size());
    for(int i=0;i<(int)filenames.size();i++)
        files[i].open(filenames[i]);
    priority_queue<pair<string,int>,vector<pair<string,int>>,greater<pair<string,int>>>pq;
    for(int i=0;i<(int)files.size();i++){
        string line;
        if(getline(files[i],line))
            pq.push({line,i});
    }
    ofstream fout(outfile);
    while(!pq.empty()){
        auto top=pq.top();
        pq.pop();
        fout<<top.first<<"\n";
        string line;
        if(getline(files[top.second],line))
            pq.push({line,top.second});
    }
    fout.close();
    for(int i=0;i<(int)files.size();i++)
        files[i].close();
}
int main(){
    int n;
    cout<<"enter number of strings: ";
    cin>>n;
    vector<string>data(n);
    cout<<"enter "<<n<<" strings: ";
    for(int i=0;i<n;i++)
        cin>>data[i];
    int chunksize;
    cout<<"enter chunk size: ";
    cin>>chunksize;
    vector<string>filenames;
    createchunks(data,chunksize,filenames);
    mergechunks(filenames,"sorted_output.txt");
    cout<<"sorted data written to sorted_output.txt";
    return 0;
}
