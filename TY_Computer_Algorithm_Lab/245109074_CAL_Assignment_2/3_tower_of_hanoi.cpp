#include<iostream>
using namespace std;
void hanoi(int n,char from,char to,char aux){
    if(n==0)
        return;
    hanoi(n-1,from,aux,to);
    cout<<"move disk "<<n<<" from "<<from<<" to "<<to<<endl;
    hanoi(n-1,aux,to,from);
}
int main(){
    int disks[]={1,2,3,4,5};
    for(int i=0;i<5;i++){
        cout<<"test case "<<i+1<<": "<<disks[i]<<" disks"<<endl;
        hanoi(disks[i],'a','c','b');
    }
    return 0;
}
