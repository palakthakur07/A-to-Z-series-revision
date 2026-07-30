# Array Rotation Algorithm

## Algorithm

### Objective

Rotate an array by **k positions to the right** using the **Reversal Algorithm**.

### Steps

1. Find the size of the array `n`.
2. Compute the effective rotations:
   - `k = k % n`
3. Reverse the entire array.
4. Reverse the first `k` elements.
5. Reverse the remaining `n-k` elements.
6. The array is now rotated by `k` positions.

---

## Approach

Instead of shifting every element one by one, we use the **Reversal Algorithm**.

The idea is:

- Reverse the complete array.
- Reverse the first `k` elements.
- Reverse the remaining elements.

This rotates the array in **O(n)** time without using an extra array.

---

## C++ Code

```cpp
void reverse(vector<int> &arr, int start, int end)
{
    while(start < end)
    {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

void rotate(vector<int> &arr, int k)
{
    int n = arr.size();

    k = k % n;

    reverse(arr, 0, n - 1);

    reverse(arr, 0, k - 1);

    reverse(arr, k, n - 1);
}
```

---

## Dry Run

### Input

```
Array = [1,2,3,4,5,6,7]

k = 3
```

### Step 1

Reverse complete array

```
7 6 5 4 3 2 1
```

### Step 2

Reverse first 3 elements

```
5 6 7 4 3 2 1
```

### Step 3

Reverse remaining elements

```
5 6 7 1 2 3 4
```

### Output

```
[5,6,7,1,2,3,4]
```

---

## Complexity

**Time Complexity:** O(n)

**Space Complexity:** O(1)

---

## Key Points

- Uses the Reversal Algorithm.
- Rotates the array in-place.
- Handles cases where `k > n` using `k = k % n`.
- More efficient than rotating one element at a time.