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
Question: Write a program to Concatenate two Doubly Linked Lists.
Time Complexity: O(n) (to traverse first list)
Space Complexity: O(1)
*/

class Solution {
public:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int v) : data(v), prev(nullptr), next(nullptr) {}
    };

    Node* head1 = nullptr;
    Node* head2 = nullptr;

    void insertAtEnd(Node*& head, int val) {
        Node* newNode = new Node(val);
        if (!head) { head = newNode; return; }
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }

    void display(Node* head) {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }

    void concatenateLists() {
        if (!head1) { head1 = head2; return; }
        if (!head2) return;
        Node* temp = head1;
        while (temp->next) temp = temp->next;
        temp->next = head2;
        head2->prev = temp;
        head2 = nullptr;
    }

    void solve() {
        insertAtEnd(head1, 1);
        insertAtEnd(head1, 2);
        insertAtEnd(head1, 3);

        insertAtEnd(head2, 4);
        insertAtEnd(head2, 5);
        insertAtEnd(head2, 6);

        cout << "List1: "; display(head1);
        cout << "List2: "; display(head2);

        concatenateLists();

        cout << "Concatenated List: "; display(head1);
    }
};

int main() {
    kulkarni;
    Solution atharv;
    atharv.solve();
    return 0;
}
