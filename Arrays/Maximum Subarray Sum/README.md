# Maximum Subarray Sum

## Problem Statement

Given an integer array `nums`, find the **contiguous subarray** (containing at least one element) that has the largest sum and return its sum.

---

## Example

### Input

```text
nums = [-2,1,-3,4,-1,2,1,-5,4]
```

### Output

```text
6
```

### Explanation

The subarray `[4,-1,2,1]` has the maximum sum.

---

# Intuition

A brute force solution checks every possible subarray and calculates its sum.

We can optimize this by avoiding repeated calculations using a running sum.

Kadane's Algorithm takes this idea one step further. Whenever the running sum becomes negative, it can never help future subarrays, so we simply discard it and start a new subarray.

---

# Approach 1: Brute Force

## Algorithm

- Generate every possible subarray.
- Calculate the sum of every subarray.
- Keep track of the maximum sum found.

### Time Complexity

**O(N³)**

### Space Complexity

**O(1)**

---

# Approach 2: Better

## Algorithm

- Fix the starting index.
- Maintain a running sum while extending the ending index.
- Update the maximum sum after every extension.

### Time Complexity

**O(N²)**

### Space Complexity

**O(1)**

---

# Approach 3: Optimal (Kadane's Algorithm)

## Algorithm

- Maintain a running sum.
- Add every element to the running sum.
- Update the maximum answer.
- If the running sum becomes negative, reset it to zero.

### Time Complexity

**O(N)**

### Space Complexity

**O(1)**

---

# Dry Run

Array

```text
[-2,1,-3,4,-1,2,1,-5,4]
```

| Element | Running Sum | Maximum Sum |
|---------|-------------|-------------|
|-2|-2|-2|
|1|1|1|
|-3|-2|1|
|4|4|4|
|-1|3|4|
|2|5|5|
|1|6|6|
|-5|1|6|
|4|5|6|

Answer = **6**

---

# Edge Cases

- Single element array
- All negative numbers
- All positive numbers
- Array containing zero

---

# Key Takeaways

- Brute force checks every subarray.
- Better approach avoids recalculating sums.
- Kadane's Algorithm solves the problem in linear time.
- Reset the running sum only when it becomes negative.

---

# Concepts Used

- Arrays
- Prefix Sum Idea
- Kadane's Algorithm
- Dynamic Programming (Greedy Perspective)

---

# Interview Tips

- Always explain the brute force first.
- Derive the better approach using a running sum.
- Finally explain why Kadane's Algorithm works.

---

# Related Problems

- Maximum Product Subarray
- Maximum Circular Subarray Sum
- Print Maximum Sum Subarray