# Second Largest Element in an Array

## Problem Statement

Given an array of integers, find the second largest distinct element in the array.

If no second largest element exists, return -1.

### Example

**Input**

```text
arr = {1, 2, 4, 7, 7, 5}
```

**Output**

```text
5
```

---

# Approach 1 : Sorting

## Algorithm

1. Sort the array.
2. Store the largest element.
3. Traverse from the second last element towards the beginning.
4. The first element different from the largest is the second largest.

## Code

```cpp
sort(arr.begin(), arr.end());

int largest = arr[n-1];

for(int i=n-2;i>=0;i--)
{
    if(arr[i] != largest)
        return arr[i];
}

return -1;
```

### Time Complexity

```
O(N log N)
```

### Space Complexity

```
O(1)
```

---

# Approach 2 : Better (Two Traversals)

## Algorithm

1. Find the largest element.
2. Traverse the array again.
3. Find the largest element smaller than the maximum.

## Dry Run

```text
arr = {1,2,4,7,7,5}

Largest = 7

1 → secondLargest = 1

2 → secondLargest = 2

4 → secondLargest = 4

7 → Ignore

7 → Ignore

5 → secondLargest = 5

Answer = 5
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

# Approach 3 : Optimal (Single Traversal)

## Algorithm

Maintain two variables:

- largest
- secondLargest

While traversing:

- If current element is greater than largest
    - secondLargest = largest
    - largest = current element
- Else if current element is smaller than largest but greater than secondLargest
    - Update secondLargest

## Dry Run

```text
arr = {1,2,4,7,7,5}

largest = 1
secondLargest = -1

2
largest = 2
secondLargest = 1

4
largest = 4
secondLargest = 2

7
largest = 7
secondLargest = 4

7
Ignore

5
secondLargest = 5

Answer = 5
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

# Interview Tip

The single traversal approach is the most efficient and is the one commonly expected during coding interviews.