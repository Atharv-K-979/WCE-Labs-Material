#include<iostream>
#include<vector>
#include<string>
using namespace std;
class QueueTwoStacks{
    vector<int>inStack;
    vector<int>outStack;
public:
    long long actualTotal=0;
    long long amortizedTotal=0;
    long long creditBank=0;
    void enqueue(int x){
        inStack.push_back(x);
        long long actual=1;
        long long amortized=2;
        creditBank+=(amortized-actual);
        actualTotal+=actual;
        amortizedTotal+=amortized;
        cout<<"enqueue("<<x<<")\t\tactual cost "<<actual<<"\tamortized charge "<<amortized<<"\tcredit bank after "<<creditBank<<endl;
    }
    void dequeue(){
        long long actual=0;
        bool empty=false;
        if(outStack.empty()){
            while(!inStack.empty()){
                outStack.push_back(inStack.back());
                inStack.pop_back();
                actual++;
                creditBank-=1;
            }
        }
        int result=-1;
        if(!outStack.empty()){
            result=outStack.back();
            outStack.pop_back();
            actual++;
        }
        else
            empty=true;
        long long amortized=empty?0:1;
        actualTotal+=actual;
        amortizedTotal+=amortized;
        if(empty)
            cout<<"dequeue() -> queue is empty\tactual cost "<<actual<<"\tamortized charge "<<amortized<<"\tcredit bank after "<<creditBank<<endl;
        else
            cout<<"dequeue() -> "<<result<<"\t\tactual cost "<<actual<<"\tamortized charge "<<amortized<<"\tcredit bank after "<<creditBank<<endl;
    }
};
struct Op{
    string type;
    int value;
};
void runTestCase(int tc,vector<Op>&ops){
    QueueTwoStacks q;
    cout<<"test case "<<tc<<":"<<endl;
    for(Op&op:ops){
        if(op.type=="enqueue")
            q.enqueue(op.value);
        else
            q.dequeue();
    }
    cout<<"total actual cost: "<<q.actualTotal<<endl;
    cout<<"total amortized cost: "<<q.amortizedTotal<<endl;
    cout<<"final credit bank: "<<q.creditBank<<endl;
    cout<<endl;
}
int main(){
    vector<Op>tc1={{"enqueue",1},{"enqueue",2},{"enqueue",3},{"enqueue",4},{"enqueue",5},{"dequeue",0}};
    vector<Op>tc2={{"enqueue",1},{"enqueue",2},{"enqueue",3},{"dequeue",0},{"dequeue",0},{"enqueue",4},{"dequeue",0}};
    vector<Op>tc3={{"dequeue",0}};
    vector<Op>tc4={{"enqueue",1},{"enqueue",2},{"enqueue",3},{"enqueue",4},{"enqueue",5},{"enqueue",6},{"enqueue",7},{"enqueue",8},{"enqueue",9},{"enqueue",10},{"dequeue",0},{"dequeue",0},{"dequeue",0},{"dequeue",0},{"dequeue",0},{"dequeue",0},{"dequeue",0},{"dequeue",0},{"dequeue",0},{"dequeue",0}};
    vector<Op>tc5={{"enqueue",1},{"dequeue",0},{"enqueue",2},{"dequeue",0},{"enqueue",3},{"dequeue",0},{"enqueue",4},{"dequeue",0}};
    runTestCase(1,tc1);
    runTestCase(2,tc2);
    runTestCase(3,tc3);
    runTestCase(4,tc4);
    runTestCase(5,tc5);
    return 0;
}
