# Count Subarrays With Given XOR K

## Problem Statement

Given an array of integers and an integer `k`, count the number of subarrays whose XOR of all elements equals `k`.

A subarray is defined as any **contiguous** part of the array (not any arbitrary subset — the elements must be picked in a continuous run).

## Example

```
Input:  arr = [4, 2, 2, 6, 4], k = 6
Output: 4
```

Explanation: The subarrays with XOR equal to `6` are:
- `[4, 2]` → `4 ^ 2 = 6`
- `[2, 2, 6]` → `2 ^ 2 = 0`, `0 ^ 6 = 6`
- `[6]` → single element, XOR is `6`
- `[6, 4, ...]`-type combinations: taking the full prefix `[4, 2, 2, 6]` gives `4 ^ 2 ^ 2 ^ 6 = 6` (the `4`s and `2`s cancel out, leaving `6`)

So there are exactly `4` subarrays with XOR `6`.

## Intuition

This problem directly reuses the concept from "Count Number of Subarrays with Given Sum K" — the same prefix-technique idea is applied here, except the running combination is XOR instead of sum.

The key identity used in the optimal approach: if `XR` is the XOR of all elements from the start up to the current index, and there exists some earlier prefix XOR `X` such that `X ^ K = XR`, then the subarray between that earlier prefix and the current index has XOR exactly `K`. This follows from XOR's self-cancelling property: XOR-ing the same value with itself gives `0`, so `X ^ K = XR` can be rearranged (XOR `K` on both sides) to `X = XR ^ K`. Every subarray ending at the current index is checked this way, by looking up how many times the required `X` has occurred as a prefix XOR so far.

## Approach 1 : Brute Force

Generate every possible subarray using two nested loops for the starting index `i` and ending index `j`, then use a third loop to iterate through the elements from `i` to `j` and compute their XOR. If the computed XOR equals `k`, increment the count.

### Algorithm
1. Run a loop with `i` from `0` to `n - 1` (start of subarray).
2. Run a nested loop with `j` from `i` to `n - 1` (end of subarray).
3. Initialize `xorVal = 0` for each `(i, j)` pair.
4. Run a third loop with `key` from `i` to `j`, computing `xorVal = xorVal ^ arr[key]`.
5. After the third loop completes, if `xorVal == k`, increment `count`.
6. Return `count`.

### Time Complexity
`O(N^3)` — two loops to generate every subarray, and one more loop to compute the XOR of each subarray.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Better

Eliminate the third loop by observing that as `j` moves forward for a fixed `i`, the subarray only grows by one element at a time. So instead of recomputing the XOR from scratch, maintain a running `xorVal` that gets updated incrementally as `j` moves.

### Algorithm
1. Run a loop with `i` from `0` to `n - 1` (start of subarray).
2. Initialize `xorVal = 0` for each `i`.
3. Run a nested loop with `j` from `i` to `n - 1`:
   - Update `xorVal = xorVal ^ arr[j]` (add the new element into the running XOR).
   - If `xorVal == k`, increment `count`.
4. Return `count`.

### Time Complexity
`O(N^2)` — two nested loops, with the XOR computed incrementally instead of with a third loop.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 3 : Optimal

Traverse the array once while maintaining a running prefix XOR (`xr`) of all elements seen so far. For every index, use a hash map to check how many earlier prefixes had an XOR value of `xr ^ k` — each such earlier prefix marks the start of a subarray ending at the current index with XOR exactly `k`. Add that count to the running answer, then record the current prefix XOR in the map (initialized with `{0: 1}` to correctly count subarrays that start from index `0`).

### Algorithm
1. Initialize `xr = 0`, `count = 0`, and a hash map `mp` with `mp[0] = 1` (representing an empty prefix before the array starts).
2. For each element in the array:
   - Update `xr = xr ^ arr[element]`.
   - Compute `x = xr ^ k` (the prefix XOR value we need to have seen before).
   - Add `mp[x]` to `count` (if `x` was never seen, this contributes `0`).
   - Increment `mp[xr]` by `1` (record the current prefix XOR for future lookups).
3. Return `count`.

### Time Complexity
`O(N)` in the average case using an unordered map (`O(1)` per lookup/insert on average), or `O(N log N)` in the worst case if an ordered map is used instead, since each of the `N` elements does one map lookup and one map insert.

### Space Complexity
`O(N)` — in the worst case, every prefix XOR value is unique and gets stored in the hash map.

--------------------------------------------

## Dry Run

Input: `arr = [4, 2, 2, 6, 4]`, `k = 6`

- Start: `xr = 0`, `mp = {0: 1}`, `count = 0`.
- Element `4`: `xr = 0 ^ 4 = 4`. Need `x = xr ^ k = 4 ^ 6 = 2`. `mp` has no `2` → `count += 0`. Update `mp = {0: 1, 4: 1}`.
- Element `2`: `xr = 4 ^ 2 = 6`. Need `x = 6 ^ 6 = 0`. `mp[0] = 1` → `count += 1` → `count = 1`. Update `mp = {0: 1, 4: 1, 6: 1}`.
- Element `2`: `xr = 6 ^ 2 = 4`. Need `x = 4 ^ 6 = 2`. `mp` has no `2` → `count += 0`. Update `mp = {0: 1, 4: 2, 6: 1}`.
- Element `6`: `xr = 4 ^ 6 = 2`. Need `x = 2 ^ 6 = 4`. `mp[4] = 2` → `count += 2` → `count = 3`. Update `mp = {0: 1, 4: 2, 6: 1, 2: 1}`.
- Element `4`: `xr = 2 ^ 4 = 6`. Need `x = 6 ^ 6 = 0`. `mp[0] = 1` → `count += 1` → `count = 4`. Update `mp = {0: 1, 4: 2, 6: 2, 2: 1}`.
- Final answer: `count = 4`.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N^3) | O(1) |
| Better | O(N^2) | O(1) |
| Optimal | O(N) avg / O(N log N) worst | O(N) |

--------------------------------------------

## Key Observations

- This problem reuses the exact prefix-technique concept from "Count Number of Subarrays with Given Sum K" — only the combining operation changes from sum to XOR.
- The core identity is `X = XR ^ K`, derived by XOR-ing both sides of `X ^ K = XR` with `K` and using the fact that XOR-ing a value with itself cancels out to `0`.
- The hash map must be initialized with `{0: 1}` before the traversal starts, so that subarrays beginning at index `0` are correctly counted.
- Every subarray has both a starting point and an ending point — the optimal approach fixes the ending point at each step and figures out, via the hash map, how many valid starting points exist for that ending point.
- The map's value at each key represents "how many times has this prefix XOR occurred so far" — multiple earlier occurrences of the same prefix XOR mean multiple valid subarrays ending at the current index.

--------------------------------------------

## Interview Tips

- Point out to the interviewer that this is a direct extension of the "subarray sum equals k" pattern, just with XOR replacing sum — this shows pattern recognition.
- Be ready to derive the `X = XR ^ K` formula on the spot; interviewers often ask you to justify it rather than just state it.
- Mention that `mp[0] = 1` must be seeded before the loop starts, and explain why (to account for subarrays starting at index `0`).
- Clarify that using `unordered_map` gives average `O(1)` operations, but the worst case can degrade, so the time complexity should be stated as `O(N)` on average and `O(N log N)` in the worst case if that distinction is asked about.

--------------------------------------------

## LeetCode

Not explicitly linked in the transcript. This problem is commonly listed as "Subarray with XOR K" (GeeksforGeeks) / "Count Subarrays with Given XOR" — check the source platform referenced in your course material for the exact link.