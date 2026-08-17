Find the Nth Root of an Integer — Interview Notes

Problem

Given two integers N and M, find the integer x such that:

x^N = M

If an exact integer Nth root exists, return x.

Otherwise, return -1.

Example: N = 3, M = 27 → 3

Example: N = 4, M = 69 → -1

Core Idea

The transcript develops the solution in three stages:

Brute force / Linear Search

Binary Search on Answers

Overflow-safe binary search, which is the final practical approach

The most important interview concept is recognizing the monotonic pattern:

If mid^N < M, move right.

If mid^N == M, answer found.

If mid^N > M, move left.

This lets binary search eliminate half of the remaining answer space at every step.

1. Brute Force

Search every possible answer from 1 through M.

For every candidate i, calculate i^N:

If it equals M, return i.

If it exceeds M, stop; every larger candidate will also exceed M.

If the loop finishes, return -1.

Complexity

If power is calculated using a normal loop:

Time: O(M × N)

Space: O(1)

If an efficient/binary exponentiation power routine is used:

Time: O(M × log N)

Space: O(1)

The transcript describes this as the extreme naive/brute-force approach.

2. Why Binary Search Works

The answer lies in a known range.

For this problem, a simple safe range is:

[1, M]

For N = 3, M = 27:

1 ... 27

For N = 4, M = 69:

1 ... 69

The important observation is monotonicity:

1^N < 2^N < 3^N < 4^N ...

Once x^N becomes greater than M, every value to the right is also impossible.

Once x^N is less than M, values to the left cannot be the answer, so we search right.

Binary Search Pattern

low = 1
high = M

while low <= high:
    mid = low + (high - low) / 2

    if mid^N == M:
        return mid
    else if mid^N < M:
        low = mid + 1
    else:
        high = mid - 1

return -1

Complexity

Binary search checks approximately log M candidates.

If each power check uses a normal multiplication loop:

Time: O(N × log M)

Space: O(1)

If binary exponentiation is used:

Time: O(log N × log M)

Space: O(1)

This is much better than the brute-force O(M × N) approach.

3. Critical Interview Edge Case: Integer Overflow

This is the most important implementation detail from the transcript.

A direct calculation such as:

mid^N

can overflow even when M itself fits inside an integer type.

Example discussed in the transcript:

N = 10

M = 10^9

mid ≈ 5 × 10^8

mid^10 is enormously larger than 10^9, so storing the complete result can overflow.

The Fix

We do not actually need the full value of mid^N.

We only need to know whether:

mid^N < M

mid^N == M

mid^N > M

Therefore, while multiplying, stop immediately when the running value becomes greater than M.

This prevents unnecessary overflow and saves work.

Use long long for the running multiplication.

Interview Explanation / 30-Second Answer

“The answer lies between 1 and M, and x^N is monotonically increasing with x. So I can binary search the answer space. For every midpoint, I calculate mid^N, but I stop the multiplication as soon as it exceeds M to avoid overflow. If it equals M, I return mid. If it is smaller, I move right; otherwise I move left. This gives O(N log M) time with O(1) space.”

Key Interview Tips

Always identify the answer range before applying binary search on answers.

Explain why the search space is monotonic.

Clearly state what happens for <, =, and >.

Mention that the question requires an exact root, not a floor root.

Return -1 if no exact integer root exists.

Be careful with mid^N: direct exponentiation can overflow.

Stop multiplication as soon as the running product exceeds M.

Prefer long long for intermediate multiplication.

Use mid = low + (high - low) / 2 to avoid midpoint overflow.

In an interview, explicitly discuss the overflow edge case; it is a major part of this problem.

Common Mistakes

Returning the floor root when the problem asks for an exact root.

Continuing after power > M.

Computing pow(mid, N) and relying on floating-point precision.

Storing a huge mid^N without checking overflow.

Forgetting to move low or high, causing an infinite loop.

Using int when intermediate multiplication may exceed its range.

Saying binary search is O(log M) without accounting for the cost of the power check.

Dry Run: N = 3, M = 27

Search range:

low = 1, high = 27

mid = 14 → 14^3 > 27 → move left

mid = 7 → 7^3 > 27 → move left

mid = 3 → 3^3 = 27 → return 3

Answer: 3

Dry Run: N = 4, M = 69

Search range:

low = 1, high = 69

35^4 > 69 → left

17^4 > 69 → left

8^4 > 69 → left

4^4 > 69 → left

2^4 < 69 → right

3^4 = 81 > 69 → left

Search space crosses → no exact root

Answer: -1

What You Should Remember

Pattern

Binary Search on Answer

Recognition Signal

The question asks you to find a value in a range where a condition changes monotonically.

This Problem's Predicate

For candidate x:

x^N <= M

is true for smaller values and eventually becomes false.

Final Approach

Binary Search + Overflow-Safe Power Check

That is the main pattern worth carrying into other LeetCode/interview problems.