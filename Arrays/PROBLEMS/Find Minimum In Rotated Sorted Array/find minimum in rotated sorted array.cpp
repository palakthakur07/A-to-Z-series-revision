#include <bits/stdc++.h>
using namespace std;

/*
    Find Minimum in Rotated Sorted Array
    Based on the provided transcript.

    Example:
    [4, 5, 6, 7, 0, 1, 2] -> 0
    [3, 4, 5, 1, 2]       -> 1

    Assumption:
    - All elements are unique.
*/

// ------------------------------------------------------------
// 1. BRUTE FORCE
// Time:  O(n)
// Space: O(1)
// ------------------------------------------------------------
int findMinBrute(vector<int>& nums) {
    int ans = INT_MAX;

    for (int x : nums) {
        ans = min(ans, x);
    }

    return ans;
}

// ------------------------------------------------------------
// 2. OPTIMAL - Binary Search
// Time:  O(log n)
// Space: O(1)
// ------------------------------------------------------------
int findMin(vector<int>& nums) {
    int low = 0;
    int high = nums.size() - 1;
    int ans = INT_MAX;

    while (low <= high) {

        // Optimization:
        // If the current search space is already sorted,
        // its first element is the minimum of this search space.
        if (nums[low] <= nums[high]) {
            ans = min(ans, nums[low]);
            break;
        }

        int mid = low + (high - low) / 2;

        // Left half is sorted.
        if (nums[low] <= nums[mid]) {
            // Since the left half is sorted, nums[low]
            // is its minimum.
            ans = min(ans, nums[low]);

            // Eliminate the left half.
            low = mid + 1;
        }
        // Otherwise, the right half is sorted.
        else {
            // Since the right half is sorted, nums[mid]
            // is its minimum.
            ans = min(ans, nums[mid]);

            // Eliminate the right half.
            high = mid - 1;
        }
    }

    return ans;
}

int main() {
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};

    cout << "Brute Force: " << findMinBrute(nums) << '\n';
    cout << "Optimal:     " << findMin(nums) << '\n';

    return 0;
}