# Count Occurrences Of A Number In A Sorted Array With Duplicates

## Problem Statement

Given a sorted array of integers (which may contain duplicates) and an integer `x`, find the total number of occurrences of `x` in the array.

## Example

```
Input:  arr = [2, 2, 3, 3, 3, 5, 6], x = 3
Output: 3
```

Explanation: `3` occurs at indices `2`, `3`, and `4` — a total of `3` occurrences.

## Intuition

Since the array is sorted, all occurrences of `x` (if any) are guaranteed to be contiguous. This means the count of occurrences can be computed directly from the first and last occurrence of `x`, which was already solved in the previous problem: `last occurrence - first occurrence + 1`. If `x` doesn't exist in the array at all (first occurrence is `-1`), the count is simply `0`.

## Approach 1 : Optimal (Reusing First and Last Occurrence)

Reuse the previously-built solution for finding the first and last occurrence of `x` in a sorted array. If the first occurrence is `-1`, `x` does not exist, so return `0`. Otherwise, the total count is `last occurrence - first occurrence + 1`.

### Algorithm
1. Compute `{first, last} = firstAndLastOccurrence(arr, n, x)` (using the Binary Search based solution from the previous problem).
2. If `first == -1`, return `0` (the value does not exist in the array).
3. Otherwise, return `last - first + 1`.

### Time Complexity
`O(2 * log N)` — reuses the two Binary Searches (for first and last occurrence) from the previous problem, each `O(log N)`.

### Space Complexity
`O(1)` — only a few variables are used, no extra data structures.

--------------------------------------------

## Dry Run

Input: `arr = [2, 2, 3, 3, 3, 5, 6]`, `x = 3`

- Find first occurrence of `3`: Binary Search narrows down to index `2`.
- Find last occurrence of `3`: Binary Search narrows down to index `4`.
- Count = `last - first + 1 = 4 - 2 + 1 = 3`.
- Final answer: `3`, matching the expected output.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Optimal (Reusing First and Last Occurrence) | O(2 log N) | O(1) |

--------------------------------------------

## Key Observations

- This problem is a direct, minimal extension of the "First and Last Occurrence in a Sorted Array" problem — no new search logic is required, only a simple arithmetic combination of its two results.
- Because the array is sorted, all occurrences of any value are guaranteed to form a contiguous block — this is precisely what makes `last - first + 1` a valid count formula.
- The `first == -1` check correctly handles the case where `x` doesn't exist in the array at all, avoiding an invalid arithmetic result (like `-1 - (-1) + 1 = 1`, which would incorrectly suggest one occurrence).
- Recognizing that a new-looking problem is really just a thin wrapper around a previously solved one is a valuable interview skill — it avoids re-deriving logic from scratch and demonstrates efficient problem-solving.

--------------------------------------------

## Interview Tips

- Immediately connect this problem to "First and Last Occurrence" when presenting your approach — showing the interviewer you recognize the reusable building block rather than treating it as a brand-new problem.
- Be explicit about the `first == -1` edge case and why it must be checked before applying the `last - first + 1` formula.
- If asked to justify the time complexity, clarify that it's simply the cost of the two Binary Searches inherited from the underlying first/last occurrence solution.
- Mention that this pattern — reducing a "count occurrences" problem to a "count occurrences = last - first + 1" formula — generalizes to many other sorted-array counting problems.

--------------------------------------------

## LeetCode

Not a standalone LeetCode problem; it is the natural follow-up to [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/), and is commonly listed separately on GeeksforGeeks as "Count number of occurrences (or frequency) in a sorted array."