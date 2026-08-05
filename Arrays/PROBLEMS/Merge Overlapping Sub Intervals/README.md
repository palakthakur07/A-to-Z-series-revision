# Merge Overlapping Sub Intervals

## Problem Statement

Given an array of `N` sub intervals, merge all the overlapping sub intervals into one and return the minimum possible number of sub intervals (in merged form) that cover the same ranges as the original array.

A sub interval like `[1, 3]` means it starts at `1` and ends at `3`.

## Example

```
Input:  intervals = [[1,3], [2,6], [8,9], [8,10], [9,11], [15,18], [16,17]]
Output: [[1,6], [8,11], [15,18]]
```

Explanation: `[1,3]`, `[2,6]`, and `[2,4]`-type overlaps all merge into `[1,6]` since every coordinate between `1` and `6` is touched by at least one interval. Similarly `[8,9]`, `[8,10]`, `[9,11]` merge into `[8,11]`, and `[15,18]`, `[16,17]` merge into `[15,18]`. The result is the minimum possible set of `3` non-overlapping sub intervals.

## Intuition

The core idea is to first sort the intervals so that overlapping ones end up next to (or close to) each other, which makes it far easier to club them together. Once sorted, two intervals `[a, b]` and `[c, d]` (with `a <= c`) overlap if `c` is less than or equal to `b` — meaning the start of the next interval falls before the end of the current one. When that happens, the two intervals can be merged into one by keeping the smaller start and extending the end to the maximum of the two ends.

The Brute Force approach checks, for every interval, all forward intervals to see how far it can expand. The Optimal approach realizes this can be done in a single pass by only ever comparing the current interval against the last interval placed in the answer.

## Approach 1 : Brute Force

Sort the intervals first. Then, for each interval, if it is not already fully contained within the most recently merged interval in the answer, treat it as the start of a new merged interval and keep expanding forward — checking every subsequent interval to see if its start lies within the current expanding range, and updating the end to the maximum seen so far. Stop expanding as soon as a subsequent interval's start falls outside the current range, since the array is sorted and nothing further can overlap.

### Algorithm
1. Sort the intervals array.
2. For each index `i` from `0` to `n - 1`:
   - If the answer is non-empty and `array[i][1]` (the end of the current interval) is less than or equal to the end of the last interval already placed in the answer, this interval is already fully covered — skip it (`continue`).
   - Otherwise, set `start = array[i][0]` and `end = array[i][1]`.
   - Run an inner loop with `j` from `i + 1` to `n - 1`:
     - If `array[j][0] <= end`, this interval overlaps — update `end = max(end, array[j][1])`.
     - Otherwise, break out of the inner loop (no further interval can overlap, since the array is sorted).
   - Push `{start, end}` into the answer.
3. Return the answer.

### Time Complexity
`O(N log N)` for sorting, plus approximately `O(2N)` for the merging pass — even though there are two nested loops, the `continue` and `break` statements mean each element is effectively visited about twice across the whole traversal, not `N` times each. Overall: `O(N log N + N)`.

### Space Complexity
`O(N)` for the answer array — in the worst case (no intervals overlap at all), every interval is stored as-is in the answer.

--------------------------------------------

## Approach 2 : Optimal

Sort the intervals first. Then make a single pass through the sorted array, comparing only the current interval against the last interval already placed in the answer. If the current interval's start is beyond the end of the last merged interval, it cannot overlap, so start a brand-new interval in the answer. Otherwise, it overlaps, so simply extend the end of the last merged interval to the maximum of its current end and the current interval's end.

### Algorithm
1. Sort the intervals array.
2. Initialize an empty answer list.
3. For each interval in the sorted array:
   - If the answer is empty, or the current interval's start is greater than the end of the last interval in the answer, push the current interval as a new entry in the answer.
   - Otherwise, the current interval overlaps with the last one in the answer — update the end of the last interval in the answer to `max(answer.back().end, current interval's end)`.
4. Return the answer.

### Time Complexity
`O(N log N)` for sorting, plus `O(N)` for the single pass — overall `O(N log N)`.

### Space Complexity
`O(N)` for the answer array — in the worst case, no intervals overlap and every interval is stored as its own entry.

--------------------------------------------

## Dry Run

Sorted input: `[[1,3], [2,4], [2,6], [8,9], [8,10], [9,11], [15,18], [16,17]]`

- `[1,3]`: answer is empty → push `[1,3]`. Answer: `[[1,3]]`.
- `[2,4]`: `2 <= 3` (last interval's end) → overlaps → extend last interval's end to `max(3,4) = 4`. Answer: `[[1,4]]`.
- `[2,6]`: `2 <= 4` → overlaps → extend end to `max(4,6) = 6`. Answer: `[[1,6]]`.
- `[8,9]`: `8 > 6` → does not overlap → push new interval `[8,9]`. Answer: `[[1,6], [8,9]]`.
- `[8,10]`: `8 <= 9` → overlaps → extend end to `max(9,10) = 10`. Answer: `[[1,6], [8,10]]`.
- `[9,11]`: `9 <= 10` → overlaps → extend end to `max(10,11) = 11`. Answer: `[[1,6], [8,11]]`.
- `[15,18]`: `15 > 11` → does not overlap → push new interval `[15,18]`. Answer: `[[1,6], [8,11], [15,18]]`.
- `[16,17]`: `16 <= 18` → overlaps → extend end to `max(18,17) = 18` (no change). Answer: `[[1,6], [8,11], [15,18]]`.
- Final answer: `[[1,6], [8,11], [15,18]]` — 3 merged intervals.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N log N + N) | O(N) |
| Optimal | O(N log N) | O(N) |

--------------------------------------------

## Key Observations

- Sorting is the essential first step for both approaches — it's what allows overlap checks to rely only on comparing a start against a previous end, instead of comparing every pair of intervals.
- In the Brute Force approach, the `continue` (when an interval is already covered) and `break` (when an interval no longer overlaps) statements are what keep the complexity close to `O(N)` for the merging step, even though it looks like nested loops would give `O(N^2)`.
- The Optimal approach only ever needs to compare the current interval with the **last** interval placed in the answer — it never needs to look further back or check multiple previous intervals.
- When merging, always take `max(existing end, new end)` rather than blindly overwriting the end — a contained interval (like `[16,17]` inside `[15,18]`) must not shrink the already-merged range.
- Two sorted intervals `[a, b]` and `[c, d]` overlap exactly when `c <= b`; this single comparison is the crux of both approaches.

--------------------------------------------

## Interview Tips

- Start by proposing sorting as the very first step — it immediately simplifies the overlap-detection logic for the interviewer.
- When presenting the Brute Force approach, be ready to justify why it isn't truly `O(N^2)` despite the nested loops — walk through how `break` and `continue` limit the total work to roughly `O(N)` on top of the sort.
- For the Optimal approach, emphasize that only the last merged interval needs to be checked against the current one — this single-pass insight is usually the main thing interviewers are listening for.
- Be careful to explicitly mention taking `max()` when extending an interval's end, since forgetting this is a common subtle bug (e.g., incorrectly shrinking the range when a fully-contained interval is encountered).

--------------------------------------------

## LeetCode

[56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)