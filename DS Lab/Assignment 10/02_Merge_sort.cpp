#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>
#include <map>
#include <set>
#include <limits.h>
using namespace std;

void merge(int *arr, int s, int e)
{
    int mid = s + (e - s) / 2;
    int len1 = mid - s + 1;
    int len2 = e - mid;   
    int *left = new int[len1];  
    int *right = new int[len2]; 

    int k = s;
    for (int i = 0; i < len1; i++)
    {
        left[i] = arr[k++];
    }
    k = mid + 1;
    for (int i = 0; i < len2; i++)
    {
        right[i] = arr[k++];
    }
    int leftIdx = 0;
    int rightIdx = 0;
    int mainArrayIdx = s;

    while (leftIdx < len1 && rightIdx < len2)
    {
        if (left[leftIdx] < right[rightIdx])
        {
            arr[mainArrayIdx++] = left[leftIdx++];
        }
        else
        {
            arr[mainArrayIdx++] = right[rightIdx++];
        }

    }
    while (leftIdx < len1)
    {
        arr[mainArrayIdx++] = left[leftIdx++];
    }

    while (rightIdx < len2)
    {
        arr[mainArrayIdx++] = right[rightIdx++];
    }
    delete[] left;
    delete[] right;
}
void mergeSort(int arr[], int s, int e)
{
    if (s >= e)
        return;
    int mid = s + (e - s) / 2;
    // Recursively sort the left half
    mergeSort(arr, s, mid);
    // Recursively sort the right half
    mergeSort(arr, mid + 1, e);
    // Merge the sorted halves
    merge(arr, s, e);
}

int main()
{
    int arr[] = {4, 5, 2, 2, 12, 19};
    int n = 6;

    cout << "Original Array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    mergeSort(arr, 0, n - 1);

    cout << "Sorted Array:   ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}