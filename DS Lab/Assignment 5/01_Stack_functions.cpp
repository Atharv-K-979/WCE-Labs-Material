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
using namespace std;

/*
Question: Menu-driven program to perform stack operations (push, pop, display) using static implementation.
Time Complexity: Push/Pop O(1), Display O(n)
Space Complexity: O(n) for stack array
*/

class Stack {
    int stackArr[20]; // simple static array of fixed size 20 we can extend by using dynamic memory
    int topIndex;      // points to the top of stack
    int maxSize;       // user-defined maximum size for stack
public:
    Stack() {
        topIndex = -1;
        cout << "Enter maximum size of stack : ";
        cin >> maxSize;
    }

    void pushElement(int value) {
        if (topIndex == maxSize - 1) {
            cout << "Stack Overflow\n";
            return;
        }
        stackArr[++topIndex] = value;
        cout << "Pushed: " << value << "\n";
    }

    void popElement() {
        if (topIndex == -1) {
            cout << "Stack Underflow\n";
            return;
        }
        cout << "Popped: " << stackArr[topIndex--] << "\n";
    }

    void displayStack() {
        if (topIndex == -1) {
            cout << "Stack is empty\n";
            return;
        }
        cout << "Stack elements: ";
        for (int i = topIndex; i >= 0; i--) cout << stackArr[i] << " ";
        cout << "\n";
    }

    void solve() {
        int choice;
        while (true) {
            cout << "\n1. Push.\n2. Pop.\n3. Display.\n4. Exit\nEnter choice: ";
            cin >> choice;
            if (choice == 1) {
                int val;
                cout << "Enter value to push: ";
                cin >> val;
                pushElement(val);
            } 
            else if (choice == 2) {
                popElement();
            } 
            else if (choice == 3) {
                displayStack();
            } 
            else if (choice >= 4) {
                cout << "Exiting...\n";
                break;
            } 
            else {
                cout << "Invalid choice\n";
            }
        }
    }
};

int main() {
    Stack atharv;
    atharv.solve();
    return 0;
}
