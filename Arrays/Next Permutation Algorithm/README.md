# Next Permutation Algorithm

## Algorithm

### Objective

Find the **next lexicographically greater permutation** of the given array.

If no next permutation exists, rearrange the array into the **smallest possible order** (ascending order).

---

## Algorithm

1. Traverse the array from right to left and find the first index `i` such that:

   ```
   nums[i] < nums[i + 1]
   ```

   This index is called the **pivot**.

2. If a pivot exists:
   - Traverse from the end of the array.
   - Find the first element greater than `nums[i]`.
   - Swap both elements.

3. Reverse all elements after the pivot (`i + 1` to `n - 1`).

4. The resulting array is the next permutation.

---

## Approach

The algorithm finds the first position from the right where the increasing order breaks.

- The suffix after the pivot is always in decreasing order.
- Swap the pivot with the smallest greater element present in the suffix.
- Reverse the suffix to obtain the smallest possible arrangement after the pivot.

This guarantees the immediate next lexicographical permutation.

---

## C++ Code

```cpp
void nextPermutation(vector<int>& nums)
{
    int n = nums.size();
    int i = n - 2;

    while(i >= 0 && nums[i] >= nums[i + 1])
        i--;

    if(i >= 0)
    {
        int j = n - 1;

        while(nums[j] <= nums[i])
            j--;

        swap(nums[i], nums[j]);
    }

    reverse(nums.begin() + i + 1, nums.end());
}
```

---

## Dry Run

### Input

```
[1,2,3,6,5,4]
```

### Step 1

Find Pivot

```
3 < 6

Pivot = 3
```

### Step 2

Find first greater element from the end

```
4
```

Swap

```
1 2 4 6 5 3
```

### Step 3

Reverse the suffix

```
6 5 3

↓

3 5 6
```

### Output

```
[1,2,4,3,5,6]
```

---

## Complexity

**Time Complexity:** O(n)

**Space Complexity:** O(1)

---

## Key Points

- Finds the next lexicographical permutation.
- Traverses the array from right to left.
- The suffix after the pivot is always in decreasing order.
- Reversing the suffix produces the smallest possible order.
- If no pivot exists, reversing the entire array gives the first permutation.