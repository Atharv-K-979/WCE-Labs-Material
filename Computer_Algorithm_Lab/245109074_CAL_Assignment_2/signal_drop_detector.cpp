#include<iostream>
using namespace std;
int main(){
    int n;
    cout<<"enter number of readings: ";
    cin>>n;
    int signal[n];
    cout<<"enter "<<n<<" signal readings: ";
    for(int i=0;i<n;i++)
        cin>>signal[i];
    int run=1,drops=0;
    for(int i=1;i<n;i++){
        if(signal[i]<signal[i-1])
            run++;
        else{
            if(run>=3)
                drops++;
            run=1;
        }
    }
    if(run>=3)
        drops++;
    cout<<"number of signal drops is "<<drops;
    return 0;
}
