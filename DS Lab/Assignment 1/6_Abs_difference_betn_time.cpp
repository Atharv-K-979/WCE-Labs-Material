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
Given two Time structs (hours, minutes, seconds), calculate the absolute difference between them.

Time Complexity:
O(1)

Space Complexity:
O(1)
*/

struct Time {
    int hours;
    int minutes;
    int seconds;
};

class Solution {
public:
    void solve() {
        cout << "Enter start time (h m s): ";
        Time t1, t2;
        cin >> t1.hours >> t1.minutes >> t1.seconds;
        cout << "Enter end time (h m s): ";
        cin >> t2.hours >> t2.minutes >> t2.seconds;

        int s1 = t1.hours*3600 + t1.minutes*60 + t1.seconds;
        int s2 = t2.hours*3600 + t2.minutes*60 + t2.seconds;
        int diff = abs(s1 - s2);
        int h = diff / 3600; diff %= 3600;
        int m = diff / 60; diff %= 60;
        int s = diff;
        cout << "Difference: " << h << ":" << m << ":" << s << endl;
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
