#include <bits/stdc++.h>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
#include<climits>
#include<limits>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<stack>
#include<queue>
#include<deque>
#include<list>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#define ak long long
#define kulkarni ios::sync_with_stdio(false); cin.tie(nullptr);
using namespace std;

/*
Question:
Write a program to Search an element in a Linked List using recursive function.

Time Complexity:
O(n), since in the worst case we may need to traverse all nodes.

Space Complexity:
O(n), due to recursive function calls (stack space).
*/

class Solution {
public:

    struct Node {
        int data;
        Node* next;
        Node(int v): data(v), next(nullptr) {}
    };

    Node* insertEnd(Node* head, int val) {
        Node* newNode = new Node(val);
        if (!head) return newNode;
        Node* ptr = head;
        while (ptr->next) {
            ptr = ptr->next;
        }
        ptr->next = newNode;
        return head;
    }

    bool searchRecursive(Node* head, int key) {
        if (!head) return false;            // base case
        if (head->data == key) return true; // found key
        return searchRecursive(head->next, key);
    }

    void display(Node* head) {
        Node* ptr = head;
        while (ptr) {
            cout << ptr->data << " ";
            ptr = ptr->next;
        }
        cout << "\n";
    }

    void solve() {
        Node* head = nullptr;
        vector<int> values = {10, 20, 30, 40, 50};


        for (int v : values) {
            head = insertEnd(head, v);
        }

        cout << "Linked List: ";
        display(head);

        int key = 30;
        cout << "Searching for " << key << " : ";
        if (searchRecursive(head, key))
            cout << "Found\n";
        else
            cout << "Not Found\n";

        key = 100;
        cout << "Searching for " << key << " : ";
        if (searchRecursive(head, key))
            cout << "Found\n";
        else
            cout << "Not Found\n";
    }
};

int main(){
    Solution atharv;
    atharv.solve();
    return 0;
}
