#include<iostream>
using namespace std;
struct node{
    int data;
    int leftsize;
    node*left;
    node*right;
};
node* insert(node*root,int data){
    if(root==NULL){
        node*n=new node();
        n->data=data;
        n->leftsize=0;
        n->left=NULL;
        n->right=NULL;
        return n;
    }
    if(data<=root->data){
        root->leftsize++;
        root->left=insert(root->left,data);
    }
    else
        root->right=insert(root->right,data);
    return root;
}
int getrank(node*root,int x){
    if(root==NULL)
        return 0;
    if(x==root->data)
        return root->leftsize;
    if(x<root->data)
        return getrank(root->left,x);
    return root->leftsize+1+getrank(root->right,x);
}
int main(){
    int q;
    cout<<"enter number of operations: ";
    cin>>q;
    node*root=NULL;
    for(int i=0;i<q;i++){
        int type;
        cout<<"enter 1 to track a number or 2 to get rank: ";
        cin>>type;
        int x;
        cout<<"enter number: ";
        cin>>x;
        if(type==1)
            root=insert(root,x);
        else
            cout<<"rank of "<<x<<" is "<<getrank(root,x)<<endl;
    }
    return 0;
}
