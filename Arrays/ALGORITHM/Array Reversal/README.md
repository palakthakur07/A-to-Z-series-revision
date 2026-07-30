# Array Reversal Algorithm

## Algorithm

### Objective

Reverse all elements of an array in-place.

### Steps

1. Initialize two pointers:
   - `left = 0`
   - `right = n - 1`

2. Repeat while `left < right`:
   - Swap `arr[left]` and `arr[right]`.
   - Increment `left`.
   - Decrement `right`.

3. When `left >= right`, the array has been completely reversed.

---

## Pseudocode

```
left = 0
right = n - 1

while(left < right)
{
    swap(arr[left], arr[right])
    left++
    right--
}
```

---

## Working Principle

The algorithm swaps the first element with the last element, the second element with the second-last element, and so on. The process continues until both pointers meet or cross each other.

---

## Example

Input

```
[1, 2, 3, 4, 5]
```

Step 1

```
Swap 1 and 5

[5, 2, 3, 4, 1]
```

Step 2

```
Swap 2 and 4

[5, 4, 3, 2, 1]
```

Pointers meet at `3`.

Output

```
[5, 4, 3, 2, 1]
```

---

## Complexity

Time Complexity: **O(n)**

Space Complexity: **O(1)**

---

## Key Points

- Uses the Two Pointer technique.
- Reverses the array in-place.
- Every element is swapped at most once.
- Stops when both pointers meet or cross.