# Rotate Matrix by 90° Clockwise

## Algorithm

### Objective

Rotate a square matrix by **90° clockwise** in-place without using any extra matrix.

---

## Algorithm

1. Find the size `n` of the matrix.

2. Traverse the matrix layer by layer.
   - The outer loop represents each layer.

3. For every layer, traverse all elements except the last one.

4. Store the top element in a temporary variable.

5. Perform the following cyclic replacements:
   - Left → Top
   - Bottom → Left
   - Right → Bottom
   - Temporary (Top) → Right

6. Repeat the process for every layer until the matrix is completely rotated.

---

## Approach

The matrix is divided into concentric layers.

For every layer, four corresponding elements are rotated simultaneously.

Each iteration moves:

Top → Right

Right → Bottom

Bottom → Left

Left → Top

Since only one temporary variable is used, the rotation is performed **in-place**.

---

## C++ Code

```cpp
void rotateMatrix(vector<vector<int>>& mat)
{
    int n = mat.size();

    for(int i = 0; i < n / 2; i++)
    {
        for(int j = i; j < n - i - 1; j++)
        {
            int temp = mat[i][j];

            mat[i][j] = mat[n - 1 - j][i];

            mat[n - 1 - j][i] = mat[n - 1 - i][n - 1 - j];

            mat[n - 1 - i][n - 1 - j] = mat[j][n - 1 - i];

            mat[j][n - 1 - i] = temp;
        }
    }
}
```

---

## Dry Run

### Input

```
1  2  3
4  5  6
7  8  9
```

### First Cycle

Store

```
temp = 1
```

Perform rotations

```
Top    ← Left
Left   ← Bottom
Bottom ← Right
Right  ← temp
```

After all cycles,

### Output

```
7 4 1
8 5 2
9 6 3
```

---

## Complexity

**Time Complexity:** O(n²)

**Space Complexity:** O(1)

---

## Key Points

- Rotates the matrix in-place.
- Uses layer-by-layer traversal.
- Every iteration rotates four elements simultaneously.
- Requires only one temporary variable.
- Works only for square matrices.