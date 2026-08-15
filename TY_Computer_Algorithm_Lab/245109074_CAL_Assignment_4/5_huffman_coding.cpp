#include<iostream>
#include<vector>
#include<queue>
#include<map>
using namespace std;
struct Node{
    string name;
    long long weight;
    Node*left;
    Node*right;
};
struct cmpNode{
    bool operator()(Node*a,Node*b){
        return a->weight>b->weight;
    }
};
void generateCodes(Node*root,string code,map<string,string>&codes){
    if(root==NULL)
        return;
    if(root->left==NULL&&root->right==NULL){
        codes[root->name]=(code.empty())?"0":code;
        return;
    }
    generateCodes(root->left,code+"0",codes);
    generateCodes(root->right,code+"1",codes);
}
void runCase(vector<pair<string,long long>>channels){
    priority_queue<Node*,vector<Node*>,cmpNode>pq;
    for(auto ch:channels){
        Node*n=new Node();
        n->name=ch.first;
        n->weight=ch.second;
        n->left=NULL;
        n->right=NULL;
        pq.push(n);
    }
    while(pq.size()>1){
        Node*a=pq.top();
        pq.pop();
        Node*b=pq.top();
        pq.pop();
        Node*merged=new Node();
        merged->name="";
        merged->weight=a->weight+b->weight;
        merged->left=a;
        merged->right=b;
        pq.push(merged);
    }
    Node*root=pq.top();
    map<string,string>codes;
    generateCodes(root,"",codes);
    long long totalweight=0,weightedlen=0;
    string shortest="",longestc="";
    for(auto ch:channels){
        string code=codes[ch.first];
        cout<<ch.first<<"="<<code<<" ";
        totalweight+=ch.second;
        weightedlen+=ch.second*code.size();
        if(shortest==""||code.size()<codes[shortest].size())
            shortest=ch.first;
        if(longestc==""||code.size()>codes[longestc].size())
            longestc=ch.first;
    }
    cout<<endl;
    cout<<"shortest code is "<<shortest<<"="<<codes[shortest]<<" longest code is "<<longestc<<"="<<codes[longestc]<<endl;
    double avg=(double)weightedlen/totalweight;
    cout<<"average code length is "<<avg<<endl;
}
int main(){
    vector<pair<string,long long>>test1={
        {"temperature",380},{"pressure",560},{"voltage",300},{"gyro",150},{"thruster",110},
        {"attitudecontrol",190},{"solarpanel",240},{"batterylevel",420},{"communication",500},
        {"radiation",70},{"magnetometer",60},{"startracker",200},{"reactionwheel",170},
        {"fuellevel",130},{"antenna",90},{"camera",210},{"gps",85},{"accelerometer",65},
        {"databus",150},{"timing",100}
    };
    vector<pair<string,long long>>test2={{"a",5},{"b",9},{"c",12},{"d",13},{"e",16},{"f",45}};
    vector<pair<string,long long>>test3={{"a",1},{"b",1},{"c",1},{"d",1}};
    vector<pair<string,long long>>test4={{"a",10},{"b",20}};
    vector<pair<string,long long>>test5={{"a",1},{"b",2},{"c",4},{"d",8},{"e",16}};
    cout<<"test case 1:"<<endl;
    cout<<endl;
    runCase(test1);
    cout<<"test case 2:"<<endl;
    runCase(test2);
    cout<<"test case 3:"<<endl;
    runCase(test3);
    cout<<"test case 4:"<<endl;
    runCase(test4);
    cout<<"test case 5:"<<endl;
    runCase(test5);
    return 0;
}
