#include <bits/stdc++.h>
using namespace std;

//--------------------------------------------------
// Brute Force
//--------------------------------------------------

void moveZeroesBrute(vector<int> &arr)
{
    int n = arr.size();

    vector<int> temp;

    // Store all non-zero elements
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != 0)
            temp.push_back(arr[i]);
    }

    // Copy back to original array
    for (int i = 0; i < temp.size(); i++)
    {
        arr[i] = temp[i];
    }

    // Fill remaining positions with zeroes
    for (int i = temp.size(); i < n; i++)
    {
        arr[i] = 0;
    }
}

//--------------------------------------------------
// Optimal (Two Pointers)
//--------------------------------------------------

void moveZeroesOptimal(vector<int> &arr)
{
    int n = arr.size();

    int j = -1;

    // Find first zero
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0)
        {
            j = i;
            break;
        }
    }

    // No zero present
    if (j == -1)
        return;

    // Swap non-zero elements with zero
    for (int i = j + 1; i < n; i++)
    {
        if (arr[i] != 0)
        {
            swap(arr[i], arr[j]);
            j++;
        }
    }
}

//--------------------------------------------------
// Driver Code
//--------------------------------------------------

int main()
{
    vector<int> arr = {1, 0, 2, 3, 0, 4, 0, 1};

    // moveZeroesBrute(arr);
    moveZeroesOptimal(arr);

    cout << "Output Array : ";

    for (int num : arr)
    {
        cout << num << " ";
    }

    return 0;
}