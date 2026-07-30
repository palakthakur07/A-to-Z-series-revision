#include <bits/stdc++.h>
using namespace std;

void leftRotate(vector<int> &arr, int d)
{
    int n = arr.size();

    d = d % n;

    vector<int> temp;

    for (int i = 0; i < d; i++)
    {
        temp.push_back(arr[i]);
    }

    for (int i = d; i < n; i++)
    {
        arr[i - d] = arr[i];
    }

    for (int i = n - d; i < n; i++)
    {
        arr[i] = temp[i - (n - d)];
    }
}

int main()
{
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};

    leftRotate(arr, 2);

    for (int x : arr)
        cout << x << " ";

    return 0;
}