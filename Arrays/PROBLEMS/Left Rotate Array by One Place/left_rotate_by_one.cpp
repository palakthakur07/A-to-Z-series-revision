#include <bits/stdc++.h>
using namespace std;

void leftRotate(vector<int> &arr, int n)
{
    int temp = arr[0];

    for(int i = 1; i < n; i++)
    {
        arr[i - 1] = arr[i];
    }

    arr[n - 1] = temp;
}

int main()
{
    vector<int> arr = {1, 2, 3, 4, 5};

    leftRotate(arr, arr.size());

    cout << "Array after left rotation: ";

    for(int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}