/*
    Problem: Longest Subarray with Sum K (Positive Numbers)

    Approaches:
    1. Brute Force
    2. Optimal (Sliding Window)

    Time & Space Complexity included for each approach.
*/

#include <iostream>
#include <vector>
using namespace std;

// ==================== BRUTE FORCE ====================
int longestSubarrayBrute(vector<int>& arr, int k) {
    int n = arr.size();
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        int sum = 0;

        for (int j = i; j < n; j++) {
            sum += arr[j];

            if (sum == k) {
                maxLen = max(maxLen, j - i + 1);
            }
        }
    }

    return maxLen;
}

// Time Complexity : O(N²)
// Space Complexity: O(1)


// ==================== OPTIMAL (Sliding Window) ====================
int longestSubarrayOptimal(vector<int>& arr, int k) {
    int left = 0;
    int right = 0;
    int sum = arr[0];
    int maxLen = 0;
    int n = arr.size();

    while (right < n) {

        while (left <= right && sum > k) {
            sum -= arr[left];
            left++;
        }

        if (sum == k) {
            maxLen = max(maxLen, right - left + 1);
        }

        right++;

        if (right < n) {
            sum += arr[right];
        }
    }

    return maxLen;
}

// Time Complexity : O(N)
// Space Complexity: O(1)


// ==================== Driver Code ====================
int main() {

    vector<int> arr = {1, 2, 3, 1, 1, 1, 1, 4, 2, 3};
    int k = 3;

    cout << "Brute Force Answer : "
         << longestSubarrayBrute(arr, k) << endl;

    cout << "Optimal Answer     : "
         << longestSubarrayOptimal(arr, k) << endl;

    return 0;
}