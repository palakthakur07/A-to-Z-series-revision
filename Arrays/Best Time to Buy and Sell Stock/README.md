# Best Time to Buy and Sell Stock

## Problem Statement

You are given an array `prices` where `prices[i]` represents the price of a stock on the `iᵗʰ` day.

You want to maximize your profit by choosing:

- One day to **buy** a stock.
- A **later** day to sell that stock.

Return the **maximum profit** that can be achieved. If no profit is possible, return `0`.

---

## Example

### Input

```text
prices = [7,1,5,3,6,4]
```

### Output

```text
5
```

### Explanation

- Buy on Day 2 at price = 1
- Sell on Day 5 at price = 6

Profit = **6 - 1 = 5**

---

# Intuition

To maximize profit:

- Buy at the **minimum price** seen so far.
- At every day, calculate the profit if we sell today.
- Update the maximum profit whenever a larger profit is found.

Instead of checking every pair of days, we only need one traversal.

---

# Optimal Approach

## Algorithm

- Initialize the minimum price as the first day's price.
- Traverse the array from left to right.
- Calculate today's profit:
  
  ```text
  Current Price - Minimum Price
  ```

- Update the maximum profit.
- Update the minimum buying price whenever a smaller price is found.

---

## Dry Run

Input

```text
prices = [7,1,5,3,6,4]
```

| Day | Price | Minimum Price | Profit | Maximum Profit |
|-----|------:|--------------:|-------:|---------------:|
|1|7|7|0|0|
|2|1|1|0|0|
|3|5|1|4|4|
|4|3|1|2|4|
|5|6|1|5|5|
|6|4|1|3|5|

Final Answer

```text
5
```

---

## Time Complexity

**O(N)**

## Space Complexity

**O(1)**

---

# Edge Cases

- Only one price
- Prices always decreasing
- Prices always increasing
- Duplicate prices

---

# Key Takeaways

- Keep track of the minimum buying price.
- Calculate profit at every step.
- Update the maximum profit whenever possible.
- Only one traversal is required.

---

# Concepts Used

- Arrays
- Greedy Algorithm
- Single Traversal

---

# Interview Tip

Never sell before buying.

Always update the minimum buying price **before** moving to the next day.

---

# Related Problems

- Best Time to Buy and Sell Stock II
- Best Time to Buy and Sell Stock III
- Maximum Subarray Sum