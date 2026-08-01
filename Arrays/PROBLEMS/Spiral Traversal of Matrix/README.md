# Spiral Traversal of Matrix

## Problem Statement

Given an `N × M` matrix, return all elements of the matrix in **spiral order**.

### Example

**Input**

```
1  2  3
4  5  6
7  8  9
```

**Output**

```
[1,2,3,6,9,8,7,4,5]
```

---

# Approach (Optimal)

## Idea

Maintain four boundaries:

- `top`
- `bottom`
- `left`
- `right`

Traverse the matrix layer by layer in four directions:

1. Left → Right
2. Top → Bottom
3. Right → Left
4. Bottom → Top

After every traversal, update the corresponding boundary.

Continue until all elements are visited.

---

## Algorithm

1. Initialize

```
top = 0
bottom = n - 1
left = 0
right = m - 1
```

2. Traverse from **Left → Right**

```
top++
```

3. Traverse from **Top → Bottom**

```
right--
```

4. If `top <= bottom`

Traverse from **Right → Left**

```
bottom--
```

5. If `left <= right`

Traverse from **Bottom → Top**

```
left++
```

Repeat until

```
top > bottom
or
left > right
```

---

## Dry Run

Matrix

```
1 2 3
4 5 6
7 8 9
```

Traversal

```
1 2 3
6
9
8 7
4
5
```

Output

```
[1,2,3,6,9,8,7,4,5]
```

---

## Time Complexity

```
O(N × M)
```

## Space Complexity

```
O(1)
```

**Note:** The output array is not considered extra space.

---

# Key Points

- Four boundaries are maintained.
- Each element is visited exactly once.
- Works for both square and rectangular matrices.

---

# Concepts Used

- Matrix
- Simulation
- Boundary Traversal

---

# Interview Tip

Always check:

```cpp
if(top <= bottom)
```

and

```cpp
if(left <= right)
```

before traversing the bottom row and left column. These conditions prevent visiting the same row or column twice in matrices with a single remaining row or column.