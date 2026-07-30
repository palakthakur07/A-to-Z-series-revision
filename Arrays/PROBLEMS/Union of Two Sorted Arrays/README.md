# Union of Two Sorted Arrays

## Problem Statement

Given two sorted arrays, return the union of both arrays.

The union should contain all distinct elements in sorted order.

---

## Example

### Input

```text
arr1 = {1,1,2,3,4,5}
arr2 = {2,3,4,4,5}
```

### Output

```text
{1,2,3,4,5}
```

---

# Approach 1 : Brute Force (Using Set)

## Algorithm

1. Create a `set`.
2. Insert all elements of the first array.
3. Insert all elements of the second array.
4. Copy all elements from the set into the answer vector.
5. Return the answer.

---

## Code Logic

```cpp
set<int> st;

for(int i = 0; i < n1; i++)
{
    st.insert(arr1[i]);
}

for(int i = 0; i < n2; i++)
{
    st.insert(arr2[i]);
}

vector<int> ans;

for(auto it : st)
{
    ans.push_back(it);
}

return ans;
```

---

## Time Complexity

```
O((N1 + N2) log(N1 + N2))
```

## Space Complexity

```
O(N1 + N2)
```

---

# Approach 2 : Optimal (Two Pointers)

## Algorithm

1. Initialize two pointers `i = 0` and `j = 0`.
2. Compare elements of both arrays.
3. Insert the smaller element into the answer vector if it is not already the last inserted element.
4. Move the corresponding pointer.
5. After one array finishes, insert the remaining elements from the other array while avoiding duplicates.

---

## Code Logic

```cpp
while(i < n1 && j < n2)
{
    if(arr1[i] <= arr2[j])
    {
        if(ans.size() == 0 || ans.back() != arr1[i])
            ans.push_back(arr1[i]);

        i++;
    }
    else
    {
        if(ans.size() == 0 || ans.back() != arr2[j])
            ans.push_back(arr2[j]);

        j++;
    }
}

while(i < n1)
{
    if(ans.size() == 0 || ans.back() != arr1[i])
        ans.push_back(arr1[i]);

    i++;
}

while(j < n2)
{
    if(ans.size() == 0 || ans.back() != arr2[j])
        ans.push_back(arr2[j]);

    j++;
}

return ans;
```

---

## Dry Run

```text
arr1 = {1,1,2,3,4,5}
arr2 = {2,3,4,4,5}

Answer

1

2

3

4

5
```

---

## Time Complexity

```
O(N1 + N2)
```

## Space Complexity

```
O(N1 + N2)
```

> The extra space is only for storing the returned union array.

---

## Interview Tip

Since both arrays are already sorted, the two-pointer approach is the most efficient solution and avoids using an ordered set.