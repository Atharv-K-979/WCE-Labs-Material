#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
struct Point
{
    double x;
    double y;
};
bool cmpX(Point a, Point b)
{
    return a.x < b.x;
}
bool cmpY(Point a, Point b)
{
    return a.y < b.y;
}
double dist(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double bruteForce(vector<Point> &pts, int left, int right)
{
    double minDist = 1e18;
    for (int i = left; i <= right; i++)
        for (int j = i + 1; j <= right; j++)
        {
            double d = dist(pts[i], pts[j]);
            if (d < minDist)
                minDist = d;
        }
    return minDist;
}
double stripClosest(vector<Point> strip, double d)
{
    double minDist = d;
    sort(strip.begin(), strip.end(), cmpY);
    for (int i = 0; i < (int)strip.size(); i++)
        for (int j = i + 1; j < (int)strip.size() && (strip[j].y - strip[i].y) < minDist; j++)
        {
            double dd = dist(strip[i], strip[j]);
            if (dd < minDist)
                minDist = dd;
        }
    return minDist;
}
double closestUtil(vector<Point> &pts, int left, int right)
{
    if (right - left <= 2)
        return bruteForce(pts, left, right);
    int mid = (left + right) / 2;
    double midX = pts[mid].x;
    double dl = closestUtil(pts, left, mid);
    double dr = closestUtil(pts, mid + 1, right);
    double d = (dl < dr) ? dl : dr;
    vector<Point> strip;
    for (int i = left; i <= right; i++)
        if (fabs(pts[i].x - midX) < d)
            strip.push_back(pts[i]);
    double stripD = stripClosest(strip, d);
    return (stripD < d) ? stripD : d;
}
double closestPair(vector<Point> pts)
{
    sort(pts.begin(), pts.end(), cmpX);
    return closestUtil(pts, 0, pts.size() - 1);
}
int main()
{
    vector<vector<Point>> tests = {
        {{0, 0}, {3, 4}, {1, 1}},
        {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}},
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
        {{0, 0}, {5, 5}, {10, 10}, {1, 1}},
        {{0, 0}, {0, 3}, {4, 0}, {4, 3}, {2, 1.5}}};
    for (int i = 0; i < (int)tests.size(); i++)
        cout << "test case " << i + 1 << ": minimum distance is " << closestPair(tests[i]) << endl;
    return 0;
}
