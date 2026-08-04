# 4Sum

## Problem Statement

Given an array of integers and a target value, find all quadruplets `(i, j, k, l)` with four **distinct indices** such that the sum of the elements at those indices equals the given `target`.

The returned quadruplets must be **unique** — no duplicate quadruplets are allowed in the output, even if they can be formed from different index orderings. The order of quadruplets in the output does not matter.

*(Note: this problem builds directly on 3Sum — the same duplicate-avoidance and two-pointer ideas are extended by one extra dimension.)*

## Example

```
Input:  nums = [1, 0, -1, 0, -2, 2], target = 0
Output: [[-2, -1, 1, 2], [-2, 0, 0, 2], [-1, 0, 0, 1]]
```

Picking the same four values in a different order (e.g. `[0, -1, 1, 0]` vs `[-1, 0, 0, 1]`) counts as the same quadruplet and must not be repeated in the output.

## Intuition

Just like 3Sum, the naive approach tries every possible combination of four elements and checks if they sum to the target, using a `set` to filter out duplicate quadruplets after sorting each one internally.

The key extension from 3Sum: for three fixed values `nums[i]`, `nums[j]`, `nums[k]`, the fourth required value is exactly `target - (nums[i] + nums[j] + nums[k])`. This value can be searched for using hashing (Better approach), or, once the array is sorted, using two pointers for the last two positions while the first two are fixed with loops (Optimal approach) — mirroring exactly how 3Sum fixes one index and two-pointers the rest, just extended by one more fixed index.

## Approach 1 : Brute Force

Try every possible quadruplet using four nested loops. For each quadruplet, check if it sums to the target. If it does, sort the quadruplet and insert it into a `set<vector<int>>` to automatically filter out duplicates. Finally, copy all quadruplets from the set into the answer list.

### Algorithm
1. Run four nested loops with indices `i`, `j`, `k`, `l`, each starting after the previous one.
2. Compute the sum carefully in `long long` to avoid integer overflow (`nums[i] + nums[j]`, then add `nums[k]`, then add `nums[l]`).
3. If the sum equals `target`, form the quadruplet `{nums[i], nums[j], nums[k], nums[l]}`.
4. Sort the quadruplet and insert it into a `set` to remove duplicates.
5. Copy all elements of the set into the final answer list.

### Time Complexity
`O(N^4)` for the four nested loops.

### Space Complexity
`O(2 * X)` where `X` is the number of unique quadruplets — one for the `set` used to filter duplicates, and one for the answer list. The temporary array used per quadruplet is a fixed size of 4, so it is treated as constant space.

--------------------------------------------

## Approach 2 : Better

Eliminate the last loop by using hashing. Fix `i`, `j`, `k` with three nested loops. For each triplet, the fourth value needed is `target - (nums[i] + nums[j] + nums[k])`. Look this value up in a hash set built only from the elements between `j` and `k` (not the entire array), since the fourth value must come from an index distinct from `i`, `j`, and `k`. If found, sort the quadruplet and insert it into an answer `set` to keep only unique quadruplets.

### Algorithm
1. For each `i` from `0` to `n - 1`:
   - For each `j` from `i + 1` to `n - 1`:
     - Initialize an empty `hashSet` (reset for every new `j`).
     - For each `k` from `j + 1` to `n - 1`:
       - Compute `sum = nums[i] + nums[j] + nums[k]` and `fourth = target - sum`.
       - If `fourth` exists in `hashSet`, form the quadruplet `{nums[i], nums[j], nums[k], fourth}`, sort it, and insert it into the answer `set`.
       - Insert `nums[k]` into `hashSet` (so future iterations of `k` can find it as a potential fourth element).
2. Copy all elements of the answer `set` into the final answer list.

### Time Complexity
`O(N^3)` for the three nested loops, multiplied by `O(log M)` for the hash set lookup/insert (`M` = size of the hash set at that point, effectively constant with an unordered set).

### Space Complexity
`O(N)` for the internal hash set (which, at most, could end up storing close to all array elements across its lifetime), plus `O(2 * X)` for the answer set and the answer list, where `X` is the number of unique quadruplets.

--------------------------------------------

## Approach 3 : Optimal

Sort the array first. Fix the first two elements using two nested loops (`i` and `j`), then use two pointers — `k` starting right after `j`, and `l` starting at the end of the array — moving them toward each other based on whether the current sum is less than, greater than, or equal to the target. Because the array is sorted, duplicates can be skipped directly by comparing against previous values, removing the need for any hash set or extra `set` data structure.

