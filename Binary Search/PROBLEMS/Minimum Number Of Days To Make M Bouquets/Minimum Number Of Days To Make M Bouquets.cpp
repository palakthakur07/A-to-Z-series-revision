#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ SHARED HELPER ================//
    // Checks whether m bouquets of k adjacent bloomed flowers can be made
    // by the given day.
    bool possible(vector<int>& bloomDay, int day, int m, int k) {
        int n = bloomDay.size();
        int count = 0;
        long long bouquets = 0;

        for (int i = 0; i < n; i++) {
            if (bloomDay[i] <= day) {
                count++;
            } else {
                bouquets += count / k;
                count = 0;
            }
        }
        bouquets += count / k; // trailing consecutive run

        return bouquets >= m;
    }

    //================ BRUTE FORCE ================//
    // Try every day from min(bloomDay) to max(bloomDay) in order, return
    // the first day for which `possible` succeeds.
    // Time: O((Max - Min) * N)  |  Space: O(1)
    int minDaysBrute(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();

        if ((long long)m * k > n) {
            return -1; // impossible: not enough flowers exist in total
        }

        int minDay = *min_element(bloomDay.begin(), bloomDay.end());
        int maxDay = *max_element(bloomDay.begin(), bloomDay.end());

        for (int day = minDay; day <= maxDay; day++) {
            if (possible(bloomDay, day, m, k)) {
                return day;
            }
        }

        return -1;
    }

    //================ OPTIMAL (BINARY SEARCH ON ANSWERS) ================//
    // Binary search over [min(bloomDay), max(bloomDay)] using `possible`
    // as the check function; converge to the smallest valid day.
    // Time: O(N log(Max - Min))  |  Space: O(1)
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();

        if ((long long)m * k > n) {
            return -1; // impossible
        }

        int low = *min_element(bloomDay.begin(), bloomDay.end());
        int high = *max_element(bloomDay.begin(), bloomDay.end());

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (possible(bloomDay, mid, m, k)) {
                high = mid - 1; // possible, look for a smaller valid day
            } else {
                low = mid + 1;  // not possible, need more days
            }
        }

        return low;
    }
};