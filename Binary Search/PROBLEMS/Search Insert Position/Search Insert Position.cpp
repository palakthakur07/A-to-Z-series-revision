#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // Scan from left to right, returning the first index where the value
    // is greater than or equal to target.
    // Time: O(N)  |  Space: O(1)
    int searchInsertBrute(vector<int>& arr, int target) {
        int n = arr.size();

        for (int i = 0; i < n; i++) {
            if (arr[i] >= target) {
                return i;
            }
        }

        return n;
    }

    //================ OPTIMAL (BINARY SEARCH - LOWER BOUND) ================//
    // Identical to the Lower Bound template: track the smallest valid index
    // in `ans`, moving left after a valid candidate to search for smaller.
    // Time: O(log N)  |  Space: O(1)
    int searchInsert(vector<int>& arr, int target) {
        int n = arr.size();
        int low = 0, high = n - 1;
        int ans = n;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] >= target) {
                ans = mid;      // possible answer, look for a smaller one
                high = mid - 1;
            } else {
                low = mid + 1;  // not possible, search the right half
            }
        }

        return ans;
    }
};