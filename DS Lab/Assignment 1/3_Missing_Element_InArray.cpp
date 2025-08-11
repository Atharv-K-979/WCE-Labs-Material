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
Question:
Write a program to find the missing element in an array.
Assumption: array contains numbers from 1..(n+1) with exactly one missing and size given is n.

Time Complexity:
method1: O(n)
method2: O(n)

Space Complexity:
O(1)
*/

class Solution
{
public:
    void method1()
    { // brute by summing
        cout << "Enter number of elements (n): ";
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        // int sum = 0;
        // for (int x : arr) sum += x;
        // int total = 0;
        // for (int i = 1; i <= n+1; i++) total += i;
        // cout << "Missing element is: " << total - sum << endl;
        int len = arr.size() + 1;
        int total = len * (len + 1) / 2;
        int sum = 0;
        for (int val : arr)
            sum += val;
        cout << "Missing element is: " << total - sum << endl;
    }

    void solve()
    {
        method1();
    }
};

int main()
{
    Solution atharv;
    atharv.solve();
    return 0;
}
