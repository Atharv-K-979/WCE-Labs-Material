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
Given count of persons C, number of items N, and N items (name price quantity),
calculate expense per item (price*quantity), total expense and per-person share.

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

struct PartyItem {
    string name;
    double price;
    int quantity;
};

class Solution {
public:
    void solve() {
        int C, N;
        cout << "Enter count of persons (C): ";
        cin >> C;
        cout << "Enter number of items (N): ";
        cin >> N;
        vector<PartyItem> items(N);
        double total = 0.0;
        for (int i = 0; i < N; i++) {
            cout << "Enter item (name price quantity): ";
            cin >> items[i].name >> items[i].price >> items[i].quantity;
            total += items[i].price * items[i].quantity;
        }
        cout << fixed << setprecision(2);
        cout << total << endl;
        cout << (C == 0 ? 0.00 : total / C) << endl;
        for (auto &it : items) {
            cout << it.name << " " << (it.price * it.quantity) << endl;
        }
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
