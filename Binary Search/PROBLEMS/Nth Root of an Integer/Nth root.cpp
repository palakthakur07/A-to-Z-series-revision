#include <bits/stdc++.h>
using namespace std;

/*
    Find the Nth root of M.

    Return:
      - x if x^N == M
      - -1 if no exact integer root exists

    Final approach from the lecture:
      Binary Search on Answers + overflow-safe multiplication.

    Complexity:
      Time  : O(N * log M)
      Space : O(1)
*/


// Returns:
//   1  -> mid^n == M
//   0  -> mid^n < M
//   2  -> mid^n > M
//
// We stop immediately when the product becomes > M,
// so we never need to calculate a potentially overflowing mid^n.
int powerCheck(long long mid, int n, long long M) {
    long long result = 1;

    for (int i = 1; i <= n; i++) {
        result *= mid;

        // We only care whether result has crossed M.
        if (result > M)
            return 2;
    }

    if (result == M)
        return 1;

    return 0;
}


// ------------------------------------------------------------
// OPTIMAL: Binary Search on Answers
// Time  : O(N * log M)
// Space : O(1)
// ------------------------------------------------------------
int nthRoot(int n, long long M) {
    long long low = 1;
    long long high = M;

    while (low <= high) {
        long long mid = low + (high - low) / 2;

        int state = powerCheck(mid, n, M);

        if (state == 1) {
            // mid^n == M
            return (int)mid;
        }
        else if (state == 0) {
            // mid^n < M
            // Need a bigger candidate.
            low = mid + 1;
        }
        else {
            // mid^n > M
            // Need a smaller candidate.
            high = mid - 1;
        }
    }

    // No exact integer root exists.
    return -1;
}


// ------------------------------------------------------------
// BRUTE FORCE
//
// Search every candidate from 1 to M.
//
// Time:
//   O(M * N) with the normal multiplication loop.
//
// Space:
//   O(1)
//
// This is included for comparison/learning.
// ------------------------------------------------------------
int nthRootBrute(int n, long long M) {
    for (long long candidate = 1; candidate <= M; candidate++) {
        long long result = 1;
        bool exceeded = false;

        for (int i = 1; i <= n; i++) {
            result *= candidate;

            // No larger candidate can work once this is exceeded.
            if (result > M) {
                exceeded = true;
                break;
            }
        }

        if (!exceeded && result == M)
            return (int)candidate;

        // Since candidate^n > M, all larger candidates
        // will also be impossible.
        if (exceeded)
            break;
    }

    return -1;
}


int main() {
    // Example 1:
    // 3rd root of 27 = 3
    cout << nthRoot(3, 27) << '\n';

    // Example 2:
    // 4th root of 69 does not exist
    cout << nthRoot(4, 69) << '\n';

    // Example 3:
    // 10th root of 1e9 does not exist
    cout << nthRoot(10, 1000000000LL) << '\n';

    return 0;
}


/*
============================================================
INTERVIEW NOTES
============================================================

1. Why binary search?

The answer lies between 1 and M.

For increasing x:

    x^N

is also increasing.

Therefore:

    x^N < M  -> search right
    x^N = M  -> answer found
    x^N > M  -> search left

This is exactly the monotonic structure needed for
Binary Search on Answers.

------------------------------------------------------------

2. Why not simply calculate mid^N?

Because it can overflow.

For example:

    n = 10
    M = 10^9

A midpoint can be extremely large, and mid^10 can be far
outside the range of a normal integer type.

We don't need the actual huge value.

We only need to know whether it is:

    less than M
    equal to M
    greater than M

So powerCheck() stops immediately after crossing M.

------------------------------------------------------------

3. Complexity

BRUTE FORCE:

    O(M * N)

Binary Search + normal power loop:

    O(N * log M)

Binary Search + binary exponentiation:

    O(log N * log M)

The transcript focuses on the simpler multiplication loop
for the overflow-safe final implementation.

------------------------------------------------------------

4. Exact root vs floor root

This problem asks for an EXACT integer root.

For:

    n = 3, M = 27

answer = 3

For:

    n = 4, M = 69

there is no integer x satisfying:

    x^4 = 69

Therefore:

    answer = -1

Do NOT return 2 or 3 as a floor value.

------------------------------------------------------------

5. Binary Search on Answers Checklist

When you see a problem like this, ask:

    1. What is the answer range?
    2. Is the condition monotonic?
    3. If current answer is too small, should I go right?
    4. If current answer is too large, should I go left?
    5. Can the checking function overflow?
    6. Do I need an exact answer or an optimal/floor answer?

------------------------------------------------------------

6. Safer midpoint

Use:

    mid = low + (high - low) / 2

instead of:

    mid = (low + high) / 2

to avoid possible overflow in low + high.

============================================================
*/