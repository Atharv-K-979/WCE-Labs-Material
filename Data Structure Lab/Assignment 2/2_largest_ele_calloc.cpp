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
Question: Find largest element in array using calloc.
Time Complexity: O(N)
Space Complexity: O(N)
*/

class Solution {
public:
    void solve() {
        int numberOfElements;
        cout << "Enter number of elements: ";
        cin >> numberOfElements;

        int *pointerArray = (int*) calloc(numberOfElements, sizeof(int));

        for(int index = 0; index < numberOfElements; index++) {
            cout << "Enter element " << index + 1 << ": ";
            cin >> pointerArray[index];
        }

        int largestElement = pointerArray[0];
        for(int index = 1; index < numberOfElements; index++) {
            if(pointerArray[index] > largestElement) {
                largestElement = pointerArray[index];
            }
        }

        cout << "Largest element: " << largestElement << "\n";

        free(pointerArray);
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
