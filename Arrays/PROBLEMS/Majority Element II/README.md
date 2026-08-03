# Majority Element II

## Problem

Given an integer array of size n, return all elements that appear more than ⌊n/3⌋ times.

There can be at most **2 majority elements**.

LeetCode: 229. Majority Element II

---

## Approach 1 : Brute Force

For every element, count its frequency by traversing the entire array.

If frequency > n/3, add it to the answer.

Since at most two elements can satisfy the condition, stop once two elements are found.

Time Complexity : O(N²)

Space Complexity : O(1)

---

## Approach 2 : Better (Hash Map)

Store the frequency of every element in a map.

Whenever frequency becomes greater than ⌊n/3⌋, add it to the answer.

Stop after finding two elements.

Time Complexity : O(N log N) using map
(or O(N) using unordered_map)

Space Complexity : O(N)

---

## Approach 3 : Optimal (Extended Moore's Voting Algorithm)

Maintain two candidates and their counts.

### First Pass
Find two possible majority candidates.

### Second Pass
Count their actual frequencies.

Return those occurring more than ⌊n/3⌋ times.

Time Complexity : O(2N)

Space Complexity : O(1)

---

## Interview Notes

- More than n/3 means there can be at most **2 answers**.
- Moore Voting for n/2 keeps one candidate.
- Moore Voting for n/3 keeps two candidates.