# Maximum Product Subarray

## Problem Statement

Given an array of integers, find the maximum product that can be obtained from any sub array of the given array.

A sub array is defined as any **contiguous** part of the array — picking non-adjacent elements (like `2` and `-2` from non-neighboring positions) does not count as a sub array; that would be a subsequence instead.

## Example

```
Input:  arr = [2, 3, -2, 4]
Output: 6
```

Explanation: The sub array `[2, 3]` gives a product of `6`, which is the maximum product obtainable from any contiguous sub array of the given array.

## Intuition

The Brute Force approach generates every possible sub array and computes its product directly, tracking the maximum seen. This can be sped up slightly (Better approach) by computing the product incrementally as the sub array's end index expands, instead of recomputing it from scratch each time.

The key insight for the optimal approach comes from analyzing how negative numbers and zeros affect the product:
- If all elements are positive, multiplying everything gives the maximum product.
- If there is an **even** number of negative elements, multiplying everything still gives the maximum product (the negatives cancel out in sign).
- If there is an **odd** number of negative elements, one negative number must be excluded to make the product positive — and it turns out the best answer always comes from either a **prefix** (excluding some suffix) or a **suffix** (excluding some prefix) of the array — never from removing an element out of the middle.
- Zeros reset any running product to garbage (`0`), so wherever a zero appears, it effectively splits the array into independent segments — the answer can never span across a zero.

Combining these observations: computing a running prefix product (left to right) and a running suffix product (right to left) in parallel, and resetting either back to `1` whenever it hits `0`, is enough to find the maximum product sub array in a single linear pass.

## Approach 1 : Brute Force

Generate every possible sub array using three nested loops — two to fix the sub array's start and end indices, and a third to compute the product of the elements within that range. Track the maximum product seen across all sub arrays.

### Algorithm
1. Initialize `maximum = INT_MIN`.
2. For each `i` from `0` to `n - 1`:
   - For each `j` from `i` to `n - 1`:
     - Initialize `product = 1`.
     - For each `k` from `i` to `j`: multiply `product = product * arr[k]`.
     - Update `maximum = max(maximum, product)`.
3. Return `maximum`.

### Time Complexity
`O(N^3)` — three nested loops: two to generate every sub array's boundaries, and one to compute the product within each.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Better

Eliminate the third loop by observing that as the sub array's end index `j` expands for a fixed start `i`, the product only needs to be multiplied by the one new element added — instead of recomputing the entire product from scratch.

### Algorithm
1. Initialize `maximum = INT_MIN`.
2. For each `i` from `0` to `n - 1`:
   - Initialize `product = 1`.
   - For each `j` from `i` to `n - 1`:
     - Update `product = product * arr[j]` (incorporate the new element into the running product).
     - Update `maximum = max(maximum, product)`.
3. Return `maximum`.

### Time Complexity
`O(N^2)` — two nested loops, with the product computed incrementally instead of with a third loop.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 3 : Optimal (Prefix / Suffix Observation)

Traverse the array once while simultaneously maintaining a running prefix product (left to right) and a running suffix product (right to left). At each step, update the maximum with both the current prefix product and the current suffix product. Whenever either running product becomes `0`, reset it back to `1`, since a zero means the multiplication chain must restart from the next element — the sub array can never span across a zero.

### Algorithm
1. Initialize `prefix = 1`, `suffix = 1`, and `maximum = INT_MIN`.
2. For each `i` from `0` to `n - 1`:
   - If `prefix == 0`, reset `prefix = 1`.
   - If `suffix == 0`, reset `suffix = 1`.
   - Update `prefix = prefix * arr[i]` (multiplying elements from the front).
   - Update `suffix = suffix * arr[n - i - 1]` (multiplying elements from the back).
   - Update `maximum = max(maximum, max(prefix, suffix))`.
3. Return `maximum`.

### Time Complexity
`O(N)` — a single traversal of the array, computing both the prefix and suffix products simultaneously.

### Space Complexity
`O(1)` — only a handful of variables are used, no extra data structures.

--------------------------------------------

## Dry Run

Input: `arr = [2, 3, -2, 4]`

- Start: `prefix = 1`, `suffix = 1`, `maximum = INT_MIN`.
- `i = 0`: `prefix = 1 * 2 = 2`; `suffix = 1 * arr[3] = 1 * 4 = 4`. `maximum = max(2, 4) = 4`.
- `i = 1`: `prefix = 2 * 3 = 6`; `suffix = 4 * arr[2] = 4 * (-2) = -8`. `maximum = max(4, 6) = 6`.
- `i = 2`: `prefix = 6 * (-2) = -12`; `suffix = -8 * arr[1] = -8 * 3 = -24`. `maximum` remains `6`.
- `i = 3`: `prefix = -12 * 4 = -48`; `suffix = -24 * arr[0] = -24 * 2 = -48`. `maximum` remains `6`.
- Final answer: `maximum = 6`, matching the expected output — coming from the prefix `[2, 3]`.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N^3) | O(1) |
| Better | O(N^2) | O(1) |
| Optimal | O(N) | O(1) |

--------------------------------------------

## Key Observations

- If the array has an even number of negative elements (including zero negatives), multiplying every element gives the maximum product directly.
- If the array has an odd number of negative elements, the maximum product always comes from either a prefix (excluding some suffix) or a suffix (excluding some prefix) of the array — never from excluding an element out of the middle.
- Zeros act as natural dividers: wherever a running product hits `0`, it must be reset back to `1`, since the maximum-product sub array can never span across a zero.
- Computing the prefix and suffix products in a single combined pass (rather than two separate passes) is possible because the suffix index can be derived directly from the loop index using `n - i - 1`.
- This optimal solution is purely observation-driven and does not require memorizing any non-intuitive formula — an alternative approach exists using a modification of Kadane's Algorithm, but it is intentionally not covered here since it is far less intuitive to explain in an interview setting.

--------------------------------------------

## Interview Tips

- Present the observation-based optimal approach in the interview rather than any Kadane's-Algorithm-based variant — it has the same `O(N)` time complexity but is dramatically easier to explain and justify on the spot.
- Walk the interviewer through the reasoning step by step: start with the all-positive case, then even negatives, then odd negatives, then zeros — building up to the prefix/suffix insight naturally rather than stating it outright.
- Be ready to justify, with a small example, why the maximum product sub array (when there's an odd number of negatives) always aligns with a prefix or a suffix rather than an arbitrary middle segment.
- Mention explicitly why zeros require resetting the running product to `1` instead of `0` — carrying a `0` forward would incorrectly zero out every subsequent product in that pass.

--------------------------------------------

## LeetCode

[152. Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)