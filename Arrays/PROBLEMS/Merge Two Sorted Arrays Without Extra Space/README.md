# Merge Two Sorted Arrays Without Extra Space

## Problem Statement

Given two sorted arrays, merge them together into a single sorted sequence **without using any extra array**. Instead of creating a third array to hold the merged result, the elements must be reshuffled in-place within the two given arrays themselves, such that reading array one followed by array two gives the fully sorted, merged sequence.

## Example

```
Input:  array1 = [1, 3, 5, 7], array2 = [0, 2, 6, 8, 9]
Output: array1 = [0, 1, 2, 3], array2 = [5, 6, 7, 8, 9]
```

Reading `array1` followed by `array2` after the operation gives `0, 1, 2, 3, 5, 6, 7, 8, 9` — the fully merged, sorted sequence, achieved without allocating any third array.

## Intuition

Since both arrays are individually sorted, a natural first idea is to merge them the standard way — using two pointers to walk through both arrays and build a sorted third array — but this uses extra space, which the problem forbids.

To avoid the extra array, we exploit a key property of sorted arrays: the largest elements of array one and the smallest elements of array two are the ones most likely to be "out of place" relative to each other. By comparing elements from the back of array one with elements from the front of array two and swapping whenever they're out of order, the smaller values get pushed toward array one and the larger values toward array two — after which sorting each array individually finishes the job. The Gap Method takes this same swapping idea further, using a shrinking gap (inspired by Shell Sort) between compared positions to avoid needing a final full sort at all.

## Approach 1 : Brute Force

Create a third array of size `n + m`. Use two pointers, one for each input array, and repeatedly pick the smaller of the two current elements, placing it into the third array, until one array is exhausted — then copy over any remaining elements from the other array. Finally, copy the sorted contents of the third array back into the two original arrays: the first `n` elements go back into array one, and the remaining `m` elements go back into array two.

### Algorithm
1. Create `array3` of size `n + m`. Initialize `left = 0` (pointer into `array1`), `right = 0` (pointer into `array2`), and `index = 0` (pointer into `array3`).
2. While `left < n` and `right < m`:
   - If `array1[left] <= array2[right]`, set `array3[index] = array1[left]`, then increment `left` and `index`.
   - Otherwise, set `array3[index] = array2[right]`, then increment `right` and `index`.
3. While `left < n` (leftover elements in array one): copy `array1[left]` into `array3[index]`, incrementing both.
4. While `right < m` (leftover elements in array two): copy `array2[right]` into `array3[index]`, incrementing both.
5. Copy `array3` back: for `i` from `0` to `n + m - 1`, if `i < n`, set `array1[i] = array3[i]`; otherwise, set `array2[i - n] = array3[i]`.

### Time Complexity
`O(N + M)` to build the merged `array3`, plus another `O(N + M)` to copy the values back into `array1` and `array2`. Overall: `O(N + M)`.

### Space Complexity
`O(N + M)` for the extra third array used to hold the merged result before copying it back.

--------------------------------------------

## Approach 2 : Optimal (Two-Pointer Swap + Sort)

Since array one holds the "left" portion and array two holds the "right" portion of what should become the fully merged array, any element in array one that is larger than it should be must eventually move to array two, and vice versa. Start with a pointer at the last index of array one and another pointer at the first index of array two. Compare the two pointed-at elements: if the one in array one is bigger, swap them. Move the array-one pointer one step backward and the array-two pointer one step forward, and repeat until either pointer runs out of bounds. This guarantees every element ends up in the correct array (though not yet in correct order within that array), so a final sort of each array individually completes the merge.

### Algorithm
1. Set `left = n - 1` (last index of `array1`) and `right = 0` (first index of `array2`).
2. While `left >= 0` and `right < m`:
   - If `array1[left] > array2[right]`, swap `array1[left]` and `array2[right]`.
   - Otherwise, the remaining elements are already correctly partitioned, so nothing further needs to happen.
   - Decrement `left` and increment `right`.
3. Sort `array1` (from `array1` to `array1 + n`).
4. Sort `array2` (from `array2` to `array2 + m`).

### Time Complexity
At most `min(N, M)` comparisons/swaps are performed in the two-pointer phase, since one of the two pointers will always run out first. This is followed by sorting each array individually: `O(N log N)` for array one and `O(M log M)` for array two. Overall: `O(min(N, M)) + O(N log N) + O(M log M)`.

### Space Complexity
`O(1)` — no extra array is used; only the two given arrays are modified in place.

--------------------------------------------

## Approach 3 : Optimal (Gap Method)

This approach borrows its intuition from Shell Sort. Treat both arrays as one combined virtual array of length `n + m`. Start with a gap equal to the ceiling of `(n + m) / 2`. Compare the elements at positions `left` and `left + gap` (mapping each position to the correct physical array — either `array1` or `array2` — based on whether the index is less than `n`), swapping them if they're out of order. Slide both `left` and `right = left + gap` forward until `right` reaches the end of the combined length. Then shrink the gap by taking the ceiling of `gap / 2`, and repeat the entire sweep. Once the gap becomes `1` and a full pass completes, the arrays are fully merged and sorted — stop as soon as gap `1` has been processed (dividing 1 by 2 would just repeatedly give 1 again, so the process naturally terminates there).

