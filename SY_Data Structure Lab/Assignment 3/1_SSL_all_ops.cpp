#include <bits/stdc++.h>
using namespace std;

/*
Problem 1:
Menu driven program on Singly Linked List
Operations:
 - Insert at Beginning, End, Middle
 - Delete at Beginning, End, Middle
 - Display Linked List

Time Complexity:
Insertion/Deletion at Beginning: O(1)
Insertion/Deletion at End: O(n)
Insertion/Deletion at Middle: O(n) (finding middle takes O(n))
Display: O(n)

Space Complexity: O(1) extra (ignoring input/output and recursion stack)
*/

class Solution
{
public:
    struct Node
    {
        int data;
        Node *next;
        Node(int val) : data(val), next(nullptr) {}  // different way to write the constructor
    };

    Node *head = nullptr;

    void insertAtBeginning(int val)
    {
        Node *newNode = new Node(val);
        newNode->next = head;
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
        Node *ptr = head;
        while (ptr->next)
        {
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }

    // void insertAtMiddle(int val) {
    //     Node* newNode = new Node(val);
    //     if (!head) {
    //         head = newNode;
    //         return;
    //     }
    //     if (!head->next) { // only 1 node, insert after head
    //         head->next = newNode;
    //         return;
    //     }
    //     Node* slow = head;
    //     Node* fast = head->next;
    //     Node* preptr = nullptr;
    //     while (fast && fast->next) {
    //         preptr = slow;
    //         slow = slow->next;
    //         fast = fast->next->next;
    //     }
    //     if (preptr == nullptr) { // just 2 nodes case
    //         newNode->next = head->next;
    //         head->next = newNode;
    //     } else {
    //         preptr->next = newNode;
    //         newNode->next = slow;
    //     }
    // }
    void insertAtMiddle(int data)
    {
        if (head == NULL)
        {
            head = new Node(data);
            return;
        }

        Node *slow = head, *fast = head;
        Node *prev = NULL;

        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            prev = slow;
            slow = slow->next;
        }

        // slow is middle, prev is before middle
        Node *newNode = new Node(data);

        // insert before slow
        prev->next = newNode;
        newNode->next = slow;
    }

    void deleteAtBeginning()
    {
        if (!head)
            return;
        Node *temp = head;
        head = head->next;
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
        Node *ptr = head;
        Node *preptr = nullptr;
        while (ptr->next)
        {
            preptr = ptr;
            ptr = ptr->next;
        }
        preptr->next = nullptr;
        delete ptr;
    }

    // void deleteAtMiddle() {
    //     if (!head) return;
    //     if (!head->next) { // only 1 node
    //         delete head;
    //         head = nullptr;
    //         return;
    //     }
    //     Node* slow = head;
    //     Node* fast = head->next;
    //     Node* preptr = nullptr;
    //     while (fast && fast->next) {
    //         preptr = slow;
    //         slow = slow->next;
    //         fast = fast->next->next;
    //     }
    //     if (preptr == nullptr) { // 2 nodes case, delete second
    //         Node* temp = head->next;
    //         head->next = head->next->next;
    //         delete temp;
    //     } else {
    //         preptr->next = slow->next;
    //         delete slow;
    //     }
    // }

    void deleteAtMiddle()
    {
        if (head == NULL)
            return;

        Node *slow = head, *fast = head;
        Node *prev = NULL;

        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            prev = slow;
            slow = slow->next;
        }

        // slow is middle
        if (prev == NULL)
        {
            // only one element
            head = head->next;
        }
        else
        {
            prev->next = slow->next;
        }

        delete slow;
    }

    // Display
    void displayList()
    {
        Node *ptr = head;
        while (ptr)
        {
            cout << ptr->data << " ";
            ptr = ptr->next;
        }
        cout << "\n";
    }

    void solve()
    {
        int choice, val;
        do
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
                cout << "Linked List: ";
                displayList();
                break;
            case 8:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid choice!\n";
            }
        } while (true);
    }
};

int main()
{
    Solution s;
    s.solve();
    return 0;
}
