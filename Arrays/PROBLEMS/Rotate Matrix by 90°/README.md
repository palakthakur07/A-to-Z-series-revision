# Rotate Matrix by 90°

## Problem Statement

Given an **N × N** matrix, rotate it by **90° clockwise**.

The rotation should be performed in-place if possible.

### Example

**Input**

```
1   2   3
4   5   6
7   8   9
```

**Output**

```
7   4   1
8   5   2
9   6   3
```

---

# Approaches

## 1. Brute Force

### Idea

Create a new matrix `ans`.

For every element:

```
mat[i][j] → ans[j][n-1-i]
```

Finally, return the new matrix.

### Time Complexity

```
O(N²)
```

### Space Complexity

```
O(N²)
```

---

## 2. Optimal Approach

### Idea

Instead of using another matrix:

### Step 1

Take the transpose of the matrix.

```
mat[i][j] ↔ mat[j][i]
```

(Diagonal elements remain at the same position.)

### Step 2

Reverse every row.

The matrix becomes rotated by **90° clockwise**.

### Time Complexity

```
O(N²)
```

### Space Complexity

```
O(1)
```

---

# Comparison

| Approach | Time | Space |
|----------|------|-------|
| Brute | O(N²) | O(N²) |
| Optimal | O(N²) | O(1) |

---

# Interview Tip

The Optimal approach performs the rotation **in-place** by using two simple operations:

1. Transpose the matrix.
2. Reverse every row.

This avoids using any extra matrix.