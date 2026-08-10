#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // Linear scan: track first and last index where arr[i] == X
    // Time: O(N) | Space: O(1)
    pair<int, int> searchFirstAndLastBrute(vector<int>& arr, int n, int x) {
        int first = -1, last = -1;

        for (int i = 0; i < n; i++) {
            if (arr[i] == x) {
                if (first == -1) {
                    first = i; // first time we found x
                }
                last = i; // keep updating till the last matching index
            }
        }

        return {first, last};
    }

    //================ BETTER ================//
    // Uses Lower Bound and Upper Bound (from previous binary search lectures)
    // Time: O(2 * log N) | Space: O(1)
    int lowerBound(vector<int>& arr, int n, int x) {
        int low = 0, high = n - 1;
        int ans = n; // if no element is >= x, answer is n (hypothetical index)

        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] >= x) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }

    int upperBound(vector<int>& arr, int n, int x) {
        int low = 0, high = n - 1;
        int ans = n; // if no element is > x, answer is n (hypothetical index)

        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] > x) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }

    pair<int, int> searchFirstAndLastBetter(vector<int>& arr, int n, int x) {
        int lb = lowerBound(arr, n, x);

        // element does not exist in the array
        if (lb == n || arr[lb] != x) {
            return {-1, -1};
        }

        int first = lb;
        int last = upperBound(arr, n, x) - 1;

        return {first, last};
    }

    //================ OPTIMAL ================//
    // Plain binary search written from scratch for first and last occurrence
    // (no reliance on lower bound / upper bound helper functions)
    // Time: O(2 * log N) | Space: O(1)
    int findFirst(vector<int>& arr, int n, int x) {
        int low = 0, high = n - 1;
        int first = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == x) {
                first = mid;
                high = mid - 1; // look further left for an earlier occurrence
            } else if (arr[mid] < x) {
                low = mid + 1; // go right
            } else {
                high = mid - 1; // go left
            }
        }

        return first;
    }

    int findLast(vector<int>& arr, int n, int x) {
        int low = 0, high = n - 1;
        int last = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == x) {
                last = mid;
                low = mid + 1; // look further right for a later occurrence
            } else if (arr[mid] < x) {
                low = mid + 1; // go right
            } else {
                high = mid - 1; // go left
            }
        }

        return last;
    }

    pair<int, int> searchFirstAndLastOptimal(vector<int>& arr, int n, int x) {
        int first = findFirst(arr, n, x);

        // if first occurrence doesn't exist, last cannot exist either,
        // so avoid wasting another O(log N) search
        if (first == -1) {
            return {-1, -1};
        }

        int last = findLast(arr, n, x);

        return {first, last};
    }
};