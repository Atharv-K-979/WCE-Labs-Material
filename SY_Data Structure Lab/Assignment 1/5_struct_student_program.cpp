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
Question:
Read students details into struct student array and sort the array based on student id.
struct student {
    char name[50];
    int id;
};
Write: struct student* solution(int N) that reads N students, sorts ascending by id and returns pointer.

Time Complexity:
O(N log N)

Space Complexity:
O(N)
*/

struct student {
    char name[50];
    int id;
};

class Solution {
public:
    struct student* solution(int N) {
        struct student* arr = new struct student[N];
        for (int i = 0; i < N; i++) {
            cout << "Enter name of student " << i + 1 << ": ";
            cin >> ws;
            cin.getline(arr[i].name, 50);
            cout << "Enter ID of student " << i + 1 << ": ";
            cin >> arr[i].id;
        }
        sort(arr, arr + N, [](const student &a, const student &b){
            return a.id < b.id;
        });
        return arr;
    }

    void solve() {
        int N; 
        cout << "Enter number of students: ";
        cin >> N;
        struct student* res = solution(N);
        cout << "\nStudents sorted by ID:\n";
        for (int i = 0; i < N; i++) {
            cout << res[i].name << " " << res[i].id << endl;
        }
        delete[] res;
    }
};

int main() {
    Solution atharv;
    atharv.solve();
    return 0;
}
