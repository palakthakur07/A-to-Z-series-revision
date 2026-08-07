# Count Inversions

## Problem Statement

Given an array of integers, count the number of pairs `(i, j)` such that `i < j` (the left element comes before the right element in the array) and the left element is greater than the right element. Such a pair is called an **inversion**.

## Example

```
Input:  arr = [5, 3, 2, 4, 1]
Output: 8
```

Explanation: The valid pairs (left greater than right) are: `(5,3)`, `(5,2)`, `(5,4)`, `(5,1)`, `(3,2)`, `(3,1)`, `(2,1)`, `(4,1)` — a total of `8` pairs. Note that pairs like `(1,5)` or `(4,2)` are not counted, since the left element must appear before the right element in the array and must be the greater of the two.

## Intuition

The most direct idea is to check every possible pair `(i, j)` with `i < j` and count how many satisfy `arr[i] > arr[j]` — this is the Brute Force approach.

To optimize this, consider a simpler sub-problem first: given two arrays that are *each already sorted*, how many pairs can be formed by picking one element from the left array and one from the right array such that the left element is greater? Because both arrays are sorted, comparing just the current pointers of each array is enough — if the left array's current element is greater than the right array's current element, then *every* remaining element in the left array (all of which are even larger, since it's sorted) will also be greater than the right array's current element, so all of them can be counted at once instead of comparing one at a time.

This is exactly the situation that arises naturally during the merge step of Merge Sort — merge sort recursively splits the array, sorts each half, and then merges two already-sorted halves back together. By counting inversions during this merge step, the total number of inversions across the whole array can be computed in `O(N log N)` time.

## Approach 1 : Brute Force

Use two nested loops: for every index `i`, check every index `j > i`, and increment a counter whenever `arr[i] > arr[j]`.

### Algorithm
1. Initialize `count = 0`.
2. For each `i` from `0` to `n - 1`:
   - For each `j` from `i + 1` to `n - 1`:
     - If `arr[i] > arr[j]`, increment `count`.
3. Return `count`.

### Time Complexity
`O(N^2)` — every pair of indices is checked using two nested loops.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal

Use a modified version of Merge Sort. Recursively split the array in half, sort (and count inversions in) each half, and then merge the two sorted halves back together. During the merge step, whenever an element from the right half is placed into the merged result before an element from the left half, it means that element is smaller than the *current* left-half element — and since the left half is already sorted, it is also smaller than every remaining element in the left half from that point onward. So instead of counting one inversion at a time, add all of those remaining left-half elements to the inversion count in one step.

### Algorithm
1. Define `mergeSort(arr, low, high)`:
   - If `low >= high`, return (base case: a single element or empty range has no inversions).
   - Compute `mid = (low + high) / 2`.
   - Recursively call `mergeSort(arr, low, mid)` and `mergeSort(arr, mid + 1, high)`.
   - Call `merge(arr, low, mid, high)` to merge the two sorted halves and count cross-inversions.
2. Define `merge(arr, low, mid, high)`:
   - Initialize `left = low`, `right = mid + 1`, an empty temporary array `temp`, and `count = 0`.
   - While `left <= mid` and `right <= high`:
     - If `arr[left] <= arr[right]`, push `arr[left]` into `temp` and increment `left`.
     - Otherwise, push `arr[right]` into `temp`, add `(mid - left + 1)` to `count` (every remaining element from `left` to `mid` forms an inversion with `arr[right]`), and increment `right`.
   - Copy any remaining elements from the left half (`left` to `mid`) into `temp`.
   - Copy any remaining elements from the right half (`right` to `high`) into `temp`.
   - Copy `temp` back into `arr[low..high]`.
   - Return `count`.
3. Every recursive call returns the sum of inversions found in the left half, the right half, and the cross-inversions found during the merge step — the top-level call returns the total inversion count for the whole array.

### Time Complexity
`O(N log N)` — identical to standard Merge Sort's time complexity, since only a constant amount of extra work (the inversion counting) is added to each merge step.

### Space Complexity
`O(N)` — for the temporary array used during each merge step. Note: this approach also modifies (sorts) the original array in place; if the original array's order must be preserved, a copy of it should be sorted instead.

--------------------------------------------

## Dry Run

Input: `arr = [5, 3, 2, 4, 1]`

- Split into `[5, 3, 2]` and `[4, 1]`, then further into `[5, 3]`, `[2]`, `[4]`, `[1]`.
- Merge `[5]` and `[3]`: `3 < 5` → `3` is placed first, `count += (mid - left + 1) = 1`. Merged: `[3, 5]`.
- Merge `[3, 5]` and `[2]`: `2` is smaller than both `3` and `5` → `count += 2` (both remaining left elements form inversions with `2`). Merged: `[2, 3, 5]`.
- Merge `[4]` and `[1]`: `1 < 4` → `count += 1`. Merged: `[1, 4]`.
- Merge `[2, 3, 5]` and `[1, 4]`: `1` is smaller than all of `2, 3, 5` → `count += 3`. Then `2 < 4` → no inversion, take `2`. Then `3 < 4` → no inversion, take `3`. Then `5 > 4`... wait, at this point `4` gets placed only if smaller than remaining left elements — following the algorithm: `5 > 4` → count `+= 1` (remaining left element `5` forms an inversion with `4`). Merged: `[1, 2, 3, 4, 5]`.
- Total count: `1 (from [5,3]) + 2 (merging with 2) + 1 (from [4,1]) + 3 + 1 (final merge) = 8`.
- Final answer: `8` inversions, matching the expected output.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N^2) | O(1) |
| Optimal | O(N log N) | O(N) |

--------------------------------------------

## Key Observations

- This problem directly extends the merge step of Merge Sort — no new sorting logic is needed, only a single extra line added during merging to accumulate the inversion count.
- The key insight that makes the optimal approach work: when merging two already-sorted halves, if a right-half element is smaller than the current left-half element, it is also smaller than *every remaining* left-half element (since the left half is sorted) — so all of those inversions can be counted at once via `mid - left + 1`, instead of comparing them individually.
- Avoid using a global variable to accumulate the count in an interview setting — instead, thread the count through return values (summing the left half's count, the right half's count, and the current merge's count) to keep the solution clean and avoid shared mutable state.
- The optimal approach modifies (sorts) the original array as a side effect — this should be explicitly communicated to the interviewer, along with the option of operating on a copy of the array if the original order must be preserved.
- The problem of counting inversions between two already-sorted arrays (one pointer per array, counting all remaining elements at once when an inversion is found) is a smaller sub-problem that generalizes directly into the merge step — recognizing this connection is the core "aha" moment of the optimal approach.

--------------------------------------------

## Interview Tips

- Mention explicitly that this optimal solution builds directly on Merge Sort — interviewers value recognizing that a modification of a known algorithm solves a new problem rather than inventing something from scratch.
- Be ready to explain, with a concrete two-sorted-arrays example, why finding one inversion during a merge lets you count multiple inversions at once (`mid - left + 1`), rather than incrementing by one every time.
- Proactively flag that the array gets modified (sorted) during the process, and offer the option of working on a copy if the interviewer wants the original array preserved — this is considered a thoughtful, real-world engineering concern.
- Avoid relying on global/shared mutable state (like a global counter) for the count — returning and combining counts through the recursive calls is the cleaner, interview-preferred style.

--------------------------------------------

## LeetCode

Not directly available on LeetCode under this exact name; commonly listed as "Count Inversions" on GeeksforGeeks. A closely related LeetCode problem using the same merge-sort-based technique is [493. Reverse Pairs](https://leetcode.com/problems/reverse-pairs/).