#include <bits/stdc++.h>
using namespace std;

int missingNumber(vector<int> &arr, int N)
{
    int xor1 = 0;
    int xor2 = 0;

    for (int i = 1; i <= N; i++)
    {
        xor1 ^= i;
    }

    for (int i = 0; i < N - 1; i++)
    {
        xor2 ^= arr[i];
    }

    return xor1 ^ xor2;
}

int main()
{
    vector<int> arr = {1, 2, 4, 5};

    int N = 5;

    cout << "Missing Number = " << missingNumber(arr, N);

    return 0;
}