### Algorithm
1. Sort the array.
2. For each `i` from `0` to `n - 1`:
   - Skip `i` if `i > 0` and `nums[i] == nums[i - 1]` (avoid duplicate first elements).
   - For each `j` from `i + 1` to `n - 1`:
     - Skip `j` if `j > i + 1` and `nums[j] == nums[j - 1]` (avoid duplicate second elements).
     - Set `k = j + 1` and `l = n - 1`.
     - While `k < l`:
       - Compute `sum = nums[i] + nums[j] + nums[k] + nums[l]` (accumulated in `long long` to avoid overflow).
       - If `sum < target`, increment `k` (need a larger sum).
       - Else if `sum > target`, decrement `l` (need a smaller sum).
       - Else (`sum == target`):
         - Store the quadruplet `{nums[i], nums[j], nums[k], nums[l]}`.
         - Move `k` forward and `l` backward.
         - Skip duplicates: move `k` forward while `nums[k] == nums[k - 1]`, and move `l` backward while `nums[l] == nums[l + 1]`.

### Time Complexity
`O(N log N)` for sorting, plus `O(N^3)` for the two outer loops (`i`, `j`) combined with the two-pointer sweep (`k`, `l`), since at most every element is visited once by the pointers for each `(i, j)` pair. Overall: `O(N^3)`.

### Space Complexity
`O(1)` extra space for the algorithm itself (no hash set or filtering set is used), not counting the space required for the answer list which holds the unique quadruplets.

--------------------------------------------

## Dry Run

Sorted input: `[-2, -1, 0, 0, 1, 2]`, `target = 0`

- `i = 0` (`-2`), `j = 1` (`-1`): `k = 2`, `l = 5` → sum `= -2 + -1 + 0 + 2 = -1` → less than target → move `k`. Continue until `k = 4` (`1`): sum `= -2 + -1 + 1 + 2 = 0` → quadruplet found: `{-2, -1, 1, 2}`. Move `k` and `l` inward; they cross, loop ends for this `(i, j)`.
- `i = 0` (`-2`), `j = 2` (`0`): `k = 3` (`0`), `l = 5` (`2`) → sum `= -2 + 0 + 0 + 2 = 0` → quadruplet found: `{-2, 0, 0, 2}`. Move `k`, `l` inward; they cross.
- `i = 0` (`-2`), `j = 3` (`0`): skipped since `nums[j] == nums[j-1]` and `j > i + 1`.
- `i = 1` (`-1`), `j = 2` (`0`): `k = 3` (`0`), `l = 5` (`2`) → sum `= -1 + 0 + 0 + 2 = 1` → greater than target → move `l`. `k = 3`, `l = 4` (`1`) → sum `= -1 + 0 + 0 + 1 = 0` → quadruplet found: `{-1, 0, 0, 1}`. `k` and `l` cross; loop ends.
- Remaining `(i, j)` pairs either repeat duplicate values (skipped) or don't produce a valid sum, so the final unique quadruplets are: `{-2, -1, 1, 2}`, `{-2, 0, 0, 2}`, `{-1, 0, 0, 1}`.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N^4) | O(2 * X) |
| Better | O(N^3 log M) | O(N) + O(2 * X) |
| Optimal | O(N^3) | O(1) (excluding answer list) |

*(X = number of unique quadruplets, M = size of the hash set at time of insertion)*

--------------------------------------------

## Key Observations

- 4Sum directly extends the 3Sum pattern by one more fixed index — the Better approach hashes between the last two moving pointers, and the Optimal approach fixes two indices with loops and two-pointers the remaining two.
- The hash set in the Better approach must only include elements strictly between `j` and `k` (not the whole array), otherwise an index could be reused, violating the "four distinct indices" rule.
- Always compute large sums incrementally (`sum += nums[i]; sum += nums[j]; ...`) rather than in a single expression, to avoid integer overflow — the transcript explicitly uses `long long` for this reason.
- In the Optimal approach, duplicates must be skipped for **all four** positions: `i`, `j`, `k`, and `l`, each compared against its immediately previous value.
- Sorting the array upfront is what enables both the duplicate-skipping logic and the two-pointer technique — without it, neither approach works correctly.

--------------------------------------------

## Interview Tips

- Mention that 4Sum is a natural generalization of 3Sum — this shows the interviewer you recognize the underlying pattern rather than memorizing each problem separately.
- Be explicit about why `long long` is used for the running sum — with large integer values, four `int` additions can overflow, which is a common bug source.
- Explain clearly why the hash set (Better approach) is restricted to elements between the two moving loop variables rather than the entire array — this is a frequent follow-up question.
- Emphasize that the Optimal approach needs duplicate-skipping logic at every one of the four index levels, not just the outermost one.

--------------------------------------------

## LeetCode

[18. 4Sum](https://leetcode.com/problems/4sum/)