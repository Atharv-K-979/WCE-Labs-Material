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
Question: Find the length of the longest valid (well-formed) parentheses substring.
Input: s = "(()"
Output: 2
Time Complexity: O(n)
Space Complexity: O(n) for stack
*/

int main() {
    string inputString;
    cout << "Enter parentheses string: ";
    cin >> inputString;

    stack<int> Stk;
    Stk.push(-1); // base index to calculate valid substring length
    int maxLength = 0;
    int n = inputString.length();
    for (int i = 0; i < n; i++) {
        if (inputString[i] == '(') {
            Stk.push(i);
        } else {
            Stk.pop();
            if (Stk.empty()) {
                Stk.push(i);
            } else {
                maxLength = max(maxLength, i - Stk.top());
            }
        }
    }

    cout << "Longest valid parentheses length: " << maxLength << "\n";
    return 0;
}
