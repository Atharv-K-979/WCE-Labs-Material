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
Write a program to delete nodes at even position in a Circular Linked List.

Time Complexity:
O(n)

Space Complexity:
O(1)
*/

class Solution {
public:
    struct Node {
        int data;
        Node* next;
        Node(int v): data(v), next(nullptr) {}
    };
    Node* createCircular(vector<int> arr) {
        if (arr.empty()) return nullptr;
        Node* head = new Node(arr[0]);
        Node* ptr = head;
        for (int i = 1; i < arr.size(); i++) {
            ptr->next = new Node(arr[i]);
            ptr = ptr->next;
        }
        ptr->next = head; // make circular
        return head;
    }
    void deleteEvenPositions(Node*& head) {
        if (!head || head->next == head) return; // empty or single node case

        Node* ptr = head;
        Node* preptr = nullptr;
        int pos = 1;

        do {
            if (pos % 2 == 0) {
                // delete current node at even position
                preptr->next = ptr->next;
                Node* del = ptr;
                ptr = ptr->next;
                delete del;
            } else {
                preptr = ptr;
                ptr = ptr->next;
            }
            pos++;
        } while (ptr != head);
    }
    void displayCircular(Node* head) {
        if (!head) return;
        Node* ptr = head;
        do {
            cout << ptr->data << " ";
            ptr = ptr->next;
        } while (ptr != head);
        cout << "\n";
    }

    void solve() {
        vector<int> arr = {1, 2, 3, 4, 5, 6};
        Node* head = createCircular(arr);

        cout << "Original Circular List: ";
        displayCircular(head);
        deleteEvenPositions(head);

        cout << "After deleting even positions: ";
        displayCircular(head);
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
