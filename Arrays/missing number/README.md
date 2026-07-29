# Missing Number

## Problem Statement

Given an array containing `N-1` distinct numbers in the range **1 to N**, find the missing number.

---

## Example

### Input

```text
N = 5

arr = {1,2,4,5}
```

### Output

```text
3
```

---

# Approach 1 : Brute Force (Linear Search)

## Algorithm

1. Traverse numbers from `1` to `N`.
2. For each number, search it in the array.
3. If a number is not found, return it.

---

## Code Logic

```cpp
for(int i = 1; i <= N; i++)
{
    bool found = false;

    for(int j = 0; j < N - 1; j++)
    {
        if(arr[j] == i)
        {
            found = true;
            break;
        }
    }

    if(!found)
        return i;
}
```

### Time Complexity

```
O(N²)
```

### Space Complexity

```
O(1)
```

---

# Approach 2 : Better (Hashing)

## Algorithm

1. Create a hash array of size `N+1`.
2. Mark every element present in the array.
3. Traverse from `1` to `N`.
4. The index whose frequency is `0` is the missing number.

---

## Code Logic

```cpp
vector<int> hash(N + 1, 0);

for(int i = 0; i < N - 1; i++)
{
    hash[arr[i]]++;
}

for(int i = 1; i <= N; i++)
{
    if(hash[i] == 0)
        return i;
}
```

### Time Complexity

```
O(N)
```

### Space Complexity

```
O(N)
```

---

# Approach 3 : Optimal (Sum Formula)

## Algorithm

1. Calculate the sum of first `N` natural numbers.
2. Calculate the sum of all array elements.
3. Their difference is the missing number.

---

## Code Logic

```cpp
int sum = (N * (N + 1)) / 2;

int arrSum = 0;

for(int i = 0; i < N - 1; i++)
{
    arrSum += arr[i];
}

return sum - arrSum;
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

# Approach 4 : Optimal (XOR)

## Algorithm

1. XOR all numbers from `1` to `N`.
2. XOR all array elements.
3. XOR both results to get the missing number.

---

## Code Logic

```cpp
int xor1 = 0;
int xor2 = 0;

for(int i = 1; i <= N; i++)
{
    xor1 ^= i;
}

for(int i = 0; i < N - 1; i++)
{
    xor2 ^= arr[i];
}

return xor1 ^ xor2;
```

---

## Dry Run

```text
N = 5

arr = {1,2,4,5}

Sum(1..5) = 15

Array Sum = 12

Missing = 15 - 12 = 3
```

---

## Time Complexity

| Approach | Time | Space |
|----------|------|-------|
| Brute Force | O(N²) | O(1) |
| Hashing | O(N) | O(N) |
| Sum Formula | O(N) | O(1) |
| XOR | O(N) | O(1) |

---

## Interview Tip

The **Sum Formula** and **XOR** approaches are the most commonly expected in interviews. The XOR method avoids integer overflow, making it the preferred optimal solution for large values of `N`.