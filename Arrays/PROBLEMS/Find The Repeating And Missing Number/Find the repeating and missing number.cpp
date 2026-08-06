#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // For each number 1..n, count its occurrences in the array via a full
    // scan. A count of 2 marks the repeating number, a count of 0 marks the
    // missing number.
    // Time: O(N^2)  |  Space: O(1)
    vector<int> findMissingRepeatingBrute(vector<int>& array, int n) {
        int repeating = -1, missing = -1;

        for (int i = 1; i <= n; i++) {
            int counter = 0;
            for (int j = 0; j < n; j++) {
                if (array[j] == i) {
                    counter++;
                }
            }

            if (counter == 2) {
                repeating = i;
            } else if (counter == 0) {
                missing = i;
            }

            if (repeating != -1 && missing != -1) {
                break;
            }
        }

        return {repeating, missing};
    }

    //================ BETTER ================//
    // Use a hash array of size n+1 to count occurrences of each number in a
    // single pass, then scan 1..n to find the counts of 2 and 0.
    // Time: O(N)  |  Space: O(N)
    vector<int> findMissingRepeatingBetter(vector<int>& array, int n) {
        vector<int> hash(n + 1, 0);

        for (int i = 0; i < n; i++) {
            hash[array[i]]++;
        }

        int repeating = -1, missing = -1;
        for (int i = 1; i <= n; i++) {
            if (hash[i] == 2) {
                repeating = i;
            } else if (hash[i] == 0) {
                missing = i;
            }
        }

        return {repeating, missing};
    }

    //================ OPTIMAL (MATHEMATICS) ================//
    // Use sum and sum-of-squares differences between the array and the
    // expected 1..n range to form two equations in x - y and x + y, then
    // solve for x (repeating) and y (missing).
    // Time: O(N)  |  Space: O(1)
    vector<int> findMissingRepeatingMath(vector<int>& array, int n) {
        long long S = 0, S2 = 0;

        for (int i = 0; i < n; i++) {
            S += array[i];
            S2 += (long long)array[i] * (long long)array[i];
        }

        long long Sn = (long long)n * (n + 1) / 2;
        long long S2n = (long long)n * (n + 1) * (2 * n + 1) / 6;

        long long val1 = S - Sn;              // x - y
        long long val2 = (S2 - S2n) / val1;   // x + y

        long long x = (val1 + val2) / 2;      // repeating
        long long y = x - val1;               // missing

        return {(int)x, (int)y};
    }

    //================ OPTIMAL (XOR METHOD) ================//
    // XOR all array elements and all numbers 1..n together to get x ^ y.
    // Find the rightmost differentiating bit, partition into two groups by
    // that bit, XOR each group to isolate x and y, then confirm which one
    // is the repeating number with a final pass through the array.
    // Time: O(N)  |  Space: O(1)
    vector<int> findMissingRepeatingXor(vector<int>& array, int n) {
        int xr = 0;

        for (int i = 0; i < n; i++) {
            xr = xr ^ array[i];
        }
        for (int i = 1; i <= n; i++) {
            xr = xr ^ i;
        }

        // Find the rightmost set (differentiating) bit
        int bitNumber = 0;
        while (true) {
            if ((xr & (1 << bitNumber)) != 0) {
                break;
            }
            bitNumber++;
        }

        int zero = 0, one = 0;

        for (int i = 0; i < n; i++) {
            if ((array[i] & (1 << bitNumber)) != 0) {
                one = one ^ array[i];
            } else {
                zero = zero ^ array[i];
            }
        }

        for (int i = 1; i <= n; i++) {
            if ((i & (1 << bitNumber)) != 0) {
                one = one ^ i;
            } else {
                zero = zero ^ i;
            }
        }

        // Confirm which of zero/one is the actual repeating number
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (array[i] == zero) {
                count++;
            }
        }

        if (count == 2) {
            return {zero, one}; // {repeating, missing}
        } else {
            return {one, zero}; // {repeating, missing}
        }
    }
};