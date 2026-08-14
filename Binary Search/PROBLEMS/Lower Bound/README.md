# Lower Bound

## Problem Statement

Given a sorted array of integers and a value `x`, find the lower bound of `x` in the array — defined as the **smallest index** such that the number at that index is **greater than or equal to** `x`.

If no such index exists (every element in the array is smaller than `x`), the lower bound is the hypothetical index equal to the size of the array (`n`).

## Example

```
Input:  arr = [1, 2, 2, 3, 7, 8, 9, 9, 9], x = 9
Output: 6
```

Explanation: Index `6` holds the value `9`, which is the smallest index where the value is greater than or equal to `9` (the first `9` in the array).

## Intuition

The straightforward way is to scan the array from the start and stop at the first element that is greater than or equal to `x` — this is the Brute Force approach.

Since the array is sorted, Binary Search can be applied instead. The key idea: maintain a variable `ans`, initialized to the hypothetical index `n` (the answer if no valid index is ever found). At each step, compute `mid` and check `arr[mid] >= x`. If true, this index is a **possible** answer — but since a smaller valid index might still exist further left, record `mid` as the current best answer and continue searching the left half (`high = mid - 1`) for something even smaller. If `arr[mid] < x`, this index can never be the answer (nor can anything to its left, since the array is sorted and everything to the left is even smaller) — so move to the right half (`low = mid + 1`) to search for a valid candidate. Because the search always moves left whenever a valid candidate is found, the last recorded `ans` is guaranteed to be the smallest valid index.

## Approach 1 : Brute Force

Scan the array from left to right and return the index of the first element that is greater than or equal to `x`. If no such element exists, return `n` (the size of the array).

### Algorithm
1. For each index `i` from `0` to `n - 1`:
   - If `arr[i] >= x`, return `i`.
2. If the loop completes without finding such an element, return `n`.

### Time Complexity
`O(N)` — in the worst case, the entire array must be scanned.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal (Binary Search)

Use Binary Search with an `ans` variable to track the best (smallest) valid index found so far, initialized to `n`. Narrow the search space based on whether `arr[mid] >= x` holds, always moving left after recording a valid candidate to look for something even smaller.

### Algorithm
1. Initialize `low = 0`, `high = n - 1`, and `ans = n`.
2. While `low <= high`:
   - Compute `mid = low + (high - low) / 2`.
   - If `arr[mid] >= x`, this index may be the answer — set `ans = mid`, then search left for something smaller: `high = mid - 1`.
   - Else (`arr[mid] < x`), this index cannot be the answer — search right: `low = mid + 1`.
3. Return `ans`.

### Time Complexity
`O(log N)` — the search space is halved at every step, identical to standard Binary Search.

### Space Complexity
`O(1)` — only a few pointer variables are used, no extra data structures.

--------------------------------------------

## Dry Run

Input: `arr = [1, 2, 2, 3, 7, 8, 9, 9, 9]`, `x = 1`

- `low = 0`, `high = 8`, `ans = 9`.
- `mid = 4`. `arr[4] = 7 >= 1` → possible answer → `ans = 4`, `high = 3`.
- `mid = 1`. `arr[1] = 2 >= 1` → possible answer → `ans = 1`, `high = 0`.
- `mid = 0`. `arr[0] = 1 >= 1` → possible answer → `ans = 0`, `high = -1`.
- `low = 0 > high = -1` → loop ends.
- Final answer: `ans = 0`.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N) | O(1) |
| Optimal (Binary Search) | O(log N) | O(1) |

--------------------------------------------

## Key Observations

- The `ans` variable is initialized to `n` (the hypothetical index just past the end of the array) to correctly handle the case where no element in the array is greater than or equal to `x`.
- Whenever a valid candidate (`arr[mid] >= x`) is found, the search always continues to the left (`high = mid - 1`) — this guarantees that by the time the search space is exhausted, `ans` holds the smallest valid index, since any further updates to `ans` can only happen at smaller indices.
- If `arr[mid] < x`, that index — and everything to its left — can never be the answer, since the array is sorted and everything to the left is even smaller than `arr[mid]`.
- This technique of tracking a separate `ans` variable (rather than directly returning from within the loop) is a reusable Binary Search pattern that extends naturally to Upper Bound, Search Insert Position, Floor, and Ceil.

--------------------------------------------

## Interview Tips

- Emphasize the `ans` variable pattern — many "find the smallest/largest index satisfying a condition" problems reduce to this exact template, so demonstrating fluency with it signals strong Binary Search fundamentals.
- Be ready to explain why moving left after finding a valid candidate (instead of returning immediately) is necessary — an interviewer will likely probe this to check understanding versus memorization.
- Mention that in C++, this can be implemented directly using the STL's `lower_bound()` function for interviews or coding rounds where writing the raw Binary Search isn't the focus.
- Note that the time complexity remains `O(log N)` regardless of whether the target value is present exactly or not — this is a common point of confusion worth clarifying upfront.

--------------------------------------------

## LeetCode

Not directly available as a standalone LeetCode problem; the underlying technique is available via the C++ STL `lower_bound()` function, and is a foundational building block for problems like [35. Search Insert Position](https://leetcode.com/problems/search-insert-position/).