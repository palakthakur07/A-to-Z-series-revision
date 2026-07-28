# Largest Element in an Array

## Problem Statement

Given an array of integers, find the largest element present in the array.

### Example

Input

```text
arr = {3, 2, 1, 5, 2}
```

Output

```text
5
```

---

## Approach 1 : Sorting

### Algorithm

1. Sort the array.
2. Return the last element.

### Code

```cpp
sort(arr.begin(), arr.end());
return arr[n - 1];
```

### Time Complexity

```
O(N log N)
```

### Space Complexity

```
O(1)
```

---

## Approach 2 : Optimal (Linear Traversal)

### Algorithm

1. Assume the first element is the largest.
2. Traverse the array.
3. If the current element is greater than the largest, update it.
4. Return the largest element.

### Dry Run

```text
arr = {3, 2, 1, 5, 2}

largest = 3

2 > 3 ❌
1 > 3 ❌
5 > 3 ✅ largest = 5
2 > 5 ❌

Answer = 5
```

### Time Complexity

```
O(N)
```

### Space Complexity

```
O(1)
```

---

## Interview Tip

The optimal solution is preferred because it scans the array only once without sorting.