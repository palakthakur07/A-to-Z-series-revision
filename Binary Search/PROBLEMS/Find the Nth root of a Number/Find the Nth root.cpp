#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // Check 1, 2, 3, ... in order, computing i^n incrementally (with early
    // exit on overflow past m). Stop at an exact match, or once exceeded.
    // Time: O(M * N)  |  Space: O(1)
private:
    int checkPowerBrute(long long base, int n, long long m) {
        long long ans = 1;
        for (int i = 1; i <= n; i++) {
            ans *= base;
            if (ans > m) {
                return 2; // exceeded, no need to keep multiplying
            }
        }
        if (ans == m) return 1;
        return 0;
    }

public:
    int nthRootBrute(int n, int m) {
        for (long long i = 1; i <= m; i++) {
            int result = checkPowerBrute(i, n, m);
            if (result == 1) {
                return (int)i;
            } else if (result == 2) {
                break; // everything larger will also exceed m
            }
        }
        return -1;
    }

    //================ OPTIMAL (BINARY SEARCH ON ANSWERS) ================//
    // Binary search over [1, m]. The check function is overflow-safe,
    // multiplying incrementally and exiting early once it exceeds m.
    // Time: O(N log M)  |  Space: O(1)
private:
    int check(long long mid, int n, long long m) {
        long long ans = 1;
        for (int i = 1; i <= n; i++) {
            ans *= mid;
            if (ans > m) {
                return 2; // too large
            }
        }
        if (ans == m) return 1; // exact match
        return 0;               // too small
    }

public:
    int nthRoot(int n, int m) {
        long long low = 1, high = m;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            int result = check(mid, n, m);

            if (result == 1) {
                return (int)mid;
            } else if (result == 0) {
                low = mid + 1; // too small, search right
            } else {
                high = mid - 1; // too large, search left
            }
        }

        return -1;
    }
};