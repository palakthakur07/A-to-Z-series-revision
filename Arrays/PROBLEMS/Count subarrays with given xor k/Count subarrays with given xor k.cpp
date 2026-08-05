#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // Generate every subarray using i (start) and j (end), then use a third
    // loop to compute the XOR of that subarray from scratch.
    // Time: O(N^3)  |  Space: O(1)
    int subarraysXorBrute(vector<int>& arr, int k) {
        int n = arr.size();
        int count = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int xorVal = 0;
                for (int key = i; key <= j; key++) {
                    xorVal = xorVal ^ arr[key];
                }
                if (xorVal == k) {
                    count++;
                }
            }
        }

        return count;
    }

    //================ BETTER ================//
    // Same two loops (i, j), but drop the third loop by maintaining a
    // running xorVal that gets updated incrementally as j moves forward.
    // Time: O(N^2)  |  Space: O(1)
    int subarraysXorBetter(vector<int>& arr, int k) {
        int n = arr.size();
        int count = 0;

        for (int i = 0; i < n; i++) {
            int xorVal = 0;
            for (int j = i; j < n; j++) {
                xorVal = xorVal ^ arr[j];
                if (xorVal == k) {
                    count++;
                }
            }
        }

        return count;
    }

    //================ OPTIMAL ================//
    // Maintain a running prefix XOR (xr) and a hash map of how many times
    // each prefix XOR has occurred. For every index, the number of valid
    // subarrays ending here equals mp[xr ^ k], using the identity:
    // X = XR ^ K  (derived from X ^ K = XR, XOR-ing K on both sides).
    // Time: O(N) average (O(N log N) worst case with an ordered map)
    // Space: O(N)
    int subarraysWithXorK(vector<int>& arr, int k) {
        int xr = 0;
        int count = 0;
        unordered_map<int, int> mp;
        mp[0] = 1; // empty prefix, needed to count subarrays starting at index 0

        for (int element : arr) {
            xr = xr ^ element;
            int x = xr ^ k; // required earlier prefix XOR

            if (mp.find(x) != mp.end()) {
                count += mp[x];
            }

            mp[xr]++;
        }

        return count;
    }
};