#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 3  // order of tree

class Node {
public:
    bool isLeaf;
    vector<int> keys;
    vector<Node*> ptr;
    Node* next;

    Node(bool leaf) {
        isLeaf = leaf;
        next = NULL;
    }
};

class BPlusTree {
    Node* root;

public:
    BPlusTree() {
        root = new Node(true);
    }

    void insert(int key) {
        Node* curr = root;

        if (curr->keys.size() < MAX) {
            curr->keys.push_back(key);
            sort(curr->keys.begin(), curr->keys.end());
        } else {
            Node* newLeaf = new Node(true);
            vector<int> temp = curr->keys;
            temp.push_back(key);
            sort(temp.begin(), temp.end());

            curr->keys.clear();
            for (int i = 0; i < (MAX+1)/2; i++)
                curr->keys.push_back(temp[i]);

            for (int i = (MAX+1)/2; i < temp.size(); i++)
                newLeaf->keys.push_back(temp[i]);

            newLeaf->next = curr->next;
            curr->next = newLeaf;
        }
    }

    void search(int key) {
        Node* curr = root;

        for (int k : curr->keys) {
            if (k == key) {
                cout << "Key found\n";
                return;
            }
        }
        cout << "Key not found\n";
    }

    void traverse() {
        Node* curr = root;
        while (curr != NULL) {
            for (int k : curr->keys)
                cout << k << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};

int main() {
    BPlusTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);

    cout << "Traversal: ";
    tree.traverse();

    tree.search(15);
    tree.search(100);

    return 0;
}