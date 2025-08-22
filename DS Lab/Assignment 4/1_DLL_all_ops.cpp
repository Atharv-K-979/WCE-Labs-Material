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
using namespace std;

/*
Question: Write a Menu Driven program to perform following operations on Doubly linked list:
          Insert at Beginning, End, Middle
          Delete at Beginning, End, Middle
          Display Linked List
Time Complexity: O(n) in worst case for insert/delete operations
Space Complexity: O(1) extra (excluding list storage)
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
    void insertAtBeginning(int val)
    {
        Node *newNode = new Node(val);
        if (!head)
        {
            head = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

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

    void insertAtMiddle(int val)
    {
        if (!head)
        {
            head = new Node(val);
            return;
        }
        Node *slow = head, *fast = head;
        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        Node *newNode = new Node(val);
        Node *prevNode = slow->prev;
        newNode->next = slow;
        newNode->prev = prevNode;
        if (prevNode)
            prevNode->next = newNode;
        slow->prev = newNode;
        if (slow == head)
            head = newNode;
    }

    void deleteAtBeginning()
    {
        if (!head)
            return;
        Node *temp = head;
        head = head->next;
        if (head)
            head->prev = nullptr;
        delete temp;
    }

    void deleteAtEnd()
    {
        if (!head)
            return;
        if (!head->next)
        {
            delete head;
            head = nullptr;
            return;
        }
        Node *temp = head;
        while (temp->next)
            temp = temp->next;
        temp->prev->next = nullptr;
        delete temp;
    }

    void deleteAtMiddle()
    {
        if (!head)
            return;
        Node *slow = head, *fast = head;
        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        if (!slow->prev && !slow->next)
        { // only one node
            delete slow;
            head = nullptr;
            return;
        }
        if (slow->prev)
            slow->prev->next = slow->next;
        if (slow->next)
            slow->next->prev = slow->prev;
        if (slow == head)
            head = slow->next;
        delete slow;
    }
    void displayList()
    {
        Node *temp = head;
        cout << "Linked List: ";
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }

    void solve()
    {
        int choice, val;
        while (true)
        {
            cout << "\nMenu:\n";
            cout << "1. Insert at Beginning\n";
            cout << "2. Insert at End\n";
            cout << "3. Insert at Middle\n";
            cout << "4. Delete at Beginning\n";
            cout << "5. Delete at End\n";
            cout << "6. Delete at Middle\n";
            cout << "7. Display List\n";
            cout << "8. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                insertAtBeginning(val);
                break;
            case 2:
                cout << "Enter value: ";
                cin >> val;
                insertAtEnd(val);
                break;
            case 3:
                cout << "Enter value: ";
                cin >> val;
                insertAtMiddle(val);
                break;
            case 4:
                deleteAtBeginning();
                break;
            case 5:
                deleteAtEnd();
                break;
            case 6:
                deleteAtMiddle();
                break;
            case 7:
                displayList();
                break;
            case 8:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        }
    }
};

int main()
{
    Solution atharv;
    atharv.solve();
    return 0;
}
