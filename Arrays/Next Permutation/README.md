# Next Permutation

## Problem Statement

A permutation of an array of integers is an arrangement of its elements in a sequence.

Given an array of integers, rearrange the numbers into the **lexicographically next greater permutation**.

If such an arrangement is not possible, rearrange it as the **lowest possible order (ascending order)**.

The rearrangement must be done **in-place** using only constant extra memory.

---

## Example 1

### Input

```text
nums = [1,2,3]
```

### Output

```text
[1,3,2]
```

---

## Example 2

### Input

```text
nums = [3,2,1]
```

### Output

```text
[1,2,3]
```

---

## Example 3

### Input

```text
nums = [1,1,5]
```

### Output

```text
[1,5,1]
```

---

# Intuition

To obtain the next permutation, we must make the **smallest possible increase** in the current arrangement.

The idea is:

1. Find the first element from the right that is smaller than its next element (Break Point).
2. Find the smallest element greater than the break point from the right.
3. Swap them.
4. Reverse the remaining suffix to obtain the smallest possible order.

If no break point exists, the array is already the largest permutation, so reverse the entire array.

---

# Approach 1: Brute Force

## Algorithm

- Generate all permutations.
- Sort all permutations lexicographically.
- Find the current permutation.
- Return the next permutation.

### Time Complexity

**O(N! × N)**

### Space Complexity

**O(N! × N)**

---

# Approach 2: Better (STL)

Use the built-in C++ STL function:

```cpp
next_permutation(nums.begin(), nums.end());
```

### Time Complexity

**O(N)**

### Space Complexity

**O(1)**

---

# Approach 3: Optimal

## Algorithm

### Step 1

Traverse from right to left and find the first index where

```text
nums[i] < nums[i + 1]
```

This is called the **break point**.

---

### Step 2

If no break point exists:

Reverse the complete array.

---

### Step 3

Otherwise,

Find the first element from the right that is greater than the break point.

Swap both elements.

---

### Step 4

Reverse the remaining part of the array after the break point.

---

## Dry Run

Input

```text
[2,1,5,4,3,0,0]
```

Break Point

```text
1
```

Swap

```text
2 3 5 4 1 0 0
```

Reverse Suffix

```text
2 3 0 0 1 4 5
```

Final Answer

```text
[2,3,0,0,1,4,5]
```

---

## Time Complexity

**O(3N)**

## Space Complexity

**O(1)**

---

# Edge Cases

- Already the largest permutation
- Single element
- Duplicate elements
- Already the smallest permutation

---

# Key Takeaways

- Traverse from the right.
- Find the break point.
- Swap with the next greater element.
- Reverse only the suffix.
- Reverse the entire array if no break point exists.

---

# Concepts Used

- Arrays
- Two Pointers
- Greedy
- STL

---

# Interview Tip

Instead of memorizing the algorithm, remember the sequence:

**Break Point → Swap → Reverse**

This is the easiest way to derive the solution during interviews.

---

# Related Problems

- Permutations
- Previous Permutation
- Lexicographical Order