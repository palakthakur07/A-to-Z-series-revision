# Linear Search

## Problem Statement

Given an array of integers and a target element, return the index of the target element if it exists. Otherwise, return `-1`.

---

## Example

### Input

```text
arr = {6, 7, 8, 4, 1}
target = 4
```

### Output

```text
3
```

Explanation:

```
arr[3] = 4
```

---

# Approach (Linear Traversal)

## Algorithm

1. Traverse the array from index `0`.
2. Compare every element with the target.
3. If both are equal, return the current index.
4. If the loop ends without finding the target, return `-1`.

---

## Code Logic

```cpp
for(int i = 0; i < n; i++)
{
    if(arr[i] == target)
        return i;
}

return -1;
```

---

## Dry Run

```text
arr = {6, 7, 8, 4, 1}
target = 4

i = 0 → 6 ≠ 4

i = 1 → 7 ≠ 4

i = 2 → 8 ≠ 4

i = 3 → 4 = 4 ✅

Return 3
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

## Key Points

- Works on both sorted and unsorted arrays.
- Checks every element one by one.
- Simple but inefficient for large datasets.

---

## Interview Tip

If the array is sorted, Binary Search is preferred because it works in **O(log N)** time.