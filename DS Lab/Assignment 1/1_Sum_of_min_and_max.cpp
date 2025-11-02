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
Given an array of integers, find the sum of the smallest and largest elements.

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
    { // Brute Force
        cout << "Enter Array Size: ";
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        int mn = arr[0], mx = arr[0];
        for (int i = 1; i < n; i++)
        {
            if (arr[i] < mn)
                mn = arr[i];
            if (arr[i] > mx)
                mx = arr[i];
        }
        cout << "Sum of Min and Max element is: " << mn + mx << endl;
    }

    void method2()
    { // Using STL
        cout << "Enter Array Size: ";
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        int mn = *min_element(arr.begin(), arr.end());
        int mx = *max_element(arr.begin(), arr.end());
        cout << "Sum of Min and Max element is: " << mn + mx << endl;
    }

    void solve()
    {
        method1();
        // method2();
    }
};

int main()
{
    Solution atharv;
    atharv.solve();
    return 0;
}