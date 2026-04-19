// Snippet by: Atharv Kulkarni
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
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;
class Solution
{
public:
    int evaluatePostfix(string &expression)
    {
        stack<int> st;
        for (char ch : expression)
        {
            if (isdigit(ch))
            {
                st.push(ch - '0');
            }
            else
            {
                if (st.size() < 2)
                {
                    cout << "wrong expression" << endl;
                    return 0;
                }
                int val2 = st.top();
                st.pop();
                int val1 = st.top();
                st.pop();

                switch (ch)
                {
                case '+':
                    st.push(val1 + val2);
                    break;
                case '-':
                    st.push(val1 - val2);
                    break;
                case '*':
                    st.push(val1 * val2);
                    break;
                case '/':
                    if (val2 == 0)
                    {
                        cout << "div by 0 wrong" << endl;
                        return 0;
                    }
                    st.push(val1 / val2);
                    break;
                case '%':
                    if (val2 == 0)
                    {
                        cout << "modulo div give error" << endl;
                        return 0;
                    }
                    st.push(val1 % val2);
                    break;
                }
            }
        }
        if (st.size() != 1)
        {
            cout << "Invalid Expression" << endl;
            return -1;
        }
        return st.top();
    }
};

int main()
{
    Solution obj;
    string exp;
    cout << "enter postfix exp ";
    cin >> exp;
    int result = obj.evaluatePostfix(exp);
    if (result != -1)
        cout << "result: " << result << endl;

    return 0;
}
