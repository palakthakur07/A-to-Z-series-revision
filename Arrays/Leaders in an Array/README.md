# Leaders in an Array

## Problem Statement

Given an integer array `nums`, return all the **leaders** in the array.

A leader is an element that is **greater than all the elements to its right**. The rightmost element is always a leader.

---

## Example

### Input

```text
nums = [10, 22, 12, 3, 0, 6]
```

### Output

```text
[22, 12, 6]
```

### Explanation

- 22 is greater than all elements to its right.
- 12 is greater than all elements to its right.
- 6 is the last element, so it is always a leader.

---

# Intuition

For every element, we need to determine whether there exists a greater element on its right.

A brute-force approach checks every element against all elements to its right.

An optimal approach traverses the array from right to left while maintaining the maximum element seen so far.

---

# Approach 1: Brute Force

## Algorithm

- Traverse every element.
- Compare it with every element on its right.
- If no greater element exists, it is a leader.

### Time Complexity

**O(N²)**

### Space Complexity

**O(N)** (for storing the answer)

---

# Approach 2: Optimal

## Algorithm

- Start from the last element.
- Maintain a variable `maxElement`.
- If the current element is greater than `maxElement`, it is a leader.
- Update `maxElement`.
- Reverse the answer before returning.

### Time Complexity

**O(N)**

### Space Complexity

**O(N)**

---

# Dry Run

Input

```text
[10,22,12,3,0,6]
```

Traverse from right:

| Element | Max So Far | Leader |
|---------|------------|--------|
|6|6|Yes|
|0|6|No|
|3|6|No|
|12|12|Yes|
|22|22|Yes|
|10|22|No|

Collected Leaders

```text
[6,12,22]
```

Reverse

```text
[22,12,6]
```

---

# Edge Cases

- Single element array
- Strictly increasing array
- Strictly decreasing array
- Duplicate elements

---

# Key Takeaways

- The last element is always a leader.
- Right-to-left traversal avoids unnecessary comparisons.
- Reverse the answer at the end because leaders are collected in reverse order.

---

# Concepts Used

- Arrays
- Reverse Traversal
- Greedy

---

# Interview Tip

Whenever you hear **"greater than all elements on its right"**, think of traversing the array from **right to left**.

---

# Related Problems

- Next Greater Element
- Stock Span Problem
- Daily Temperatures