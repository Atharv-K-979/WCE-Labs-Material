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
Question: Find largest element in array using recursion.
Time Complexity: O(N)
Space Complexity: O(N)
*/

class Solution {
public:
    int findLargestRecursive(int arrayValues[], int currentIndex, int numberOfElements) {
        // base case
        if(currentIndex == numberOfElements - 1) {
            return arrayValues[currentIndex];
        }
        // find max from rest of array
        int largestInRest = findLargestRecursive(arrayValues, currentIndex + 1, numberOfElements);
        // return max between current and rest
        return max(arrayValues[currentIndex], largestInRest);
    }

    void solve() {
        int numberOfElements;
        cout << "Enter number of elements: ";
        cin >> numberOfElements;

        int *arrayValues = new int[numberOfElements];
        for(int index = 0; index < numberOfElements; index++) {
            cin >> arrayValues[index];
        }

        int largestValue = findLargestRecursive(arrayValues, 0, numberOfElements);
        cout << "Largest element: " << largestValue << "\n";

        delete[] arrayValues;
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
