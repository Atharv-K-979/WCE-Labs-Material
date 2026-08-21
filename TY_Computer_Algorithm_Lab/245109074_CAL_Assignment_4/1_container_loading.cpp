#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int containerLoading(vector<int> weights, int capacity)
{
    sort(weights.begin(), weights.end());
    int total = 0, count = 0;
    for (int w : weights)
    {
        if (total + w <= capacity)
        {
            total += w;
            count++;
        }
        else
            break;
    }
    return count;
}
int main()
{
    vector<int> test1 = {22, 18, 40, 15, 60, 33, 27, 50, 12, 45};
    vector<int> test2 = {22, 18, 40, 15, 60, 33, 27, 50, 12, 45, 38, 29, 55, 19, 42, 31, 24, 48, 36, 20, 58, 16, 47, 25, 34, 41, 13, 52, 28, 37};
    vector<int> test3 = {5, 10, 15, 20, 25, 30};
    vector<int> test4 = {1, 2, 3};
    vector<int> test5 = {100, 100, 100, 100};
    cout << "test case 1: bags loaded is " << containerLoading(test1, 100) << endl;
    cout << "test case 2: bags loaded is " << containerLoading(test2, 3000) << endl;
    cout << "test case 3: bags loaded is " << containerLoading(test3, 50) << endl;
    cout << "test case 4: bags loaded is " << containerLoading(test4, 0) << endl;
    cout << "test case 5: bags loaded is " << containerLoading(test5, 200) << endl;
    return 0;
}

// Container Loading
// O(n log n)
// O(n log n)
// O(n log n)