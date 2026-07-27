# Matrix Multiplication Algorithm

## Algorithm

### Objective

Multiply two square matrices of size **n × n** and return the resultant matrix.

---

## Algorithm

1. Determine the size `n` of the matrices.

2. Create a result matrix of size `n × n` initialized with `0`.

3. Traverse every row of the first matrix using index `i`.

4. Traverse every column of the second matrix using index `j`.

5. For every element `(i, j)`, calculate:

   ```
   result[i][j] += firstMatrix[i][k] × secondMatrix[k][j]
   ```

   where `k` iterates from `0` to `n-1`.

6. Return the resultant matrix.

---

## Approach

Matrix multiplication is performed by multiplying the elements of a row from the first matrix with the corresponding elements of a column from the second matrix.

For every cell in the answer matrix:

- Select one row from the first matrix.
- Select one column from the second matrix.
- Multiply corresponding elements.
- Add all the products.
- Store the final sum in the current cell.

---

## C++ Code

```cpp
vector<vector<int>> multiply(vector<vector<int>>& arr,
                             vector<vector<int>>& brr)
{
    int n = arr.size();

    vector<vector<int>> res(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < n; k++)
            {
                res[i][j] += arr[i][k] * brr[k][j];
            }
        }
    }

    return res;
}
```

---

## Dry Run

### Input

Matrix A

```
1 2
3 4
```

Matrix B

```
5 6
7 8
```

### Calculation

Result[0][0]

```
= (1×5) + (2×7)

= 5 + 14

= 19
```

Result[0][1]

```
= (1×6) + (2×8)

= 6 + 16

= 22
```

Result[1][0]

```
= (3×5) + (4×7)

= 15 + 28

= 43
```

Result[1][1]

```
= (3×6) + (4×8)

= 18 + 32

= 50
```

### Output

```
19 22
43 50
```

---

## Complexity

**Time Complexity:** O(n³)

**Space Complexity:** O(n²)

---

## Key Points

- Uses three nested loops.
- `i` represents the row of the first matrix.
- `j` represents the column of the second matrix.
- `k` performs the row-column multiplication.
- The result matrix is initialized with `0` because every cell stores the sum of multiple products.