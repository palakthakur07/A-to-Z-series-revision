#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ OPTIMAL (REUSING FIRST AND LAST OCCURRENCE) ================//
    // Count = last occurrence - first occurrence + 1, since all occurrences
    // of x are contiguous in a sorted array. Returns 0 if x doesn't exist.
    // Time: O(2 log N)  |  Space: O(1)
private:
    int firstOccurrence(vector<int>& arr, int x) {
        int n = arr.size();
        int low = 0, high = n - 1;
        int first = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == x) {
                first = mid;
                high = mid - 1;
            } else if (arr[mid] < x) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return first;
    }

    int lastOccurrence(vector<int>& arr, int x) {
        int n = arr.size();
        int low = 0, high = n - 1;
        int last = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == x) {
                last = mid;
                low = mid + 1;
            } else if (arr[mid] < x) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return last;
    }

public:
    int countOccurrences(vector<int>& arr, int x) {
        int first = firstOccurrence(arr, x);

        if (first == -1) {
            return 0; // x does not exist in the array
        }

        int last = lastOccurrence(arr, x);
        return last - first + 1;
    }
};