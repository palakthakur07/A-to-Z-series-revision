# Set Matrix Zeroes

## Problem Statement

Given an `n x m` matrix, if an element is **0**, set its entire row and column to **0**.

The operation must be performed on the matrix itself.

### Example

**Input**

```
1 1 1
1 0 1
1 1 1
```

**Output**

```
1 0 1
0 0 0
1 0 1
```

---

# Approaches

## 1. Brute Force

### Idea

Whenever a `0` is found:

- Mark its entire row as `-1` (except existing zeros).
- Mark its entire column as `-1`.
- After processing the whole matrix, convert every `-1` into `0`.

### Time Complexity

```
O((N×M) × (N+M))
```

### Space Complexity

```
O(1)
```

---

## 2. Better Approach

### Idea

Instead of modifying the matrix immediately:

- Maintain two arrays:
  - `row[]`
  - `col[]`
- If matrix[i][j] == 0:
  - row[i] = 1
  - col[j] = 1
- Traverse the matrix again and make every marked row/column zero.

### Time Complexity

```
O(2 × N × M)
```

### Space Complexity

```
O(N + M)
```

---

## 3. Optimal Approach

### Idea

Instead of using two extra arrays, use:

- First row as the column marker.
- First column as the row marker.
- Store whether the first column should become zero using a separate variable (`col0`).

This reduces the extra space to constant.

### Time Complexity

```
O(2 × N × M)
```

### Space Complexity

```
O(1)
```

---

# Comparison

| Approach | Time | Space |
|----------|------|-------|
| Brute | O((N×M)×(N+M)) | O(1) |
| Better | O(2×N×M) | O(N+M) |
| Optimal | O(2×N×M) | O(1) |

---

# Interview Tip

The Optimal approach uses the **first row and first column as marker arrays**, eliminating the need for extra row[] and col[] arrays while keeping the solution in-place.