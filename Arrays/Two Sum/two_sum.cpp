/*
    Problem: Two Sum

    Approaches:
    1. Brute Force
    2. Better (Hash Map)
    3. Optimal (Two Pointers after Sorting)

    Note:
    - Hash Map returns original indices.
    - Two Pointer approach only tells whether a pair exists.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// ==================== BRUTE FORCE ====================

bool twoSumBrute(vector<int>& arr, int target)
{
    int n = arr.size();

    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(arr[i] + arr[j] == target)
            {
                return true;
            }
        }
    }

    return false;
}

// Time Complexity : O(N²)
// Space Complexity: O(1)


// ==================== BETTER (HASH MAP) ====================

bool twoSumBetter(vector<int>& arr, int target)
{
    unordered_map<int, int> mp;

    for(int i = 0; i < arr.size(); i++)
    {
        int remaining = target - arr[i];

        if(mp.find(remaining) != mp.end())
        {
            return true;
        }

        mp[arr[i]] = i;
    }

    return false;
}

// Time Complexity : O(N)
// Space Complexity: O(N)


// ==================== OPTIMAL (TWO POINTER) ====================

bool twoSumOptimal(vector<int> arr, int target)
{
    sort(arr.begin(), arr.end());

    int left = 0;
    int right = arr.size() - 1;

    while(left < right)
    {
        int sum = arr[left] + arr[right];

        if(sum == target)
        {
            return true;
        }
        else if(sum < target)
        {
            left++;
        }
        else
        {
            right--;
        }
    }

    return false;
}

// Time Complexity : O(N log N)
// Space Complexity: O(1)


// ==================== DRIVER CODE ====================

int main()
{
    vector<int> arr = {2, 6, 5, 8, 11};
    int target = 14;

    cout << "Brute Force : "
         << (twoSumBrute(arr, target) ? "YES" : "NO") << endl;

    cout << "Better      : "
         << (twoSumBetter(arr, target) ? "YES" : "NO") << endl;

    cout << "Optimal     : "
         << (twoSumOptimal(arr, target) ? "YES" : "NO") << endl;

    return 0;
}