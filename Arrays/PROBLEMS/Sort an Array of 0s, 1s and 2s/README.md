# Sort an Array of 0s, 1s and 2s

## Problem Statement

Given an array containing only **0s, 1s, and 2s**, sort the array in ascending order **without using any built-in sorting algorithm** for the optimal approach.

### Example

Input

```
arr = [2, 0, 2, 1, 1, 0]
```

Output

```
0 0 1 1 2 2
```

---

## Approach 1: Brute Force

- Use the built-in sorting function to sort the array.

**Time Complexity:** `O(N log N)`

**Space Complexity:** `O(1)`

---

## Approach 2: Counting

- Count the number of `0s`, `1s`, and `2s`.
- Overwrite the array with the counted values.

**Time Complexity:** `O(N)`

**Space Complexity:** `O(1)`

---

## Approach 3: Dutch National Flag Algorithm (Optimal)

Maintain three pointers:

- `low` → Boundary for 0s
- `mid` → Current element
- `high` → Boundary for 2s

Rules:

- If `arr[mid] == 0`
  - Swap `low` and `mid`
  - Increment both `low` and `mid`
- If `arr[mid] == 1`
  - Increment `mid`
- If `arr[mid] == 2`
  - Swap `mid` and `high`
  - Decrement `high`

This sorts the array in a single traversal.

**Time Complexity:** `O(N)`

**Space Complexity:** `O(1)`

---

## Concepts Used

- Arrays
- Two Pointers
- Dutch National Flag Algorithm
- In-place Sorting