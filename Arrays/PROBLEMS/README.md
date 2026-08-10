# Count Occurrences of a Number in a Sorted Array

## Problem Statement
Given a sorted array of `N` integers (which may contain duplicates) and an integer `X`, find the total number of occurrences of `X` in the array.

## Example
Array: `[1, 2, 2, 2, 3, 4]`, `X = 2`

There are 2 occurrences... wait, let's use the transcript's own framing: if `X = 3` in an array where 3 appears twice, the answer is 2 (since the array is sorted, all occurrences of `X` are contiguous).

## Intuition
This problem builds directly on top of the "First and Last Occurrence" problem. Since the array is sorted, all occurrences of `X` lie in one contiguous block. So once we know the **first occurrence** and the **last occurrence** of `X`, the count of occurrences is simply:

```
count = last occurrence - first occurrence + 1
```

If `X` doesn't exist in the array (first occurrence is `-1`), the count is `0`.

This reuses the exact same function built in the previous problem (finding first and last occurrence via binary search) — no new algorithm is introduced.

## Approach 1 : Optimal (Reusing First & Last Occurrence)
### Explain
Call the previously built function that returns a pair `{first, last}` for `X` in the sorted array.
- If `first == -1`, `X` does not exist in the array → return `0`.
- Otherwise, return `last - first + 1`.

### Algorithm
1. Call `ans = searchFirstAndLast(arr, n, x)` which returns `{first, last}`.
2. If `ans.first == -1`, return `0`.
3. Otherwise, return `ans.second - ans.first + 1`.

### Time Complexity
`O(2 * log N)` — same as the underlying first/last occurrence function (binary search called twice).

### Space Complexity
`O(1)` — no extra space used.

## Dry Run
Array: `[3, 4, 8, 8, 8, 8, 11, 11]`, `X = 8`

- `searchFirstAndLast(arr, n, 8)` returns `{first = 2, last = 5}` (as derived in the previous topic's dry run).
- `count = last - first + 1 = 5 - 2 + 1 = 4`

**Answer: 4 occurrences of 8**

## Comparison Table
| Approach | Time | Space |
|---|---|---|
| Optimal (reuse first/last occurrence) | O(2 log N) | O(1) |

## Key Observations
- Since the array is sorted, all occurrences of a given number are always contiguous.
- This problem doesn't need a new algorithm — it directly reuses the first/last occurrence solution.
- Always check `first == -1` before computing `last - first + 1`, otherwise you'd get an incorrect result like `-1 - (-1) + 1 = 1` for an element that doesn't even exist.

## Interview Tips
- Mention explicitly that this is a direct extension of the first/last occurrence problem — interviewers like to see you recognize reusable subproblems instead of writing fresh code.
- Don't forget the `first == -1` edge case check before returning the count.

## LeetCode
Not directly listed as a separate LeetCode problem in the transcript — this is a GeeksforGeeks-style variant built on top of [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/).