#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Find the Single Element in a Sorted Array

    Given a sorted array:
    - Every element appears exactly twice, except one element.
    - The single element appears exactly once.
    - Find and return that single element.

    Example:
    nums = [1, 1, 2, 3, 3, 4, 4]
    Answer = 2

    Approaches covered from the video:
    1. Brute Force / Linear Search
    2. Optimal Binary Search

    Note:
    O(1) for the brute-force time complexity,
    but because the loop may inspect all n elements, the actual worst-case
    time complexity is O(n).
*/


// ============================================================
// APPROACH 1: BRUTE FORCE / LINEAR SEARCH
// ============================================================

/*
    Idea:
    For every index i:
      - If i == 0, compare nums[0] with nums[1].
      - If i == n-1, compare nums[n-1] with nums[n-2].
      - Otherwise, compare nums[i] with both neighbors.

    If the element is different from both neighbors, it is the answer.

    Time Complexity: O(n)
    Space Complexity: O(1)
*/
int singleNonDuplicateBrute(vector<int>& nums) {
    int n = nums.size();

    // Edge case: array contains only one element.
    if (n == 1)
        return nums[0];

    for (int i = 0; i < n; i++) {

        // First element
        if (i == 0) {
            if (nums[i] != nums[i + 1])
                return nums[i];
        }

        // Last element
        else if (i == n - 1) {
            if (nums[i] != nums[i - 1])
                return nums[i];
        }

        // Middle elements
        else {
            if (nums[i] != nums[i - 1] &&
                nums[i] != nums[i + 1]) {
                return nums[i];
            }
        }
    }

    // Guaranteed by the problem that an answer exists.
    return -1;
}


// ============================================================
// APPROACH 2: OPTIMAL BINARY SEARCH
// ============================================================

/*
    Key observation:

    Before the single element:
        [pair starts at even index, pair ends at odd index]

    Example:
        index:  0  1  2  3  4  5  6
        value:  1  1  2  2  3  4  4
                E  O  E  O  E  O  E

    After the single element, this pattern breaks.

    Therefore:

    1. If mid is odd and nums[mid] == nums[mid - 1]:
         We are on the LEFT half.
         The single element must be on the RIGHT.
         Eliminate the left half.

    2. If mid is even and nums[mid] == nums[mid + 1]:
         We are on the LEFT half.
         The single element must be on the RIGHT.
         Eliminate the left half.

    3. Otherwise:
         We are on the RIGHT half.
         Eliminate the right half.

    To avoid boundary checks for mid-1 and mid+1:
      - Handle the first element separately.
      - Handle the last element separately.
      - Binary-search only from index 1 to n-2.

    Time Complexity: O(log n)
    Space Complexity: O(1)
*/
int singleNonDuplicateOptimal(vector<int>& nums) {
    int n = nums.size();

    // Edge case: only one element.
    if (n == 1)
        return nums[0];

    // Check the first element separately.
    if (nums[0] != nums[1])
        return nums[0];

    // Check the last element separately.
    if (nums[n - 1] != nums[n - 2])
        return nums[n - 1];

    // We can safely use mid-1 and mid+1 now.
    int low = 1;
    int high = n - 2;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Is nums[mid] the single element?
        if (nums[mid] != nums[mid - 1] &&
            nums[mid] != nums[mid + 1]) {
            return nums[mid];
        }

        /*
            Determine whether we are on the left half.

            Case 1:
                mid is odd AND previous element is equal.
                Example: [x, x]
                       mid-1  mid
                This pair is correctly aligned.

            Case 2:
                mid is even AND next element is equal.
                Example: [x, x]
                        mid  mid+1
                This pair is correctly aligned.

            In either case, the single element is to the RIGHT.
        */
        if ((mid % 2 == 1 && nums[mid] == nums[mid - 1]) ||
            (mid % 2 == 0 && nums[mid] == nums[mid + 1])) {

            // Eliminate the left half.
            low = mid + 1;
        }
        else {
            // We are on the right half.
            // Eliminate the right half.
            high = mid - 1;
        }
    }

    // Dummy return; problem guarantees an answer exists.
    return -1;
}


// ============================================================
// MAIN
// ============================================================

int main() {
    vector<int> nums = {1, 1, 2, 3, 3, 4, 4};

    cout << "Brute Force Answer: "
         << singleNonDuplicateBrute(nums) << '\n';

    cout << "Optimal Answer: "
         << singleNonDuplicateOptimal(nums) << '\n';

    return 0;
}


/*
    ============================================================
    COMPLEXITY SUMMARY
    ============================================================

    Approach                    Time        Space
    ------------------------------------------------------------
    Brute Force / Linear Search O(n)        O(1)
    Binary Search (Optimal)     O(log n)    O(1)
    ------------------------------------------------------------

    Why is binary search O(log n)?
    Because every iteration eliminates approximately half
    of the remaining search space.

    Important edge cases:
    - n == 1
    - Single element at index 0
    - Single element at index n-1
    - Single element somewhere in the middle

    Important implementation detail:
    Do NOT blindly access nums[mid - 1] or nums[mid + 1]
    when mid can be 0 or n-1. The optimal solution first
    handles the first and last elements separately.
*/