# Remove Duplicates from Sorted Array

## Problem Statement

Given a sorted array, remove the duplicate elements in-place such that each unique element appears only once.

Return the number of unique elements.

---

## Example

**Input**

```text
arr = {1,1,2,2,2,3,3}
```

**Output**

```text
Length = 3

Array = {1,2,3}
```

---

# Approach 1 : Brute Force (Using Set)

## Algorithm

1. Insert all array elements into a set.
2. Copy the set elements back to the array.
3. Return the size of the set.

---

## Code

```cpp
set<int> st;

for(int i = 0; i < n; i++)
{
    st.insert(arr[i]);
}

int index = 0;

for(auto it : st)
{
    arr[index] = it;
    index++;
}

return index;
```

---

## Time Complexity

```
O(N log N)
```

## Space Complexity

```
O(N)
```

---

# Approach 2 : Optimal (Two Pointers)

## Algorithm

1. Initialize pointer `i = 0`.
2. Traverse the array using pointer `j`.
3. Whenever `arr[j] != arr[i]`
   - Increment `i`
   - Copy `arr[j]` to `arr[i]`
4. Return `i + 1`.

---

## Code

```cpp
int i = 0;

for(int j = 1; j < n; j++)
{
    if(arr[i] != arr[j])
    {
        i++;
        arr[i] = arr[j];
    }
}

return i + 1;
```

---

## Dry Run

```text
arr = {1,1,2,2,3,3}

i = 0

j = 1

1 == 1

Ignore

j = 2

2 != 1

i = 1

arr[1] = 2

Array

1 2 2 2 3 3

j = 3

2 == 2

Ignore

j = 4

3 != 2

i = 2

arr[2] = 3

Array

1 2 3 2 3 3

Length = 3
```

---

## Time Complexity

```
O(N)
```

## Space Complexity

```
O(1)
```

---

## Interview Tip

Since the array is already sorted, all duplicate elements are adjacent. This property allows us to solve the problem efficiently using the two-pointer technique without any extra space.