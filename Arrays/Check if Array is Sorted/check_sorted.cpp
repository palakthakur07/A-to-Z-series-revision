#include <bits/stdc++.h>
using namespace std;

bool isSorted(vector<int> &arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    vector<int> arr = {1, 2, 2, 3, 4, 5};

    if (isSorted(arr, arr.size()))
        cout << "Array is Sorted";
    else
        cout << "Array is Not Sorted";

    return 0;
}