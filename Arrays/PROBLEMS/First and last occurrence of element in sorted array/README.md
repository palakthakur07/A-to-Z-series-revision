# First and Last Occurrence of an Element in a Sorted Array

## Problem Statement
Given a sorted array of `N` integers and an integer `X`, find the first and the last occurrence (index) of `X` in the array.
If `X` does not exist in the array, return `{-1, -1}`.

## Example
Array: `[3, 4, 8, 8, 8, 8, 11, 11]`

- If `X = 8` → First occurrence = index 3, Last occurrence = index 5
- If `X = 10` → Not present → return `{-1, -1}`
- If `X = 11` → Only one occurrence → First = 6, Last = 6

## Intuition
The most obvious idea is to linearly scan the array and keep track of the first time and the last time we see `X`. Since this doesn't use the fact that the array is sorted, it takes `O(N)` time.

Since the array is sorted, whenever we need to search for something in a sorted array, we should think of **Binary Search**. Two ways to apply binary search here:
1. Use the **Lower Bound** and **Upper Bound** concepts already built in previous lectures.
2. Write a **plain binary search from scratch** (without relying on lower/upper bound) — because some interviewers specifically don't want you to use the lower bound trick and want to see you derive binary search directly.

For the lower/upper bound approach:
- `lowerBound(X)` gives the smallest index where `arr[index] >= X`.
- `upperBound(X)` gives the smallest index where `arr[index] > X`.

