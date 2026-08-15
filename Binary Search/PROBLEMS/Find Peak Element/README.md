# Find Peak Element

## Problem Statement

Given an array of integers, find a peak element and return it. An element at index `i` is a peak if it is **strictly greater** than both its left and right neighbors. The array is conceptually bounded by `-infinity` on both the left of the first element and the right of the last element — meaning the first or last element can qualify as a peak by only needing to beat its one existing neighbor. The array may contain multiple peaks, in which case returning any one of them is acceptable. It is guaranteed that at least one peak always exists. Consecutive elements in the array are never equal.

## Example

```
Input:  arr = [1, 2, 3, 4, 5, 6, 7, 8, 5, 1]
Output: 8
```

Explanation: `8` is greater than both its neighbors (`7` and `5`), making it a peak.

```
Input:  arr = [1, 2, 1, 3, 5, 6, 4]
Output: 2 or 6 (either is acceptable)
```

Explanation: Both `2` (greater than `1` and `1`) and `6` (greater than `5` and `4`) are valid peaks.

## Intuition

The Brute Force approach checks every index directly against its neighbors, treating the boundary as `-infinity` where a neighbor doesn't exist.

The optimal approach uses Binary Search, motivated by the fact that the array always has a "sorted tendency" — it alternates between increasing and decreasing stretches. At any `mid` position: if `mid` is a peak, return it immediately. If `arr[mid] < arr[mid + 1]` (the curve is increasing at this point), a peak is guaranteed to exist somewhere to the right — so the left half can be eliminated. If `arr[mid] > arr[mid + 1]` (the curve is decreasing), a peak is guaranteed to exist somewhere to the left — so the right half can be eliminated. This works correctly even when there are multiple peaks in the array, because eliminating a half based on the increasing/decreasing direction only ever discards a portion that is guaranteed to still have a peak on the *other* side — the discarded half is never the one that could contain the last remaining peak. To avoid excessive boundary-check conditions for the first and last elements (which only have one real neighbor each), those two cases are checked separately up front, and the Binary Search only operates on the trimmed range from index `1` to `n - 2`.

## Approach 1 : Brute Force

Scan every index and check it against its existing neighbor(s), treating a missing neighbor (at the boundaries) as `-infinity`.

### Algorithm
1. For each index `i` from `0` to `n - 1`:
   - Check the left condition: if `i == 0`, treat it as satisfied (left is `-infinity`); otherwise check `arr[i - 1] < arr[i]`.
   - Check the right condition: if `i == n - 1`, treat it as satisfied (right is `-infinity`); otherwise check `arr[i] > arr[i + 1]`.
   - If both conditions hold, return `arr[i]` (or index `i`, depending on what's required).

### Time Complexity
`O(N)` — in the worst case, every element is checked.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal (Binary Search)

Handle the single-element array case, and the first and last elements, as separate special cases up front — this avoids ever needing to check `arr[-1]` or `arr[n]`. Then run Binary Search over the trimmed range `[1, n - 2]`: at each `mid`, check directly if it's a peak; if `arr[mid] < arr[mid + 1]` (increasing), eliminate the left half; if `arr[mid] > arr[mid + 1]` (decreasing), eliminate the right half. This same logic correctly handles arrays with multiple peaks, since eliminating a half always discards a region that's guaranteed not to contain the only remaining candidate peak.

### Algorithm
1. If `n == 1`, return `arr[0]` (a single-element array's only element is trivially a peak).
2. If `arr[0] > arr[1]`, return `arr[0]` (the first element is a peak).
3. If `arr[n - 1] > arr[n - 2]`, return `arr[n - 1]` (the last element is a peak).
4. Initialize `low = 1`, `high = n - 2`.
5. While `low <= high`:
   - Compute `mid = low + (high - low) / 2`.
   - If `arr[mid] > arr[mid - 1]` and `arr[mid] > arr[mid + 1]`, return `arr[mid]` (found a peak).
   - Else if `arr[mid] > arr[mid - 1]` (on an increasing curve): eliminate the left half — search right: `low = mid + 1`.
   - Else if `arr[mid] > arr[mid + 1]` (on a decreasing curve): eliminate the right half — search left: `high = mid - 1`.
   - Else (neither condition holds — `mid` sits at a local minimum / valley between two peaks): a peak is guaranteed to exist on either side, so either direction is safe to search — search right: `low = mid + 1`.
6. (Unreachable, since a peak is guaranteed to exist) return a dummy value such as `-1`.

### Time Complexity
`O(log N)` — the search space is halved at every step, identical to standard Binary Search.

### Space Complexity
`O(1)` — only a few variables are used, no extra data structures.

--------------------------------------------

## Dry Run

Input: `arr = [1, 2, 1, 3, 5, 6, 4]`

- `n = 7`. `arr[0] = 1 > arr[1] = 2`? No. `arr[6] = 4 > arr[5] = 6`? No.
- `low = 1`, `high = 5`.
- `mid = 3`. `arr[3] = 3`. Is it a peak? `arr[3] > arr[2] = 1`? Yes. `arr[3] > arr[4] = 5`? No — not a peak. `arr[3] > arr[2]`? Yes (increasing) → eliminate left → `low = 4`.
- `low = 4`, `high = 5`. `mid = 4`. `arr[4] = 5`. Is it a peak? `arr[4] > arr[3] = 3`? Yes. `arr[4] > arr[5] = 6`? No — not a peak. `arr[4] > arr[3]`? Yes (increasing) → eliminate left → `low = 5`.
- `low = 5`, `high = 5`. `mid = 5`. `arr[5] = 6`. Is it a peak? `arr[5] > arr[4] = 5`? Yes. `arr[5] > arr[6] = 4`? Yes → peak found.
- Return `6`.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N) | O(1) |
| Optimal (Binary Search) | O(log N) | O(1) |

--------------------------------------------

## Key Observations

- The array's implicit `-infinity` boundaries guarantee that a peak always exists, no matter the array's contents — even a strictly increasing or strictly decreasing array has a peak at one of its ends.
- On an increasing curve at `mid`, a peak is guaranteed somewhere to the right; on a decreasing curve, a peak is guaranteed somewhere to the left — this is the property that makes Binary Search elimination valid.
- This elimination logic works correctly even with multiple peaks in the array, because discarding a half based on the increasing/decreasing direction never discards the half that could contain the sole remaining peak candidate — the retained half is always guaranteed to still contain at least one peak.
- The "valley" case (where `mid` is smaller than both neighbors) requires an explicit fallback — searching in either direction is safe, since both sides are guaranteed to contain a peak in that scenario.
- Handling the first and last elements as separate special cases (rather than inside the main loop) avoids extra boundary-check conditions for out-of-range neighbor access, keeping the core Binary Search loop clean.

--------------------------------------------

## Interview Tips

- Frame the solution visually — describe the array as a sequence of increasing and decreasing "curves," and explain that Binary Search works because eliminating a half based on slope direction never discards the only remaining peak.
- Be ready to explain why the algorithm still works correctly with multiple peaks — this is a common follow-up question, and the key argument is that the retained half is always guaranteed to still contain a peak.
- Proactively mention the "valley" edge case (`mid` smaller than both neighbors) and how it's handled — many candidates miss this case and end up with an infinite loop.
- As with the "Single Element in a Sorted Array" problem, mention the deliberate choice to handle the first and last elements as special cases up front, to avoid extra boundary-check conditions inside the main Binary Search loop.

--------------------------------------------

## LeetCode

[162. Find Peak Element](https://leetcode.com/problems/find-peak-element/)