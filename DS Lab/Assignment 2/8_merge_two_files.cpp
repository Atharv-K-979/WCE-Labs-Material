#include <bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/*
Question: Merge two files alternatively line by line after first writing exactly 4 lines to each file.
Time Complexity: O(N)
Space Complexity: O(1)
*/

class Solution {
public:
    void solve() {
 
        ofstream firstFile("file1.txt");
        firstFile << "Apple\n";
        firstFile << "Banana\n";
        firstFile << "Cherry\n";
        firstFile << "Date\n";
        firstFile.close();

        ofstream secondFile("file2.txt");
        secondFile << "Ant\n";
        secondFile << "Bat\n";
        secondFile << "Cat\n";
        secondFile << "Dog\n";
        secondFile.close();

        ifstream readFirst("file1.txt");
        ifstream readSecond("file2.txt");
     
        ofstream mergedFile("merged.txt");

        string line1, line2;

        while (getline(readFirst, line1) && getline(readSecond, line2)) {
            mergedFile << line1 << "\n";
            mergedFile << line2 << "\n";
        }
        // close all file streams
        readFirst.close();
        readSecond.close();
        mergedFile.close();

        cout << "Files merged successfully into merged.txt\n";
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
