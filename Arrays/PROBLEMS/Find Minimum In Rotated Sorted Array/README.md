# Find Minimum In Rotated Sorted Array

## Problem Statement

Given a rotated sorted array of unique integers, find and return the minimum element in the array.

A rotated sorted array is a sorted array that has been rotated at some unknown pivot point — for example, `[0, 1, 2, 4, 5, 6, 7]` rotated at index `3` becomes `[4, 5, 6, 7, 0, 1, 2]`.

## Example

```
Input:  arr = [4, 5, 6, 7, 0, 1, 2]
Output: 0
```

Explanation: `0` is the smallest element in the array, located at the point where the rotation occurred.

## Intuition

The Brute Force approach simply scans the array once to find the minimum, ignoring the rotated structure entirely.

Since the array is "sorted" (with a rotation), Binary Search can be applied — but a direct comparison against a single target isn't possible here since we're searching for an unknown minimum, not a specific value. The key insight: at any point during the search, one half of the current search space (either the left half from `low` to `mid`, or the right half from `mid` to `high`) is guaranteed to be sorted, because the rotation point can only exist in one of the two halves. Whichever half is sorted, its own smallest element is simply its leftmost element — so that value can be captured directly, and that entire half can be eliminated from further consideration (since its minimum has already been recorded), leaving the search to continue in the other, unsorted half, which may still contain a smaller value hiding the true minimum.

## Approach 1 : Brute Force

Scan the entire array once, tracking the smallest value seen.

### Algorithm
1. Initialize `ans = INT_MAX`.
2. For each index `i` from `0` to `n - 1`:
   - Update `ans = min(ans, arr[i])`.
3. Return `ans`.

### Time Complexity
`O(N)` — a single traversal of the array.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal (Binary Search)

At each step, determine which half of the current search space (`low` to `mid`, or `mid` to `high`) is sorted by comparing `arr[low]` with `arr[mid]`. Whichever half is sorted, its minimum is simply its leftmost element (`arr[low]` for the left half, `arr[mid]` for the right half) — record that value against the running answer, then eliminate that entire half and continue searching the other (still possibly unsorted) half.

### Algorithm
1. Initialize `low = 0`, `high = n - 1`, `ans = INT_MAX`.
2. While `low <= high`:
   - Compute `mid = low + (high - low) / 2`.
   - If `arr[low] <= arr[mid]` (the left half, from `low` to `mid`, is sorted):
     - Update `ans = min(ans, arr[low])` (the smallest value in a sorted range is its first element).
     - Eliminate the left half: `low = mid + 1`.
   - Else (the right half, from `mid` to `high`, must be sorted instead):
     - Update `ans = min(ans, arr[mid])`.
     - Eliminate the right half: `high = mid - 1`.
3. Return `ans`.

### Time Complexity
`O(log N)` — the search space is halved at every step, identical to standard Binary Search.

### Space Complexity
`O(1)` — only a few variables are used, no extra data structures.

--------------------------------------------

## Approach 3 : Optimal (With Early-Exit Optimization)

An optional refinement to Approach 2: at each step, first check whether the *entire* current search space (`low` to `high`) is already sorted, by comparing `arr[low] <= arr[high]`. If so, there's no need to continue any further Binary Search steps — the minimum of a fully sorted range is simply its first element (`arr[low]`), so the answer can be updated and the loop can break immediately. This check naturally becomes true once the search has moved entirely past the rotation point.

### Algorithm
1. Initialize `low = 0`, `high = n - 1`, `ans = INT_MAX`.
2. While `low <= high`:
   - Compute `mid = low + (high - low) / 2`.
   - If `arr[low] <= arr[high]` (the entire current search space is sorted):
     - Update `ans = min(ans, arr[low])`.
     - Break out of the loop immediately — no further searching is needed.
   - Else if `arr[low] <= arr[mid]` (the left half is sorted):
     - Update `ans = min(ans, arr[low])`.
     - Eliminate the left half: `low = mid + 1`.
   - Else (the right half is sorted):
     - Update `ans = min(ans, arr[mid])`.
     - Eliminate the right half: `high = mid - 1`.
3. Return `ans`.

### Time Complexity
`O(log N)` — same asymptotic complexity as Approach 2, but with a practical early exit once the remaining search space becomes fully sorted, avoiding unnecessary further iterations.

### Space Complexity
`O(1)` — only a few variables are used, no extra data structures.

--------------------------------------------

## Dry Run

Input: `arr = [4, 5, 6, 7, 0, 1, 2]` (using Approach 2)

- `low = 0`, `high = 6`, `ans = INT_MAX`.
- `mid = 3`. `arr[0] = 4 <= arr[3] = 7`? Yes → left half sorted → `ans = min(INT_MAX, 4) = 4`. Eliminate left: `low = 4`.
- `low = 4`, `high = 6`. `mid = 5`. `arr[4] = 0 <= arr[5] = 1`? Yes → left half sorted → `ans = min(4, 0) = 0`. Eliminate left: `low = 6`.
- `low = 6`, `high = 6`. `mid = 6`. `arr[6] = 2 <= arr[6] = 2`? Yes → left half sorted → `ans = min(0, 2) = 0`. Eliminate left: `low = 7`.
- `low = 7 > high = 6` → loop ends.
- Final answer: `0`, matching the expected output.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N) | O(1) |
| Optimal (Binary Search) | O(log N) | O(1) |
| Optimal (With Early-Exit Optimization) | O(log N) | O(1) |

--------------------------------------------

## Key Observations

- At every step of the Binary Search, exactly one half of the current search space is guaranteed to be sorted — this is a direct consequence of the array being rotated at exactly one pivot point.
- The minimum of any sorted range is always its leftmost element — this is what allows the sorted half's contribution to the answer to be captured in constant time, without further searching within it.
- The unsorted half is the one that must still be searched further, since it may still contain the true minimum (hidden past the rotation point).
- The early-exit optimization (Approach 3) recognizes that once the entire remaining search space becomes sorted (which happens once the search has moved past the rotation point), no further Binary Search steps are needed — the answer is immediately known.
- This problem assumes unique elements in the array; handling duplicates requires additional care (mentioned in the transcript as a follow-up extension, analogous to the duplicate-handling variant of "Search in Rotated Sorted Array").

--------------------------------------------

## Interview Tips

- Emphasize the core insight clearly: at each Binary Search step, one half is always sorted, and that half's minimum can be captured directly via its leftmost element.
- Be ready to justify the `<=` (rather than strict `<`) comparison when checking if the left half is sorted — this correctly handles the edge case of a single-element search space.
- Mention the early-exit optimization as a nice-to-have refinement, but be clear that it doesn't change the asymptotic time complexity — it's a practical improvement, not a different algorithm.
- If asked about duplicates, acknowledge that the direct `arr[low] <= arr[mid]` check can become ambiguous when duplicate values are present, and mention that additional handling (similar to duplicate-handling in "Search in Rotated Sorted Array") would be needed.

--------------------------------------------

## LeetCode

[153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)