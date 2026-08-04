# 3Sum

## Problem Statement

Given an array of integers, find all triplets `(i, j, k)` such that `i != j`, `j != k`, `i != k`, and the sum of the three elements equals zero.

The returned triplets must be **unique** — no duplicate triplets are allowed in the output, even if they are formed from different indices. The order of triplets in the output does not matter.

## Example

```
Input:  nums = [-1, 0, 1, 2, -1, -4]
Output: [[-1, -1, 2], [-1, 0, 1]]
```

`[-1, 2, -1]` and `[-1, -1, 2]` are considered the same triplet (duplicates of each other) once sorted, so only one of them is kept.

## Intuition

A triplet has three positions to fill — a first, second, and third element. The naive idea is to try every possible combination of three elements and check whether they sum to zero, then filter out duplicate triplets.

To avoid duplicates, any triplet found can be sorted internally (e.g. `[-1, 2, -1]` → `[-1, -1, 2]`). Once sorted, two triplets made of the same three values will always look identical, so a `set` can be used to automatically discard repeats.

The insight that leads to better solutions: for a fixed pair `(i, j)`, the third value needed is exactly `-(nums[i] + nums[j])`. So instead of brute-forcing a third loop, we can search for that required value using hashing, or — if the array is sorted first — using a two-pointer sweep, which also naturally avoids duplicates without needing an extra `set`.

## Approach 1 : Brute Force

Try every possible triplet using three nested loops. For each triplet, check if it sums to zero. If it does, sort the triplet and insert it into a `set<vector<int>>` so that duplicate triplets (which become identical after sorting) are automatically filtered out. Finally, copy all triplets from the set into the answer list.

### Algorithm
1. Run three nested loops with indices `i`, `j`, `k` where `j` starts after `i` and `k` starts after `j`.
2. If `nums[i] + nums[j] + nums[k] == 0`, form the triplet `{nums[i], nums[j], nums[k]}`.
3. Sort the triplet and insert it into a `set` to remove duplicates.
4. Copy all elements of the set into the final answer list.

### Time Complexity
`O(N^3)` for the three nested loops, plus `O(log(M))` for each insertion into the set, where `M` is the number of unique triplets found so far. Overall: `O(N^3 * log M)`.

### Space Complexity
`O(2 * X)` where `X` is the number of unique triplets — once for the `set` used to filter duplicates, and once for the answer list that stores the final result.

--------------------------------------------

## Approach 2 : Better

Eliminate the third loop by using hashing. Fix `i` and `j` with two nested loops, and for each pair, the third value needed is `-(nums[i] + nums[j])`. Look this value up in a hash set built from the elements already seen between `i` and `j` (not the whole array), since the third value must come from a different index than `i` and `j`. If found, sort the triplet and insert it into an answer `set` to keep only unique triplets.

### Algorithm
1. For each `i` from `0` to `n - 1`:
   - Initialize an empty `hashSet` (reset for every new `i`).
   - For each `j` from `i + 1` to `n - 1`:
     - Compute `third = -(nums[i] + nums[j])`.
     - If `third` exists in `hashSet`, form the triplet `{nums[i], nums[j], third}`, sort it, and insert it into the answer `set`.
     - Insert `nums[j]` into `hashSet` (so future iterations of `j` can find it as a potential third element).
2. Copy all elements of the answer `set` into the final answer list.

### Time Complexity
`O(N^2)` for the two nested loops, multiplied by `O(log M)` for the hash set lookup/insert (`M` = size of the hash set at that point, effectively constant with an unordered set). Overall: approximately `O(N^2)`.

### Space Complexity
`O(N)` for the hash set used during the `i, j` loops, plus `O(2 * X)` for the answer set and the answer list, where `X` is the number of unique triplets.

--------------------------------------------

## Approach 3 : Optimal

Sort the array first. Fix the first element with a loop on `i`. Use two pointers — `j` starting right after `i`, and `k` starting at the end of the array — and move them toward each other based on whether the current sum is less than, greater than, or equal to zero. Because the array is sorted, duplicates can be skipped directly by comparing adjacent elements, removing the need for any extra `set` data structure.

