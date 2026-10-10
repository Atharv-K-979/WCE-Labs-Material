#include<iostream>
#include<vector>
#include<string>
using namespace std;
enum Policy{POLICY_A,POLICY_B};
class DynamicTable{
    int size;
    int count;
    Policy policy;
public:
    long long totalCost=0;
    int opCount=0;
    DynamicTable(int startSize,Policy p){
        size=startSize;
        count=startSize;
        policy=p;
    }
    long long insertItem(){
        long long cost=1;
        if(count==size){
            cost+=size;
            size*=2;
        }
        count++;
        totalCost+=cost;
        opCount++;
        return cost;
    }
    long long deleteItem(){
        long long cost=1;
        if(count>0)
            count--;
        double loadFactor=(size>0)?(double)count/size:0;
        double threshold=(policy==POLICY_A)?0.5:0.25;
        if(size>1&&loadFactor<=threshold){
            cost+=size/2;
            size/=2;
        }
        totalCost+=cost;
        opCount++;
        return cost;
    }
    int getSize(){return size;}
    int getCount(){return count;}
};
vector<string>buildAdversarialSequence(int startSize,int totalOps){
    vector<string>ops;
    int boundaryDeletes=startSize/2;
    for(int i=0;i<boundaryDeletes&&(int)ops.size()<totalOps;i++)
        ops.push_back("delete");
    while((int)ops.size()<totalOps){
        ops.push_back("insert");
        if((int)ops.size()<totalOps)
            ops.push_back("delete");
    }
    return ops;
}
void runPolicy(string label,Policy p,int startSize,vector<string>&ops){
    DynamicTable table(startSize,p);
    cout<<"policy "<<label<<endl;
    for(string op:ops){
        if(op=="insert")
            table.insertItem();
        else
            table.deleteItem();
    }
    double avg=(double)table.totalCost/table.opCount;
    cout<<"total cost ("<<table.opCount<<" ops): "<<table.totalCost<<endl;
    cout<<"average cost per operation: "<<avg<<endl;
}
void runTestCase(int tc,int startSize,int totalOps){
    vector<string>ops=buildAdversarialSequence(startSize,totalOps);
    cout<<"test case "<<tc<<": start size = "<<startSize<<", total operations = "<<totalOps<<endl;
    runPolicy("A - naive (contract at 1/2 full)",POLICY_A,startSize,ops);
    runPolicy("B - safe (contract at 1/4 full)",POLICY_B,startSize,ops);
    cout<<endl;
}
int main(){
    runTestCase(1,16,30);
    runTestCase(2,8,20);
    runTestCase(3,32,40);
    runTestCase(4,16,10);
    runTestCase(5,64,50);
    return 0;
}
