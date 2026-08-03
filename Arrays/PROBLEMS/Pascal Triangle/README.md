# Pascal Triangle

## Problem

Pascal Triangle is a triangular arrangement of numbers where every element is the sum of the two elements directly above it.

This topic has three interview variants.

1. Find the element at (Row, Column).
2. Print the Nth Row.
3. Print the complete Pascal Triangle.

---

## Approach 1 : Find Element at (R,C)

Use the formula

nCr

where

n = Row - 1

r = Column - 1

Instead of calculating factorials, compute nCr iteratively.

Time Complexity : O(r)

Space Complexity : O(1)

---

## Approach 2 : Print Nth Row

Generate every element of the row using the previous element.

Start with

1

Every next element

ans = ans * (row - col)
ans = ans / col

Time Complexity : O(N)

Space Complexity : O(1)

---

## Approach 3 : Print Complete Pascal Triangle

Generate every row using the previous approach.

For every row

call generateRow(row)

Time Complexity : O(N²)

Space Complexity : O(N²)

---

## LeetCode

118. Pascal Triangle

119. Pascal Triangle II