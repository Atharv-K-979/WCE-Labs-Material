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
Given array of car number-plates and day of month, calculate total fines:
Odd cars on even day or even cars on odd day fined $250 per occurrence.

Time Complexity:
method1: O(n)
method2: O(n)

Space Complexity:
O(1)
*/

class Solution {
public:
    void method1() { // brute
        cout << "Enter number of plates (n): ";
        int n; cin >> n;
        vector<int> arr(n);
        cout << "Enter plates: ";
        for (int i = 0; i < n; i++) cin >> arr[i];
        cout << "Enter day: ";
        int day; cin >> day;
        int fine = 0;
        for (int x : arr) {
            if ((day % 2 == 0 && x % 2 != 0) || (day % 2 != 0 && x % 2 == 0))
                fine += 250;
        }
        cout << "Total fine: " << fine << endl;
    }

    // void method2() { // using count_if (shortcut)
    //     cout << "Enter number of plates (n): ";
    //     int n; cin >> n;
    //     vector<int> arr(n);
    //     cout << "Enter plates: ";
    //     for (int i = 0; i < n; i++) cin >> arr[i];
    //     cout << "Enter day: ";
    //     int day; cin >> day;
    //     int violations = count_if(arr.begin(), arr.end(), [&](int x){
    //         return (day % 2 == 0 && x % 2 != 0) || (day % 2 != 0 && x % 2 == 0);
    //     });
    //     cout << "Total fine: " << violations * 250 << endl;
    // }

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
