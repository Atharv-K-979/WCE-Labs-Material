#include<iostream>
#include<vector>
#include<string>
using namespace std;
class BrowserStack{
    vector<string>data;
public:
    long long actualTotal=0;
    long long amortizedTotal=0;
    long long creditBank=0;
    void push(string page){
        data.push_back(page);
        long long actual=1;
        long long amortized=2;
        creditBank+=(amortized-actual);
        actualTotal+=actual;
        amortizedTotal+=amortized;
        cout<<"push("<<page<<")\t\tactual cost "<<actual<<"\tamortized charge "<<amortized<<"\tcredit bank after "<<creditBank<<endl;
    }
    void pop(){
        long long actual=0;
        if(!data.empty()){
            data.pop_back();
            actual=1;
        }
        long long amortized=0;
        creditBank-=actual;
        actualTotal+=actual;
        amortizedTotal+=amortized;
        cout<<"pop()\t\t\tactual cost "<<actual<<"\tamortized charge "<<amortized<<"\tcredit bank after "<<creditBank<<endl;
    }
    void multipop(int k){
        int popped=0;
        while(popped<k&&!data.empty()){
            data.pop_back();
            popped++;
        }
        long long actual=popped;
        long long amortized=0;
        creditBank-=popped;
        actualTotal+=actual;
        amortizedTotal+=amortized;
        cout<<"multipop("<<k<<")\t\tactual cost "<<actual<<"\tamortized charge "<<amortized<<"\tcredit bank after "<<creditBank<<endl;
    }
};
struct Op{
    string type;
    int value;
    string page;
};
void runTestCase(int tc,vector<Op>&ops){
    BrowserStack s;
    cout<<"test case "<<tc<<":"<<endl;
    for(Op&op:ops){
        if(op.type=="push")
            s.push(op.page);
        else if(op.type=="pop")
            s.pop();
        else if(op.type=="multipop")
            s.multipop(op.value);
    }
    cout<<"total actual cost: "<<s.actualTotal<<endl;
    cout<<"total amortized cost: "<<s.amortizedTotal<<endl;
    cout<<"final credit bank: "<<s.creditBank<<endl;
    cout<<endl;
}
int main(){
    vector<Op>tc1={{"push",0,"a"},{"push",0,"b"},{"push",0,"c"},{"push",0,"d"},{"push",0,"e"},{"multipop",3,""},{"push",0,"f"},{"pop",0,""},{"multipop",10,""}};
    vector<Op>tc2={{"push",0,"x1"},{"push",0,"x2"},{"push",0,"x3"},{"push",0,"x4"},{"push",0,"x5"},{"push",0,"x6"},{"multipop",2,""},{"multipop",10,""}};
    vector<Op>tc3={{"push",0,"p1"},{"push",0,"p2"},{"pop",0,""},{"push",0,"p3"},{"push",0,"p4"},{"push",0,"p5"},{"multipop",5,""}};
    vector<Op>tc4={{"multipop",5,""},{"pop",0,""},{"push",0,"q1"},{"pop",0,""}};
    vector<Op>tc5={{"push",0,"1"},{"push",0,"2"},{"push",0,"3"},{"push",0,"4"},{"push",0,"5"},{"push",0,"6"},{"push",0,"7"},{"push",0,"8"},{"push",0,"9"},{"push",0,"10"},{"multipop",4,""},{"multipop",4,""},{"multipop",4,""}};
    runTestCase(1,tc1);
    runTestCase(2,tc2);
    runTestCase(3,tc3);
    runTestCase(4,tc4);
    runTestCase(5,tc5);
    return 0;
}
