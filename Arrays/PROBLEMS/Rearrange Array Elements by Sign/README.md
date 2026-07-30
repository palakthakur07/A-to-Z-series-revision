# Rearrange Array Elements by Sign

## Problem Statement

Given an array of integers containing an equal number of positive and negative elements, rearrange the array such that positive and negative numbers appear alternately while maintaining their relative order.

---

## Example

### Input

```text
nums = [3,1,-2,-5,2,-4]
```

### Output

```text
[3,-2,1,-5,2,-4]
```

---

# Intuition

Since the number of positive and negative elements is equal, we know exactly where each element should be placed.

- Positive numbers occupy even indices.
- Negative numbers occupy odd indices.

---

# Approach 1: Brute Force

## Algorithm

- Store all positive numbers in one array.
- Store all negative numbers in another array.
- Traverse both arrays together.
- Place positive elements at even indices and negative elements at odd indices.

### Time Complexity

**O(N)**

### Space Complexity

**O(N)**

---

# Approach 2: Optimal

## Algorithm

- Create an answer array of size `N`.
- Maintain two pointers:
  - `posIndex = 0`
  - `negIndex = 1`
- Traverse the original array once.
- If the current element is positive, place it at `posIndex` and increment it by 2.
- Otherwise, place it at `negIndex` and increment it by 2.

### Time Complexity

**O(N)**

### Space Complexity

**O(N)**

---

# Follow-Up

If the number of positive and negative elements is **not equal**:

- Arrange alternate positive and negative numbers as long as possible.
- Append the remaining elements of the larger group at the end while maintaining their order.

---

# Dry Run

Input

```text
[3,1,-2,-5,2,-4]
```

| Element | Position |
|---------|----------|
|3|0|
|-2|1|
|1|2|
|-5|3|
|2|4|
|-4|5|

Output

```text
[3,-2,1,-5,2,-4]
```

---

# Edge Cases

- Equal positives and negatives
- More positives than negatives
- More negatives than positives
- Single positive or single negative element

---

# Key Takeaways

- Relative order is preserved.
- Even indices store positives.
- Odd indices store negatives.
- Follow-up handles unequal counts.

---

# Concepts Used

- Arrays
- Two Pointers
- Simulation

---

# Interview Tip

Mention the brute-force approach first using two temporary arrays, then derive the optimal approach using two indices (`0` and `1`) to directly place elements into the answer array.

---

# Related Problems

- Move Zeroes
- Sort Colors
- Partition Array by Pivot