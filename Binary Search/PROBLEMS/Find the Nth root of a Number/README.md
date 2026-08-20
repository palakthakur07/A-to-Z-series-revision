# Find The Nth Root Of A Number M

## Problem Statement

Given two integers `n` and `m`, find the `n`th root of `m` — that is, find an integer `x` such that `x` raised to the power `n` equals `m` exactly. If no such integer exists, return `-1`.

## Example

```
Input:  n = 3, m = 27
Output: 3
```

Explanation: `3^3 = 27`.

```
Input:  n = 4, m = 69
Output: -1
```

Explanation: No integer, when raised to the power `4`, equals `69` exactly (`3^4 = 81` overshoots, `2^4 = 16` undershoots).

## Intuition

The Brute Force approach checks `1, 2, 3, ...` in order, computing each candidate raised to the power `n`, and stops as soon as either a match is found or the computed value exceeds `m` (since further increasing the candidate can only make the result even larger).

This "possible up to a point, then definitely impossible beyond it" structure is the same pattern seen in "Find Square Root of a Number" — making this a direct instance of **Binary Search on Answers**. The answer, if it exists, must lie between `1` and `m` (since `m` raised to any power `>= 1` is always at least `m`, and `1` is the smallest possible candidate). At each `mid`, check whether `mid^n` equals, is less than, or exceeds `m`, and narrow the search space accordingly.

A key implementation detail: directly computing `mid^n` can overflow even a `long long` for large inputs. Instead, the check function multiplies incrementally and stops early — the moment the running product exceeds `m`, there's no need to continue multiplying, since the final result would only be even larger.

## Approach 1 : Brute Force

Check `1, 2, 3, ...` in increasing order. For each candidate `i`, compute `i^n` incrementally (stopping early if it exceeds `m`). If it equals `m`, return `i`. If it's already exceeded `m`, no further candidate can work, so return `-1`.

### Algorithm
1. For each `i` from `1` to `m`:
   - Compute `i^n` incrementally, stopping early if the running product exceeds `m`.
   - If the result equals `m`, return `i`.
   - If the result exceeds `m`, break out of the loop (no larger `i` can work either).
2. Return `-1` if no valid `i` was found.

### Time Complexity
`O(M * N)` — up to `M` candidates checked, each requiring up to `N` multiplications in the worst case (or `O(M log N)` if a fast exponentiation method is used instead of a simple loop).

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal (Binary Search on Answers)

Apply Binary Search over the range `[1, m]`. At each `mid`, use an overflow-safe check function that incrementally multiplies `mid` by itself `n` times, stopping early if the running product exceeds `m`. Based on whether the result equals, is less than, or exceeds `m`, narrow the search space accordingly.

### Algorithm
1. Define a helper `check(mid, n, m)` that returns `1` if `mid^n == m`, `0` if `mid^n < m`, and `2` if `mid^n > m` — computed incrementally with early exit the moment the running product exceeds `m` (to avoid overflow).
2. Initialize `low = 1`, `high = m`.
3. While `low <= high`:
   - Compute `mid = low + (high - low) / 2`.
   - Call `result = check(mid, n, m)`.
   - If `result == 1`, return `mid` (exact match found).
   - Else if `result == 0` (too small): search right — `low = mid + 1`.
   - Else (`result == 2`, too large): search left — `high = mid - 1`.
4. Return `-1` if the loop ends without finding an exact match.

### Time Complexity
`O(N * log M)` — the search space `[1, m]` is halved at every Binary Search step (`O(log M)` steps), and each step's check function does up to `N` multiplications.

### Space Complexity
`O(1)` — only a few variables are used, no extra data structures.

--------------------------------------------

## Dry Run

Input: `n = 3`, `m = 27`

- `low = 1`, `high = 27`.
- `mid = 14`. `14^3` far exceeds `27` (exits early during incremental multiplication) → `result = 2` → search left → `high = 13`.
- `mid = 7`. `7^3 = 343 > 27` → `result = 2` → search left → `high = 6`.
- `mid = 3`. `3^3 = 27 == 27` → `result = 1` → return `3`.
- Final answer: `3`, matching the expected output.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(M * N) | O(1) |
| Optimal (Binary Search on Answers) | O(N log M) | O(1) |

--------------------------------------------

## Key Observations

- This problem directly extends the "Binary Search on Answers" pattern introduced in "Find Square Root of a Number" — the search range and check condition change, but the overall Binary Search skeleton stays identical.
- The check function must be overflow-safe: rather than computing `mid^n` directly (which can overflow even `long long` for large inputs), it multiplies incrementally and exits as soon as the running product exceeds `m`.
- Unlike the square-root problem (which asks for a floor value and therefore keeps searching right after finding a valid candidate), this problem asks for an *exact* match — so the search terminates immediately once `mid^n == m` is found, with no need to keep narrowing further.
- If no exact match is ever found by the time the search space is exhausted, the correct answer is `-1`, since the problem requires an exact `n`th root rather than a floor or ceiling approximation.

--------------------------------------------

## Interview Tips

- Proactively raise the overflow concern before being asked — explain why the check function multiplies incrementally with early exit rather than computing the full power directly.
- Contrast this problem with "Find Square Root of a Number" when explaining your approach — pointing out that this one requires an *exact* match (hence immediate return) rather than a floor value (which would require continuing to search for a better candidate).
- Be ready to state the time complexity precisely: `O(N log M)`, breaking down the `log M` from the Binary Search and the `N` from each check's incremental multiplication.
- Mention that the search range `[1, m]` is a safe, easy-to-justify choice, even though a tighter range could be derived for better constant-factor performance.

--------------------------------------------

## LeetCode

Not directly available as a standalone LeetCode problem; commonly listed as "N-th root of a number using binary search" on GeeksforGeeks.