# Search Insert Position

## Problem Statement

Given a sorted array of **distinct** values and a target value, search for the index of the target value in the array. If the target is present, return its index. If the target is not present, determine the index where it would be inserted in order to keep the array sorted.

## Example

```
Input:  arr = [1, 2, 4, 7], target = 6
Output: 3
```

Explanation: `6` is not present in the array. To keep the array sorted, `6` would need to be inserted right before `7`, at index `3`, giving `[1, 2, 4, 6, 7]`.

## Intuition

If the target is present in the array, its index is simply where it's found. If the target is not present, it needs to be inserted at the position of the first element that is greater than it (so that the array stays sorted).

This is exactly the definition of **Lower Bound**: the smallest index such that the value at that index is greater than or equal to the target. If the target exists, Lower Bound lands directly on it (satisfying "greater than or equal to" via equality). If the target doesn't exist, Lower Bound lands on the first element greater than it — exactly the position where the target should be inserted. So this problem reduces entirely to computing the Lower Bound of the target.

## Approach 1 : Brute Force

Scan the array from left to right and return the index of the first element that is greater than or equal to the target. If no such element exists, return `n` (the size of the array, meaning the target belongs at the very end).

### Algorithm
1. For each index `i` from `0` to `n - 1`:
   - If `arr[i] >= target`, return `i`.
2. If the loop completes without finding such an element, return `n`.

### Time Complexity
`O(N)` — in the worst case, the entire array must be scanned.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal (Binary Search — Lower Bound)

Apply the exact same Binary Search / Lower Bound template used previously: track the smallest valid index in an `ans` variable, initialized to `n`, moving left after finding a valid candidate to search for something smaller.

### Algorithm
1. Initialize `low = 0`, `high = n - 1`, and `ans = n`.
2. While `low <= high`:
   - Compute `mid = low + (high - low) / 2`.
   - If `arr[mid] >= target`, this index may be the answer — set `ans = mid`, then search left: `high = mid - 1`.
   - Else (`arr[mid] < target`), this index cannot be the answer — search right: `low = mid + 1`.
3. Return `ans`.

### Time Complexity
`O(log N)` — the search space is halved at every step.

### Space Complexity
`O(1)` — only a few pointer variables are used, no extra data structures.

--------------------------------------------

## Dry Run

Input: `arr = [1, 2, 4, 7]`, `target = 6`

- `low = 0`, `high = 3`, `ans = 4`.
- `mid = 1`. `arr[1] = 2 >= 6`? No → search right → `low = 2`.
- `mid = 2`. `arr[2] = 4 >= 6`? No → search right → `low = 3`.
- `mid = 3`. `arr[3] = 7 >= 6`? Yes → possible answer → `ans = 3`, `high = 2`.
- `low = 3 > high = 2` → loop ends.
- Final answer: `ans = 3`, matching the expected output.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N) | O(1) |
| Optimal (Binary Search — Lower Bound) | O(log N) | O(1) |

--------------------------------------------

## Key Observations

- This problem is a direct, unmodified application of the Lower Bound technique — no additional logic is needed beyond computing `lower_bound(target)`.
- Whether the target is present or absent in the array, the same Lower Bound computation handles both cases correctly: if present, it returns the target's own index (via the `>=` equality case); if absent, it returns the correct insertion index.
- Because the array contains distinct values (as stated in the problem), there's no ambiguity about which index to return when the target is present.
- Recognizing this problem as "just Lower Bound in disguise" is the key insight — problems described in everyday language (like "insert position") often map directly onto standard Binary Search templates once translated into "smallest index where condition X holds."

--------------------------------------------

## Interview Tips

- Explicitly state to the interviewer that this problem is equivalent to computing the Lower Bound of the target — this demonstrates the ability to recognize known patterns within differently-worded problems.
- Avoid writing separate logic for the "found" and "not found" cases — a single Lower Bound computation naturally handles both, and pointing this out shows a cleaner, more elegant solution.
- Mention that in C++, `lower_bound(arr.begin(), arr.end(), target) - arr.begin()` solves this in one line using the STL.
- Be careful to re-read problem statements for subtle wording differences (e.g. index vs. value) before assuming a problem maps directly onto a known template — the transcript explicitly calls out this habit as good practice.

--------------------------------------------

## LeetCode

[35. Search Insert Position](https://leetcode.com/problems/search-insert-position/)