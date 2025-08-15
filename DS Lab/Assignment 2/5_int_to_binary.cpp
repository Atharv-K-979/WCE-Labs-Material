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
Question: Convert integer to binary using recursion.
Time Complexity: O(log N)
Space Complexity: O(log N)
*/

class Solution {
public:
    void printBinary(int numberValue) {
        // base case
        if(numberValue == 0) {
            return;
        }
        // recursive call
        printBinary(numberValue / 2);
        // print last bit
        cout << numberValue % 2;
    }

    void solve() {
        int numberValue;
        cout << "Enter an integer: ";
        cin >> numberValue;

        if(numberValue == 0) {
            cout << "Binary: 0\n";
        } else {
            cout << "Binary: ";
            printBinary(numberValue);
            cout << "\n";
        }
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
