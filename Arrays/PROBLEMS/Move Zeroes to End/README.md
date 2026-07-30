# Move Zeroes to End

## Problem Statement

Given an array of integers, move all zeroes to the end while maintaining the relative order of the non-zero elements.

---

## Example

**Input**

```text
arr = {1,0,2,3,0,4,0,1}
```

**Output**

```text
1 2 3 4 1 0 0 0
```

---

# Approach 1 : Brute Force (Using Temporary Array)

## Algorithm

1. Store all non-zero elements in a temporary array.
2. Copy them back to the original array.
3. Fill the remaining positions with zeroes.

### Time Complexity

```
O(N)
```

### Space Complexity

```
O(N)
```

---

# Approach 2 : Optimal (Two Pointers)

## Algorithm

1. Find the first zero in the array.
2. Traverse the remaining array.
3. Whenever a non-zero element is found, swap it with the zero position.
4. Move the zero pointer forward.

### Dry Run

```text
Input

1 0 2 3 0 4 0 1

↓

Swap(2,0)

1 2 0 3 0 4 0 1

↓

Swap(3,0)

1 2 3 0 0 4 0 1

↓

Swap(4,0)

1 2 3 4 0 0 0 1

↓

Swap(1,0)

1 2 3 4 1 0 0 0
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

The optimal solution uses the **two-pointer technique**, making it both efficient and in-place.