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
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;
class Solution {
public:
    queue<string> ticketQueue;
    void addCustomer(string name) {
        ticketQueue.push(name);
    }
    void serveCustomer() {
        if (ticketQueue.empty()) {
            cout << "no customer are present to serve"<<endl;
        } 
        else {
            ticketQueue.pop();
        }
    }
    void displayQueue() {
        if (ticketQueue.empty()) {
            cout << "queue is empty"<<endl;
        } 
        else {
            cout << "customers in queue: "<<endl;
            queue<string> temp = ticketQueue;
            int unique_id=1;
            while (!temp.empty()) {
                cout<<unique_id<<" ";
                cout << temp.front() <<endl;
                temp.pop();
                unique_id++;
            }
            cout<<endl;
        }
    }
};
int main() {
    int opt;
    string name;
    Solution ans;
    while (1) {
        cout << "\nticket booking system"<<endl;
        cout << "1.customer come\n2.serve the customer\n3.display queue\n4.exit"<<endl;
        cout << "enter choice: ";
        cin >> opt;
        if(opt>3){
            cout<<"exiting code"<<endl;
            return 0;
        }
        switch (opt) {
            case 1:
                cout << "enter customer name: ";
                cin >> name;
                ans.addCustomer(name);
                break;
            case 2:
                ans.serveCustomer();
                break;
            case 3:
                ans.displayQueue();
                break;
            default:
                cout << "give correct option"<<endl;
        }
    }
    return 0;
}
