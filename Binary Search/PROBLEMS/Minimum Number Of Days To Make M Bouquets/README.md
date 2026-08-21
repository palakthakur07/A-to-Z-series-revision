# Minimum Number Of Days To Make M Bouquets

## Problem Statement

Given an array `bloomDay` where `bloomDay[i]` represents the day on which the `i`th flower blooms, along with integers `m` (number of bouquets needed) and `k` (number of **adjacent** flowers required per bouquet), find the minimum number of days needed to be able to make `m` bouquets. Each bouquet must use `k` adjacent (contiguous) flowers that have already bloomed by that day. If it is impossible to make `m` bouquets under any number of days, return `-1`.

## Example

```
Input:  bloomDay = [7, 13, 12], m = 2, k = 1
Output: 12
```

Explanation: On day `12`, flowers at indices `0` and `2` have bloomed (`7 <= 12` and `12 <= 12`), and each bouquet only needs `1` flower, so `2` bouquets can be made. Day `11` doesn't work, since only one flower has bloomed by then.

## Intuition

The Brute Force approach checks every candidate day starting from the minimum bloom day up to the maximum bloom day, and for each day, checks whether enough adjacent-bloomed groups exist to form `m` bouquets.

Before anything else, one impossibility check must be handled: if `m * k > n` (the total flowers needed exceeds the total flowers available), it is never possible to make `m` bouquets, regardless of how many days are waited — since even if every flower blooms, there still aren't enough of them. In every other case, waiting long enough (up to the maximum bloom day) guarantees success, since every flower will have bloomed and adjacent groups can always be picked. This "impossible below a threshold, possible from that threshold onward" structure is exactly what enables **Binary Search on Answers**: search over the range `[min(bloomDay), max(bloomDay)]`, using a "possible on this day?" check function to narrow down to the minimum valid day.

## Approach 1 : Brute Force

First check the impossibility condition (`m * k > n`). Otherwise, try every day from `min(bloomDay)` to `max(bloomDay)` in increasing order, and return the first day for which the "possible" check succeeds.

### Algorithm
1. Define `possible(bloomDay, day, m, k)`:
   - Initialize `count = 0` (consecutive bloomed flowers) and `bouquets = 0`.
   - For each flower in `bloomDay`:
     - If `flower <= day` (it has bloomed), increment `count`.
     - Else: add `count / k` to `bouquets` (form as many bouquets as possible from the consecutive run), then reset `count = 0`.
   - After the loop, add `count / k` to `bouquets` one more time (to account for a trailing consecutive run that reaches the end of the array).
   - Return `true` if `bouquets >= m`, else `false`.
2. If `(long long) m * k > n`, return `-1` (impossible — not enough flowers exist in total).
3. For each `day` from `min(bloomDay)` to `max(bloomDay)`:
   - If `possible(bloomDay, day, m, k)`, return `day`.
4. Return `-1` if no valid day was found (should not happen if the impossibility check above passed).

### Time Complexity
`O((Max - Min) * N)` — up to `(Max - Min)` candidate days are checked, each requiring an `O(N)` pass through the array via the `possible` function.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal (Binary Search on Answers)

Apply Binary Search over the range `[min(bloomDay), max(bloomDay)]`, using the same `possible` check function. At each `mid`, if it's possible to form `m` bouquets by that day, record it as a candidate answer and search left for an even smaller valid day; otherwise, search right for a larger day.

### Algorithm
1. If `(long long) m * k > n`, return `-1` (impossible).
2. Initialize `low = min(bloomDay)`, `high = max(bloomDay)`.
3. While `low <= high`:
   - Compute `mid = low + (high - low) / 2`.
   - If `possible(bloomDay, mid, m, k)`: this day works — search left for a smaller valid day: `high = mid - 1`.
   - Else: this day doesn't work — search right: `low = mid + 1`.
4. Return `low` (by the end of the loop, `low` converges to the smallest valid day).

### Time Complexity
`O(N * log(Max - Min))` — the search space of size `(Max - Min + 1)` is halved at every Binary Search step, and each step's `possible` check does an `O(N)` pass through the array.

### Space Complexity
`O(1)` — only a few variables are used, no extra data structures.

--------------------------------------------

## Dry Run

Input: `bloomDay = [7, 13, 12]`, `m = 2`, `k = 1`

- `n = 3`, `m * k = 2 <= 3` → not immediately impossible.
- `low = 7`, `high = 13`.
- `mid = 10`. Check `possible(10)`: flowers bloomed by day `10`: `[7]` only → `1` bouquet possible (needs `2`) → not possible → search right → `low = 11`.
- `low = 11`, `high = 13`. `mid = 12`. Check `possible(12)`: flowers bloomed by day `12`: `[7, 12]` (not `13`) → `2` separate single-flower bouquets possible (since `k=1`) → possible → search left → `high = 11`.
- `low = 11`, `high = 11`. `mid = 11`. Check `possible(11)`: flowers bloomed by day `11`: `[7]` only → `1` bouquet possible → not possible → search right → `low = 12`.
- `low = 12 > high = 11` → loop ends.
- Final answer: `low = 12`, matching the expected output.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O((Max - Min) * N) | O(1) |
| Optimal (Binary Search on Answers) | O(N log(Max - Min)) | O(1) |

--------------------------------------------

## Key Observations

- The single impossibility condition (`m * k > n`) must be checked before anything else — if it holds, no amount of waiting can ever produce enough flowers, since there simply aren't `m * k` flowers in the array at all.
- In every other case, the problem is always solvable by day `max(bloomDay)`, since every flower will have bloomed by then, guaranteeing enough adjacent groups can be picked.
- The trailing `count / k` addition after the main loop in the `possible` function is essential — without it, a consecutive bloomed run that extends all the way to the end of the array would be missed.
- As with other Binary Search on Answers problems, the final answer converges to `low` rather than `high`, since the search is looking for the smallest day for which "possible" first becomes true — moving left after a valid day is found always converges `low` toward that boundary.
- This problem generalizes the same "Binary Search on Answers" pattern seen in "Find Square Root of a Number," "Find the Nth Root," and "Koko Eating Bananas" — only the range and the check function differ.

--------------------------------------------

## Interview Tips

- State the impossibility condition (`m * k > n`) clearly and early — this is a common edge case interviewers specifically probe for.
- Be precise about why the trailing bouquet count (after the main loop) is necessary in the `possible` function — a common bug is forgetting this and undercounting bouquets that end exactly at the last flower.
- Emphasize the reusable structure of Binary Search on Answers: define the range, define a `possible(x)` check, then binary search over that range — this template applies to multiple problems, and stating it explicitly signals strong pattern recognition.
- Clarify whether `low` or `high` should be returned by walking through a quick example — getting this backwards is a common source of off-by-one bugs in these problems.

--------------------------------------------

## LeetCode

[1482. Minimum Number of Days to Make m Bouquets](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/)