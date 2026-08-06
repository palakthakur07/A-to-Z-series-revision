Sure — here's the full content as plain text:

markdown
# Find The Repeating And Missing Number

## Problem Statement

Given an array of `n` integers, where the integers are meant to contain every number from `1` to `n` exactly once, but due to a data error one number is **repeated** (appears twice) and another number is **missing** (appears zero times). Find and return the repeating number and the missing number.

## Example
Input: arr = [4, 3, 6, 2, 1, 1], n = 6
Output: repeating = 1, missing = 5


Explanation: Numbers `1` through `6` should each appear exactly once. `1` appears twice (the repeating number), and `5` doesn't appear at all (the missing number).

## Intuition

Since every number from `1` to `n` should appear exactly once, the simplest idea is to count how many times each number from `1` to `n` actually appears in the array — a count of `2` marks the repeating number, and a count of `0` marks the missing number. This counting idea can be sped up using hashing (Better approach). Beyond that, two optimal approaches exist: one uses algebraic equations built from the sum and sum-of-squares of the array versus the expected sum and sum-of-squares of `1` to `n`, and the other uses XOR's self-cancelling property (similar in spirit to the classic "find the single non-repeating element" trick) to isolate the two unknown numbers without any extra space.

## Approach 1 : Brute Force

For each number `i` from `1` to `n`, iterate through the entire array and count how many times `i` appears. If it appears twice, `i` is the repeating number. If it appears zero times, `i` is the missing number. Stop early once both numbers have been found.

### Algorithm
1. Initialize `repeating = -1` and `missing = -1`.
2. For each `i` from `1` to `n`:
   - Initialize `counter = 0`.
   - For each `j` from `0` to `n - 1`: if `array[j] == i`, increment `counter`.
   - If `counter == 2`, set `repeating = i`.
   - Else if `counter == 0`, set `missing = i`.
   - If both `repeating != -1` and `missing != -1`, break out of the outer loop.
3. Return `{repeating, missing}`.

### Time Complexity
`O(N^2)` — an outer loop over `1` to `n`, combined with an inner loop over the entire array for each candidate number.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Better

Use a hash array of size `n + 1` to count how many times each number from `1` to `n` appears in a single traversal of the input array. Then iterate from `1` to `n`: a hash count of `2` marks the repeating number, and a hash count of `0` marks the missing number.

### Algorithm
1. Create a hash array `hash` of size `n + 1`, initialized to all `0`s.
2. Traverse the input array once: for each element `array[i]`, increment `hash[array[i]]`.
3. Initialize `repeating = -1` and `missing = -1`.
4. For each `i` from `1` to `n`:
   - If `hash[i] == 2`, set `repeating = i`.
   - Else if `hash[i] == 0`, set `missing = i`.
5. Return `{repeating, missing}`.

### Time Complexity
`O(N)` — one pass to build the hash array, and another pass of size `N` to scan from `1` to `n`. Overall: `O(N)`.

### Space Complexity
`O(N)` — for the hash array used to count occurrences.

--------------------------------------------

## Approach 3 : Optimal (Mathematics)

Let `x` be the repeating number and `y` be the missing number. Compute the sum of all array elements (`S`) and compare it against the expected sum of `1` to `n` (`Sn = n(n+1)/2`). The difference `S - Sn` equals `x - y`, since `x` is counted an extra time and `y` isn't counted at all. This gives one equation, but two unknowns need two equations — so also compute the sum of squares of all array elements (`S2`) and compare it against the expected sum of squares of `1` to `n` (`S2n = n(n+1)(2n+1)/6`). The difference `S2 - S2n` equals `x^2 - y^2`, which factors as `(x - y)(x + y)`. Dividing this by the first equation's result (`x - y`) isolates `x + y`. With both `x - y` and `x + y` known, standard algebra yields `x` and `y`.

### Algorithm
1. Compute `S` = sum of all elements in the array (using `long long` to avoid overflow).
2. Compute `Sn = n * (n + 1) / 2`.
3. Compute `S2` = sum of squares of all elements in the array (using `long long` to avoid overflow).
4. Compute `S2n = n * (n + 1) * (2 * n + 1) / 6`.
5. Compute `val1 = S - Sn` (this equals `x - y`).
6. Compute `val2 = (S2 - S2n) / val1` (this equals `x + y`, obtained by dividing `x^2 - y^2` by `x - y`).
7. Compute `x = (val1 + val2) / 2`.
8. Compute `y = x - val1`.
9. Return `{x, y}` (`x` is the repeating number, `y` is the missing number).

### Time Complexity
`O(N)` — a single pass through the array to compute `S` and `S2`; everything else is constant-time arithmetic.

### Space Complexity
`O(1)` — only a few `long long` variables are used, no extra data structures.

--------------------------------------------

## Approach 4 : Optimal (XOR Method)

XOR every element of the array together with every number from `1` to `n`. Since matching pairs cancel out (`a ^ a = 0`), everything that appears an even number of times disappears, leaving `x ^ y` (the XOR of the repeating and missing numbers) in a variable `xr`. Since `x` and `y` are different numbers, they must differ in at least one bit — find that rightmost differentiating (set) bit in `xr`. Use that bit to partition both the array's elements and the numbers `1` to `n` into two groups: those with that bit set, and those without. XOR each group separately (rather than storing values) — every number that appears twice will fully cancel within its group, leaving exactly one survivor per group: `x` in one group and `y` in the other. Finally, do one more pass through the original array to check which of the two survivors actually appears twice — that one is the repeating number, and the other is the missing number.

