# Two Sum

## Problem Statement

Given an integer array and a target value, determine whether there exists a pair of elements whose sum equals the target.

### Example

Input

```
arr = [2, 6, 5, 8, 11]
target = 14
```

Output

```
YES
```

---

## Approach 1: Brute Force

- Check every possible pair.
- Return true if any pair sums to the target.

**Time Complexity:** `O(N²)`

**Space Complexity:** `O(1)`

---

## Approach 2: Hash Map (Better)

- Traverse the array once.
- For every element, calculate `target - currentElement`.
- If it already exists in the map, a valid pair is found.

**Time Complexity:** `O(N)`

**Space Complexity:** `O(N)`

---

## Approach 3: Two Pointers (Optimal)

- Sort the array.
- Place one pointer at the beginning and another at the end.
- Move pointers based on the current sum.

> **Note:** This approach modifies the order of elements. It is ideal when only checking if a pair exists, not when original indices are required.

**Time Complexity:** `O(N log N)`

**Space Complexity:** `O(1)`

---

## Concepts Used

- Arrays
- Hash Map
- Two Pointers
- Sorting