### Algorithm
1. Sort the array.
2. For each `i` from `0` to `n - 1`:
   - Skip `i` if `nums[i] == nums[i - 1]` (to avoid duplicate triplets from repeated first elements).
   - Set `j = i + 1` and `k = n - 1`.
   - While `j < k`:
     - Compute `sum = nums[i] + nums[j] + nums[k]`.
     - If `sum < 0`, increment `j` (need a larger sum).
     - Else if `sum > 0`, decrement `k` (need a smaller sum).
     - Else (`sum == 0`):
       - Store the triplet `{nums[i], nums[j], nums[k]}`.
       - Move `j` forward while `nums[j] == nums[j - 1]` (skip duplicates).
       - Move `k` backward while `nums[k] == nums[k + 1]` (skip duplicates).
       - Then move both `j` and `k` one step further inward.

### Time Complexity
`O(N log N)` for sorting, plus `O(N^2)` for the outer loop combined with the two-pointer sweep. Overall: `O(N log N + N^2)`, which simplifies to `O(N^2)`.

### Space Complexity
`O(1)` extra space for the algorithm itself (no external hash set or filtering set is used), not counting the space required for the answer list which holds the unique triplets.

--------------------------------------------

## Dry Run

Sorted input: `[-4, -2, -2, -1, -1, 0, 0, 1, 2, 2]`

- `i = 0` (`-4`): `j = 1`, `k = 9` → sum too low/high, pointers move around, but no triplet sums to zero with `-4` as the fixed element in this particular pass.
- `i = 1` (`-2`): `j = 2`, `k = 9` → sum `= -2 + -2 + 2 = -2` (less than 0) → move `j`. Eventually `j` reaches `3` (`-1`), `k = 9` (`2`): sum `= -2 + -1 + 2 = -1` → still less than 0 → move `j` further. Eventually reaches sum `0` → triplet found: `{-2, 0, 2}`. Continue moving `j` and `k` inward, skipping duplicates, until `j` and `k` cross.
- `i = 3` (`-1`): `j = 4` (`-1`), `k = 9` (`2`) → sum `= -1 + -1 + 2 = 0` → triplet found: `{-1, -1, 2}`. Since `nums[j]` still equals the previous value, `j` and `k` are advanced carefully to avoid re-adding the same triplet.
- The sweep continues for remaining values of `i`, skipping any `i` equal to its previous value, until all unique triplets are collected: `{-2, 0, 2}`, `{-1, -1, 2}`, `{-1, 0, 1}` (and any others formed by the sorted array), each discovered exactly once due to the duplicate-skipping logic.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N^3 log M) | O(2 * X) |
| Better | O(N^2) | O(N) + O(2 * X) |
| Optimal | O(N^2) | O(1) (excluding answer list) |

*(X = number of unique triplets, M = size of the set at time of insertion)*

--------------------------------------------

## Key Observations

- A triplet is only valid if all three indices `i`, `j`, `k` are distinct — repeating the same index is not allowed even if the values happen to repeat.
- Sorting a triplet's values gives a canonical form, which is what makes duplicate detection possible using a `set`.
- In the Better approach, the hash set must be built incrementally between `i` and `j` only — using the whole array would risk picking the same index twice.
- In the Optimal approach, sorting the entire array upfront is what enables the two-pointer technique and the direct duplicate-skipping logic (no extra set needed).
- When `sum == 0` in the two-pointer approach, both `j` and `k` must be moved past all consecutive duplicate values before continuing, otherwise the same triplet gets added multiple times.

--------------------------------------------

## Interview Tips

- Start with the Brute Force approach to show you understand the base logic, then explain its `O(N^3)` drawback before moving to a better solution.
- Clearly explain *why* sorting the array is necessary for the two-pointer approach — it enables predictable, monotonic movement of `j` and `k`.
- Be ready to explain how duplicates are avoided in each approach — this is usually the interviewer's core follow-up question for 3Sum.
- Mention that the Optimal approach avoids extra space (aside from the output) unlike the Brute/Better approaches, which rely on a `set` for deduplication.

--------------------------------------------

## LeetCode

[15. 3Sum](https://leetcode.com/problems/3sum/)