### Algorithm
1. Initialize `xr = 0`.
2. XOR `xr` with every element of the array, then XOR `xr` with every number from `1` to `n`. Now `xr = x ^ y`.
3. Find the rightmost set bit of `xr` (the differentiating bit) — call it `bitNumber`. This can be found by checking, starting from bit `0`, whether `xr & (1 << bitNumber)` is non-zero, or directly via `xr & (~(xr - 1))`.
4. Initialize `zero = 0` and `one = 0` (the two group accumulators).
5. For every element in the array: if the `bitNumber`-th bit of the element is set, XOR it into `one`; otherwise, XOR it into `zero`.
6. For every number from `1` to `n`: if the `bitNumber`-th bit of the number is set, XOR it into `one`; otherwise, XOR it into `zero`.
7. Now `zero` and `one` hold `x` and `y` in some order. To determine which is which, traverse the array once more and count how many times the value stored in `zero` appears.
8. If it appears twice, `zero` is the repeating number and `one` is the missing number; otherwise, `one` is the repeating number and `zero` is the missing number.
9. Return `{repeating, missing}`.

### Time Complexity
`O(N)` — a constant number of passes through the array (to compute `xr`, to partition into `zero`/`one`, and to determine which is repeating), plus `O(N)` work for the loop from `1` to `n`. Overall: `O(N)`.

### Space Complexity
`O(1)` — only a handful of variables are used, no extra buckets or arrays.

--------------------------------------------

## Dry Run

Input: `arr = [4, 3, 6, 2, 1, 1]`, `n = 6` (using the XOR Method)

- `xr = 4^3^6^2^1^1^1^2^3^4^5^6`. All numbers except `1` (appears 3 times total) and `5` (appears once total) cancel out in pairs → `xr = 1 ^ 1 ^ 1 ^ 5`. Since `1^1 = 0`, this reduces to `xr = 1 ^ 5 = 4` (binary `100`).
- The rightmost (and only) set bit of `4` is at bit position `2` → `bitNumber = 2`.
- Partition array elements `[4,3,6,2,1,1]` and numbers `[1,2,3,4,5,6]` by whether bit `2` is set:
  - Bit `2` set (value `4` in that position): `4` (`100`), `6` (`110`), `5` (`101`) → XOR-ed together into `one`.
  - Bit `2` not set: `3` (`011`), `2` (`010`), `1` (`001`), `1` (`001`), `1` (`001`), `2` (`010`), `3` (`011`) → XOR-ed together into `zero`.
- After XOR-ing each group, matching pairs cancel: `one` ends up as `1` (since only `1` survives in its group after all array/number pairs cancel — following the logic above), and `zero` ends up as `5`. *(Groups are determined by the transcript's method: each group's survivor is whichever of `x` or `y` falls into it.)*
- A final pass through the array checks whether the value in one group appears twice — `1` appears twice in the array, confirming `1` is the repeating number, and `5` is the missing number.
- Final answer: `repeating = 1`, `missing = 5`.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N^2) | O(1) |
| Better | O(N) | O(N) |
| Optimal (Mathematics) | O(N) | O(1) |
| Optimal (XOR Method) | O(N) | O(1) |

--------------------------------------------

## Key Observations

- Both optimal approaches reduce the problem to solving for two unknowns (`x` = repeating, `y` = missing) using two independent relationships — the mathematics approach uses sum and sum-of-squares, while the XOR approach uses bit-level cancellation.
- In the Mathematics approach, always use `long long` for sums and sum-of-squares, since these values can exceed the range of a regular `int` for larger arrays.
- The XOR approach hinges on one guaranteed fact: two different numbers must differ in at least one bit, so there is always a valid differentiating bit to partition on.
- After partitioning by the differentiating bit, every number that appears an even number of times cancels out within its group — leaving exactly one of `x` or `y` in each group.
- The XOR approach requires one final confirmation pass through the array to determine which of the two survivors is actually the repeating number, since the partitioning alone doesn't reveal which group holds which.

--------------------------------------------

## Interview Tips

- Present the Brute Force and Better (hashing) approaches quickly, then pivot to at least one optimal solution — the Mathematics approach is generally easier to explain and is sufficient for most interviews.
- If asked to further optimize space beyond the Better approach, be ready to derive the two algebraic equations (`x - y` from sums, `x + y` from sum-of-squares divided by the first result) live.
- The XOR Method is more advanced and not required in most interviews, but mentioning it shows deeper problem-solving ability if time permits or if the interviewer specifically wants a bit-manipulation-based solution.
- Be explicit about why the final "confirmation pass" is necessary in the XOR Method — without it, there's no way to know which of the two isolated values is the repeating number versus the missing number.

--------------------------------------------

## LeetCode

This problem is commonly listed as "Find the repeating and missing numbers" on GeeksforGeeks; no direct LeetCode link was mentioned in the transcript.