So:
- First occurrence = `lowerBound(X)`, but only if that index actually contains `X` (otherwise `X` doesn't exist).
- Last occurrence = `upperBound(X) - 1`.

Edge cases to check before trusting `lowerBound(X)` as the first occurrence:
- If `lowerBound(X)` returns `N` (points past the end), `X` is not present.
- If `arr[lowerBound(X)] != X`, `X` is not present.

## Approach 1 : Brute Force
### Explain
Traverse the entire array from index `0` to `N-1`. Maintain `first` and `last`, both initialized to `-1`.
- Whenever `arr[i] == X`:
  - If `first == -1`, set `first = i` (this is the first time we found X).
  - Always update `last = i` (keeps updating till the last matching index).

### Algorithm
1. Initialize `first = -1`, `last = -1`.
2. Loop `i` from `0` to `N-1`:
   - If `arr[i] == X`:
     - If `first == -1`, set `first = i`.
     - Set `last = i`.
3. Return `{first, last}`.

### Time Complexity
`O(N)` — single linear traversal of the array.

### Space Complexity
`O(1)` — no extra space used.

## Approach 2 : Better (Using Lower Bound & Upper Bound)
### Explain
Since the array is sorted, we can binary search for boundaries instead of scanning linearly.
- `first = lowerBound(arr, N, X)` — smallest index where `arr[index] >= X`.
- Before trusting this as the answer, check whether it's a valid occurrence: if `lowerBound` returns `N`, or `arr[lowerBound] != X`, then `X` is not present, so return `{-1, -1}`.
- Otherwise, `last = upperBound(arr, N, X) - 1`.

### Algorithm
1. Call `lb = lowerBound(arr, N, X)`.
2. If `lb == N` or `arr[lb] != X`, return `{-1, -1}` (element does not exist).
3. Otherwise, `first = lb`.
4. Call `ub = upperBound(arr, N, X)`.
5. `last = ub - 1`.
6. Return `{first, last}`.

### Time Complexity
`O(2 * log N)` — one binary search for lower bound, one for upper bound.

### Space Complexity
`O(1)` — no extra space used.

## Approach 3 : Optimal (Plain Binary Search from Scratch)
### Explain
Instead of relying on prewritten lower bound / upper bound functions, we write two separate binary searches directly:

**Finding the first occurrence:**
- Standard binary search with `low = 0`, `high = N-1`.
- Whenever `arr[mid] == X`, record `first = mid`, but since we want the *first* occurrence, keep searching on the **left half** by setting `high = mid - 1` (don't stop immediately).
- If `arr[mid] < X`, move `low = mid + 1` (search right).
- If `arr[mid] > X`, move `high = mid - 1` (search left).

**Finding the last occurrence:**
- Same standard binary search setup.
- Whenever `arr[mid] == X`, record `last = mid`, but since we want the *last* occurrence, keep searching on the **right half** by setting `low = mid + 1`.
- If `arr[mid] < X`, move `low = mid + 1`.
- If `arr[mid] > X`, move `high = mid - 1`.

Important optimization: always call the "find first occurrence" function first. If it returns `-1` (not found), immediately return `{-1, -1}` without wasting another `O(log N)` search for the last occurrence — if the first occurrence doesn't exist, the last cannot exist either.

### Algorithm
**findFirst(arr, N, X):**
1. `low = 0`, `high = N - 1`, `first = -1`.
2. While `low <= high`:
   - `mid = low + (high - low) / 2`.
   - If `arr[mid] == X`: set `first = mid`, then `high = mid - 1` (look further left).
   - Else if `arr[mid] < X`: `low = mid + 1`.
   - Else: `high = mid - 1`.
3. Return `first`.

**findLast(arr, N, X):**
1. `low = 0`, `high = N - 1`, `last = -1`.
2. While `low <= high`:
   - `mid = low + (high - low) / 2`.
   - If `arr[mid] == X`: set `last = mid`, then `low = mid + 1` (look further right).
   - Else if `arr[mid] < X`: `low = mid + 1`.
   - Else: `high = mid - 1`.
3. Return `last`.

**Main function:**
1. `first = findFirst(arr, N, X)`.
2. If `first == -1`, return `{-1, -1}`.
3. `last = findLast(arr, N, X)`.
4. Return `{first, last}`.

### Time Complexity
`O(2 * log N)` — one binary search to find the first occurrence, one binary search to find the last occurrence.

### Space Complexity
`O(1)` — no extra space used.

## Dry Run
Array (0-indexed): `[3, 4, 8, 8, 8, 8, 11, 11]`, `X = 8`

**Finding first occurrence:**
| Step | low | high | mid | arr[mid] | Action | first |
|---|---|---|---|---|---|---|
| 1 | 0 | 7 | 3 | 8 | match → go left, `high = 2` | 3 |
| 2 | 0 | 2 | 1 | 4 | `4 < 8` → go right, `low = 2` | 3 |
| 3 | 2 | 2 | 2 | 8 | match → go left, `high = 1` | 2 |
| — | 2 | 1 | — | — | `low > high`, loop ends | **2** |

**First occurrence = 2**

**Finding last occurrence:**
| Step | low | high | mid | arr[mid] | Action | last |
|---|---|---|---|---|---|---|
| 1 | 0 | 7 | 3 | 8 | match → go right, `low = 4` | 3 |
| 2 | 4 | 7 | 5 | 8 | match → go right, `low = 6` | 5 |
| 3 | 6 | 7 | 6 | 11 | `11 > 8` → go left, `high = 5` | 5 |
| — | 6 | 5 | — | — | `low > high`, loop ends | **5** |

**Last occurrence = 5**

Final answer: `{first = 2, last = 5}`

## Comparison Table
| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N) | O(1) |
| Better (Lower/Upper Bound) | O(2 log N) | O(1) |
| Optimal (Plain Binary Search) | O(2 log N) | O(1) |

## Key Observations
- Whenever the array is sorted and you need to "search" for something, think **Binary Search**.
- Lower Bound = smallest index where `arr[index] >= X`.
- Upper Bound = smallest index where `arr[index] > X`.
- Always validate that the lower bound index actually contains `X` before treating it as the first occurrence — it might point to a hypothetical/non-existing position.
- When searching for the first occurrence in plain binary search, keep moving `high` left even after finding a match, to find an earlier one.
- When searching for the last occurrence, keep moving `low` right even after finding a match, to find a later one.
- Always find the first occurrence before attempting to find the last occurrence — if first doesn't exist, don't waste another `O(log N)` search.

## Interview Tips
- If the interviewer is fine with reusing Lower Bound / Upper Bound helper functions, that approach is fast to write and easy to explain.
- If the interviewer explicitly asks you not to use lower/upper bound, be ready to write the plain binary search version from scratch for both first and last occurrence.
- Don't forget the edge case check (`lowerBound == N` or `arr[lowerBound] != X`) — this is a common place candidates lose marks.

## LeetCode
[34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)