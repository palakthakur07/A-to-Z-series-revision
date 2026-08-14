# Binary Search

## Problem Statement

Given a sorted array of unique integers and a target value, find and return the index at which the target exists in the array. If the target does not exist in the array, return `-1`.

Binary Search is a searching algorithm applicable whenever the search is being performed over a **sorted** search space — this doesn't have to be an array; it can be any problem where the space of possible answers is sorted (e.g. searching for a word in a dictionary, or searching over a range of possible numeric answers).

## Example

```
Input:  arr = [3, 4, 6, 7, 9, 12, 16, 17], target = 6
Output: 2
```

Explanation: `6` is found at index `2`. If the target were, say, `13` (not present in the array), the function would return `-1`.

## Intuition

The naive way to search for a target is to check every element one by one from the start until it's found — this is **Linear Search**, and it doesn't take advantage of the array being sorted, giving `O(N)` time.

Since the array is sorted, a much smarter approach is possible: split the search space in half using a `mid` index. Compare the target against the middle element. If they match, the answer is found. If the target is greater than the middle element, the entire left half (including the middle) can never contain the target — because the array is sorted, everything on the left is smaller — so the search space shrinks to the right half only. Symmetrically, if the target is smaller, the search space shrinks to the left half only. Repeating this halving process — exactly like flipping open a dictionary to search for a word — narrows the search space exponentially fast, giving `O(log N)` time. This idea can be implemented either **iteratively** (using a loop) or **recursively** (calling the same function on a shrunken search space each time), since the steps performed at each stage are identical.

## Approach 1 : Brute Force (Linear Search)

Check every element in the array one at a time, from the first to the last, until the target is found or the array is exhausted.

### Algorithm
1. For each index `i` from `0` to `n - 1`:
   - If `array[i] == target`, return `i`.
2. If the loop completes without finding the target, return `-1`.

### Time Complexity
`O(N)` — in the worst case (target absent, or located at the very end), every element must be checked.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal (Iterative Binary Search)

Maintain two pointers, `low` (starting at index `0`) and `high` (starting at index `n - 1`), representing the current search space — everything between `low` and `high` (inclusive) is where the target could still be. Repeatedly compute the middle index `mid`, compare `array[mid]` against the target, and shrink the search space accordingly: match found → return `mid`; target is greater → discard the left half by moving `low` to `mid + 1`; target is smaller → discard the right half by moving `high` to `mid - 1`. Stop when `low` exceeds `high`, meaning the search space is exhausted and the target isn't present.

### Algorithm
1. Initialize `low = 0` and `high = n - 1`.
2. While `low <= high`:
   - Compute `mid = low + (high - low) / 2` (overflow-safe form of `(low + high) / 2`).
   - If `array[mid] == target`, return `mid`.
   - Else if `array[mid] < target`, the target lies on the right — set `low = mid + 1`.
   - Else (`array[mid] > target`), the target lies on the left — set `high = mid - 1`.
3. If the loop ends without finding the target (i.e. `low > high`), return `-1`.

### Time Complexity
`O(log N)` — the search space is halved at every step; for a space of size `N`, this takes roughly `log2(N)` steps to shrink down to a single element (e.g. a size-`32` space takes about `5` steps, since `32 = 2^5`).

### Space Complexity
`O(1)` — only a few pointer variables are used, no extra data structures or recursive call stack.

--------------------------------------------

## Approach 3 : Optimal (Recursive Binary Search)

Since the exact same three steps (compute `mid`, compare, shrink the search space) are repeated at every stage regardless of the current `low` and `high`, this naturally maps to a recursive function: call the same function again with an updated `low` or `high` representing the shrunken search space, until the base case (search space exhausted) is reached.

### Algorithm
1. Define `binarySearch(array, low, high, target)`:
   - **Base case**: if `low > high`, the search space is exhausted — return `-1`.
   - Compute `mid = low + (high - low) / 2`.
   - If `array[mid] == target`, return `mid`.
   - Else if `array[mid] < target`, the target lies on the right — return `binarySearch(array, mid + 1, high, target)`.
   - Else (`array[mid] > target`), the target lies on the left — return `binarySearch(array, low, mid - 1, target)`.
2. The main function calls `binarySearch(array, 0, n - 1, target)` to kick off the search over the entire array.

### Time Complexity
`O(log N)` — identical reasoning to the iterative version; the search space is halved with each recursive call.

### Space Complexity
`O(log N)` — due to the recursion call stack, which grows to a depth of roughly `log2(N)` before hitting the base case (unlike the iterative version, which uses constant space).

--------------------------------------------

## Dry Run

Input: `arr = [3, 4, 6, 7, 9, 12, 16, 17]`, `target = 13`

