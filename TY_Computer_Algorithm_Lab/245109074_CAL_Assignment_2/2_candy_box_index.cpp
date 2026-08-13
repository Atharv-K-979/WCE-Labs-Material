#include <iostream>
using namespace std;
long long candyBox(long long n, long long k)
{
    long long len = (n == 1) ? 1 : 2 * (n - 1);
    long long r = (k - 1) % len;
    return (r < n) ? r + 1 : 2 * n - r - 1;
}
int main()
{
    long long n[] = {3, 5, 1, 4, 4};
    long long k[] = {7, 6, 100, 1, 10};
    for (int i = 0; i < 5; i++)
        cout << "test case " << i + 1 << ": kth candy is in box number " << candyBox(n[i], k[i]) << endl;
    return 0;
}
