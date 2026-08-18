#include <bits/stdc++.h>
using namespace std;

/*
    LeetCode 875 - Koko Eating Bananas

    Approaches:
    1. Brute Force
    2. Linear Search + helper
    3. Optimal Binary Search on Answer

    Complexity:
    Brute/Linear: O(n * maxPile), O(1)
    Optimal:      O(n * log(maxPile)), O(1)
*/

// Returns total hours needed at speed k.
long long requiredHours(const vector<int>& piles, int k) {
    long long hours = 0;

    for (int pile : piles) {
        // ceil(pile / k), using integer arithmetic
        hours += (pile + k - 1) / k;
    }

    return hours;
}


// ============================================================
// 1. BRUTE FORCE
// ============================================================

/*
    Try every possible speed from 1 to maxPile.

    TC: O(n * maxPile)
    SC: O(1)
*/
int minEatingSpeedBrute(vector<int>& piles, int h) {
    int maxPile = *max_element(piles.begin(), piles.end());

    for (int k = 1; k <= maxPile; k++) {
        if (requiredHours(piles, k) <= h)
            return k;
    }

    return -1;
}


// ============================================================
// 2. LINEAR SEARCH + HELPER
// ============================================================

/*
    Same idea, explicitly treating [1, maxPile] as the answer range.

    TC: O(n * maxPile)
    SC: O(1)
*/
int minEatingSpeedLinear(vector<int>& piles, int h) {
    int low = 1;
    int high = *max_element(piles.begin(), piles.end());

    while (low <= high) {
        if (requiredHours(piles, low) <= h)
            return low;

        low++;
    }

    return -1;
}


// ============================================================
// 3. OPTIMAL — BINARY SEARCH ON ANSWER
// ============================================================

/*
    Feasibility pattern:

        speed:       1  2  3  4  5  6  ...
        possible:    F  F  F  T  T  T  ...

    We need the FIRST true value.

    If mid is possible:
        search left -> high = mid - 1

    If mid is impossible:
        search right -> low = mid + 1

    TC: O(n * log(maxPile))
    SC: O(1)
*/
int minEatingSpeedOptimal(vector<int>& piles, int h) {
    int low = 1;
    int high = *max_element(piles.begin(), piles.end());

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (requiredHours(piles, mid) <= h) {
            // mid works, but we want a smaller valid speed.
            high = mid - 1;
        } else {
            // mid is too slow.
            low = mid + 1;
        }
    }

    return low;
}


// ============================================================
// LEETCODE SUBMISSION
// ============================================================

class Solution {
public:
    long long requiredHours(vector<int>& piles, int k) {
        long long hours = 0;

        for (int pile : piles) {
            hours += (pile + k - 1) / k;
        }

        return hours;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1;
        int high = *max_element(piles.begin(), piles.end());

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (requiredHours(piles, mid) <= h) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return low;
    }
};


/*
    ============================================================
    QUICK REVISION
    ============================================================

    Answer range:
        [1, max(piles)]

    Hours for one pile:
        ceil(pile / k)

    Integer ceiling:
        (pile + k - 1) / k

    If speed works:
        high = mid - 1

    If speed does not work:
        low = mid + 1

    Final answer:
        low

    Optimal:
        TC = O(n log(maxPile))
        SC = O(1)

    Interview pattern:
        "minimum X such that condition is satisfied"
        + monotonic feasibility
        = Binary Search on Answer
*/