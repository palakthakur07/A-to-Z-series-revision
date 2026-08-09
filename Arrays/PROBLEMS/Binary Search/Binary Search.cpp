#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE (LINEAR SEARCH) ================//
    // Check every element one by one until the target is found.
    // Time: O(N)  |  Space: O(1)
    int linearSearch(vector<int>& array, int target) {
        int n = array.size();

        for (int i = 0; i < n; i++) {
            if (array[i] == target) {
                return i;
            }
        }

        return -1;
    }

    //================ OPTIMAL (ITERATIVE BINARY SEARCH) ================//
    // Maintain low/high pointers over the search space, halving it each
    // step based on comparing the target against the middle element.
    // Time: O(log N)  |  Space: O(1)
    int binarySearchIterative(vector<int>& array, int target) {
        int n = array.size();
        int low = 0, high = n - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2; // overflow-safe mid

            if (array[mid] == target) {
                return mid;
            } else if (array[mid] < target) {
                low = mid + 1; // target lies on the right
            } else {
                high = mid - 1; // target lies on the left
            }
        }

        return -1;
    }

    //================ OPTIMAL (RECURSIVE BINARY SEARCH) ================//
    // Same halving logic as the iterative version, implemented via
    // recursive calls on a shrinking search space.
    // Time: O(log N)  |  Space: O(log N) (recursion call stack)
private:
    int binarySearchHelper(vector<int>& array, int low, int high, int target) {
        if (low > high) {
            return -1; // search space exhausted
        }

        int mid = low + (high - low) / 2; // overflow-safe mid

        if (array[mid] == target) {
            return mid;
        } else if (array[mid] < target) {
            return binarySearchHelper(array, mid + 1, high, target); // search right
        } else {
            return binarySearchHelper(array, low, mid - 1, target); // search left
        }
    }

public:
    int binarySearchRecursive(vector<int>& array, int target) {
        int n = array.size();
        return binarySearchHelper(array, 0, n - 1, target);
    }
};