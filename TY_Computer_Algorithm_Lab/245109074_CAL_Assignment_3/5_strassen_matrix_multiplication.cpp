#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>> addMatrix(vector<vector<int>>&A,vector<vector<int>>&B){
    int n=A.size();
    vector<vector<int>>C(n,vector<int>(n));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            C[i][j]=A[i][j]+B[i][j];
    return C;
}
vector<vector<int>> subMatrix(vector<vector<int>>&A,vector<vector<int>>&B){
    int n=A.size();
    vector<vector<int>>C(n,vector<int>(n));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            C[i][j]=A[i][j]-B[i][j];
    return C;
}
vector<vector<int>> strassen(vector<vector<int>>&A,vector<vector<int>>&B){
    int n=A.size();
    if(n==1){
        vector<vector<int>>C(1,vector<int>(1));
        C[0][0]=A[0][0]*B[0][0];
        return C;
    }
    int half=n/2;
    vector<vector<int>>A11(half,vector<int>(half)),A12(half,vector<int>(half)),A21(half,vector<int>(half)),A22(half,vector<int>(half));
    vector<vector<int>>B11(half,vector<int>(half)),B12(half,vector<int>(half)),B21(half,vector<int>(half)),B22(half,vector<int>(half));
    for(int i=0;i<half;i++)
        for(int j=0;j<half;j++){
            A11[i][j]=A[i][j];
            A12[i][j]=A[i][j+half];
            A21[i][j]=A[i+half][j];
            A22[i][j]=A[i+half][j+half];
            B11[i][j]=B[i][j];
            B12[i][j]=B[i][j+half];
            B21[i][j]=B[i+half][j];
            B22[i][j]=B[i+half][j+half];
        }
    vector<vector<int>>t1=addMatrix(A11,A22);
    vector<vector<int>>t2=addMatrix(B11,B22);
    vector<vector<int>>M1=strassen(t1,t2);
    vector<vector<int>>t3=addMatrix(A21,A22);
    vector<vector<int>>M2=strassen(t3,B11);
    vector<vector<int>>t4=subMatrix(B12,B22);
    vector<vector<int>>M3=strassen(A11,t4);
    vector<vector<int>>t5=subMatrix(B21,B11);
    vector<vector<int>>M4=strassen(A22,t5);
    vector<vector<int>>t6=addMatrix(A11,A12);
    vector<vector<int>>M5=strassen(t6,B22);
    vector<vector<int>>t7=subMatrix(A21,A11);
    vector<vector<int>>t8=addMatrix(B11,B12);
    vector<vector<int>>M6=strassen(t7,t8);
    vector<vector<int>>t9=subMatrix(A12,A22);
    vector<vector<int>>t10=addMatrix(B21,B22);
    vector<vector<int>>M7=strassen(t9,t10);
    vector<vector<int>>t11=addMatrix(M1,M4);
    vector<vector<int>>t12=subMatrix(t11,M5);
    vector<vector<int>>C11=addMatrix(t12,M7);
    vector<vector<int>>C12=addMatrix(M3,M5);
    vector<vector<int>>C21=addMatrix(M2,M4);
    vector<vector<int>>t13=addMatrix(M1,M3);
    vector<vector<int>>t14=subMatrix(t13,M2);
    vector<vector<int>>C22=addMatrix(t14,M6);
    vector<vector<int>>C(n,vector<int>(n));
    for(int i=0;i<half;i++)
        for(int j=0;j<half;j++){
            C[i][j]=C11[i][j];
            C[i][j+half]=C12[i][j];
            C[i+half][j]=C21[i][j];
            C[i+half][j+half]=C22[i][j];
        }
    return C;
}
void runCase(vector<vector<int>>A,vector<vector<int>>B){
    vector<vector<int>>C=strassen(A,B);
    for(int i=0;i<(int)C.size();i++){
        for(int j=0;j<(int)C.size();j++)
            cout<<C[i][j]<<" ";
        cout<<endl;
    }
}
int main(){
    vector<vector<int>>a1={{1,2},{3,4}};
    vector<vector<int>>b1={{5,6},{7,8}};
    vector<vector<int>>a2={{2,0},{1,2}};
    vector<vector<int>>b2={{1,1},{0,1}};
    vector<vector<int>>a3={{1,0},{0,1}};
    vector<vector<int>>b3={{9,8},{7,6}};
    vector<vector<int>>a4={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    vector<vector<int>>b4={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    vector<vector<int>>a5={{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2}};
    vector<vector<int>>b5={{3,3,3,3},{3,3,3,3},{3,3,3,3},{3,3,3,3}};
    cout<<"test case 1:"<<endl;
    runCase(a1,b1);
    cout<<"test case 2:"<<endl;
    runCase(a2,b2);
    cout<<"test case 3:"<<endl;
    runCase(a3,b3);
    cout<<"test case 4:"<<endl;
    runCase(a4,b4);
    cout<<"test case 5:"<<endl;
    runCase(a5,b5);
    return 0;
}
