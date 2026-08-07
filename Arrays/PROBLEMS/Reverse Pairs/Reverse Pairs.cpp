#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // Check every pair (i, j) with i < j and count how many satisfy
    // arr[i] > 2 * arr[j].
    // Time: O(N^2)  |  Space: O(1)
    int reversePairsBrute(vector<int>& arr) {
        int n = arr.size();
        int count = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if ((long long)arr[i] > 2LL * arr[j]) {
                    count++;
                }
            }
        }

        return count;
    }

    //================ OPTIMAL ================//
    // Modified Merge Sort: before merging two already-sorted halves, run a
    // separate counting pass using a right pointer that never resets, then
    // perform the standard merge step.
    // Time: O(N log N)  |  Space: O(N) (temporary array during merge)
private:
    int countPairs(vector<int>& arr, int low, int mid, int high) {
        int right = mid + 1;
        int count = 0;

        for (int i = low; i <= mid; i++) {
            while (right <= high && (long long)arr[i] > 2LL * arr[right]) {
                right++;
            }
            count += (right - (mid + 1));
        }

        return count;
    }

    void merge(vector<int>& arr, int low, int mid, int high) {
        vector<int> temp;
        int left = low;
        int right = mid + 1;

        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) {
                temp.push_back(arr[left]);
                left++;
            } else {
                temp.push_back(arr[right]);
                right++;
            }
        }

        while (left <= mid) {
            temp.push_back(arr[left]);
            left++;
        }

        while (right <= high) {
            temp.push_back(arr[right]);
            right++;
        }

        for (int i = low; i <= high; i++) {
            arr[i] = temp[i - low];
        }
    }

    int mergeSort(vector<int>& arr, int low, int high) {
        int count = 0;
        if (low >= high) {
            return count;
        }

        int mid = (low + high) / 2;
        count += mergeSort(arr, low, mid);
        count += mergeSort(arr, mid + 1, high);
        count += countPairs(arr, low, mid, high); // count before merging
        merge(arr, low, mid, high);

        return count;
    }

public:
    int reversePairs(vector<int>& arr) {
        int n = arr.size();
        return mergeSort(arr, 0, n - 1);
    }
};