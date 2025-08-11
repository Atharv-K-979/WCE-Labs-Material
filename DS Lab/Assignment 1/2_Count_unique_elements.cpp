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
Write a program to count the unique elements in array.

Time Complexity:
method1: O(n^2)
method2: O(n)

Space Complexity:
method1: O(1)
method2: O(n)
*/

class Solution
{
public:
    void method1()
    { // Brute Force count unique values
        cout << "Enter Array Size: ";
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        int uniqueCount = 0;
        for (int i = 0; i < n; i++)
        {
            bool seen = false;
            for (int j = 0; j < i; j++)
            {
                if (arr[i] == arr[j])
                {
                    seen = true;
                    break;
                }
            }
            if (!seen)
                uniqueCount++;
        }
        cout << "Unique elements count: " << uniqueCount << endl;
    }

    void method2()
    { // Using set
        cout << "Enter Array Size: ";
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        unordered_set<int> st(arr.begin(), arr.end());
        cout << "Unique elements count: " << st.size() << endl;
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
