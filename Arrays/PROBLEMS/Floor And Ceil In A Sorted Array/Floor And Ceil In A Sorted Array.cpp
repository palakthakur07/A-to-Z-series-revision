#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // Single traversal: track the largest value <= x for floor, and the
    // first (smallest) value >= x for ceil.
    // Time: O(N)  |  Space: O(1)
    pair<int, int> getFloorAndCeilBrute(vector<int>& arr, int x) {
        int n = arr.size();
        int floorVal = -1, ceilVal = -1;

        for (int i = 0; i < n; i++) {
            if (arr[i] <= x) {
                floorVal = arr[i]; // later valid values overwrite earlier ones
            }
            if (arr[i] >= x && ceilVal == -1) {
                ceilVal = arr[i]; // first such value is the smallest
            }
        }

        return {floorVal, ceilVal};
    }

    //================ OPTIMAL (BINARY SEARCH) ================//
    // Ceil: identical to Lower Bound, returning the value instead of index.
    // Floor: mirrored version, moving right after a valid candidate.
    // Time: O(log N) each  |  Space: O(1)
private:
    int findCeil(vector<int>& arr, int x) {
        int n = arr.size();
        int low = 0, high = n - 1;
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] >= x) {
                ans = arr[mid]; // possible answer, look for something smaller
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }

    int findFloor(vector<int>& arr, int x) {
        int n = arr.size();
        int low = 0, high = n - 1;
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] <= x) {
                ans = arr[mid]; // possible answer, look for something bigger
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }

public:
    pair<int, int> getFloorAndCeil(vector<int>& arr, int x) {
        int floorVal = findFloor(arr, x);
        int ceilVal = findCeil(arr, x);
        return {floorVal, ceilVal};
    }
};