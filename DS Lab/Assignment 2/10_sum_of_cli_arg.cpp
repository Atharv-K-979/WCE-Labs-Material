#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
using namespace std;

/*
Question: Find sum of all command line arguments.
Time Complexity: O(N)
Space Complexity: O(1)
g++ sum_of_cli_arg.cpp -o sum
*/

class Solution
{
public:
    void solve(int argc, char *argv[])
    {
        int sum = 0;

        // loop through arguments starting from index 1
        for (int i = 1; i < argc; i++)
        {
            sum += atoi(argv[i]); // convert string to int
        }

        // display result
        cout << "Sum of command line arguments: " << sum << "\n";
    }
};

int main(int argc, char *argv[])
{
    Solution atharv;
    atharv.solve(argc, argv);
    return 0;
}
