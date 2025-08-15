#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    void method1()
    {
        // Ask user for number of elements present in the array
        cout << "Enter number of elements (n): ";
        int n;
        cin >> n;

        // Create a vector to store the array elements
        vector<int> arr(n);

        // Input the elements from user
        cout << "Enter the elements: ";
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        // Total number of elements should be n+1 since one is missing
        int totalCount = n + 1;

        // Calculate sum of numbers from 1 to n+1 using formula
        int expectedSum = totalCount * (totalCount + 1) / 2;

        // Calculate actual sum of the given elements
        int actualSum = 0;
        for (int val : arr)
            actualSum += val;

        // Missing element = expected sum - actual sum
        cout << "Missing element is: " << expectedSum - actualSum << endl;
    }

    void solve()
    {
        method1();
    }
};

int main()
{
    // Create object of Solution class
    Solution obj;

    // Call the solve method
    obj.solve();

    return 0;
}
