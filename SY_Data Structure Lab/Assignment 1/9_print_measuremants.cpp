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
Given two measurements (inches int, feet double), add them and print result.

Time Complexity:
O(1)

Space Complexity:
O(1)
*/

struct Measurement {
    int inches;
    double feet;
};

class Solution {
public:
    void solve() {
        Measurement a, b;
        cout << "Enter first measurement (inches feet): ";
        cin >> a.inches >> a.feet;
        cout << "Enter second measurement (inches feet): ";
        cin >> b.inches >> b.feet;
        int inchesSum = a.inches + b.inches;
        double feetSum = a.feet + b.feet;
        cout << inchesSum << " " << fixed << setprecision(1) << feetSum << endl;
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
