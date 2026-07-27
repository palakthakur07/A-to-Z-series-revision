# Moore's Voting Algorithm

## Algorithm

### Objective

Find the **majority element** in an array.

A majority element is an element that appears **more than ⌊n/2⌋ times**.

### Steps

1. Initialize:
   - `count = 0`
   - `candidate = -1`

2. Traverse the array.

3. If `count == 0`, make the current element the new candidate.

4. If the current element equals the candidate:
   - Increment `count`.

5. Otherwise:
   - Decrement `count`.

6. After completing the traversal, the candidate is the majority element.

---

## Approach

Moore's Voting Algorithm is based on the **cancellation principle**.

- If two different elements are paired together, they cancel each other.
- Since the majority element appears more than `n/2` times, it can never be completely cancelled.
- The remaining candidate after the entire traversal is the majority element.

> **Note:** If the problem does not guarantee that a majority element exists, perform a second traversal to verify the candidate.

---

## C++ Code

```cpp
int majorityElement(vector<int>& nums)
{
    int count = 0;
    int candidate = -1;

    for(int i = 0; i < nums.size(); i++)
    {
        if(count == 0)
            candidate = nums[i];

        if(nums[i] == candidate)
            count++;
        else
            count--;
    }

    return candidate;
}
```

---

## Dry Run

### Input

```
[2,2,1,1,1,2,2]
```

| Element | Candidate | Count |
|---------:|:---------:|------:|
|2|2|1|
|2|2|2|
|1|2|1|
|1|2|0|
|1|1|1|
|2|1|0|
|2|2|1|

### Output

```
2
```

---

## Complexity

**Time Complexity:** O(n)

**Space Complexity:** O(1)

---

## Key Points

- Uses the cancellation principle.
- Traverses the array only once.
- Requires constant extra space.
- If the majority element is not guaranteed, verify the candidate with a second traversal.
- One of the most frequently asked interview algorithms.