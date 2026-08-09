# Floor And Ceil In A Sorted Array

## Problem Statement

Given a sorted array of integers and a value `x`, find the **floor** and **ceil** of `x` in the array.

- **Floor**: the largest number in the array that is less than or equal to `x`.
- **Ceil**: the smallest number in the array that is greater than or equal to `x`.

If no such number exists (e.g. `x` is smaller than every element for floor, or larger than every element for ceil), return `-1` for that value.

## Example

```
Input:  arr = [10, 20, 25, 30, 40, 50], x = 25
Output: floor = 25, ceil = 25
```

Explanation: `25` itself exists in the array, so both the floor and the ceil are `25`.

```
Input:  arr = [10, 20, 25, 30, 40, 50], x = 22
Output: floor = 20, ceil = 25
```

Explanation: `20` is the largest value `<= 22`, and `25` is the smallest value `>= 22`.

## Intuition

**Ceil** is exactly the definition of **Lower Bound**: the smallest value in the array that is greater than or equal to `x`. The only difference from the standard Lower Bound problem is that this problem asks for the *value* itself rather than its index.

**Floor** is the mirror image: instead of searching for the smallest value `>= x` and always moving left to find something smaller, the search looks for the largest value `<= x` and always moves right to find something even larger (but still valid) — since moving right in a sorted array always yields bigger values, there's no need to compare for "largest" explicitly; each new valid candidate found while moving right is automatically bigger than the last.

## Approach 1 : Brute Force

Scan the entire array once for each value. For floor, track the largest element seen so far that is `<= x`. For ceil, track the smallest element seen so far that is `>= x` (or simply return the first such element found, since a sorted array processed left-to-right hits the ceil condition at its smallest valid value first).

### Algorithm
1. Initialize `floor = -1` and `ceil = -1`.
2. For each index `i` from `0` to `n - 1`:
   - If `arr[i] <= x`, update `floor = arr[i]` (later, larger valid values overwrite earlier ones as the array is sorted).
   - If `arr[i] >= x` and `ceil == -1`, set `ceil = arr[i]` (the first such value found is the smallest, since the array is sorted).
3. Return `{floor, ceil}`.

### Time Complexity
`O(N)` — a single traversal of the array computes both floor and ceil.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal (Binary Search)

Use two separate Binary Searches, each following a mirrored version of the Lower Bound template.

**Ceil** (identical to Lower Bound, but returning the value instead of the index): track the smallest valid value found so far, moving left after finding a valid candidate to look for something smaller.

**Floor**: track the largest valid value found so far, moving right after finding a valid candidate — since moving right in a sorted array always yields larger values, there's no need to explicitly compare for "largest"; the most recently recorded candidate is always the current best.

### Algorithm

**Ceil:**
1. Initialize `low = 0`, `high = n - 1`, `ans = -1`.
2. While `low <= high`:
   - Compute `mid = low + (high - low) / 2`.
   - If `arr[mid] >= x`, this value may be the answer — set `ans = arr[mid]`, then search left: `high = mid - 1`.
   - Else, search right: `low = mid + 1`.
3. Return `ans`.

**Floor:**
1. Initialize `low = 0`, `high = n - 1`, `ans = -1`.
2. While `low <= high`:
   - Compute `mid = low + (high - low) / 2`.
   - If `arr[mid] <= x`, this value may be the answer — set `ans = arr[mid]`, then search right for something bigger (but still valid): `low = mid + 1`.
   - Else, search left: `high = mid - 1`.
3. Return `ans`.

### Time Complexity
`O(log N)` for each of floor and ceil, so `O(log N)` overall (two independent binary searches, not multiplicative).

### Space Complexity
`O(1)` — only a few variables are used, no extra data structures.

--------------------------------------------

## Dry Run

Input: `arr = [10, 20, 25, 30, 40, 50]`, `x = 22` (computing floor)

- `low = 0`, `high = 5`, `ans = -1`.
- `mid = 2`. `arr[2] = 25 <= 22`? No → search left → `high = 1`.
- `mid = 0`. `arr[0] = 10 <= 22`? Yes → possible answer → `ans = 10`, `low = 1`.
- `mid = 1`. `arr[1] = 20 <= 22`? Yes → possible answer → `ans = 20`, `low = 2`.
- `low = 2 > high = 1` → loop ends.
- Final floor: `20`.

Computing ceil for the same input:

- `low = 0`, `high = 5`, `ans = -1`.
- `mid = 2`. `arr[2] = 25 >= 22`? Yes → possible answer → `ans = 25`, `high = 1`.
- `mid = 0`. `arr[0] = 10 >= 22`? No → search right → `low = 1`.
- `mid = 1`. `arr[1] = 20 >= 22`? No → search right → `low = 2`.
- `low = 2 > high = 1` → loop ends.
- Final ceil: `25`.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N) | O(1) |
| Optimal (Binary Search) | O(log N) | O(1) |

--------------------------------------------

## Key Observations

- Ceil is exactly Lower Bound, just returning the value at the found index rather than the index itself.
- Floor is the mirror image of Lower Bound: instead of moving left after a valid candidate (to find something smaller), it moves right (to find something larger, while remaining `<= x`).
- When moving right after a valid floor candidate, there's no need to explicitly compare for "largest" — since the array is sorted, any later valid candidate encountered while moving right is guaranteed to be larger than the previous one.
- Both floor and ceil default to `-1` if no valid value exists — this happens when `x` is smaller than every element (no valid floor) or larger than every element (no valid ceil).
- When `x` itself is present in the array, floor and ceil both equal `x`.

--------------------------------------------

## Interview Tips

- Explicitly connect ceil to the previously-covered Lower Bound problem, and floor as its direct mirror — this shows the interviewer you're building on a reusable mental template rather than solving each problem from scratch.
- Clarify with the interviewer early on whether the expected return value is the array value or its index — the problem statement matters here, unlike Search Insert Position which strictly wants an index.
- Be ready to explain why floor doesn't need an explicit "is this bigger than my current best" comparison — the sortedness of the array guarantees it.
- Mention the `-1` default return value explicitly, and confirm with the interviewer what the expected behavior should be when no valid floor or ceil exists.

--------------------------------------------

## LeetCode

Not directly available as a standalone LeetCode problem; commonly listed as "Floor and Ceil in a sorted array" on GeeksforGeeks.