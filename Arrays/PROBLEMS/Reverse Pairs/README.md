# Reverse Pairs

## Problem Statement

Given an array of integers, count the number of pairs `(i, j)` such that `i < j` (the left element comes before the right element in the array) and the left element is strictly greater than **twice** the right element — that is, `arr[i] > 2 * arr[j]`.

*(Note: this problem builds directly on Count Inversions — the same merge-sort-based idea is reused, but the pairing condition changes from `arr[i] > arr[j]` to `arr[i] > 2 * arr[j]`, which requires a different counting technique before the merge step.)*

## Example

```
Input:  arr = [40, 25, 19, 12, 9, 6, 2]
Output: 15
```

Explanation: For `2`, all `6` remaining elements to its left satisfy the condition. For `6`, `3` elements satisfy it (`19, 25, 40`). For `9`, `3` elements satisfy it. For `12`, `2` elements satisfy it. For `19`, `1` element satisfies it. For `25` and `40`, none of the remaining elements to their left satisfy the condition. Total: `6 + 3 + 3 + 2 + 1 = 15`.

## Intuition

The Brute Force approach checks every pair `(i, j)` with `i < j` directly.

The optimal idea reuses the Merge Sort technique from Count Inversions, but with an important twist: in Count Inversions, once `arr[left] > arr[right]` was found true for one right-half element, *all* remaining left-half elements were also greater than that right-half element (since the left half is sorted) — allowing a batch count. However, for the condition `arr[left] > 2 * arr[right]`, the same shortcut doesn't directly apply in the same direction: if `6` is not greater than twice of `13`, that doesn't mean nothing after `6` (like `13`, `21`, `25` on the left, if `6` were smaller) will work — rather, elements further right in the sorted right half might still satisfy the condition even if earlier right elements didn't, or vice versa. So instead of counting during the merge itself, a separate counting pass runs **before** the actual merge (while both halves are still individually sorted and unmodified), using two pointers that only ever move forward — giving a linear-time count per merge level, just computed slightly differently from Count Inversions.

## Approach 1 : Brute Force

Use two nested loops: for every index `i`, check every index `j > i`, and increment a counter whenever `arr[i] > 2 * arr[j]`.

### Algorithm
1. Initialize `count = 0`.
2. For each `i` from `0` to `n - 1`:
   - For each `j` from `i + 1` to `n - 1`:
     - If `arr[i] > 2 * arr[j]`, increment `count`.
3. Return `count`.

### Time Complexity
`O(N^2)` — every pair of indices is checked using two nested loops.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal

Use a modified Merge Sort. Recursively split the array in half and solve each half. Before merging the two already-sorted halves, run a separate counting pass: for every element in the left half (from `low` to `mid`), advance a `right` pointer (starting at `mid + 1`, and never reset between iterations of the left pointer) as far as possible while `arr[i] > 2 * arr[right]` holds. The number of valid right-half elements for that `i` is `right - (mid + 1)`. Because both halves are sorted and the `right` pointer only ever moves forward across the entire counting pass, this step runs in linear time. After counting, perform the standard Merge Sort merge step to combine the two halves.

### Algorithm
1. Define `mergeSort(arr, low, high)`:
   - If `low >= high`, return `0` (base case: no pairs possible).
   - Compute `mid = (low + high) / 2`.
   - Let `count = mergeSort(arr, low, mid) + mergeSort(arr, mid + 1, high)`.
   - Add `countPairs(arr, low, mid, high)` to `count` (counts valid pairs across the two sorted halves, using the still-unmerged, sorted state of each half).
   - Call `merge(arr, low, mid, high)` to merge the two halves back together (identical to the standard Merge Sort merge step).
   - Return `count`.
2. Define `countPairs(arr, low, mid, high)`:
   - Initialize `right = mid + 1` and `count = 0`.
   - For each `i` from `low` to `mid`:
     - While `right <= high` and `arr[i] > 2 * arr[right]`, increment `right`.
     - Add `right - (mid + 1)` to `count` (the number of valid right-half elements found so far for this `i`).
   - Return `count`.
3. Define `merge(arr, low, mid, high)`: standard Merge Sort merge — merge the two sorted halves `arr[low..mid]` and `arr[mid+1..high]` into a temporary array using two pointers, then copy the result back into `arr[low..high]`.

### Time Complexity
`O(N log N)` — the counting pass (`countPairs`) runs in `O(N)` per merge level since the `right` pointer never resets and only moves forward across the whole pass, and the merge step is also `O(N)` per level, giving `O(N log N)` total across `O(log N)` levels of recursion.

