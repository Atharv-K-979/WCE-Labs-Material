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
Question:
Write a program to Merge two sorted circular Linked Lists.

Time Complexity:
O(n + m), where n and m are the lengths of the two lists.

Space Complexity:
O(n + m), since we are creating a new merged list.
*/

class Solution
{
public:
    struct Node
    {
        int data;
        Node *next;
        Node(int v) : data(v), next(nullptr) {}
    };

    Node *createCircular(vector<int> arr)
    {
        if (arr.empty())
            return nullptr;
        Node *head = new Node(arr[0]);
        Node *ptr = head;
        for (int i = 1; i < arr.size(); i++)
        {
            ptr->next = new Node(arr[i]);
            ptr = ptr->next;
        }
        ptr->next = head; // make it circular
        return head;
    }

    Node *mergeCircular(Node *head1, Node *head2)
    {
        if (!head1)
            return head2;
        if (!head2)
            return head1;

        Node *ptr1 = head1;
        Node *ptr2 = head2;

        Node *dummy = new Node(0); // temporary dummy node
        Node *tail = dummy;

        do
        {
            if (ptr1->data <= ptr2->data)
            {
                tail->next = new Node(ptr1->data);
                tail = tail->next;
                ptr1 = ptr1->next;
            }
            else
            {
                tail->next = new Node(ptr2->data);
                tail = tail->next;
                ptr2 = ptr2->next;
            }
        } while (ptr1 != head1 && ptr2 != head2);

        while (ptr1 != head1)
        {
            tail->next = new Node(ptr1->data);
            tail = tail->next;
            ptr1 = ptr1->next;
        }

        while (ptr2 != head2)
        {
            tail->next = new Node(ptr2->data);
            tail = tail->next;
            ptr2 = ptr2->next;
        }

        tail->next = dummy->next;

        Node *mergedHead = dummy->next;
        delete dummy;
        return mergedHead;
    }
    void displayCircular(Node *head)
    {
        if (!head)
            return;
        Node *ptr = head;
        do
        {
            cout << ptr->data << " ";
            ptr = ptr->next;
        } while (ptr != head);
        cout << "\n";
    }

    void solve()
    {
        Node *head1 = createCircular({1, 3, 5, 7});
        Node *head2 = createCircular({2, 4, 6, 8});

        cout << "List 1: ";
        displayCircular(head1);

        cout << "List 2: ";
        displayCircular(head2);

        Node *merged = mergeCircular(head1, head2);

        cout << "Merged Circular List: ";
        displayCircular(merged);
    }
};

int main()
{
    Solution atharv;
    atharv.solve();
    return 0;
}
