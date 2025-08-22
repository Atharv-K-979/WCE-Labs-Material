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
Question: Reverse a given string using stack.
Time Complexity: O(n)
Space Complexity: O(n) for stack
*/

int main() {
    string inputString;
    cout << "Enter string: ";
    cin >> inputString;

    stack<char> charStack;
    for (char ch : inputString) {
        charStack.push(ch);
    }

    string reversedString;
    while (!charStack.empty()) {
        reversedString += charStack.top();
        charStack.pop();
    }

    cout << "Reversed string: " << reversedString << "\n";
    return 0;
}
