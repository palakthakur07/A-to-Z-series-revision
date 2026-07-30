# Left Rotate Array by D Places

## Problem Statement

Given an array of integers, rotate the array to the left by `D` places.

---

## Example

**Input**

```text
arr = {1,2,3,4,5,6,7}
D = 2
```

**Output**

```text
3 4 5 6 7 1 2
```

---

# Approach 1 : Brute Force (Using Temporary Array)

## Algorithm

1. Compute `D = D % N`.
2. Store the first `D` elements in a temporary array.
3. Shift the remaining elements to the left.
4. Copy the temporary array to the end.

---

## Code

```cpp
d = d % n;

vector<int> temp;

for(int i = 0; i < d; i++)
    temp.push_back(arr[i]);

for(int i = d; i < n; i++)
    arr[i-d] = arr[i];

for(int i = n-d; i < n; i++)
    arr[i] = temp[i-(n-d)];
```

### Dry Run

```text
arr = {1,2,3,4,5,6,7}
D = 2

Temp = {1,2}

Shift Left

3 4 5 6 7 _ _

Copy Temp

3 4 5 6 7 1 2
```

### Time Complexity

```
O(N)
```

### Space Complexity

```
O(D)
```

---

# Approach 2 : Optimal (Reversal Algorithm)

## Algorithm

1. Compute `D = D % N`.
2. Reverse first `D` elements.
3. Reverse remaining `N-D` elements.
4. Reverse the complete array.

---

## Code

```cpp
d = d % n;

reverse(arr.begin(), arr.begin()+d);

reverse(arr.begin()+d, arr.end());

reverse(arr.begin(), arr.end());
```

### Dry Run

```text
arr = {1,2,3,4,5,6,7}
D = 2

Reverse First D

2 1 3 4 5 6 7

Reverse Remaining

2 1 7 6 5 4 3

Reverse Whole Array

3 4 5 6 7 1 2
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

Always compute

```cpp
d = d % n;
```

This handles cases where `D > N` and prevents unnecessary rotations.