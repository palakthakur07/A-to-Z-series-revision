# Longest Subarray with Given Sum K (Positive Numbers)

## Problem Statement
Given an array of **positive integers** and an integer `K`, find the length of the longest subarray whose sum is exactly `K`.

### Example

Input:
```
arr = [1,2,3,1,1,1,1,4,2,3]
K = 3
```

Output:
```
3
```

---

## Approaches

### 1. Brute Force
- Generate every possible subarray.
- Compute its sum.
- Update the maximum length whenever the sum equals `K`.

**Time Complexity:** `O(N²)`

**Space Complexity:** `O(1)`

---

### 2. Optimal (Sliding Window)
Since all elements are positive:
- Expand the window by moving the right pointer.
- If the sum becomes greater than `K`, shrink the window from the left.
- Whenever the sum equals `K`, update the answer.

**Time Complexity:** `O(N)`

**Space Complexity:** `O(1)`

---

## Concepts Used
- Arrays
- Sliding Window
- Two Pointers
