#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if(root == NULL) return createNode(value);
    if(value < root->data) root->left = insert(root->left, value);
    else root->right = insert(root->right, value);
    return root;
}

int findMin(Node* root) {
    while(root->left != NULL)
        root = root->left;
    return root->data;
}

int main() {
    Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);

    cout << "Minimum value in BST: " << findMin(root);
    return 0;
}
