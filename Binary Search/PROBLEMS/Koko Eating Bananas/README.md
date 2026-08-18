Koko Eating Bananas — LeetCode 875

Problem

Koko has n piles of bananas and h hours. She eats at a fixed speed k bananas/hour and must finish each pile before moving to the next. For a pile of x bananas, required hours are ceil(x / k).

Find the minimum integer k such that all bananas can be eaten within h hours.

LeetCode: 875. Koko Eating Bananas

Example

piles = [3,6,7,11], h = 8

k=2 → 2+3+4+6 = 15 hours ❌

k=3 → 1+2+3+4 = 10 hours ❌

k=4 → 1+2+2+3 = 8 hours ✅

Answer = 4.

Key Observation

The answer is always in:

[1, max(piles)]

For a chosen speed k, calculate total hours:

sum(ceil(pile / k))

As k increases, required time never increases. Therefore feasibility has the monotonic pattern:

FALSE FALSE FALSE TRUE TRUE TRUE

We need the first TRUE, so this is Binary Search on Answers.

Approach 1 — Brute Force

Try every speed from 1 to max(piles) and return the first speed whose required hours are at most h.

TC: O(n * maxPile)
SC: O(1)

Approach 2 — Linear Search + Helper

Keep a helper requiredHours(piles, k) and linearly search the answer range.

TC: O(n * maxPile)
SC: O(1)

This is useful for understanding the optimization, but can be too slow.

Approach 3 — Optimal Binary Search

Set:

low = 1

high = max(piles)

For mid:

If requiredHours(mid) <= h, mid works. Since we need the minimum, search left: high = mid - 1.

Otherwise mid is too slow. Search right: low = mid + 1.

At the end, low is the minimum valid speed.

TC: O(n log(maxPile))
SC: O(1)

Why Binary Search Works

If speed k works, every speed greater than k also works. If k does not work, every smaller speed also does not work. This monotonicity lets us discard half the answer range each iteration.

Ceiling Division

For integers, instead of floating point:

ceil(pile / k)

use:

(pile + k - 1) / k

Example: ceil(7/3) = 3, and (7+3-1)/3 = 3.

Interview Tips

First identify the answer range, not an array range.

Ask: "Can I check whether a candidate answer is feasible?"

Look for a monotonic not possible -> possible or possible -> not possible pattern.

If the problem asks for the minimum valid value, binary search for the first valid value.

Keep feasibility logic in a helper function; it makes the interview explanation cleaner.

Use long long for the total hours.

Remember that the upper bound can be exactly max(piles); it may itself be the answer.

Interview Explanation

The answer lies between 1 and the maximum pile size. For a candidate speed k, I can calculate the total hours as the sum of ceil(pile/k) over all piles. Feasibility is monotonic: if a speed works, every larger speed works too. Therefore I binary search the answer range and find the smallest speed whose required time is at most h.

Reusable Pattern

For Binary Search on Answers:

Find minimum possible answer.

Find maximum possible answer.

Write a feasibility function.

Confirm monotonicity.

Binary search for the minimum/maximum valid answer.

Source Coverage

These notes follow the supplied transcript: it develops the 1..maxPile range, required-hours calculation, linear search, the impossible -> possible pattern, binary-search optimization, and O(n log(maxPile)) complexity. The transcript explicitly emphasizes determining the range and feasibility pattern as the main concept. fileciteturn1file0L1009-L1019