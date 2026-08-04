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
Question: Write a program to Sort a Doubly Linked List.
Time Complexity: O(n^2) using bubble sort
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

    void sortList()
    {
        if (!head)
            return;
        bool swapped;
        do
        {
            swapped = false;
            Node *curr = head;
            while (curr->next)
            {
                if (curr->data > curr->next->data)
                {
                    swap(curr->data, curr->next->data);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
    }

    void solve()
    {
        insertAtEnd(40);
        insertAtEnd(10);
        insertAtEnd(30);
        insertAtEnd(20);
        insertAtEnd(60);
        insertAtEnd(90);
        insertAtEnd(70);
        insertAtEnd(5);

        cout << "Original List: ";
        display();
        sortList();
        cout << "Sorted List: ";
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
