#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <limits>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#define ak long long
#define kulkarni                 \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
using namespace std;

/*
Question: Write a program to Reverse a Doubly Linked List.
Time Complexity: O(n)
Space Complexity: O(1)
*/

class Solution
{
public:
    struct Node
    {
        int data;
        Node *prev;
        Node *next;
        Node(int v) : data(v), prev(nullptr), next(nullptr) {}
    };

    Node *head = nullptr;

    void insertAtEnd(int val)
    {
        Node *newNode = new Node(val);
        if (!head)
        {
            head = newNode;
            return;
        }
        Node *temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }

    void display()
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }

    void reverseList()
    {
        Node *curr = head;
        Node *temp = nullptr;
        while (curr)
        {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }
        if (temp)
            head = temp->prev;
    }

    void solve()
    {
        insertAtEnd(10);
        insertAtEnd(20);
        insertAtEnd(30);
        insertAtEnd(40);
        insertAtEnd(50);
        insertAtEnd(60);
        insertAtEnd(60);
        cout << "Original List: ";
        display();
        reverseList();
        cout << "Reversed List: ";
        display();
    }
};

int main()
{
    kulkarni;
    Solution atharv;
    atharv.solve();
    return 0;
}
