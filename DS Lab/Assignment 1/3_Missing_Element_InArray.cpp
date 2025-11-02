#include <iostream>
#include <vector>
using namespace std;

int missingNum(vector<int> &arr)
{
    int n = arr.size() + 1;

    // Iterate from 1 to n and check
    // if the current number is present
    for (int i = 1; i <= n; i++)
    {
        bool found = false;
        for (int j = 0; j < n - 1; j++)
        {
            if (arr[j] == i)
            {
                found = true;
                break;
            }
        }

        // If the current number is not present
        if (!found)
            return i;
    }
    return -1;
}

int main()
{
    vector<int> arr = {1, 8, 6, 7, 5, 3, 2};
    cout << missingNum(arr) << endl;
    return 0;
}