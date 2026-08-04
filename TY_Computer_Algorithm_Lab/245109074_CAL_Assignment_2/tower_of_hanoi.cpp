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
    int n;
    cout<<"enter number of disks: ";
    cin>>n;
    hanoi(n,'a','c','b');
    return 0;
}
