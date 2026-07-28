# Left Rotate Array by One Place

## Problem Statement

Given an array, rotate all elements to the left by one position.

The first element moves to the last position, and every other element shifts one position to the left.

---

## Example

### Input

```text
arr = {1,2,3,4,5}
```

### Output

```text
{2,3,4,5,1}
```

---

# Approach : Optimal (Using Temporary Variable)

## Algorithm

1. Store the first element of the array in a variable.
2. Shift all elements one position towards the left.
3. Place the stored first element at the last index.

---

## Code Logic

```cpp
temp = arr[0];

for(i = 1; i < n; i++)
{
    arr[i-1] = arr[i];
}

arr[n-1] = temp;
```

---

## Dry Run

```text
arr = {1,2,3,4,5}

temp = 1

Shift left:

2 3 4 5 _

Place temp at end:

2 3 4 5 1
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

Since only one rotation is required, storing only the first element is enough. No extra array is needed.