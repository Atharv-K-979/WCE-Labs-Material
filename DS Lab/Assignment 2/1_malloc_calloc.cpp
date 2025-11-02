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
Question 1: Create memory for int, char, float using malloc and free it after use.
Question 2: Do the same task using calloc and free it after use.

Time Complexity: O(1)
Space Complexity: O(1)
*/

class Solution {
public:
    // Using malloc
    void solve() {
        int *pointerInteger = (int*) malloc(sizeof(int));
        char *pointerCharacter = (char*) malloc(sizeof(char));
        float *pointerFloat = (float*) malloc(sizeof(float));

        cout << "Using malloc:\n";
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

        // Free allocated memory
        free(pointerInteger);
        free(pointerCharacter);
        free(pointerFloat);
    }

    // Using calloc
    void solve2() {
        int *pointerInteger = (int*) calloc(1, sizeof(int));
        char *pointerCharacter = (char*) calloc(1, sizeof(char));
        float *pointerFloat = (float*) calloc(1, sizeof(float));

        cout << "\nUsing calloc:\n";
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

        // Free allocated memory
        free(pointerInteger);
        free(pointerCharacter);
        free(pointerFloat);
    }
};

int main() {
    Solution atharv;
    atharv.solve();   // malloc version
    atharv.solve2();  // calloc version
    return 0;
}


// malloc allocates the single block calloc allocates multiple blocks
// one argument and 2 arguments size and no of blocks
// while initialization malloc uses garbage and for calloc it uses zero at first
