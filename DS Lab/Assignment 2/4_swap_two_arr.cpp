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
Question: Swap two integer arrays using pointers.
Time Complexity: O(N)
Space Complexity: O(1)
*/

class Solution
{
public:
    void solve()
    {
        int numberOfElements;
        cout << "Enter size of arrays: ";
        cin >> numberOfElements;

        // allocate memory for both arrays
        int *pointerArrayOne = (int *)malloc(numberOfElements * sizeof(int));
        int *pointerArrayTwo = (int *)malloc(numberOfElements * sizeof(int));

        cout << "Enter elements for first array:\n";
        for (int index = 0; index < numberOfElements; index++)
        {
            cin >> pointerArrayOne[index];
        }

        cout << "Enter elements for second array:\n";
        for (int index = 0; index < numberOfElements; index++)
        {
            cin >> pointerArrayTwo[index];
        }

        for (int index = 0; index < numberOfElements; index++)
        {
            int tempValue = *(pointerArrayOne + index);
            *(pointerArrayOne + index) = *(pointerArrayTwo + index);
            *(pointerArrayTwo + index) = tempValue;
        }

        cout << "First array after swap: ";
        for (int index = 0; index < numberOfElements; index++)
        {
            cout << pointerArrayOne[index] << " ";
        }
        cout << "\nSecond array after swap: ";
        for (int index = 0; index < numberOfElements; index++)
        {
            cout << pointerArrayTwo[index] << " ";
        }
        cout << "\n";

        free(pointerArrayOne);
        free(pointerArrayTwo);
    }
};

int main()
{
    Solution atharv;
    atharv.solve();
    return 0;
}