### Algorithm
1. Let `length = n + m`. Set the initial `gap = ceil(length / 2)`, computed as `(length / 2) + (length % 2)`.
2. While `gap > 0`:
   - Set `left = 0` and `right = left + gap`.
   - While `right < length`:
     - Determine which physical array `left` and `right` map to:
       - If `left < n` and `right >= n`: compare `array1[left]` with `array2[right - n]`, swapping if `array1[left] > array2[right - n]`.
       - If `left >= n` and `right >= n`: both map to `array2` — compare `array2[left - n]` with `array2[right - n]`, swapping if out of order.
       - If `left < n` and `right < n`: both map to `array1` — compare `array1[left]` with `array1[right]`, swapping if out of order.
     - Increment `left` and `right`.
   - If `gap == 1`, set `gap = 0` to stop (do not divide further).
   - Otherwise, update `gap = (gap / 2) + (gap % 2)` (ceiling of `gap / 2`).

### Time Complexity
The outer loop halves the gap each time (using ceiling division), giving `O(log(N + M))` iterations. The inner loop, for each gap value, sweeps across roughly the full combined length, contributing `O(N + M)` per outer iteration. Overall: `O((N + M) * log(N + M))`.

### Space Complexity
`O(1)` — no extra array is used; only the two given arrays are modified in place using swaps.

--------------------------------------------

## Dry Run

Using the Gap Method on `array1 = [1, 3, 5, 7]`, `array2 = [0, 2, 6, 8, 9]` (`n = 4`, `m = 5`, `length = 9`):

- Initial gap: `ceil(9 / 2) = 5`.
- `gap = 5`: compare `(array1[0]=1, array2[1]=2)` → in order. Compare `(array1[1]=3, array2[2]=6)` → in order. Compare `(array1[2]=5, array2[3]=8)` → in order. Compare `(array1[3]=7, array2[4]=9)` → in order. No swaps this pass.
- Next gap: `ceil(5 / 2) = 3`.
- `gap = 3`: several comparisons across array1/array2 boundary cause swaps (e.g. `3` and `0` swap, `5` and `2` swap), progressively moving smaller values into array1 and larger values into array2.
- Next gap: `ceil(3 / 2) = 2`, then `ceil(2 / 2) = 1` — each pass does more local swaps, fixing the ordering.
- At `gap = 1`, a final adjacent-element pass fully sorts both arrays.
- Final result: `array1 = [0, 1, 2, 3]`, `array2 = [5, 6, 7, 8, 9]`.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N + M) | O(N + M) |
| Optimal (Two-Pointer Swap + Sort) | O(min(N,M)) + O(N log N) + O(M log M) | O(1) |
| Optimal (Gap Method) | O((N + M) log(N + M)) | O(1) |

--------------------------------------------

## Key Observations

- The problem explicitly forbids extra space, so the Brute Force approach (which creates a third array) will not satisfy the interviewer even though it's the most intuitive starting point.
- The Two-Pointer Swap approach relies on a key insight: after enough swaps between the tail of array one and the head of array two, every element ends up in the array it belongs to — even though within each array the order may still need a final sort.
- The Gap Method avoids the need for a final sort altogether by repeatedly comparing elements at a shrinking gap distance, following the same principle as Shell Sort.
- When mapping a virtual combined index to a physical array in the Gap Method, subtracting `n` (the length of array one) is only needed when the index falls into array two's range — this mirrors the same indexing trick used in the Brute Force copy-back step.
- The gap sequence must stop at `1` rather than continuing to divide, since `ceil(1/2) = 1` would otherwise create an infinite loop.

--------------------------------------------

## Interview Tips

- Always state the Brute Force answer first, but immediately flag that it violates the "no extra space" constraint, showing the interviewer you understood the problem constraints from the start.
- For the Two-Pointer Swap approach, be ready to explain why comparing the tail of array one against the head of array two (rather than any other positions) is sufficient to correctly partition all elements between the two arrays.
- Mention both optimal solutions if time allows — interviewers are often impressed by knowing more than one no-extra-space technique, and the Gap Method in particular signals familiarity with Shell Sort.
- Be precise about complexity: the Two-Pointer Swap approach's overall complexity is dominated by the two individual sorts (`O(N log N + M log M)`), not by the swap phase itself, while the Gap Method's complexity is `O((N+M) log(N+M))` without needing a separate sort step.

--------------------------------------------

## LeetCode

[88. Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/) *(note: the LeetCode version typically merges into a single array with extra capacity; this transcript's version merges two separate fixed-size sorted arrays in place — closely related in spirit to GeeksforGeeks' "Merge two sorted arrays without extra space".)*

