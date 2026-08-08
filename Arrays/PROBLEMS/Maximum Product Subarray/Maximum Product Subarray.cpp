#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // Generate every subarray using i (start) and j (end), then compute its
    // product from scratch using a third loop, tracking the maximum.
    // Time: O(N^3)  |  Space: O(1)
    int maxProductBrute(vector<int>& arr) {
        int n = arr.size();
        int maximum = INT_MIN;

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int product = 1;
                for (int k = i; k <= j; k++) {
                    product *= arr[k];
                }
                maximum = max(maximum, product);
            }
        }

        return maximum;
    }

    //================ BETTER ================//
    // Same two loops (i, j), but drop the third loop by maintaining a
    // running product that gets updated incrementally as j moves forward.
    // Time: O(N^2)  |  Space: O(1)
    int maxProductBetter(vector<int>& arr) {
        int n = arr.size();
        int maximum = INT_MIN;

        for (int i = 0; i < n; i++) {
            int product = 1;
            for (int j = i; j < n; j++) {
                product *= arr[j];
                maximum = max(maximum, product);
            }
        }

        return maximum;
    }

    //================ OPTIMAL (PREFIX / SUFFIX OBSERVATION) ================//
    // Maintain a running prefix product (left to right) and suffix product
    // (right to left) in one pass. Reset either to 1 whenever it hits 0,
    // since the max-product subarray can never span across a zero.
    // Time: O(N)  |  Space: O(1)
    int maxProduct(vector<int>& arr) {
        int n = arr.size();
        int prefix = 1, suffix = 1;
        int maximum = INT_MIN;

        for (int i = 0; i < n; i++) {
            if (prefix == 0) {
                prefix = 1;
            }
            if (suffix == 0) {
                suffix = 1;
            }

            prefix *= arr[i];
            suffix *= arr[n - i - 1];

            maximum = max(maximum, max(prefix, suffix));
        }

        return maximum;
    }
};