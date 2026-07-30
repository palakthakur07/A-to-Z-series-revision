# Check if an Array is Sorted

## Problem Statement

Given an array of integers, determine whether the array is sorted in non-decreasing order.

Return:

- `true` if the array is sorted.
- `false` otherwise.

---

## Example 1

**Input**

```text
arr = {1,2,2,3,4,5}
```

**Output**

```text
true
```

---

## Example 2

**Input**

```text
arr = {1,3,2,4}
```

**Output**

```text
false
```

---

# Optimal Approach (Single Traversal)

## Algorithm

1. Traverse the array from index `1`.
2. Compare the current element with the previous element.
3. If `arr[i] < arr[i-1]`, the array is not sorted.
4. Otherwise, continue the traversal.
5. If no violation is found, return `true`.

---

## Code

```cpp
for(int i = 1; i < n; i++)
{
    if(arr[i] < arr[i - 1])
        return false;
}

return true;
```

---

## Dry Run

```text
arr = {1,2,2,3,4}

2 >= 1 ✓

2 >= 2 ✓

3 >= 2 ✓

4 >= 3 ✓

Answer = true
```

---

### Dry Run 2

```text
arr = {1,3,2,4}

3 >= 1 ✓

2 < 3 ✗

Answer = false
```

---

## Time Complexity

```
O(N)
```

## Space Complexity

```
O(1)
```

---

## Interview Tip

The moment you find an element smaller than its previous element, return `false` immediately. This avoids unnecessary iterations.