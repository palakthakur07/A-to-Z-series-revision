# Intersection of Two Sorted Arrays

## Problem Statement

Given two sorted arrays, return the intersection of both arrays.

Each common element should appear as many times as it appears in both arrays.

---

## Example

### Input

```text
arr1 = {1,2,2,3,3,4,5,6}
arr2 = {2,3,3,5,6,6,7}
```

### Output

```text
{2,3,3,5,6}
```

---

# Approach 1 : Brute Force (Visited Array)

## Algorithm

1. Create a visited array of size `n2` initialized with `0`.
2. Traverse every element of the first array.
3. For each element, search it in the second array.
4. If found and not visited:
   - Add it to the answer.
   - Mark it as visited.
5. If the current element in the second array becomes greater than the current element in the first array, break the inner loop.

---

## Code Logic

```cpp
vector<int> ans;
int vis[n2] = {0};

for(int i = 0; i < n1; i++)
{
    for(int j = 0; j < n2; j++)
    {
        if(arr1[i] == arr2[j] && vis[j] == 0)
        {
            ans.push_back(arr1[i]);
            vis[j] = 1;
            break;
        }

        if(arr2[j] > arr1[i])
            break;
    }
}

return ans;
```

---

## Time Complexity

```
O(N1 × N2)
```

## Space Complexity

```
O(N2)
```

---

# Approach 2 : Optimal (Two Pointers)

## Algorithm

1. Initialize two pointers `i = 0` and `j = 0`.
2. If `arr1[i] < arr2[j]`, increment `i`.
3. If `arr2[j] < arr1[i]`, increment `j`.
4. If both are equal:
   - Store the element.
   - Increment both pointers.
5. Continue until one array finishes.

---

## Code Logic

```cpp
while(i < n1 && j < n2)
{
    if(arr1[i] < arr2[j])
    {
        i++;
    }
    else if(arr2[j] < arr1[i])
    {
        j++;
    }
    else
    {
        ans.push_back(arr1[i]);
        i++;
        j++;
    }
}

return ans;
```

---

## Dry Run

```text
arr1 = {1,2,2,3,3,4,5,6}
arr2 = {2,3,3,5,6,6,7}

i=0,j=0

1<2 → i++

2==2 → add 2

2<3 → i++

3==3 → add 3

3==3 → add 3

4<5 → i++

5==5 → add 5

6==6 → add 6

Answer = {2,3,3,5,6}
```

---

## Time Complexity

```
O(N1 + N2)
```

## Space Complexity

```
O(1) Auxiliary Space

O(K) space is used only for storing the returned answer.
```

---

## Interview Tip

Whenever both arrays are sorted, always think about the **Two Pointer** technique before using nested loops.