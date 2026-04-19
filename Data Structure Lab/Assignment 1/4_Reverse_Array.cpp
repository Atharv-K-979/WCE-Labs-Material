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
Write a program to reverse an array.

Time Complexity:
method1: O(n)
method2: O(n)

Space Complexity:
method1: O(1) (printing in reverse)
method2: O(1) (in-place reverse)
*/

class Solution {
public:
    void method1() { // print in reverse (brute)
        cout<<"Enter Array Size: ";
        int n; cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) cin >> arr[i];

        cout << "Reversed array: ";
        for (int i = n - 1; i >= 0; i--) cout << arr[i] << " ";
        cout << endl;
    }

    void method2() { // using reverse
        cout<<"Enter Array Size: ";
        int n; cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) cin >> arr[i];

        reverse(arr.begin(), arr.end());
        cout << "Reversed array: ";
        for (int x : arr) cout << x << " ";
        cout << endl;
    }

    void solve() {
        method1();
        //method2();
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
