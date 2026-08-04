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
Question:
Store product details in a Product structure and display the product details along with the total cost.
Input:
Name
Price (double)
Quantity (int)

Time Complexity:
O(1)

Space Complexity:
O(1)
*/

struct Product {
    string name;
    double price;
    int quantity;
};

class Solution {
public:
    void solve() {
        Product p;
        cout << "Enter product name: ";
        cin >> ws;
        getline(cin, p.name);
        cout << "Enter price: ";
        cin >> p.price;
        cout << "Enter quantity: ";
        cin >> p.quantity;

        double total = p.price * p.quantity;
        cout << p.name << endl;
        cout << fixed << setprecision(2) << p.price << endl;
        cout << p.quantity << endl;
        cout << fixed << setprecision(2) << total << endl;
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
