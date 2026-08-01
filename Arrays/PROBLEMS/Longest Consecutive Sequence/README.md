# Longest Consecutive Sequence

## Problem Statement

Given an unsorted array of integers, return the length of the longest consecutive elements sequence.

### Example

Input:
```
arr = [102, 4, 100, 1, 101, 3, 2, 1]
```

Output:
```
4
```

Explanation:

The longest consecutive sequence is:

```
1 → 2 → 3 → 4
```

Length = **4**

---

# Approaches

## 1. Brute Force

### Idea

For every element:

- Start the sequence from that element.
- Check whether the next consecutive number exists using linear search.
- Continue until the sequence breaks.
- Store the maximum length.

### Algorithm

- Take every element as the starting element.
- Search for `x+1`.
- If found, continue.
- Update the maximum length.

### Time Complexity

```
O(N²)
```

### Space Complexity

```
O(1)
```

---

## 2. Better Approach (Sorting)

### Idea

Sort the array first.

After sorting:

- Ignore duplicate elements.
- If current element = previous + 1,
  increase count.
- Otherwise start a new sequence.
- Keep updating the longest length.

### Time Complexity

```
O(N log N) + O(N)
```

### Space Complexity

```
O(1)
```

> **Note:** Sorting changes the original array.

---

## 3. Optimal Approach (Hash Set)

### Idea

Store every element inside an unordered set.

A number is considered the **starting point** of a sequence only if:

```
number - 1
```

does **not** exist.

Then keep checking

```
number + 1
number + 2
number + 3
...
```

until the sequence ends.

Update the maximum length.

### Time Complexity

```
O(3N) ≈ O(N)
```

### Space Complexity

```
O(N)
```

---

# Comparison

| Approach | Time | Space |
|----------|------|-------|
| Brute | O(N²) | O(1) |
| Better | O(N log N) | O(1) |
| Optimal | O(N) | O(N) |

---

# Interview Tip

The Optimal approach works because we only start counting from the **first element of a sequence**, avoiding repeated work.