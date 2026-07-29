# Longest Subarray with Given Sum K (Positive & Negative Numbers)

## Problem Statement

Given an integer array (which may contain positive, negative, and zero values) and an integer `K`, find the length of the longest subarray whose sum is exactly `K`.

### Example

Input

```
arr = [1, 2, 3, 1, 1, 1, -1, 4, 2, -3]
K = 3
```

Output

```
4
```

---

## Approach 1: Brute Force

- Generate every possible subarray.
- Compute its sum.
- Update the maximum length whenever the sum equals `K`.

**Time Complexity:** `O(N²)`

**Space Complexity:** `O(1)`

---

## Approach 2: Prefix Sum + Hash Map (Optimal)

- Maintain the running prefix sum.
- Store the first occurrence of every prefix sum.
- If `(prefixSum - K)` exists in the map, a valid subarray is found.
- Update the maximum length accordingly.

**Time Complexity:** `O(N)`

**Space Complexity:** `O(N)`

---

## Concepts Used

- Arrays
- Prefix Sum
- Hash Map
- Longest Subarray