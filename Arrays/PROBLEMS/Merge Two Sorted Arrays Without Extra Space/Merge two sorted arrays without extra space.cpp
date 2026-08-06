#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // Merge both arrays into a third array using the standard two-pointer
    // merge, then copy the merged result back into array1 and array2.
    // Time: O(N + M)  |  Space: O(N + M)
    void mergeBrute(vector<int>& array1, vector<int>& array2, int n, int m) {
        vector<int> array3(n + m);
        int left = 0, right = 0, index = 0;

        while (left < n && right < m) {
            if (array1[left] <= array2[right]) {
                array3[index] = array1[left];
                left++;
                index++;
            } else {
                array3[index] = array2[right];
                right++;
                index++;
            }
        }

        while (left < n) {
            array3[index] = array1[left];
            left++;
            index++;
        }

        while (right < m) {
            array3[index] = array2[right];
            right++;
            index++;
        }

        // Copy the merged result back into the original arrays
        for (int i = 0; i < n + m; i++) {
            if (i < n) {
                array1[i] = array3[i];
            } else {
                array2[i - n] = array3[i];
            }
        }
    }

    //================ OPTIMAL (TWO-POINTER SWAP + SORT) ================//
    // Compare the tail of array1 with the head of array2, swapping whenever
    // out of order, so every element ends up in the correct array. Then sort
    // each array individually to complete the merge.
    // Time: O(min(N,M)) + O(N log N) + O(M log M)  |  Space: O(1)
    void mergeTwoPointerSwap(vector<int>& array1, vector<int>& array2, int n, int m) {
        int left = n - 1;
        int right = 0;

        while (left >= 0 && right < m) {
            if (array1[left] > array2[right]) {
                swap(array1[left], array2[right]);
            }
            left--;
            right++;
        }

        sort(array1.begin(), array1.begin() + n);
        sort(array2.begin(), array2.begin() + m);
    }

    //================ OPTIMAL (GAP METHOD) ================//
    // Treat both arrays as one virtual combined array of length n + m.
    // Compare elements a shrinking "gap" distance apart (Shell Sort style),
    // swapping when out of order, until the gap reaches 1.
    // Time: O((N + M) * log(N + M))  |  Space: O(1)
    void swapIfGreater(vector<int>& array1, vector<int>& array2, int n, int index1, int index2) {
        // index1 and index2 are positions in the virtual combined array
        if (index1 < n && index2 < n) {
            // Both in array1
            if (array1[index1] > array1[index2]) {
                swap(array1[index1], array1[index2]);
            }
        } else if (index1 < n && index2 >= n) {
            // index1 in array1, index2 in array2
            if (array1[index1] > array2[index2 - n]) {
                swap(array1[index1], array2[index2 - n]);
            }
        } else {
            // Both in array2
            if (array2[index1 - n] > array2[index2 - n]) {
                swap(array2[index1 - n], array2[index2 - n]);
            }
        }
    }

    void mergeGapMethod(vector<int>& array1, vector<int>& array2, int n, int m) {
        int length = n + m;
        int gap = (length / 2) + (length % 2);

        while (gap > 0) {
            int left = 0;
            int right = left + gap;

            while (right < length) {
                swapIfGreater(array1, array2, n, left, right);
                left++;
                right++;
            }

            if (gap == 1) {
                gap = 0; // stop after the gap-1 pass
            } else {
                gap = (gap / 2) + (gap % 2); // ceiling of gap / 2
            }
        }
    }
};