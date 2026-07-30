# Spiral Matrix Traversal Algorithm

## Algorithm

### Objective

Traverse all elements of a matrix in **spiral order**.

The traversal follows the sequence:

```
Left → Right
Top → Bottom
Right → Left
Bottom → Top
```

This process continues until all elements have been visited.

---

## Algorithm

1. Initialize four boundaries:

   - `top = 0`
   - `bottom = rows - 1`
   - `left = 0`
   - `right = columns - 1`

2. Repeat while:

   ```
   top <= bottom && left <= right
   ```

3. Traverse the **top row** from left to right.

4. Increment `top`.

5. Traverse the **right column** from top to bottom.

6. Decrement `right`.

7. If `top <= bottom`, traverse the **bottom row** from right to left.

8. Decrement `bottom`.

9. If `left <= right`, traverse the **left column** from bottom to top.

10. Increment `left`.

11. Repeat until all elements are visited.

---

## Approach

The matrix is traversed layer by layer.

Four boundaries are maintained:

- `top`
- `bottom`
- `left`
- `right`

After completing one side of the current rectangle, the corresponding boundary is moved inward.

This gradually reduces the size of the unvisited matrix until every element has been visited exactly once.

---

## C++ Code

```cpp
vector<int> spirallyTraverse(vector<vector<int>>& mat)
{
    int m = mat.size();
    int n = mat[0].size();

    vector<int> res;

    int top = 0;
    int bottom = m - 1;
    int left = 0;
    int right = n - 1;

    while(top <= bottom && left <= right)
    {
        for(int i = left; i <= right; i++)
            res.push_back(mat[top][i]);
        top++;

        for(int i = top; i <= bottom; i++)
            res.push_back(mat[i][right]);
        right--;

        if(top <= bottom)
        {
            for(int i = right; i >= left; i--)
                res.push_back(mat[bottom][i]);
            bottom--;
        }

        if(left <= right)
        {
            for(int i = bottom; i >= top; i--)
                res.push_back(mat[i][left]);
            left++;
        }
    }

    return res;
}
```

---

## Dry Run

### Input

```
1   2   3   4
5   6   7   8
9  10  11  12
13 14  15 16
```

### Traversal Order

```
Top Row
↓

1 2 3 4

↓

Right Column

8 12 16

↓

Bottom Row

15 14 13

↓

Left Column

9 5

↓

Inner Matrix

6 7 11 10
```

### Output

```
1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10
```

---

## Complexity

**Time Complexity:** O(m × n)

**Space Complexity:** O(1) Auxiliary Space

> Note: The returned vector stores the output and is not counted as extra working space.

---

## Key Points

- Uses four boundaries:
  - `top`
  - `bottom`
  - `left`
  - `right`
- Traverses the matrix layer by layer.
- Every element is visited exactly once.
- The two `if` conditions prevent duplicate traversal when only one row or one column remains.