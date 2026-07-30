#include <bits/stdc++.h>
using namespace std;

int linearSearch(vector<int> &arr, int n, int target)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }

    return -1;
}

int main()
{
    vector<int> arr = {6, 7, 8, 4, 1};
    int target = 4;

    int index = linearSearch(arr, arr.size(), target);

    if (index != -1)
        cout << "Element found at index: " << index;
    else
        cout << "Element not found";

    return 0;
}