#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // Check every pair (i, j) with i < j and count how many satisfy
    // arr[i] > arr[j].
    // Time: O(N^2)  |  Space: O(1)
    int countInversionsBrute(vector<int>& arr) {
        int n = arr.size();
        int count = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] > arr[j]) {
                    count++;
                }
            }
        }

        return count;
    }

    //================ OPTIMAL ================//
    // Modified Merge Sort: while merging two already-sorted halves, whenever
    // a right-half element is placed before the current left-half element,
    // it forms an inversion with every remaining element in the left half.
    // Time: O(N log N)  |  Space: O(N) (temporary array during merge)
private:
    int merge(vector<int>& arr, int low, int mid, int high) {
        vector<int> temp;
        int left = low;
        int right = mid + 1;
        int count = 0;

        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) {
                temp.push_back(arr[left]);
                left++;
            } else {
                temp.push_back(arr[right]);
                count += (mid - left + 1); // all remaining left elements form inversions
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

        return count;
    }

    int mergeSort(vector<int>& arr, int low, int high) {
        int count = 0;
        if (low >= high) {
            return count;
        }

        int mid = (low + high) / 2;
        count += mergeSort(arr, low, mid);
        count += mergeSort(arr, mid + 1, high);
        count += merge(arr, low, mid, high);

        return count;
    }

public:
    int countInversions(vector<int>& arr) {
        int n = arr.size();
        return mergeSort(arr, 0, n - 1);
    }
};