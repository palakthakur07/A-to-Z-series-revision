# Majority Element

## Problem Statement

Given an integer array of size `n`, return the element that appears **more than ⌊n/2⌋ times**. If no such element exists, return `-1`.

### Example

Input

```
nums = [2,2,1,1,1,2,2]
```

Output

```
2
```

---

## Approach 1: Brute Force

- For every element, count its frequency by traversing the entire array.
- Return the element whose frequency is greater than `n/2`.

**Time Complexity:** `O(N²)`

**Space Complexity:** `O(1)`

---

## Approach 2: Hash Map

- Store the frequency of each element in a hash map.
- Traverse the map and return the element whose frequency is greater than `n/2`.

**Time Complexity:** `O(N)`

**Space Complexity:** `O(N)`

---

## Approach 3: Moore's Voting Algorithm (Optimal)

- Maintain a candidate and a counter.
- Different elements cancel each other.
- The remaining candidate is verified in a second traversal.

**Time Complexity:** `O(N)`

**Space Complexity:** `O(1)`

---

## Concepts Used

- Arrays
- Hash Map
- Moore's Voting Algorithm
- Frequency Counting