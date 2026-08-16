#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // Check 1, 2, 3, ... in order, stopping as soon as a value's square
    // exceeds n. The last valid value checked is the answer.
    // Time: O(N)  |  Space: O(1)
    int floorSqrtBrute(long long n) {
        long long ans = 1;

        for (long long i = 1; i <= n; i++) {
            if (i * i <= n) {
                ans = i;
            } else {
                break;
            }
        }

        return (int)ans;
    }

    //================ OPTIMAL (BINARY SEARCH ON ANSWERS) ================//
    // Binary search over the range of candidate answers [1, n]. If
    // mid*mid <= n, mid is a possible answer, search right for bigger;
    // otherwise search left.
    // Time: O(log N)  |  Space: O(1)
    int floorSqrt(long long n) {
        long long low = 1, high = n;
        long long ans = 1;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (mid * mid <= n) {
                ans = mid;      // possible answer, look for a bigger one
                low = mid + 1;
            } else {
                high = mid - 1; // too large, search smaller values
            }
        }

        return (int)ans;
    }
};