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
Question: Create memory for int, char, float using malloc and free it after use.
Time Complexity: O(1)
Space Complexity: O(1)
*/

class Solution {
public:
    void solve() {
        int *pointerInteger = (int*) malloc(sizeof(int));
        char *pointerCharacter = (char*) malloc(sizeof(char));
        float *pointerFloat = (float*) malloc(sizeof(float));

        cout << "Enter an integer: ";
        cin >> *pointerInteger;
        cout << "Enter a character: ";
        cin >> *pointerCharacter;
        cout << "Enter a float: ";
        cin >> *pointerFloat;

        cout << "\nYou entered:\n";
        cout << "Integer: " << *pointerInteger << "\n";
        cout << "Character: " << *pointerCharacter << "\n";
        cout << "Float: " << *pointerFloat << "\n";

        free(pointerInteger);
        free(pointerCharacter);
        free(pointerFloat);
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