### Space Complexity
`O(N)` — for the temporary array used during each merge step. Note: this approach also modifies (sorts) the original array as a side effect; if the original array's order must be preserved, a copy of it should be sorted instead.

--------------------------------------------

## Dry Run

Input: `arr = [40, 25, 19, 12, 9, 6, 2]`

- Split into `[40, 25, 19, 12]` and `[9, 6, 2]`, and further down to individual elements.
- Merging `[40]` and `[25]`: `countPairs` finds `40 > 2*25`? No → `0` pairs. Merge gives `[25, 40]`.
- Merging `[19]` and `[12]`: `19 > 2*12`? No → `0` pairs. Merge gives `[12, 19]`.
- Merging `[25, 40]` and `[12, 19]`: for `25`, `right` starts at `12`: `25 > 2*12`? Yes → advance; `25 > 2*19`? No → stop; count `1`. For `40`, `right` continues from `19`: `40 > 2*19`? Yes → advance past both → count `2`. Total this step: `1 + 2 = 3`. Merge gives `[12, 19, 25, 40]`.
- Merging `[9]` and `[6]`: `9 > 2*6`? No → `0` pairs. Merge gives `[6, 9]`.
- Merging `[6, 9]` and `[2]`: for `6`, `right` starts at `2`: `6 > 2*2`? Yes → advance past `2` → count `1`. For `9`, `right` already past the end → count `1` (no further advance needed, still counts as `1` remaining). Total this step: `1 + 1 = 2`. Merge gives `[2, 6, 9]`.
- Merging `[12, 19, 25, 40]` and `[2, 6, 9]`: for `12`, `right` starts at `2`: `12 > 2*2`? Yes → advance; `12 > 2*6`? No → stop; count `1`. For `19`, continue from `6`: `19 > 2*6`? Yes → advance; `19 > 2*9`? Yes → advance past end; count `3`. For `25`, `right` already past end → count `3`. For `40`, already past end → count `3`. Total this step: `1 + 3 + 3 + 3 = 10`.
- Grand total: `0 (from [40,25]) + 0 (from [19,12]) + 3 (merging into [12,19,25,40]) + 0 (from [9,6]) + 2 (merging into [2,6,9]) + 10 (final merge) = 15`.
- Final answer: `15`, matching the expected output.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N^2) | O(1) |
| Optimal | O(N log N) | O(N) |

--------------------------------------------

## Key Observations

- This problem reuses the merge-sort-based structure of Count Inversions, but the counting logic cannot be folded directly into the merge step — a separate pre-merge counting pass is required because the `arr[i] > 2 * arr[j]` condition doesn't allow the same "count all remaining elements at once" shortcut used mid-merge in Count Inversions.
- The key insight enabling `O(N)` counting per level: the `right` pointer used in `countPairs` never resets as `i` advances through the left half — because both halves are sorted, once `right` has moved past a certain point for a smaller `i`, it will never need to move backward for a larger `i`.
- The counting pass must happen **before** the merge step, while both halves are still in their pre-merge sorted order — if counting were attempted after merging, the two sorted halves' relative positions would already be interleaved and lost.
- As with Count Inversions, this approach modifies (sorts) the original array as a side effect — this should be explicitly communicated to the interviewer, along with the option of operating on a copy of the array if the original order must be preserved.
- Avoid using a global variable to accumulate the count — thread the count through return values instead (summing the left half's count, right half's count, and the cross-pair count) for cleaner, interview-preferred code.

--------------------------------------------

## Interview Tips

- Explicitly connect this problem back to Count Inversions when presenting it — showing the interviewer that you recognize the shared merge-sort skeleton, while also explaining precisely why the counting logic must differ (the batch-counting shortcut doesn't apply the same way).
- Be ready to justify why the `right` pointer in the counting step never needs to reset or move backward — this non-obvious detail is what keeps the counting step at `O(N)` instead of `O(N^2)`.
- Emphasize that counting must happen as a separate step before the actual merge, not interleaved within it — a common mistake is trying to count during the merge itself, which doesn't work for this condition.
- As with the inversions problem, proactively mention that the input array gets modified (sorted), and offer to work on a copy if the interviewer prefers the original array untouched.

--------------------------------------------

## LeetCode

[493. Reverse Pairs](https://leetcode.com/problems/reverse-pairs/)