# Count Subarray Sum Equals K

## Problem Statement

Given an integer array `nums` and an integer `k`, return the **total number of continuous subarrays whose sum equals `k`**.

---

## Example

### Input

```text
nums = [1,1,1]
k = 2
```

### Output

```text
2
```

### Explanation

The subarrays with sum equal to `2` are:

```text
[1,1] (Index 0 to 1)
[1,1] (Index 1 to 2)
```

Hence, the answer is **2**.

---

# Intuition

A brute force solution checks every possible subarray and calculates its sum.

A better solution avoids recalculating the sum by maintaining a running sum.

The optimal solution uses the **Prefix Sum + Hash Map** technique to find how many previous prefix sums satisfy the required condition.

---

# Approach 1: Brute Force

## Algorithm

- Generate every possible subarray.
- Calculate the sum of each subarray.
- If the sum equals `k`, increase the count.

### Time Complexity

```
O(N³)
```

### Space Complexity

```
O(1)
```

---

# Approach 2: Better

## Algorithm

- Fix the starting index.
- Maintain a running sum while extending the ending index.
- If the running sum becomes equal to `k`, increase the count.

### Time Complexity

```
O(N²)
```

### Space Complexity

```
O(1)
```

---

# Approach 3: Optimal (Prefix Sum + Hash Map)

## Idea

Maintain:

- `preSum` → Prefix Sum till current index.
- `mpp` → Stores the frequency of every prefix sum.

Initially,

```cpp
mpp[0] = 1;
```

For every element:

- Add the current element to `preSum`.
- Calculate

```text
remove = preSum - k
```

- If `remove` exists in the map, then all those prefix sums can form a valid subarray ending at the current index.
- Add their frequency to the answer.
- Store the current prefix sum in the map.

### Time Complexity

```
O(N)
```

### Space Complexity

```
O(N)
```

---

# Dry Run

Input

```text
nums = [1,2,3]
k = 3
```

| Index | Element | Prefix Sum | Remove (`preSum-k`) | Count |
|------:|--------:|-----------:|--------------------:|------:|
|0|1|1|-2|0|
|1|2|3|0|1|
|2|3|6|3|2|

Final Answer

```text
2
```

---

# Comparison

| Approach | Time | Space |
|----------|------|-------|
| Brute | O(N³) | O(1) |
| Better | O(N²) | O(1) |
| Optimal | O(N) | O(N) |

---

# Key Takeaways

- Prefix Sum stores the sum from index `0` to the current index.
- Hash Map stores the frequency of prefix sums.
- `remove = preSum - k` helps identify valid subarrays efficiently.
- Initialize `mpp[0] = 1` to handle subarrays starting from index `0`.

---

# Concepts Used

- Arrays
- Prefix Sum
- Hash Map

---

# Interview Tip

Always remember this equation:

```text
Current Prefix Sum - Previous Prefix Sum = K
```

which means,

```text
Previous Prefix Sum = Current Prefix Sum - K
```

This is the key idea behind the optimal solution.