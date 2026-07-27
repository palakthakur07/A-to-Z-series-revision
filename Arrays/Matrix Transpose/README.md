# Matrix Transpose Algorithm

## Algorithm

### Objective

Find the **transpose** of a given matrix.

In a transpose, every element at position **(i, j)** moves to **(j, i)**.

---

## Algorithm

1. Find the number of rows and columns.
2. Create a new matrix having:
   - Number of rows = Original columns
   - Number of columns = Original rows
3. Traverse every element of the original matrix.
4. Copy every element using:
   ```
   transpose[j][i] = matrix[i][j]
   ```
5. Return the transpose matrix.

---

## Approach

The transpose of a matrix is obtained by converting its rows into columns.

For every element:

```
(i, j)

↓

(j, i)
```

Since the dimensions change after transpose, a new matrix is created to store the result.

---

## C++ Code

```cpp
vector<vector<int>> transpose(vector<vector<int>>& mat)
{
    int rows = mat.size();
    int cols = mat[0].size();

    vector<vector<int>> tMat(cols, vector<int>(rows));

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            tMat[j][i] = mat[i][j];
        }
    }

    return tMat;
}
```

---

## Dry Run

### Input

```
1 2 3
4 5 6
```

### Initial Transpose Matrix

```
0 0
0 0
0 0
```

### Step-by-Step

```
tMat[0][0] = 1
tMat[1][0] = 2
tMat[2][0] = 3

tMat[0][1] = 4
tMat[1][1] = 5
tMat[2][1] = 6
```

### Output

```
1 4
2 5
3 6
```

---

## Complexity

**Time Complexity:** O(rows × cols)

**Space Complexity:** O(rows × cols)

---

## Key Points

- Every element `(i, j)` becomes `(j, i)`.
- Rows become columns.
- Columns become rows.
- Uses an extra matrix to store the transpose.
- Works for both square and rectangular matrices.