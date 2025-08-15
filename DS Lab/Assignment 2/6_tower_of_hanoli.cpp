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
Question: Solve Tower of Hanoi using recursion.
Time Complexity: O(2^N)
Space Complexity: O(N)
*/

class Solution {
public:
    void moveDisks(int numberOfDisks, char sourceRod, char destinationRod, char helperRod) {
        // base case
        if(numberOfDisks == 1) {
            cout << "Move disk 1 from " << sourceRod << " to " << destinationRod << "\n";
            return;
        }
        // move n-1 disks to helper rod
        moveDisks(numberOfDisks - 1, sourceRod, helperRod, destinationRod);
        // move largest disk to destination
        cout << "Move disk " << numberOfDisks << " from " << sourceRod << " to " << destinationRod << "\n";
        // move n-1 disks from helper to destination
        moveDisks(numberOfDisks - 1, helperRod, destinationRod, sourceRod);
    }

    void solve() {
        int numberOfDisks;
        cout << "Enter number of disks: ";
        cin >> numberOfDisks;

        moveDisks(numberOfDisks, 'A', 'C', 'B');
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
