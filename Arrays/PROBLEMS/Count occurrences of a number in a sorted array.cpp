#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ OPTIMAL ================//
    // Reuses the first/last occurrence binary search functions.
    // Since the array is sorted, all occurrences of x are contiguous,
    // so count = last - first + 1.
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
                low = mid + 1;
            } else {
                high = mid - 1;
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
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return last;
    }

    pair<int, int> searchFirstAndLast(vector<int>& arr, int n, int x) {
        int first = findFirst(arr, n, x);

        if (first == -1) {
            return {-1, -1};
        }

        int last = findLast(arr, n, x);
        return {first, last};
    }

    int countOccurrences(vector<int>& arr, int n, int x) {
        pair<int, int> ans = searchFirstAndLast(arr, n, x);

        if (ans.first == -1) {
            // element does not exist
            return 0;
        }

        return ans.second - ans.first + 1;
    }
};