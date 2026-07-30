# Kadane's Algorithm

## Algorithm

### Objective

Find the **maximum sum of any contiguous subarray** in a given array.

### Steps

1. Initialize two variables:
   - `currSum = 0`
   - `maxSum = INT_MIN`

2. Traverse the array from left to right.

3. Add the current element to `currSum`.

4. Update `maxSum` if `currSum` is greater.

5. If `currSum` becomes negative, reset it to `0`.

6. After traversing the entire array, `maxSum` stores the maximum subarray sum.

---

## Approach

Kadane's Algorithm works on the idea that a **negative running sum can never help in obtaining a larger subarray sum in the future**.

- Keep adding elements to the current sum.
- Whenever the current sum becomes negative, discard it by setting it to zero.
- Track the maximum sum encountered during traversal.

---

## C++ Code

```cpp
int maxSubArray(vector<int>& nums)
{
    int currSum = 0;
    int maxSum = INT_MIN;

    for(int i = 0; i < nums.size(); i++)
    {
        currSum += nums[i];

        maxSum = max(maxSum, currSum);

        if(currSum < 0)
            currSum = 0;
    }

    return maxSum;
}
```

---

## Dry Run

### Input

```
[-2,1,-3,4,-1,2,1,-5,4]
```

| Element | Current Sum | Maximum Sum |
|---------:|------------:|------------:|
| -2 | -2 | -2 |
| 1 | 1 | 1 |
| -3 | -2 → 0 | 1 |
| 4 | 4 | 4 |
| -1 | 3 | 4 |
| 2 | 5 | 5 |
| 1 | 6 | 6 |
| -5 | 1 | 6 |
| 4 | 5 | 6 |

### Output

```
6
```

Maximum Subarray:

```
[4,-1,2,1]
```

---

## Complexity

**Time Complexity:** O(n)

**Space Complexity:** O(1)

---

## Key Points

- Traverses the array only once.
- Uses a running sum.
- Resets the running sum whenever it becomes negative.
- Maintains the maximum subarray sum throughout the traversal.
- One of the most frequently asked interview algorithms.