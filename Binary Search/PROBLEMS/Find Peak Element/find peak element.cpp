#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // Check every index against its existing neighbor(s), treating a
    // missing neighbor at the boundaries as -infinity.
    // Time: O(N)  |  Space: O(1)
    int findPeakElementBrute(vector<int>& arr) {
        int n = arr.size();

        for (int i = 0; i < n; i++) {
            bool leftOk = (i == 0) || (arr[i - 1] < arr[i]);
            bool rightOk = (i == n - 1) || (arr[i] > arr[i + 1]);

            if (leftOk && rightOk) {
                return arr[i];
            }
        }

        return -1; // unreachable, since a peak is guaranteed to exist
    }

    //================ OPTIMAL (BINARY SEARCH) ================//
    // Handle single-element, first, and last cases separately, then binary
    // search over [1, n-2]: increasing curve -> peak on the right,
    // decreasing curve -> peak on the left, valley -> either side works.
    // Time: O(log N)  |  Space: O(1)
    int findPeakElement(vector<int>& arr) {
        int n = arr.size();

        if (n == 1) {
            return arr[0];
        }
        if (arr[0] > arr[1]) {
            return arr[0];
        }
        if (arr[n - 1] > arr[n - 2]) {
            return arr[n - 1];
        }

        int low = 1, high = n - 2;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
                return arr[mid]; // found a peak
            } else if (arr[mid] > arr[mid - 1]) {
                // increasing curve, peak lies to the right
                low = mid + 1;
            } else if (arr[mid] > arr[mid + 1]) {
                // decreasing curve, peak lies to the left
                high = mid - 1;
            } else {
                // valley: both sides guaranteed to have a peak, go either way
                low = mid + 1;
            }
        }

        return -1; // unreachable, since a peak is guaranteed to exist
    }
};