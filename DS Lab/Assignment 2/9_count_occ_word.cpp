#include <bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;

/*
Question: Count occurrences of all words in a file.
Time Complexity: O(N)
Space Complexity: O(N)
*/

class Solution {
public:
    void solve() {
        // create file with some default content
        ofstream myFile("sample.txt");
        myFile << "apple banana apple cherry banana apple";
        myFile.close();

        // open file for reading
        ifstream readFile("sample.txt");

        map<string, int> wordCount;
        string word;

        // read each word and count frequency
        while (readFile >> word) {
            wordCount[word]++;
        }

        readFile.close();

        // display word counts
        cout << "Word occurrences:\n";
        for (auto &entry : wordCount) {
            cout << entry.first << " : " << entry.second << "\n";
        }
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
