# Upper Bound

## Problem Statement

Given a sorted array of integers and a value `x`, find the upper bound of `x` in the array — defined as the **smallest index** such that the number at that index is **strictly greater than** `x`.

If no such index exists (no element in the array is strictly greater than `x`), the upper bound is the hypothetical index equal to the size of the array (`n`).

*(Note: this problem is nearly identical to Lower Bound — the only difference is the comparison changes from "greater than or equal to" to "strictly greater than".)*

## Example

```
Input:  arr = [3, 5, 8, 9, 15, 19], x = 9
Output: 4
```

Explanation: `9` itself is present in the array, but `9` is not strictly greater than `9`. Index `4` holds the value `15`, which is the smallest index where the value is strictly greater than `9`.

## Intuition

Just like Lower Bound, the straightforward way is to scan the array from the start and stop at the first element that is strictly greater than `x` — this is the Brute Force approach.

The optimal approach reuses the exact same Binary Search template as Lower Bound, with a single change: the condition `arr[mid] >= x` becomes `arr[mid] > x`. Everything else — the `ans` variable initialized to `n`, moving left after finding a valid candidate to search for something smaller, and moving right otherwise — stays identical.

## Approach 1 : Brute Force

Scan the array from left to right and return the index of the first element that is strictly greater than `x`. If no such element exists, return `n` (the size of the array).

### Algorithm
1. For each index `i` from `0` to `n - 1`:
   - If `arr[i] > x`, return `i`.
2. If the loop completes without finding such an element, return `n`.

### Time Complexity
`O(N)` — in the worst case, the entire array must be scanned.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal (Binary Search)

Use Binary Search with an `ans` variable to track the best (smallest) valid index found so far, initialized to `n`. Narrow the search space based on whether `arr[mid] > x` holds, always moving left after recording a valid candidate to look for something even smaller.

### Algorithm
1. Initialize `low = 0`, `high = n - 1`, and `ans = n`.
2. While `low <= high`:
   - Compute `mid = low + (high - low) / 2`.
   - If `arr[mid] > x`, this index may be the answer — set `ans = mid`, then search left for something smaller: `high = mid - 1`.
   - Else (`arr[mid] <= x`), this index cannot be the answer — search right: `low = mid + 1`.
3. Return `ans`.

### Time Complexity
`O(log N)` — the search space is halved at every step, identical to standard Binary Search.

### Space Complexity
`O(1)` — only a few pointer variables are used, no extra data structures.

--------------------------------------------

## Dry Run

Input: `arr = [3, 5, 8, 9, 15, 19]`, `x = 9`

- `low = 0`, `high = 5`, `ans = 6`.
- `mid = 2`. `arr[2] = 8 > 9`? No → search right → `low = 3`.
- `mid = 4`. `arr[4] = 15 > 9`? Yes → possible answer → `ans = 4`, `high = 3`.
- `low = 3, high = 3` → loop continues → `mid = 3`. `arr[3] = 9 > 9`? No → search right → `low = 4`.
- `low = 4 > high = 3` → loop ends.
- Final answer: `ans = 4`.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N) | O(1) |
| Optimal (Binary Search) | O(log N) | O(1) |

--------------------------------------------

## Key Observations

- Upper Bound and Lower Bound share the exact same Binary Search template; only the comparison operator changes (`>=` becomes `>`).
- The `ans` variable is initialized to `n` to correctly handle the case where no element in the array is strictly greater than `x`.
- When `x` itself exists in the array, the Upper Bound skips past all occurrences of `x` and lands on the first element strictly greater than it — unlike Lower Bound, which would land directly on the first occurrence of `x`.
- As with Lower Bound, moving left after finding a valid candidate guarantees the final `ans` holds the smallest valid index once the search space is exhausted.

--------------------------------------------

## Interview Tips

- Point out to the interviewer immediately that this is a one-symbol variation of Lower Bound — showing you recognize the shared template rather than treating it as an unrelated problem.
- Be ready to explain, with the example of a value that appears multiple times in the array, why Lower Bound lands on the first occurrence while Upper Bound skips past all occurrences.
- Mention that in C++, this can be implemented directly using the STL's `upper_bound()` function for interviews or coding rounds where writing the raw Binary Search isn't the focus.
- Emphasize that despite the tiny code change, being able to correctly reason about which direction to move (and why) demonstrates deeper understanding than simply memorizing the modified condition.

--------------------------------------------

## LeetCode

Not directly available as a standalone LeetCode problem; the underlying technique is available via the C++ STL `upper_bound()` function.