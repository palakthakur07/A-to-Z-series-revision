/*
    Problem: Longest Subarray with Given Sum K
    (Array can contain positive, negative and zero)

    Approaches:
    1. Brute Force
    2. Optimal (Prefix Sum + Hash Map)
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// ==================== BRUTE FORCE ====================

int longestSubarrayBrute(vector<int>& arr, int k)
{
    int n = arr.size();
    int maxLen = 0;

    for(int i = 0; i < n; i++)
    {
        int sum = 0;

        for(int j = i; j < n; j++)
        {
            sum += arr[j];

            if(sum == k)
            {
                maxLen = max(maxLen, j - i + 1);
            }
        }
    }

    return maxLen;
}

// Time Complexity : O(N²)
// Space Complexity: O(1)


// ==================== OPTIMAL ====================

int longestSubarrayOptimal(vector<int>& arr, int k)
{
    unordered_map<int, int> prefixMap;

    int prefixSum = 0;
    int maxLen = 0;

    for(int i = 0; i < arr.size(); i++)
    {
        prefixSum += arr[i];

        if(prefixSum == k)
            maxLen = i + 1;

        int remaining = prefixSum - k;

        if(prefixMap.find(remaining) != prefixMap.end())
        {
            maxLen = max(maxLen, i - prefixMap[remaining]);
        }

        if(prefixMap.find(prefixSum) == prefixMap.end())
        {
            prefixMap[prefixSum] = i;
        }
    }

    return maxLen;
}

// Time Complexity : O(N)
// Space Complexity: O(N)


// ==================== DRIVER CODE ====================

int main()
{
    vector<int> arr = {1, 2, 3, 1, 1, 1, -1, 4, 2, -3};
    int k = 3;

    cout << "Brute Force Answer : "
         << longestSubarrayBrute(arr, k) << endl;

    cout << "Optimal Answer     : "
         << longestSubarrayOptimal(arr, k) << endl;

    return 0;
}