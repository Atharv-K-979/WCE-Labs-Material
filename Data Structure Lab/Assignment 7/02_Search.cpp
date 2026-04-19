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

bool search(Node* root, int key) {
    if(root == NULL) return false;
    if(root->data == key) return true;
    return search(root->left, key) || search(root->right, key);
}

int main() {
    Node* root = createNode(10);
    root->left = createNode(20);
    root->right = createNode(30);
    root->left->left = createNode(40);

    int key = 30;
    if(search(root, key))
        cout << key << " found in tree";
    else
        cout << key << " not found in tree";
    return 0;
}