- `low = 0`, `high = 7`. `mid = 0 + (7-0)/2 = 3`. `arr[3] = 7`. `13 > 7` → target is on the right → `low = 4`.
- `low = 4`, `high = 7`. `mid = 4 + (7-4)/2 = 5`. `arr[5] = 12`. `13 > 12` → target is on the right → `low = 6`.
- `low = 6`, `high = 7`. `mid = 6 + (7-6)/2 = 6`. `arr[6] = 16`. `13 < 16` → target is on the left → `high = 5`.
- Now `low = 6 > high = 5` — the search space is exhausted.
- Return `-1`, since `13` is not present in the array.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force (Linear Search) | O(N) | O(1) |
| Optimal (Iterative) | O(log N) | O(1) |
| Optimal (Recursive) | O(log N) | O(log N) (recursion call stack) |

--------------------------------------------

## Key Observations

- Binary Search applies to any sorted search space, not just arrays — it can be used to search over a sorted range of possible answers in a wide variety of problems.
- The search space at any point is precisely everything between `low` and `high` (inclusive); the loop or recursion continues exactly as long as `low <= high` holds.
- When `array[mid]` doesn't match the target, an entire half of the current search space can always be safely discarded, thanks to the sorted property — this is what gives Binary Search its logarithmic time complexity.
- **Overflow case**: computing `mid` as `(low + high) / 2` can overflow if `low` and `high` are both close to the maximum value an integer can hold (this matters when the search space isn't a bounded array size but something like `INT_MAX`). The safe alternative is `mid = low + (high - low) / 2`, which is mathematically equivalent but avoids ever computing a sum that could exceed the integer range. Alternatively, `low` and `high` can be declared as `long long` if the search space might exceed `INT_MAX`.
- The recursive implementation performs identical logical steps to the iterative one, but incurs `O(log N)` extra space due to the call stack — the iterative version is preferred when space is a concern.

--------------------------------------------

## Interview Tips

- Always confirm that the search space is sorted before proposing Binary Search — this is the one precondition that makes the entire technique valid.
- Be ready to write both the iterative and recursive versions, and to explain the space trade-off between them (`O(1)` vs `O(log N)` due to the call stack).
- Proactively mention the overflow-safe `mid` calculation (`low + (high - low) / 2`) — this is a commonly asked follow-up in interviews, especially when the search space could be very large (close to `INT_MAX`).
- Emphasize that Binary Search isn't limited to searching in arrays — it generalizes to any monotonic/sorted decision space, which is a common pattern in "search on the answer" style problems.

--------------------------------------------

## LeetCode

[704. Binary Search](https://leetcode.com/problems/binary-search/)# Binary Search

## Problem Statement

Given a sorted array of unique integers and a target value, find and return the index at which the target exists in the array. If the target does not exist in the array, return `-1`.

Binary Search is a searching algorithm applicable whenever the search is being performed over a **sorted** search space — this doesn't have to be an array; it can be any problem where the space of possible answers is sorted (e.g. searching for a word in a dictionary, or searching over a range of possible numeric answers).

## Example

```
Input:  arr = [3, 4, 6, 7, 9, 12, 16, 17], target = 6
Output: 2
```

Explanation: `6` is found at index `2`. If the target were, say, `13` (not present in the array), the function would return `-1`.

## Intuition

The naive way to search for a target is to check every element one by one from the start until it's found — this is **Linear Search**, and it doesn't take advantage of the array being sorted, giving `O(N)` time.

Since the array is sorted, a much smarter approach is possible: split the search space in half using a `mid` index. Compare the target against the middle element. If they match, the answer is found. If the target is greater than the middle element, the entire left half (including the middle) can never contain the target — because the array is sorted, everything on the left is smaller — so the search space shrinks to the right half only. Symmetrically, if the target is smaller, the search space shrinks to the left half only. Repeating this halving process — exactly like flipping open a dictionary to search for a word — narrows the search space exponentially fast, giving `O(log N)` time. This idea can be implemented either **iteratively** (using a loop) or **recursively** (calling the same function on a shrunken search space each time), since the steps performed at each stage are identical.

## Approach 1 : Brute Force (Linear Search)

Check every element in the array one at a time, from the first to the last, until the target is found or the array is exhausted.

### Algorithm
1. For each index `i` from `0` to `n - 1`:
   - If `array[i] == target`, return `i`.
2. If the loop completes without finding the target, return `-1`.

### Time Complexity
`O(N)` — in the worst case (target absent, or located at the very end), every element must be checked.

### Space Complexity
`O(1)` — no extra data structure is used.

--------------------------------------------

## Approach 2 : Optimal (Iterative Binary Search)

Maintain two pointers, `low` (starting at index `0`) and `high` (starting at index `n - 1`), representing the current search space — everything between `low` and `high` (inclusive) is where the target could still be. Repeatedly compute the middle index `mid`, compare `array[mid]` against the target, and shrink the search space accordingly: match found → return `mid`; target is greater → discard the left half by moving `low` to `mid + 1`; target is smaller → discard the right half by moving `high` to `mid - 1`. Stop when `low` exceeds `high`, meaning the search space is exhausted and the target isn't present.

### Algorithm
1. Initialize `low = 0` and `high = n - 1`.
2. While `low <= high`:
   - Compute `mid = low + (high - low) / 2` (overflow-safe form of `(low + high) / 2`).
   - If `array[mid] == target`, return `mid`.
   - Else if `array[mid] < target`, the target lies on the right — set `low = mid + 1`.
   - Else (`array[mid] > target`), the target lies on the left — set `high = mid - 1`.
3. If the loop ends without finding the target (i.e. `low > high`), return `-1`.

### Time Complexity
`O(log N)` — the search space is halved at every step; for a space of size `N`, this takes roughly `log2(N)` steps to shrink down to a single element (e.g. a size-`32` space takes about `5` steps, since `32 = 2^5`).

### Space Complexity
`O(1)` — only a few pointer variables are used, no extra data structures or recursive call stack.

--------------------------------------------

## Approach 3 : Optimal (Recursive Binary Search)

Since the exact same three steps (compute `mid`, compare, shrink the search space) are repeated at every stage regardless of the current `low` and `high`, this naturally maps to a recursive function: call the same function again with an updated `low` or `high` representing the shrunken search space, until the base case (search space exhausted) is reached.

### Algorithm
1. Define `binarySearch(array, low, high, target)`:
   - **Base case**: if `low > high`, the search space is exhausted — return `-1`.
   - Compute `mid = low + (high - low) / 2`.
   - If `array[mid] == target`, return `mid`.
   - Else if `array[mid] < target`, the target lies on the right — return `binarySearch(array, mid + 1, high, target)`.
   - Else (`array[mid] > target`), the target lies on the left — return `binarySearch(array, low, mid - 1, target)`.
2. The main function calls `binarySearch(array, 0, n - 1, target)` to kick off the search over the entire array.

### Time Complexity
`O(log N)` — identical reasoning to the iterative version; the search space is halved with each recursive call.

### Space Complexity
`O(log N)` — due to the recursion call stack, which grows to a depth of roughly `log2(N)` before hitting the base case (unlike the iterative version, which uses constant space).

--------------------------------------------

## Dry Run

Input: `arr = [3, 4, 6, 7, 9, 12, 16, 17]`, `target = 13`

- `low = 0`, `high = 7`. `mid = 0 + (7-0)/2 = 3`. `arr[3] = 7`. `13 > 7` → target is on the right → `low = 4`.
- `low = 4`, `high = 7`. `mid = 4 + (7-4)/2 = 5`. `arr[5] = 12`. `13 > 12` → target is on the right → `low = 6`.
- `low = 6`, `high = 7`. `mid = 6 + (7-6)/2 = 6`. `arr[6] = 16`. `13 < 16` → target is on the left → `high = 5`.
- Now `low = 6 > high = 5` — the search space is exhausted.
- Return `-1`, since `13` is not present in the array.

--------------------------------------------

## Comparison Table

| Approach | Time | Space |
|---|---|---|
| Brute Force (Linear Search) | O(N) | O(1) |
| Optimal (Iterative) | O(log N) | O(1) |
| Optimal (Recursive) | O(log N) | O(log N) (recursion call stack) |

--------------------------------------------

## Key Observations

- Binary Search applies to any sorted search space, not just arrays — it can be used to search over a sorted range of possible answers in a wide variety of problems.
- The search space at any point is precisely everything between `low` and `high` (inclusive); the loop or recursion continues exactly as long as `low <= high` holds.
- When `array[mid]` doesn't match the target, an entire half of the current search space can always be safely discarded, thanks to the sorted property — this is what gives Binary Search its logarithmic time complexity.
- **Overflow case**: computing `mid` as `(low + high) / 2` can overflow if `low` and `high` are both close to the maximum value an integer can hold (this matters when the search space isn't a bounded array size but something like `INT_MAX`). The safe alternative is `mid = low + (high - low) / 2`, which is mathematically equivalent but avoids ever computing a sum that could exceed the integer range. Alternatively, `low` and `high` can be declared as `long long` if the search space might exceed `INT_MAX`.
- The recursive implementation performs identical logical steps to the iterative one, but incurs `O(log N)` extra space due to the call stack — the iterative version is preferred when space is a concern.

--------------------------------------------

## Interview Tips

- Always confirm that the search space is sorted before proposing Binary Search — this is the one precondition that makes the entire technique valid.
- Be ready to write both the iterative and recursive versions, and to explain the space trade-off between them (`O(1)` vs `O(log N)` due to the call stack).
- Proactively mention the overflow-safe `mid` calculation (`low + (high - low) / 2`) — this is a commonly asked follow-up in interviews, especially when the search space could be very large (close to `INT_MAX`).
- Emphasize that Binary Search isn't limited to searching in arrays — it generalizes to any monotonic/sorted decision space, which is a common pattern in "search on the answer" style problems.

--------------------------------------------

## LeetCode

[704. Binary Search](https://leetcode.com/problems/binary-search/)