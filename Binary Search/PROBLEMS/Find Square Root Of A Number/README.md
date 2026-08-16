# Find Square Root Of A Number

## Problem Statement

Given an integer `n`, find and return the floor value of the square root of `n` — that is, the maximum integer whose square is less than or equal to `n`.

*(Note: this is the first problem in the "Binary Search on Answers" pattern — instead of searching over an array, Binary Search is applied directly over a range of possible answer values.)*

## Example

```
Input:  n = 28
Output: 5
```

Explanation: `5 * 5 = 25 <= 28`, but `6 * 6 = 36 > 28`. So `5` is the maximum integer whose square doesn't exceed `28`.

```
Input:  n = 36
Output: 6
```

Explanation: `6 * 6 = 36`, which is exactly `n`, so the floor of the square root is `6` itself.

## Intuition

The Brute Force approach checks `1, 2, 3, ...` in order, stopping as soon as a value's square exceeds `n` — the last valid value checked is the answer.

The key realization for the optimal approach: for any candidate integer `i`, either `i * i <= n` (a *possible* answer, since a bigger value might still work) or `i * i > n` (definitely *not* an answer, and neither is anything bigger than `i`, since squares only grow larger). This "possible up to a point, then definitely impossible beyond it" structure is exactly what makes Binary Search applicable — not on an array, but directly on the range of candidate answers from `1` to `n`. At each step, check whether `mid * mid <= n`: if true, record `mid` as a possible answer and search further right (to find an even bigger valid value); if false, discard `mid` and everything to its right, searching left instead. This pattern — searching over a range of integer answers using a check condition — is called **Binary Search on Answers**, and it generalizes to many problems beyond this one, wherever the problem asks for a minimum or maximum valid integer within a known range.

## Approach 1 : Brute Force

Check `1, 2, 3, ...` in increasing order, stopping as soon as a value's square exceeds `n`. The last value found valid is the answer.

### Algorithm
1. Initialize `ans = 1`.
2. For each `i` from `1` up to `n`:
   - If `i * i <= n`, update `ans = i` and continue.
   - Otherwise, break out of the loop (no larger value can be valid either).
3. Return `ans`.

### Time Complexity
`O(N)` in the general form of the loop (as it iterates candidate values one by one); in practice the loop terminates as soon as a value's square exceeds `n`, which happens well before `i` reaches `n` for larger inputs.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal (Binary Search on Answers)

Apply Binary Search directly over the range of candidate answers, from `1` to `n`. At each `mid`, check whether `mid * mid <= n`. If true, `mid` is a possible answer — record it and search further right for a bigger valid value. If false, `mid` (and everything larger) is definitely invalid — search left instead.

### Algorithm
1. Initialize `low = 1`, `high = n`, `ans = 1`.
2. While `low <= high`:
   - Compute `mid = low + (high - low) / 2`.
   - If `mid * mid <= n` (using a wide enough integer type to avoid overflow): this is a possible answer — set `ans = mid`, then search right for a bigger one: `low = mid + 1`.
   - Else: this value is too large — search left: `high = mid - 1`.
3. Return `ans` (equivalently, `high` also holds the answer once the loop ends, since `high` naturally converges to the last valid value while `low` converges to the first invalid value).

### Time Complexity
`O(log N)` — the search space is halved at every step, identical to standard Binary Search.

### Space Complexity
`O(1)` — only a few variables are used, no extra data structures.

--------------------------------------------

## Dry Run

Input: `n = 28`

- `low = 1`, `high = 28`, `ans = 1`.
- `mid = 14`. `14 * 14 = 196 > 28` → invalid → search left → `high = 13`.
- `mid = 7`. `7 * 7 = 49 > 28` → invalid → search left → `high = 6`.
- `mid = 3`. `3 * 3 = 9 <= 28` → possible answer → `ans = 3`, search right → `low = 4`.
- `mid = 5`. `5 * 5 = 25 <= 28` → possible answer → `ans = 5`, search right → `low = 6`.
- `mid = 6`. `6 * 6 = 36 > 28` → invalid → search left → `high = 5`.
- `low = 6 > high = 5` → loop ends.
- Final answer: `ans = 5` (and `high = 5` also holds the same value), matching the expected output.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N) | O(1) |
| Optimal (Binary Search on Answers) | O(log N) | O(1) |

--------------------------------------------

## Key Observations

- This problem introduces the **Binary Search on Answers** pattern: Binary Search applied over a range of candidate integer answers rather than over an array.
- The pattern applies whenever a problem has a clear "possible up to a point, then definitely impossible beyond it" (or vice versa) structure across a known range of integers — this is often phrased as finding a minimum or maximum valid integer.
- The check condition here (`mid * mid <= n`) is referred to as the "check function" — different Binary Search on Answers problems will have different check conditions, but the overall Binary Search skeleton stays the same.
- By the time the loop ends, `low` naturally points to the first invalid value, while `high` points to the last valid value (the answer) — this holds because `low` always advances past valid candidates while `high` always retreats past invalid ones.
- Always use a wide enough integer type (e.g. `long long`) when computing `mid * mid`, since squaring a large `n` (such as `10^9`) can overflow a standard 32-bit integer.

--------------------------------------------

## Interview Tips

- Explicitly name this as an instance of "Binary Search on Answers" when presenting the optimal solution — this framing helps interviewers see that you recognize a broader pattern, not just a one-off trick.
- Be ready to explain why checking `mid * mid <= n` and moving right (rather than stopping immediately) is necessary — the goal is to find the *maximum* valid integer, so a valid `mid` should prompt searching for something even bigger.
- Proactively flag the overflow risk when computing `mid * mid` for large inputs, and mention using `long long` — this is a commonly probed detail in interviews.
- Mention that both `ans` and `high` end up holding the correct final answer, and be ready to explain why, as it demonstrates a deeper understanding of how Binary Search converges.

--------------------------------------------

## LeetCode

[69. Sqrt(x)](https://leetcode.com/problems/sqrtx/)