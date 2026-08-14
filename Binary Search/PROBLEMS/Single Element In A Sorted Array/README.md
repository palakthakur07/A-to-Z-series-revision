# Single Element In A Sorted Array

## Problem Statement

Given a sorted array of integers where every element appears exactly twice except for one element which appears exactly once, find and return that single element. It is guaranteed that a single element always exists, and since the array is sorted, all pairs of duplicate elements sit next to each other.

## Example

```
Input:  arr = [1, 1, 2, 3, 3, 4, 4, 5, 5, 6, 6]
Output: 2
```

Explanation: Every element appears twice except `2`, which appears only once.

## Intuition

The Brute Force approach checks, for every index, whether its left and right neighbors match it — an index with neither neighbor matching is the single element.

The optimal approach uses Binary Search, but requires finding a property of the single element that allows eliminating half the search space. The key observation: before the single element, every pair sits at an (even index, odd index) position — i.e., the first of each pair is at an even index and the second at an odd index. After the single element, this pattern flips — every pair instead sits at an (odd index, even index) position, because the single element shifted everything after it by one position. So: if standing at an even index and the next element matches, or standing at an odd index and the previous element matches, the current position is still in the pre-single-element region (the left half), meaning the single element lies to the right — eliminate the left half. Otherwise, the single element lies to the left — eliminate the right half. To keep the implementation clean and avoid a large number of boundary checks for the first and last elements, those two are checked separately up front, and the Binary Search only operates on the trimmed range from index `1` to `n - 2`.

## Approach 1 : Brute Force

For each index, check its neighbors: the first index only has a right neighbor, the last index only has a left neighbor, and every other index has both. An index whose existing neighbor(s) don't match its own value is the single element.

### Algorithm
1. If `n == 1`, return `arr[0]` (a single-element array has no pairs, so it must itself be the answer).
2. For each index `i` from `0` to `n - 1`:
   - If `i == 0`: if `arr[i] != arr[i + 1]`, return `arr[i]`.
   - Else if `i == n - 1`: if `arr[i] != arr[i - 1]`, return `arr[i]`.
   - Else: if `arr[i] != arr[i - 1]` and `arr[i] != arr[i + 1]`, return `arr[i]`.

### Time Complexity
`O(N)` — in the worst case, every element is checked.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal (Binary Search)

Handle the single-element array case and the two boundary elements (first and last index) separately, up front, to avoid repeated out-of-bounds checks inside the main loop. Then run Binary Search over the trimmed range `[1, n - 2]`: at each `mid`, first check directly whether `mid` is the single element (neither neighbor matches). If not, determine whether `mid` lies in the "pre-single-element" region (where even-odd pairing still holds) or the "post-single-element" region (where odd-even pairing holds), and eliminate the appropriate half accordingly.

### Algorithm
1. If `n == 1`, return `arr[0]`.
2. If `arr[0] != arr[1]`, return `arr[0]` (the first element is the single element).
3. If `arr[n - 1] != arr[n - 2]`, return `arr[n - 1]` (the last element is the single element).
4. Initialize `low = 1`, `high = n - 2`.
5. While `low <= high`:
   - Compute `mid = low + (high - low) / 2`.
   - If `arr[mid] != arr[mid + 1]` and `arr[mid] != arr[mid - 1]`, return `arr[mid]` (found the single element).
   - Else if (`mid` is odd and `arr[mid - 1] == arr[mid]`) or (`mid` is even and `arr[mid] == arr[mid + 1]`): this position is still in the pre-single-element region — eliminate the left half: `low = mid + 1`.
   - Else: this position is in the post-single-element region — eliminate the right half: `high = mid - 1`.
6. (Unreachable, since the answer is guaranteed to exist) return a dummy value such as `-1`.

### Time Complexity
`O(log N)` — the search space is halved at every step, identical to standard Binary Search.

### Space Complexity
`O(1)` — only a few variables are used, no extra data structures.

--------------------------------------------

## Dry Run

Input: `arr = [1, 1, 3, 3, 4, 4, 5, 7, 7, 8, 8]` (indices `0` to `10`, single element `5` at index `6`)

- `n = 11`. `arr[0] = 1 == arr[1] = 1` → not the first-element case. `arr[10] = 8 == arr[9] = 8` → not the last-element case.
- `low = 1`, `high = 9`.
- `mid = 5`. `arr[5] = 4`. `arr[5] != arr[6] = 5`? Yes. `arr[5] != arr[4] = 4`? No — so not the single element (matches left neighbor). `mid = 5` is odd, and `arr[4] == arr[5]` (`4 == 4`) → pre-single-element region → eliminate left: `low = 6`.
- `low = 6`, `high = 9`. `mid = 7`. `arr[7] = 7`. `arr[7] != arr[8] = 7`? No — not the single element. `mid = 7` is odd, but `arr[6] = 5 != arr[7] = 7` → not the pre-single-element condition → eliminate right: `high = 6`.
- `low = 6`, `high = 6`. `mid = 6`. `arr[6] = 5`. `arr[6] != arr[7] = 7`? Yes. `arr[6] != arr[5] = 4`? Yes → both neighbors differ → this is the single element.
- Return `5`.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N) | O(1) |
| Optimal (Binary Search) | O(log N) | O(1) |

--------------------------------------------

## Key Observations

- Before the single element, each pair occupies an (even, odd) index pattern; after the single element, this shifts to an (odd, even) pattern — this parity shift is the property that enables Binary Search elimination.
- Handling the first and last elements as separate special cases (rather than inside the main loop) avoids writing extra boundary-check conditions for out-of-range neighbor access, resulting in cleaner, more readable code.
- Trimming the Binary Search range to `[1, n - 2]` is a direct consequence of having already handled the two boundary elements separately — every index inside this trimmed range is guaranteed to have both a left and a right neighbor.
- The direct check (`arr[mid] != arr[mid+1] && arr[mid] != arr[mid-1]`) at each step is what allows the algorithm to terminate immediately upon finding the answer, rather than continuing to narrow the search space unnecessarily.
- A single-element array (`n == 1`) is an important edge case, since such an array has no pairs at all — the one element present is trivially the answer.

--------------------------------------------

## Interview Tips

- Lead with the parity-shift observation (even-odd before the single element, odd-even after) — this is the crux insight interviewers are looking for, and stating it clearly demonstrates genuine understanding rather than memorized code.
- Proactively mention the decision to handle the first and last elements separately, and explain that this is a deliberate readability choice to avoid extra conditional boundary checks — not a workaround for a bug.
- Be ready to justify why trimming the search space to `[1, n-2]` is safe — every index in that range is guaranteed to have both neighbors present.
- Emphasize consistency in Binary Search style (`low <= high` with `low = mid + 1` / `high = mid - 1`) across different Binary Search problems — this signals disciplined coding practice to interviewers.

--------------------------------------------

## LeetCode

[540. Single Element in a Sorted Array](https://leetcode.com/problems/single-element-in-a-sorted-array/)